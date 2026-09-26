using System.Text;

public static partial class ExcelSchemaConverter
{
    // 엑셀 한 장 → C++ 헤더 한 개.
    // 행 클래스(IStaticData 구현)와 그 행들을 담는 DataManager 싱글턴을 선언한다.
    private static void WriteHeaderFile(string headerPath, string xlsxPath, StaticDataSchema schema)
    {
        var sb = new StringBuilder();

        sb.AppendLine("#pragma once");
        sb.AppendLine();
        AppendGeneratedBanner(sb, xlsxPath);
        sb.AppendLine();
        sb.AppendLine("#include <cstdint>");
        sb.AppendLine("#include <memory>");
        sb.AppendLine("#include <string>");
        sb.AppendLine("#include <unordered_map>");
        sb.AppendLine();
        sb.AppendLine("#include <boost/json.hpp>");
        sb.AppendLine();
        sb.AppendLine("#include <Engine/Singleton.h>");
        sb.AppendLine("#include <Engine/StaticData/IStaticData.h>");
        sb.AppendLine();
        sb.AppendLine("namespace GenericBoson");
        sb.AppendLine("{");

        AppendRowClass(sb, schema);
        sb.AppendLine();
        AppendManagerClass(sb, schema);

        sb.AppendLine("}");

        WriteTextFile(headerPath, sb.ToString());
        Console.WriteLine($"[완료] {headerPath} (필드 {schema.Fields.Count}개)");
    }

    private static void AppendRowClass(StringBuilder sb, StaticDataSchema schema)
    {
        // 게터 선언을 보기 좋게 정렬하기 위한 폭 계산
        var returnWidth = schema.Fields.Max(f => f.ReturnType.Length);
        var memberWidth = schema.Fields.Max(f => f.CppType.Length);

        sb.AppendLine($"\tclass {schema.ClassName} : public IStaticData");
        sb.AppendLine("\t{");
        sb.AppendLine("\tpublic:");
        sb.AppendLine($"\t\t// FnvHash64(\"{schema.ClassName.ToLowerInvariant()}\")");
        sb.AppendLine($"\t\tstatic constexpr int64_t CLASS_ID = {schema.ClassId}LL;");
        sb.AppendLine();
        sb.AppendLine("\t\tvoid Insert(const boost::json::object& obj) override;");
        sb.AppendLine("\t\tstd::shared_ptr<IStaticData> Create() override;");
        sb.AppendLine();

        foreach (var field in schema.Fields)
        {
            var returnType = field.ReturnType.PadRight(returnWidth);
            sb.AppendLine($"\t\t{returnType} {field.Name}() const {{ return m_{field.Name}; }}");
        }

        sb.AppendLine();
        sb.AppendLine("\tprivate:");

        foreach (var field in schema.Fields)
        {
            var cppType = field.CppType.PadRight(memberWidth);
            sb.AppendLine($"\t\t{cppType} m_{field.Name}{{}};");
        }

        sb.AppendLine("\t};");
    }

    private static void AppendManagerClass(StringBuilder sb, StaticDataSchema schema)
    {
        var mapType = $"std::unordered_map<{schema.KeyType}, std::shared_ptr<{schema.ClassName}>>";
        var keyParam = schema.KeyField.IsString ? "const std::string& key" : $"{schema.KeyType} key";

        sb.AppendLine($"\t// {schema.ClassName} 행들을 {schema.KeyField.Name} 기준으로 보관한다.");
        sb.AppendLine($"\tclass {schema.ManagerName} : public Singleton<{schema.ManagerName}>");
        sb.AppendLine("\t{");
        sb.AppendLine("\tpublic:");
        sb.AppendLine($"\t\t// 키가 이미 있으면 false. {schema.ClassName}::Insert()가 호출한다.");
        sb.AppendLine($"\t\tbool Add(std::shared_ptr<{schema.ClassName}>&& pData);");
        sb.AppendLine();
        sb.AppendLine($"\t\t// 없으면 nullptr.");
        sb.AppendLine($"\t\tstd::shared_ptr<const {schema.ClassName}> Get({keyParam}) const;");
        sb.AppendLine();
        sb.AppendLine($"\t\tconst {mapType}& GetAll() const {{ return m_data; }}");
        sb.AppendLine("\t\tstd::size_t Size() const { return m_data.size(); }");
        sb.AppendLine();
        sb.AppendLine("\tprivate:");
        sb.AppendLine($"\t\t{mapType} m_data;");
        sb.AppendLine("\t};");
    }
}
