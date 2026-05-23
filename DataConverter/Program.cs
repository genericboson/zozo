using MiniExcelLibs;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;

public static class ExcelSchemaConverter
{
    // 지원 타입: int, long, float, double, bool, string
    // 헤더 미매칭 시 string 기본값으로 처리

    private static readonly JsonSerializerOptions JsonOpts = new() { WriteIndented = true };
    private static readonly Regex HeaderRx = new(@"^(.+?)\((\w+)\)$", RegexOptions.Compiled);

    public static void Convert(string xlsxPath, string sheetName, string outputPath)
    {
        var rows = ReadSheet(xlsxPath, sheetName);

        Directory.CreateDirectory(Path.GetDirectoryName(outputPath)!);
        File.WriteAllText(outputPath, JsonSerializer.Serialize(rows, JsonOpts), Encoding.UTF8);

        Console.WriteLine($"[완료] {sheetName} → {outputPath} ({rows.Count}행)");
    }

    private static List<Dictionary<string, object?>> ReadSheet(string xlsxPath, string sheet)
    {
        // dynamic 모드: 첫 번째 행을 키로 사용, 클래스 정의 불필요
        var rawRows = MiniExcel.Query(xlsxPath, useHeaderRow: true, sheetName: sheet)
                               .Cast<IDictionary<string, object>>()
                               .ToList();

        if (rawRows.Count == 0) return [];

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

        return rawRows.Select(row =>
        {
            var record = new Dictionary<string, object?>(headers.Count);
            foreach (var (rawKey, fieldName, typeName) in headers)
            {
                row.TryGetValue(rawKey, out var rawVal);
                record[fieldName] = CastCell(rawVal, typeName);
            }
            return record;
        }).ToList();
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
            "int" => Int32.Parse( raw.ToString() ),
            "long" => Int64.Parse( raw.ToString() ),
            "float" => float.Parse( raw.ToString() ),
            "double" => double.Parse( raw.ToString() ),
            "bool" => raw is bool b ? b : bool.Parse(raw.ToString()!),
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
            ExcelSchemaConverter.Convert(xlsxPath, sheetName, outputPath);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}