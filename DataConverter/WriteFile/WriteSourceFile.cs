using System.Text;

public static partial class ExcelSchemaConverter
{
    // 엑셀 한 장 → C++ 소스 한 개.
    // json 파싱, DataManager 구현, 그리고 static 초기화 시점의 프로토타입 등록을 담는다.
    private static void WriteSourceFile(string sourcePath, string headerPath, string xlsxPath, StaticDataSchema schema)
    {
        var sb = new StringBuilder();

        AppendGeneratedBanner(sb, xlsxPath);
        sb.AppendLine();
        sb.AppendLine("#include \"PCH.h\"");
        sb.AppendLine();
        sb.AppendLine("#include <Engine/StaticData/GlobalInitializer.h>");
        sb.AppendLine("#include <Engine/StaticData/StaticDataParse.h>");
        sb.AppendLine();
        sb.AppendLine($"#include \"{Path.GetFileName(headerPath)}\"");
        sb.AppendLine();
        sb.AppendLine("namespace GenericBoson");
        sb.AppendLine("{");

        AppendInitializer(sb, schema);
        sb.AppendLine();
        AppendRowImpl(sb, schema);
        sb.AppendLine();
        AppendManagerImpl(sb, schema);

        sb.AppendLine("}");

        WriteTextFile(sourcePath, sb.ToString());
        Console.WriteLine($"[완료] {sourcePath}");
    }

    private static void AppendInitializer(StringBuilder sb, StaticDataSchema schema)
    {
        var variableName = $"g_{char.ToLowerInvariant(schema.ClassName[0])}{schema.ClassName.Substring(1)}Initializer";

        sb.AppendLine("\tnamespace");
        sb.AppendLine("\t{");
        sb.AppendLine($"\t\t// main() 진입 전에 {schema.ClassName} 프로토타입을 StaticDataManager에 등록한다.");
        sb.AppendLine($"\t\tconst GlobalInitializer<{schema.ClassName}> {variableName}{{ std::make_shared<{schema.ClassName}>() }};");
        sb.AppendLine("\t}");
    }

    private static void AppendRowImpl(StringBuilder sb, StaticDataSchema schema)
    {
        sb.AppendLine($"\tstd::shared_ptr<IStaticData> {schema.ClassName}::Create()");
        sb.AppendLine("\t{");
        sb.AppendLine($"\t\treturn std::make_shared<{schema.ClassName}>();");
        sb.AppendLine("\t}");
        sb.AppendLine();
        sb.AppendLine($"\tvoid {schema.ClassName}::Insert(const boost::json::object& obj)");
        sb.AppendLine("\t{");

        foreach (var field in schema.Fields)
            sb.AppendLine($"\t\tStaticDataParse::Read(obj, \"{field.Name}\", m_{field.Name});");

        sb.AppendLine();
        sb.AppendLine("\t\t// 파싱된 행을 자기 타입의 DataManager에 담는다.");
        sb.AppendLine($"\t\t{schema.ManagerName}::GetInstance()->Add(std::make_shared<{schema.ClassName}>(*this));");
        sb.AppendLine("\t}");
    }

    private static void AppendManagerImpl(StringBuilder sb, StaticDataSchema schema)
    {
        var keyExpression = schema.KeyField.IsString
            ? $"pData->{schema.KeyField.Name}()"
            : $"static_cast<{schema.KeyType}>(pData->{schema.KeyField.Name}())";

        var keyParam = schema.KeyField.IsString ? "const std::string& key" : $"{schema.KeyType} key";

        sb.AppendLine($"\tbool {schema.ManagerName}::Add(std::shared_ptr<{schema.ClassName}>&& pData)");
        sb.AppendLine("\t{");
        sb.AppendLine("\t\tif (!pData)");
        sb.AppendLine("\t\t{");
        sb.AppendLine("\t\t\treturn false;");
        sb.AppendLine("\t\t}");
        sb.AppendLine();
        sb.AppendLine($"\t\tconst auto key = {keyExpression};");
        sb.AppendLine("\t\tif (m_data.contains(key))");
        sb.AppendLine("\t\t{");
        sb.AppendLine($"\t\t\tWARN_LOG(\"Duplicated {schema.ClassName} key in static data.\");");
        sb.AppendLine("\t\t\treturn false;");
        sb.AppendLine("\t\t}");
        sb.AppendLine();
        sb.AppendLine("\t\tm_data.emplace(key, std::move(pData));");
        sb.AppendLine("\t\treturn true;");
        sb.AppendLine("\t}");
        sb.AppendLine();
        sb.AppendLine($"\tstd::shared_ptr<const {schema.ClassName}> {schema.ManagerName}::Get({keyParam}) const");
        sb.AppendLine("\t{");
        sb.AppendLine("\t\tconst auto found = m_data.find(key);");
        sb.AppendLine("\t\tif (found == m_data.end())");
        sb.AppendLine("\t\t{");
        sb.AppendLine("\t\t\treturn nullptr;");
        sb.AppendLine("\t\t}");
        sb.AppendLine();
        sb.AppendLine("\t\treturn found->second;");
        sb.AppendLine("\t}");
    }
}
