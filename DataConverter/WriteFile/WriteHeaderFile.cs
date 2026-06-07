using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

public static partial class ExcelSchemaConverter
{
    // 엑셀의 첫 번째 행(헤더) 정보를 토대로 static data 객체에 대한
    // C++ 클래스 선언이 들어 있는 헤더 파일을 생성한다.
    //
    // 헤더 포맷은 Program.cs의 HeaderRx로 이미 파싱되어 rows의 값으로
    // 타입이 박싱되어 들어온다(int, long, float, double, bool, string).
    public static void WriteHeaderFile(string targetPath, List<Dictionary<string, object?>> rows)
    {
        if (rows.Count == 0) return;

        // rows[0]의 키 = 필드명, 값의 런타임 타입 = C++ 타입 추정 근거
        var fields = rows[0]
            .Select(kvp => (Name: kvp.Key, CppType: ToCppType(kvp.Value)))
            .ToList();

        if (fields.Count == 0) return;

        // 출력 파일/클래스 이름은 targetPath의 파일명에서 유도
        var baseName = Path.GetFileNameWithoutExtension(targetPath);
        if (string.IsNullOrWhiteSpace(baseName))
            baseName = "StaticData";

        var className  = ToPascalCase(baseName);
        var headerPath = Path.ChangeExtension(targetPath, ".h");

        var sb = new StringBuilder();
        sb.AppendLine("#pragma once");
        sb.AppendLine();
        sb.AppendLine("#include <cstdint>");
        sb.AppendLine("#include <string>");
        sb.AppendLine();
        sb.AppendLine("namespace GenericBoson");
        sb.AppendLine("{");
        sb.AppendLine($"\tstruct {className}");
        sb.AppendLine("\t{");
        foreach (var (name, cppType) in fields)
        {
            var safeName = SanitizeIdentifier(name);
            sb.AppendLine($"\t\t{cppType} {safeName}{{}};");
        }
        sb.AppendLine("\t};");
        sb.AppendLine("}");

        var dir = Path.GetDirectoryName(headerPath);
        if (!string.IsNullOrEmpty(dir))
            Directory.CreateDirectory(dir);

        File.WriteAllText(headerPath, sb.ToString(), Encoding.UTF8);
        Console.WriteLine($"[완료] {headerPath} ({fields.Count} fields)");
    }

    // 셀 런타임 타입 → C++ 타입.
    // CastCell이 빈 셀을 타입별 기본값으로 박싱해 두기 때문에 추정이 가능하다.
    // 다만 CastCell이 float 기본값을 double(0.0)로 박싱하므로,
    // float 컬럼이 전부 비어 있으면 double로 추정될 수 있다(알려진 한계).
    private static string ToCppType(object? value) => value switch
    {
        int    => "int32_t",
        long   => "int64_t",
        float  => "float",
        double => "double",
        bool   => "bool",
        string => "std::string",
        _      => "std::string",
    };

    private static string ToPascalCase(string name)
    {
        if (string.IsNullOrEmpty(name)) return "StaticData";

        var parts = name.Split(new[] { '_', '-', ' ', '.' },
                               StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 0) return "StaticData";

        return string.Concat(parts.Select(p =>
            char.ToUpperInvariant(p[0]) + (p.Length > 1 ? p.Substring(1) : string.Empty)));
    }

    // C++ 식별자에 쓸 수 없는 문자는 '_'로 치환, 숫자로 시작하면 '_' 접두.
    private static string SanitizeIdentifier(string name)
    {
        if (string.IsNullOrEmpty(name)) return "_";

        var sb = new StringBuilder(name.Length);
        foreach (var c in name)
            sb.Append(char.IsLetterOrDigit(c) || c == '_' ? c : '_');

        if (char.IsDigit(sb[0]))
            sb.Insert(0, '_');

        return sb.ToString();
    }
}
