// DataConverter.cs — 빌드 파이프라인용 독립 도구

using MiniExcelLibs;
using System.Text;
using System.Text.Json;
using System.Linq;

// JSON 키 이름을 camelCase로 통일 (C++, C# 양쪽 같은 키 사용)
var JsonOptions = new JsonSerializerOptions
{
    WriteIndented = true,
    PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
};

ConvertSheet<ItemData>("items.xlsx", "Items", "output/items.json");

static void ConvertSheet<T>(string xlsxPath, string sheetName, string outPath) where T : class, new()
{
    var rows = MiniExcel.Query<T>(xlsxPath, sheetName: sheetName).ToList();

    Directory.CreateDirectory(Path.GetDirectoryName(outPath)!);
    File.WriteAllText(outPath,
        JsonSerializer.Serialize(rows, JsonSerializerOptions.Default ),
        Encoding.UTF8);

    Console.WriteLine($"[변환] {sheetName} → {outPath} ({rows.Count}행)");
}

// Excel 헤더와 1:1 대응하는 모델
// MiniExcel은 헤더 이름으로 자동 매핑 (대소문자 무관)
public class ItemData
{
    public int Id { get; set; }
    public string Name { get; set; }
    public string Type { get; set; }
    public int MaxStack { get; set; }
    public int Price { get; set; }

    public string Description { get; set; }
}