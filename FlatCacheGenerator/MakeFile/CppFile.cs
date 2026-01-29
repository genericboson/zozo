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
                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::Set{SC.GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine("    }");

                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::Get{SC.GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine("    {");
                    cppContent.AppendLine("    }");
                }
            }

            cppContent.AppendLine("}");

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.cpp"), cppContent.ToString());
        }
    }
}
