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

    public static void ConvertXlsxToJson(string xlsxPath, string sheetName, string outputPath)
    {
        var outputRootPath = Path.GetDirectoryName(outputPath);
        var xlsxRootPath = Path.GetFullPath(xlsxPath);

        foreach (var itFile in Directory.GetFiles(xlsxRootPath, "*.xlsx", SearchOption.AllDirectories))
        {
            var relativePath = Path.GetRelativePath(itFile, xlsxRootPath);
            var targetPath = Path.Combine(outputPath, relativePath);

            Directory.CreateDirectory(targetPath);

            SheetToFiles(xlsxPath, targetPath, sheetName);
        }
    }

    private static void SheetToFiles(string xlsxPath, string targetPath, string sheet)
    {
        // dynamic 모드: 첫 번째 행을 키로 사용, 클래스 정의 불필요
        var rawRows = MiniExcel.Query(xlsxPath, useHeaderRow: true, sheetName: sheet)
                               .Cast<IDictionary<string, object>>()
                               .ToList();

        if (rawRows.Count == 0) return;

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
                record[fieldName] = CastCell(rawVal, typeName);
            }

            return record;
        }).ToList();

        WriteJsonFile(targetPath, rows);

        WriteHeaderFile(targetPath, rows);

        WriteSourceFile();
    }

    private static void WriteSourceFile()
    {
        throw new NotImplementedException();
    }

    private static void WriteJsonFile(string targetPath, List<Dictionary<string, object?>> rows)
    {
        File.WriteAllText(targetPath, JsonSerializer.Serialize(rows, JsonOpts), Encoding.UTF8);
        Console.WriteLine($"[완료] {targetPath} ({rows.Count}행)");
    }

    private static object? CastCell(object? raw, string type)
    {
        // 빈 셀 처리 — 타입별 기본값 반환
        if (raw is null || (raw is string s && string.IsNullOrWhiteSpace(s)))
            return type switch
            {
                "int" or "long" => (object)0,
                "float" or "double" => 0.0,
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
        if (args.Length != 3)
        {
            Console.WriteLine("Usage: ExcelSchemaConverter <xlsxPath> <sheetName> <outputPath>");
            return;
        }
        var (xlsxPath, sheetName, outputPath) = (args[0], args[1], args[2]);
        try
        {
            ExcelSchemaConverter.ConvertXlsxToJson(xlsxPath, sheetName, outputPath);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}