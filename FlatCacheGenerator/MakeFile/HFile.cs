using Antlr4.Runtime.Tree;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public class HFile
    {
        public static void Make()
        {
            var hContent = new StringBuilder();

            hContent.AppendLine($"#pragma once");
            hContent.AppendLine();
            hContent.AppendLine($"#include \"{Path.Combine(SC.pathOnly, $"{SC.fileNameOnly}_generated.h")}\"");
            hContent.AppendLine();
            hContent.AppendLine(@"#include <Engine/Tx/CacheField.h>");
            hContent.AppendLine(@"#include <Engine/Tx/CacheObject.h>");
            hContent.AppendLine();
            hContent.AppendLine($"namespace {string.Join("::", SC.tree.m_namespaces)}");
            hContent.AppendLine(@"{");

            foreach (var typeOne in SC.tree.m_types)
            {
                hContent.AppendLine($"    enum {typeOne.m_name.ToUpper()}");
                hContent.AppendLine(@"    {");
                int count = 0;
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        {field.m_name.ToUpper()} = {count++},");
                }
                hContent.AppendLine($"        MAX");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"    class {SC.SnakeToPascalOrCamel(field.m_name)};");
                }
                hContent.AppendLine();
            }

            foreach (var typeOne in SC.tree.m_types)
            {
                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    class {typeOne.m_name}Cache : public T,");
                hContent.AppendLine($"        private {typeOne.m_name}T,");
                hContent.AppendLine($"        std::enable_shared_from_this<{typeOne.m_name}Cache<T>>");
                hContent.AppendLine(@"    {");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        friend class {SC.SnakeToPascalOrCamel(field.m_name)};");
                }
                hContent.AppendLine(@"    public:");
                hContent.AppendLine($"        {typeOne.m_name}Cache(CacheTx& tx);");
                hContent.AppendLine($"        std::shared_ptr<ICacheObject> CreateObject() override;");
                hContent.AppendLine();
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        class {SC.SnakeToPascalOrCamel(field.m_name)} : public CacheField");
                    hContent.AppendLine(@"        {");
                    hContent.AppendLine(@"        public:");
                    hContent.AppendLine($"            {SC.SnakeToPascalOrCamel(field.m_name)}({typeOne.m_name}Cache& owner);");
                    if (field.m_type != "string")
                        hContent.AppendLine($"            void Set(const {SC.ChangeToCppType(field.m_type)}& param);");
                    hContent.AppendLine($"            void Set(const boost::mysql::field_view value) override;");
                    hContent.AppendLine($"            void SetKey(const {SC.ChangeToCppType(field.m_type)}& param);");
                    hContent.AppendLine($"            auto Get() const -> const {SC.ChangeToCppType(field.m_type)}&;");
                    hContent.AppendLine(@"            std::string GetName() const override;");
                    hContent.AppendLine($"            std::string GetValueString() const override;");
                    hContent.AppendLine(@"            bool IsKey() const override;");
                    hContent.AppendLine(@"            void Bind() override;");
                    hContent.AppendLine(@"            bool IsBound() const override;");
                    hContent.AppendLine(@"        private:");
                    hContent.AppendLine($"            {typeOne.m_name}Cache& m_owner;");
                    hContent.AppendLine(@"            FieldState m_state = FieldState::None;");
                    hContent.AppendLine(@"        };");
                    hContent.AppendLine($"        {SC.SnakeToPascalOrCamel(field.m_name)}& Get{SC.SnakeToPascalOrCamel(field.m_name)}();");
                    hContent.AppendLine();
                }
                hContent.AppendLine(@"    protected:");
                hContent.AppendLine(@"        auto GetObjectName() const                            -> std::string                           override;");
                hContent.AppendLine(@"        auto GetFieldNames() const                            -> const std::vector<std::string>&       override;");
                hContent.AppendLine(@"        auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                           override;");
                hContent.AppendLine(@"        auto GetField(const std::string& fieldName) const     -> const CacheField*                     override;");
                hContent.AppendLine(@"        auto GetField(const int32_t fieldEnumValue) const     -> const CacheField*                     override;");
                hContent.AppendLine($"        auto GetFields() const                                -> const std::vector<const CacheField*>& override;");
                hContent.AppendLine(@"    private:");

                var names = new List<string>();
                foreach (var field in typeOne.m_fields)
                {
                    names.Add($"\"{field.m_name}\"");
                    hContent.AppendLine($"        CacheField* m_p{SC.SnakeToPascalOrCamel(field.m_name)} = nullptr;");
                }

                hContent.AppendLine();
                hContent.AppendLine(@"        std::vector<std::string> m_names = ");
                hContent.AppendLine(@"        {");
                hContent.AppendLine($"            {string.Join(",\n            ", names)}");
                hContent.AppendLine(@"        };");
                hContent.AppendLine();
                hContent.AppendLine(@"        std::unordered_map<std::string, std::shared_ptr<CacheField>> m_fieldMap;");
                hContent.AppendLine(@"        std::vector<const CacheField*>                               m_fieldVector;");

                hContent.AppendLine(@"    };");

                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    {typeOne.m_name}Cache<T>::{typeOne.m_name}Cache(CacheTx& tx)");
                hContent.AppendLine(@"        : T(tx)");
                hContent.AppendLine(@"    {");
                hContent.AppendLine($"        m_fieldVector.reserve({typeOne.m_fields.Count()});");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        m_fieldMap[\"{field.m_name}\"] = std::make_shared<{SC.SnakeToPascalOrCamel(field.m_name)}>(*this);");
                    hContent.AppendLine($"        m_p{SC.SnakeToPascalOrCamel(field.m_name)} = m_fieldMap[\"{field.m_name}\"].get();");
                    hContent.AppendLine($"        m_fieldVector.push_back(m_p{SC.SnakeToPascalOrCamel(field.m_name)});");
                }
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    std::shared_ptr<ICacheObject> {typeOne.m_name}Cache<T>::CreateObject()");
                hContent.AppendLine(@"    {");
                hContent.AppendLine($"        return std::make_shared<{typeOne.m_name}Cache<T>>(this->m_tx);");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::{SC.SnakeToPascalOrCamel(field.m_name)}({typeOne.m_name}Cache& owner)");
                    hContent.AppendLine(@"        : m_owner(owner)");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    if(field.m_type != "string")
                    {
                        hContent.AppendLine($"    template<typename T>");
                        hContent.AppendLine($"    void {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::Set(const {SC.ChangeToCppType(field.m_type)}& param)");
                        hContent.AppendLine(@"    {");
                        hContent.AppendLine($"        m_owner.{typeOne.m_name}T::{field.m_name} = param;");
                        hContent.AppendLine($"        m_state = FieldState::Bound;");
                        hContent.AppendLine(@"    }");
                        hContent.AppendLine();
                    }

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    void {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::Set(const boost::mysql::field_view param)");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        m_owner.{typeOne.m_name}T::{field.m_name} = {SC.ChangeToMySqlRowPrefix(field.m_type)}param.{SC.ChangeToMySqlRowAsFunctionName(field.m_type)};");
                    hContent.AppendLine($"        m_state = FieldState::Bound;");
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    void {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::SetKey(const {SC.ChangeToCppType(field.m_type)}& param)");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        m_owner.{typeOne.m_name}T::{field.m_name} = param;");
                    hContent.AppendLine($"        m_state = FieldState::Key;");
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::Get() const");
                    hContent.AppendLine($"        -> const {SC.ChangeToCppType(field.m_type)}&");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        return m_owner.{typeOne.m_name}T::{field.m_name};");
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    std::string {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::GetName() const");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        return \"{field.m_name}\";");
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    std::string {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::GetValueString() const");
                    hContent.AppendLine(@"    {");
                    if (SC.IsString(field.m_type))
                    {
                        hContent.AppendLine($"        return m_owner.{typeOne.m_name}T::{field.m_name};");
                    }
                    else
                    {
                        hContent.AppendLine($"        return std::to_string(m_owner.{typeOne.m_name}T::{field.m_name});");
                    }
                    hContent.AppendLine(@"    }");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    void {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::Bind()");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        m_state = FieldState::Bound;");
                    hContent.AppendLine(@"    };");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    bool {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::IsBound() const");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        return m_state == FieldState::Bound || m_state == FieldState::Key;");
                    hContent.AppendLine(@"    };");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    bool {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}::IsKey() const");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        return m_state == FieldState::Key;");
                    hContent.AppendLine(@"    };");
                    hContent.AppendLine();

                    hContent.AppendLine($"    template<typename T>");
                    hContent.AppendLine($"    {typeOne.m_name}Cache<T>::{SC.SnakeToPascalOrCamel(field.m_name)}& {typeOne.m_name}Cache<T>::Get{SC.SnakeToPascalOrCamel(field.m_name)}()");
                    hContent.AppendLine(@"    {");
                    hContent.AppendLine($"        return *static_cast<{typeOne.m_name}Cache::{SC.SnakeToPascalOrCamel(field.m_name)}*>(m_p{SC.SnakeToPascalOrCamel(field.m_name)});");
                    hContent.AppendLine(@"    };");
                    hContent.AppendLine();
                }

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetObjectName() const -> std::string");
                hContent.AppendLine(@"    {");
                hContent.AppendLine($"        return \"{typeOne.m_name}\";");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetFieldNames() const -> const std::vector<std::string>&");
                hContent.AppendLine(@"    {");
                hContent.AppendLine(@"        return m_names;");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetFieldName(const int32_t fieldEnumValue) const -> std::string");
                hContent.AppendLine(@"    {");
                hContent.AppendLine($"        NULL_RETURN(0 <= fieldEnumValue && fieldEnumValue < {typeOne.m_name.ToUpper()}::MAX, std::string{{}});");
                hContent.AppendLine(@"        return m_names[fieldEnumValue];");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetField(const std::string& fieldName) const -> const CacheField*");
                hContent.AppendLine(@"    {");
                hContent.AppendLine(@"        if (const auto found = m_fieldMap.find(fieldName);");
                hContent.AppendLine(@"            found == m_fieldMap.end())");
                hContent.AppendLine(@"            return nullptr;");
                hContent.AppendLine(@"         else");
                hContent.AppendLine(@"            return found->second.get();");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetField(const int32_t fieldEnumValue) const -> const CacheField*");
                hContent.AppendLine(@"    {");
                hContent.AppendLine(@"        return GetField(GetFieldName(fieldEnumValue));");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();

                hContent.AppendLine($"    template<typename T>");
                hContent.AppendLine($"    auto {typeOne.m_name}Cache<T>::GetFields() const -> const std::vector<const CacheField*>&");
                hContent.AppendLine(@"    {");
                hContent.AppendLine($"        return m_fieldVector;");
                hContent.AppendLine(@"    };");
                hContent.AppendLine();
            }

            hContent.AppendLine(@"}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.h"), hContent.ToString());
        }
    }
}
 