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
                hContent.AppendLine($"    class {typeOne.m_name}Cache : ");
                hContent.AppendLine($"        public CacheObject,");
                hContent.AppendLine($"        private {typeOne.m_name}T,");
                hContent.AppendLine($"        std::enable_shared_from_this<{typeOne.m_name}Cache>");
                hContent.AppendLine(@"    {");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        friend class {SC.SnakeToPascalOrCamel(field.m_name)};");
                }
                hContent.AppendLine(@"    public:");
                hContent.AppendLine($"       {typeOne.m_name}Cache(CacheTx& tx);");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        class {SC.SnakeToPascalOrCamel(field.m_name)} : public CacheField");
                    hContent.AppendLine(@"        {");
                    hContent.AppendLine(@"        public:");
                    hContent.AppendLine($"            {SC.SnakeToPascalOrCamel(field.m_name)}({typeOne.m_name}Cache& owner);");
                    hContent.AppendLine($"            void Set(const {SC.ChangeToCppType(field.m_type)}& param);");
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
            }

            hContent.AppendLine(@"}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.h"), hContent.ToString());
        }
    }
}
 