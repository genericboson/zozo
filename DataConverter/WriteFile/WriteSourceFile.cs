using System;
using System.Collections.Generic;
using System.Text;

public static partial class ExcelSchemaConverter
{
    public static void WriteSourceFile(string targetPath, List<Dictionary<string, object?>> rows)
    {
        if (rows.Count == 0)
            return;

        // rows[0]의 키 = 필드명, 값의 런타임 타입 = C++ 타입 추정 근거
        var fields = rows[0]
            .Select(kvp => (Name: kvp.Key, CppType: ToCppType(kvp.Value)))
            .ToList();

        if (fields.Count == 0)
            return;

        // 출력 파일/클래스 이름은 targetPath의 파일명에서 유도
        var baseName = Path.GetFileNameWithoutExtension(targetPath);
        if (string.IsNullOrWhiteSpace(baseName))
            baseName = "StaticData";

        var className = ToPascalCase(baseName);
        var headerPath = Path.ChangeExtension(targetPath, ".h");

        var sb = new StringBuilder();
        sb.AppendLine("#pragma once");
        sb.AppendLine();
        sb.AppendLine("#include <cstdint>");
        sb.AppendLine("#include <string>");
        sb.AppendLine();
        sb.AppendLine("namespace GenericBoson");
        sb.AppendLine("{");
        sb.AppendLine("");
        sb.AppendLine($"\tclass {className}DataManager");
        sb.AppendLine("\t{");
        sb.AppendLine("\t}");
        sb.AppendLine("");
        sb.AppendLine($"\tclass {className} : IStaticData");
        sb.AppendLine("\t{");
        sb.AppendLine("\tpublic:");
        foreach (var (name, cppType) in fields)
        {
            var safeName = SanitizeIdentifier(name);
            sb.AppendLine($"\t\t{cppType} {safeName}();");
        }
        sb.AppendLine("\t};");
        sb.AppendLine("}");

        var dir = Path.GetDirectoryName(headerPath);
        if (!string.IsNullOrEmpty(dir))
            Directory.CreateDirectory(dir);

        File.WriteAllText(headerPath, sb.ToString(), Encoding.UTF8);
        Console.WriteLine($"[완료] {headerPath} ({fields.Count} fields)");
    }
}