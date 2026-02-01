using Antlr4.Runtime.Tree;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public class CppFile
    {
        public static void Make()
        {
            var cppContent = new StringBuilder();

            cppContent.AppendLine($"#include \"PCH.h\"");
            cppContent.AppendLine();
            cppContent.AppendLine($"#include \"{SC.fileNameOnly}.h\"");
            cppContent.AppendLine();
            cppContent.AppendLine($"namespace {string.Join("::", SC.tree.m_namespaces)}");
            cppContent.AppendLine("{");

            foreach (var typeOne in SC.tree.m_types)
            {
                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::Set{SC.GetFunctionName(field.m_name)}(const {SC.ChangeToCppType(field.m_type)}& param)");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine($"        {typeOne.m_name}T::{field.m_name} = param;");
                    cppContent.AppendLine($"        m_flags[{typeOne.m_name.ToUpper()}::{field.m_name.ToUpper()}] = true;");
                    cppContent.AppendLine("    }");

                    cppContent.AppendLine($"    const {SC.ChangeToCppType(field.m_type)}& {typeOne.m_name}Cache::Get{SC.GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine($"        return {typeOne.m_name}T::{field.m_name};");
                    cppContent.AppendLine("    }");

                    cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetNames() -> const std::vector<std::string>&");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine("        return m_names;");
                    cppContent.AppendLine("    };");
                }
            }

            cppContent.AppendLine("}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.cpp"), cppContent.ToString());
        }
    }
}
