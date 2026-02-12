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
            cppContent.AppendLine($"#include <Engine/Concepts.h>");
            cppContent.AppendLine();
            cppContent.AppendLine($"namespace {string.Join("::", SC.tree.m_namespaces)}");
            cppContent.AppendLine(@"{");

            foreach (var typeOne in SC.tree.m_types)
            {
                cppContent.AppendLine($"    {typeOne.m_name}Cache::{typeOne.m_name}Cache()");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine($"        m_fieldVector.reserve({typeOne.m_fields.Count()});");
                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"        m_fieldMap[\"{field.m_name}\"] = std::make_shared<{SC.SnakeToPascalOrCamel(field.m_name)}>(*this);");
                    cppContent.AppendLine($"        m_p{SC.SnakeToPascalOrCamel(field.m_name)} = m_fieldMap[\"{field.m_name}\"].get();");
                    cppContent.AppendLine($"        m_fieldVector.push_back(m_p{SC.SnakeToPascalOrCamel(field.m_name)});");
                }
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"    {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::{SC.SnakeToPascalOrCamel(field.m_name)}({typeOne.m_name}Cache& owner)");
                    cppContent.AppendLine(@"        : m_owner(owner)");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine(@"    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::Set(const {SC.ChangeToCppType(field.m_type)}& param)");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine($"        m_owner.{typeOne.m_name}T::{field.m_name} = param;");
                    cppContent.AppendLine($"        m_isBound = true;");
                    cppContent.AppendLine(@"    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    auto {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::Get() const");
                    cppContent.AppendLine($"        -> const {SC.ChangeToCppType(field.m_type)}&");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine($"        return m_owner.{typeOne.m_name}T::{field.m_name};");
                    cppContent.AppendLine(@"    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    std::string {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::GetName() const");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine($"        return \"{field.m_name}\";");
                    cppContent.AppendLine(@"    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    std::string {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::GetValueString() const");
                    cppContent.AppendLine(@"    {");
                    if (SC.IsString(field.m_type))
                    {
                        cppContent.AppendLine($"        return m_owner.{typeOne.m_name}T::{field.m_name};");
                    }
                    else
                    {
                        cppContent.AppendLine($"        return std::to_string(m_owner.{typeOne.m_name}T::{field.m_name});");
                    }
                    cppContent.AppendLine(@"    }");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    bool {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}::IsBound() const");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine($"        return m_isBound;");
                    cppContent.AppendLine(@"    };");
                    cppContent.AppendLine();

                    cppContent.AppendLine($"    {typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}& {typeOne.m_name}Cache::Get{SC.SnakeToPascalOrCamel(field.m_name)}()");
                    cppContent.AppendLine(@"    {");
                    cppContent.AppendLine($"        return *static_cast<{typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}*>(m_p{SC.SnakeToPascalOrCamel(field.m_name)});");
                    cppContent.AppendLine(@"    };");
                    cppContent.AppendLine();
                }

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetObjectName() const -> std::string");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine($"        return \"{typeOne.m_name}\";");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetFieldNames() const -> const std::vector<std::string>&");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine(@"        return m_names;");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetFieldName(const int32_t fieldEnumValue) const -> std::string");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine($"        NULL_RETURN(0 <= fieldEnumValue && fieldEnumValue < {typeOne.m_name.ToUpper()}::MAX, std::string{{}});");
                cppContent.AppendLine(@"        return m_names[fieldEnumValue];");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetField(const std::string& fieldName) const -> const CacheField*");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine(@"        if (const auto found = m_fieldMap.find(fieldName);");
                cppContent.AppendLine(@"            found == m_fieldMap.end())");
                cppContent.AppendLine(@"            return nullptr;");
                cppContent.AppendLine(@"         else");
                cppContent.AppendLine(@"            return found->second.get();");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetField(const int32_t fieldEnumValue) const -> const CacheField*");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine(@"        return GetField(GetFieldName(fieldEnumValue));");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();

                cppContent.AppendLine($"    auto {typeOne.m_name}Cache::GetFields() const -> const std::vector<const CacheField*>&");
                cppContent.AppendLine(@"    {");
                cppContent.AppendLine($"        return m_fieldVector;");
                cppContent.AppendLine(@"    };");
                cppContent.AppendLine();
            }

            cppContent.AppendLine("}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.cpp"), cppContent.ToString());
        }
    }
}
