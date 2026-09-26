using System.Text;

// 생성할 C++ 클래스 한 개 분량의 스키마.
// 헤더 생성기와 소스 생성기가 같은 정보를 보도록 한 곳에서만 만든다.
public sealed record StaticDataField(string Name, string CppType)
{
    // 반환 타입: 문자열은 복사를 피하려고 const 참조로 돌려준다.
    public string ReturnType => CppType == "std::string" ? "const std::string&" : CppType;

    public bool IsString => CppType == "std::string";
}

public sealed record StaticDataSchema(
    string ClassName,
    long ClassId,
    IReadOnlyList<StaticDataField> Fields)
{
    // 첫 번째 컬럼을 행의 기본키로 쓴다.
    public StaticDataField KeyField => Fields[0];

    // 맵의 키 타입. 정수 컬럼이면 int64_t로 통일하고, 그 외에는 컬럼 타입을 그대로 쓴다.
    public string KeyType => KeyField.CppType switch
    {
        "int32_t" or "int64_t" => "int64_t",
        _ => KeyField.CppType,
    };

    public string ManagerName => $"{ClassName}DataManager";
}

public static partial class ExcelSchemaConverter
{
    private static StaticDataSchema? BuildSchema(string xlsxPath, List<Dictionary<string, object?>> rows)
    {
        if (rows.Count == 0)
            return null;

        var fields = rows[0]
            .Select(kvp => new StaticDataField(SanitizeIdentifier(kvp.Key), ToCppType(kvp.Value)))
            .ToList();

        if (fields.Count == 0)
            return null;

        return new StaticDataSchema(
            ClassName: ToPascalCase(Path.GetFileNameWithoutExtension(xlsxPath)),
            ClassId: MakeClassId(xlsxPath),
            Fields: fields);
    }

    // 셀 런타임 타입 → C++ 타입.
    // CastCell이 빈 셀도 타입별 기본값으로 박싱해 두기 때문에 추정이 가능하다.
    private static string ToCppType(object? value) => value switch
    {
        int => "int32_t",
        long => "int64_t",
        float => "float",
        double => "double",
        bool => "bool",
        string => "std::string",
        _ => "std::string",
    };

    private static string ToPascalCase(string name)
    {
        if (string.IsNullOrEmpty(name))
            return "StaticData";

        var parts = name.Split(new[] { '_', '-', ' ', '.' },
                               StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 0)
            return "StaticData";

        return string.Concat(parts.Select(p =>
            char.ToUpperInvariant(p[0]) + (p.Length > 1 ? p.Substring(1) : string.Empty)));
    }

    // C++ 식별자에 쓸 수 없는 문자는 '_'로 치환, 숫자로 시작하면 '_' 접두.
    private static string SanitizeIdentifier(string name)
    {
        if (string.IsNullOrEmpty(name))
            return "_";

        var sb = new StringBuilder(name.Length);
        foreach (var c in name)
            sb.Append(char.IsLetterOrDigit(c) || c == '_' ? c : '_');

        if (char.IsDigit(sb[0]))
            sb.Insert(0, '_');

        return sb.ToString();
    }

    // 생성 파일 상단에 붙는 공통 주석.
    private static void AppendGeneratedBanner(StringBuilder sb, string xlsxPath)
    {
        var sourceName = Path.GetFileName(xlsxPath);

        sb.AppendLine("//============================================================");
        sb.AppendLine($"// 이 파일은 DataConverter가 {sourceName} 로부터 자동 생성했습니다.");
        sb.AppendLine("// 직접 수정하지 마세요.");
        sb.AppendLine("// 엑셀을 수정한 뒤 DataConverter를 다시 실행하면 갱신됩니다.");
        sb.AppendLine("//============================================================");
    }
}
