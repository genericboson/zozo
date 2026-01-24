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
            "string" => "std::string",
            "byte"   => "int8_t",
            "ubyte"  => "uint8_t",
            "long"   => "int64_t",
            "ulong"  => "uint64_t",
            _ => flatBufferType,
        };
    }
    static string ChangeToSqlType(string flatBufferType)
    {
        return flatBufferType switch
        {
            "int"    => "INT",
            "float"  => "FLOAT",
            "double" => "DOUBLE",
            "string" => "VARCHAR(1024)",
            "bool"   => "TINYINT",
            "long"   => "BIGINT",
            "ulong"  => "BIGINT UNSIGNED",
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

        var splitteds = fileNameOnly.Split('_');
        if ( splitteds.Length != 2 )
        {
            Console.WriteLine("Wrong fbs file name. file name must be splitted by '_'. example - DB_ServerName.fbs");
            return;
        }

        if (splitteds[0] != "DB")
        {
            Console.WriteLine("Wrong fbs file name. file name must be started with 'DB_'. example - DB_ServerName.fbs");
            return;
        }

        var serverName = splitteds[1];
        var pathOnly = Path.GetDirectoryName(args[0]) ?? "";

        var serverCacheDir = Path.Combine(pathOnly, $"{serverName}Cache");
        if ( !Directory.Exists(serverCacheDir) )
        {
            Directory.CreateDirectory(serverCacheDir);
        }

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
            cppContent.AppendLine($"namespace {string.Join("::", m_tree.m_namespaces)}");
            cppContent.AppendLine( "{");

            foreach (var typeOne in m_tree.m_types)
            {
                foreach (var field in typeOne.m_fields)
                {
                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::Set{GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( "    }");

                    cppContent.AppendLine($"    void {typeOne.m_name}Cache::Get{GetFunctionName(field.m_name)}()");
                    cppContent.AppendLine( "    {");
                    cppContent.AppendLine( "    }");
                }
            }

            cppContent.AppendLine("}");

            File.WriteAllText(Path.Combine(serverCacheDir, $"{fileNameOnly}.cpp"), cppContent.ToString());
        }

        // make h file
        {
            var hContent = new StringBuilder();

            hContent.AppendLine($"#pragma once");
            hContent.AppendLine();
            hContent.AppendLine($"#include \"{Path.Combine(pathOnly,$"{fileNameOnly}_generated.h")}\"");
            hContent.AppendLine();
            hContent.AppendLine($"namespace {string.Join("::", m_tree.m_namespaces)}");
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
                hContent.AppendLine( "    };");
            }

            hContent.AppendLine("}");

            File.WriteAllText(Path.Combine(serverCacheDir, $"{fileNameOnly}.h"), hContent.ToString());
        }

        // make sql file
        {
            var sqlContent = new StringBuilder();

            foreach (var typeOne in m_tree.m_types)
            {
                var primaryKey = "";
                var indexes = new List<string>();

                sqlContent.AppendLine($"CREATE TABLE {typeOne.m_name.ToLower()} (");
                foreach (var field in typeOne.m_fields)
                {
                    sqlContent.AppendLine($"    {field.m_name} {ChangeToSqlType(field.m_type)}");
                }

                sqlContent.AppendLine($"");

                sqlContent.AppendLine(")");
                sqlContent.AppendLine();
            }

            File.WriteAllText(Path.Combine(serverCacheDir, $"{fileNameOnly}.sql"), sqlContent.ToString());
        }
    }
}