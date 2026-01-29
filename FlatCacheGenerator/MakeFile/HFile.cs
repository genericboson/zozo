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
            hContent.AppendLine($"namespace {string.Join("::", SC.tree.m_namespaces)}");
            hContent.AppendLine("{");

            foreach (var typeOne in SC.tree.m_types)
            {
                hContent.AppendLine($"    enum {typeOne.m_name.ToUpper()}");
                hContent.AppendLine("    {");
                int count = 0;
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        {field.m_name.ToUpper()} = {count++},");
                }
                hContent.AppendLine($"        MAX");
                hContent.AppendLine("    };");
                hContent.AppendLine();
            }

            foreach (var typeOne in SC.tree.m_types)
            {
                hContent.AppendLine($"    class {typeOne.m_name}Cache : private {typeOne.m_name}T");
                hContent.AppendLine("    {");
                hContent.AppendLine("    public:");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        void Set{SC.GetFunctionName(field.m_name)}(const {SC.ChangeToCppType(field.m_type)}& param);");
                    hContent.AppendLine($"        const {SC.ChangeToCppType(field.m_type)}& Get{SC.GetFunctionName(field.m_name)}();");
                    hContent.AppendLine();
                }
                hContent.AppendLine("    private:");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        {SC.ChangeToCppType(field.m_type)} m_{field.m_name};");
                }

                var names = new List<string>();
                foreach (var field in typeOne.m_fields)
                {
                    names.Add($"\"{field.m_name}\"");
                }

                hContent.AppendLine();
                hContent.AppendLine("        std::vector<std::string> m_names = ");
                hContent.AppendLine("        {");
                hContent.AppendLine($"            {string.Join(",\n            ", names)}");
                hContent.AppendLine("        };");
                hContent.AppendLine();
                hContent.AppendLine($"        bool m_flags[{typeOne.m_fields.Count}] = {{ false, }};");

                hContent.AppendLine("    };");
            }

            hContent.AppendLine("}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.h"), hContent.ToString());
        }
    }
}
