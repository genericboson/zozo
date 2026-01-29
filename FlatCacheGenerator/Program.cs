using Antlr4.Runtime;
using FlatCacheGenerator;
using System;
using System.Linq;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.WriteLine("Usage: FlatCacheGenerator XXX.fbs");
            return;
        }

        SC.fileNameOnly = Path.GetFileNameWithoutExtension(args[0]);

        var splitteds = SC.fileNameOnly.Split('_');
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
        SC.pathOnly = Path.GetDirectoryName(args[0]) ?? "";

        SC.serverCacheDir = Path.Combine(SC.pathOnly, $"{serverName}Cache");
        if ( !Directory.Exists(SC.serverCacheDir) )
        {
            Directory.CreateDirectory(SC.serverCacheDir);
        }

        var fileContent = File.ReadAllText(args[0]);
        var antlrStream = new AntlrInputStream(fileContent);
        var lexer = new FlatBuffersLexer(antlrStream);

        var tokens = new CommonTokenStream(lexer);
        var parser = new FlatBuffersParser(tokens);
        parser.ErrorHandler = new BailErrorStrategy();

        var schema = parser.schema();
        SC.tree = schema.output;

        CppFile.Make();
        HFile.Make();
        SQLFile.Make();
    }
}