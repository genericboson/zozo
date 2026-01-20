using Antlr4.Runtime;
using FlatCacheGenerator;
using System;

class Program
{
    static FlatBufferTree? m_tree = null;

    static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.WriteLine("Usage: FlatCacheGenerator XXX.fbs");
            return;
        }

        var fileContent = File.ReadAllText(args[0]);
        var antlrStream = new AntlrInputStream(fileContent);
        var lexer = new FlatBuffersLexer(antlrStream);

        var tokens = new CommonTokenStream(lexer);
        var parser = new FlatBuffersParser(tokens);
        parser.ErrorHandler = new BailErrorStrategy();

        var schema = parser.schema();
        m_tree = schema.output;

        foreach(var typeOne in m_tree.m_types)
        {
            Console.WriteLine($"Type: {typeOne.m_name}");
            foreach(var field in typeOne.m_fields)
            {
                Console.WriteLine($"    FieldType : {field.m_type}, FieldName : {field.m_name}");
            }
        }

        Console.WriteLine("Hello, World!");
    }
}