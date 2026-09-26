using MiniExcelLibs;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;

public static partial class ExcelSchemaConverter
{
    // 지원 타입: int, long, float, double, bool, string
    // 헤더 미매칭 시 string 기본값으로 처리

    private static readonly JsonSerializerOptions JsonOpts = new() { WriteIndented = true };
    private static readonly Regex HeaderRx = new(@"^(.+?)\((\w+)\)$", RegexOptions.Compiled);

    // json은 boost::json이 읽으므로 BOM이 있으면 파싱에 실패한다.
    private static readonly UTF8Encoding JsonEncoding = new(encoderShouldEmitUTF8Identifier: false);

    // C++ 소스는 주석에 한글이 들어가므로 MSVC가 UTF-8로 해석하도록 BOM을 붙인다.
    private static readonly UTF8Encoding CppEncoding = new(encoderShouldEmitUTF8Identifier: true);

    public static void ConvertAll(string xlsxRoot, string sheetName, string outputRoot)
    {
        var xlsxRootPath = Path.GetFullPath(xlsxRoot);
        if (!Directory.Exists(xlsxRootPath))
        {
            Console.WriteLine($"[오류] 입력 폴더가 없습니다: {xlsxRootPath}");
            return;
        }

        var xlsxFiles = Directory.GetFiles(xlsxRootPath, "*.xlsx", SearchOption.AllDirectories)
            // 엑셀이 열려 있을 때 생기는 임시 파일(~$foo.xlsx)은 건너뛴다.
            .Where(path => !Path.GetFileName(path).StartsWith("~$", StringComparison.Ordinal))
            .ToList();

        if (xlsxFiles.Count == 0)
        {
            Console.WriteLine($"[경고] xlsx 파일을 찾지 못했습니다: {xlsxRootPath}");
            return;
        }

        var converted = 0;
        foreach (var xlsxPath in xlsxFiles)
        {
            // 입력 폴더 구조를 출력 폴더에 그대로 재현한다.
            var relativeDir = Path.GetRelativePath(xlsxRootPath, Path.GetDirectoryName(xlsxPath)!);
            var targetDir = relativeDir == "."
                ? outputRoot
                : Path.Combine(outputRoot, relativeDir);

            Directory.CreateDirectory(targetDir);

            try
            {
                if (SheetToFiles(xlsxPath, targetDir, sheetName))
                    converted++;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[오류] {Path.GetFileName(xlsxPath)}: {ex.Message}");
            }
        }

        Console.WriteLine($"\n{xlsxFiles.Count}개 중 {converted}개 변환 완료.");
    }

    private static bool SheetToFiles(string xlsxPath, string targetDir, string sheetName)
    {
        var sheet = ResolveSheetName(xlsxPath, sheetName);

        // dynamic 모드: 첫 번째 행을 키로 사용, 클래스 정의 불필요
        var rawRows = MiniExcel.Query(xlsxPath, useHeaderRow: true, sheetName: sheet)
                               .Cast<IDictionary<string, object>>()
                               .ToList();

        if (rawRows.Count == 0)
        {
            Console.WriteLine($"[건너뜀] {Path.GetFileName(xlsxPath)}: 데이터 행이 없습니다.");
            return false;
        }

        // 첫 번째 데이터 행의 키로 헤더 파싱 (한 번만 수행)
        var headers = rawRows[0].Keys
            .Select(key =>
            {
                var m = HeaderRx.Match(key.Trim());
                return m.Success
                    ? (rawKey: key, fieldName: m.Groups[1].Value.Trim(), typeName: m.Groups[2].Value.ToLower())
                    : (rawKey: key, fieldName: key, typeName: "string");
            })
            .ToList();

        var rows = rawRows.Select(row =>
        {
            var record = new Dictionary<string, object?>(headers.Count);
            foreach (var (rawKey, fieldName, typeName) in headers)
            {
                row.TryGetValue(rawKey, out var rawVal);
                record[SanitizeIdentifier(fieldName)] = CastCell(rawVal, typeName);
            }

            return record;
        }).ToList();

        var schema = BuildSchema(xlsxPath, rows);
        if (schema is null)
        {
            Console.WriteLine($"[건너뜀] {Path.GetFileName(xlsxPath)}: 컬럼을 찾지 못했습니다.");
            return false;
        }

        var stem = Path.GetFileNameWithoutExtension(xlsxPath);
        var jsonPath = Path.Combine(targetDir, $"{stem}.json");
        var headerPath = Path.Combine(targetDir, $"{stem}.h");
        var sourcePath = Path.Combine(targetDir, $"{stem}.cpp");

        WriteJsonFile(jsonPath, schema, rows);
        WriteHeaderFile(headerPath, xlsxPath, schema);
        WriteSourceFile(sourcePath, headerPath, xlsxPath, schema);

        return true;
    }

    // 지정한 시트가 없으면 첫 번째 시트로 대체한다.
    // (여러 엑셀을 일괄 변환할 때 시트명이 제각각일 수 있다.)
    private static string ResolveSheetName(string xlsxPath, string requested)
    {
        var sheets = MiniExcel.GetSheetNames(xlsxPath);
        if (sheets.Count == 0)
            throw new InvalidOperationException("시트가 없습니다.");

        if (!string.IsNullOrWhiteSpace(requested) &&
            sheets.Contains(requested, StringComparer.OrdinalIgnoreCase))
        {
            return sheets.First(s => string.Equals(s, requested, StringComparison.OrdinalIgnoreCase));
        }

        return sheets[0];
    }

    // 배열의 첫 원소에 CLASS_ID 메타를 넣고, 그 뒤에 실제 행들을 넣는다.
    // GameServer::ReadStaticData가 이 형식을 기대한다.
    private static void WriteJsonFile(string jsonPath, StaticDataSchema schema, List<Dictionary<string, object?>> rows)
    {
        var document = new List<Dictionary<string, object?>>(rows.Count + 1)
        {
            new() { ["CLASS_ID"] = schema.ClassId },
        };
        document.AddRange(rows);

        File.WriteAllText(jsonPath, JsonSerializer.Serialize(document, JsonOpts), JsonEncoding);
        Console.WriteLine($"[완료] {jsonPath} ({rows.Count}행, CLASS_ID {schema.ClassId})");
    }

    private static void WriteTextFile(string path, string content)
        => File.WriteAllText(path, content, CppEncoding);

    private static object? CastCell(object? raw, string type)
    {
        // 빈 셀 처리 — 타입별 기본값 반환
        if (raw is null || (raw is string s && string.IsNullOrWhiteSpace(s)))
            return type switch
            {
                "int" => 0,
                "long" => 0L,
                "float" => 0.0f,
                "double" => 0.0,
                "bool" => false,
                _ => string.Empty,
            };

        // Excel은 숫자를 double로 반환하므로 int/long 변환 시 주의
        return type switch
        {
            "int"    => (object?)Convert.ToInt32(raw),  // 여기 한 곳만 명시하면 전체 switch가 object?로 확정
            "long"   => Convert.ToInt64(raw),
            "float"  => (float)Convert.ToDouble(raw),
            "double" => Convert.ToDouble(raw),
            "bool"   => raw is bool b ? b : bool.Parse(raw.ToString()!),
            "string" => Convert.ToString(raw) ?? string.Empty,
            _ => raw.ToString() ?? string.Empty,
        };
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        if (args.Length is < 2 or > 3)
        {
            Console.WriteLine("Usage: DataConverter <xlsxRoot> <outputRoot> [sheetName]");
            Console.WriteLine("  sheetName을 생략하거나 못 찾으면 각 파일의 첫 번째 시트를 사용합니다.");
            return;
        }

        var xlsxRoot = args[0];
        var outputRoot = args[1];
        var sheetName = args.Length == 3 ? args[2] : string.Empty;

        try
        {
            ExcelSchemaConverter.ConvertAll(xlsxRoot, sheetName, outputRoot);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}
