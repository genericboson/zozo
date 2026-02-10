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
                cppContent.AppendLine($"    {typeOne.m_name}Cache::{typeOne.m_name}Cache()");
                cppContent.AppendLine( "    {");
                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"        m_fields[{field.m_name.ToUpper()}] = std::make_shared<{SC.GetFunctionName(field.m_name)}>(*this);");
                }
                cppContent.AppendLine( "    };");
                cppContent.AppendLine();

                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"    {typeOne.m_name}Cache::{SC.GetFunctionName(field.m_name)}::{SC.GetFunctionName(field.m_name)}({typeOne.m_name}Cache& owner)");
                    cppContent.AppendLine( "        : m_owner(owner)");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( "    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::{SC.GetFunctionName(field.m_name)}::Set(const {SC.ChangeToCppType(field.m_type)}& param)");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( $"        m_owner.{typeOne.m_name}T::{field.m_name} = param;");
                    cppContent.AppendLine( $"        m_flag = true;");
                    cppContent.AppendLine( "    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    auto {typeOne.m_name}Cache::{SC.GetFunctionName(field.m_name)}::Get() const");
                    cppContent.AppendLine($"        -> const {SC.ChangeToCppType(field.m_type)}&");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine($"        return m_owner.{typeOne.m_name}T::{field.m_name};");
                    cppContent.AppendLine( "    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    auto {typeOne.m_name}Cache::{SC.GetFunctionName(field.m_name)}::GetName() const");
                    cppContent.AppendLine($"        -> std::string");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine($"        return \"{field.m_name}\";");
                    cppContent.AppendLine("    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    bool {typeOne.m_name}Cache::{SC.GetFunctionName(field.m_name)}::IsFlagged() const");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine($"        return m_flag;");
                    cppContent.AppendLine( "    };");
                    cppContent.AppendLine();
                }

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetFieldNames() -> const std::vector<std::string>&");
                cppContent.AppendLine( "    {");
                cppContent.AppendLine( "        return m_names;");
                cppContent.AppendLine( "    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetObjectName() -> std::string");
                cppContent.AppendLine( "    {");
                cppContent.AppendLine($"        return \"{typeOne.m_name}\";");
                cppContent.AppendLine( "    };");
                cppContent.AppendLine();
            }

            cppContent.AppendLine("}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.cpp"), cppContent.ToString());
        }
    }
}
