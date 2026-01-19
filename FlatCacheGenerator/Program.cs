using Antlr4.Runtime;
using System;

class FlatCacheGenerator
{
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

        Console.WriteLine("Hello, World!");
    }
}