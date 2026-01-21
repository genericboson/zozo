using Antlr4.Runtime;
using FlatCacheGenerator;
using System;
using System.Text;

class Program
{
    static FlatBufferTree? m_tree = null;

    static string ChangeToCppType(string flatBufferType)
    {
        return flatBufferType switch
        {
            "int"    => "int32_t",
            "float"  => "float",
            "string" => "std::string",
            _ => flatBufferType,
        };
    }

    static string GetFunctionName(string fieldName)
    {
        if (fieldName.Length <= 1)
        {
            Console.WriteLine($"Too short length. field name - {fieldName}");
            return "";
        }

        var upperFirstChar = char.ToUpper(fieldName[0]);

        return $"{upperFirstChar}{fieldName.Substring(1)}";
    }

    static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.WriteLine("Usage: FlatCacheGenerator XXX.fbs");
            return;
        }

        var fileNameOnly = Path.GetFileNameWithoutExtension(args[0]);

        var fileContent = File.ReadAllText(args[0]);
        var antlrStream = new AntlrInputStream(fileContent);
        var lexer = new FlatBuffersLexer(antlrStream);

        var tokens = new CommonTokenStream(lexer);
        var parser = new FlatBuffersParser(tokens);
        parser.ErrorHandler = new BailErrorStrategy();

        var schema = parser.schema();
        m_tree = schema.output;

        ///////////////////////////////////////////////////////////////////////////

        // make cpp file
        {
            var cppContent = new StringBuilder();

            cppContent.AppendLine($"#include \"PCH.h\"");
            cppContent.AppendLine();
            cppContent.AppendLine($"#include \"{fileNameOnly}.h\"");
            cppContent.AppendLine();
            cppContent.AppendLine( "namespace GenericBoson");
            cppContent.AppendLine( "{");

            foreach (var typeOne in m_tree.m_types)
            {
                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"    void {typeOne.m_name}::Set{GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( "    }");

                    cppContent.AppendLine($"    void {typeOne.m_name}::Get{GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( "    }");
                }
            }

            cppContent.AppendLine("}");

            File.WriteAllText($"{fileNameOnly}.cpp", cppContent.ToString());
        }

        // make h file
        {
            var hContent = new StringBuilder();

            hContent.AppendLine($"#pragma once");
            hContent.AppendLine();
            hContent.AppendLine("namespace GenericBoson");
            hContent.AppendLine("{");

            foreach (var typeOne in m_tree.m_types)
            {
                hContent.AppendLine($"    class {typeOne.m_name}Cache : private {typeOne.m_name}T");
                hContent.AppendLine( "    {");
                hContent.AppendLine( "    public:");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        void Set{GetFunctionName(field.m_name)}();");
                    hContent.AppendLine($"        void Get{GetFunctionName(field.m_name)}();");
                }
                hContent.AppendLine();
                hContent.AppendLine( "    private:");
                foreach (var field in typeOne.m_fields)
                {
                    hContent.AppendLine($"        {ChangeToCppType(field.m_type)} m_{field.m_name};");
                }
                hContent.AppendLine( "    }");
            }

            hContent.AppendLine("}");

            File.WriteAllText($"{fileNameOnly}.h", hContent.ToString());
        }
    }
}