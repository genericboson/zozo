using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    // Static Class
    public static class SC
    {
        public static FlatBufferTree tree = new();
        public static string pathOnly = "", serverCacheDir = "", fileNameOnly = "";

        public static string ChangeToCppType(string flatBufferType)
        {
            return flatBufferType switch
            {
                "int" => "int32_t",
                "string" => "std::string",
                "byte" => "int8_t",
                "ubyte" => "uint8_t",
                "long" => "int64_t",
                "ulong" => "uint64_t",
                _ => flatBufferType,
            };
        }

        public static string ChangeToSqlType(string flatBufferType)
        {
            return flatBufferType switch
            {
                "int" => "INT",
                "float" => "FLOAT",
                "double" => "DOUBLE",
                "string" => "VARCHAR(1024)",
                "bool" => "TINYINT",
                "long" => "BIGINT",
                "ulong" => "BIGINT UNSIGNED",
                _ => flatBufferType,
            };
        }

        public static string SnakeToPascal(string name)
        {
            if (name.Length <= 1)
            {
                Console.WriteLine($"Too short length. field name - {name}");
                return "";
            }

            var upperFirstChar = char.ToUpper(name[0]);
            var functionName = $"{upperFirstChar}{name.Substring(1)}";

            functionName = Regex.Replace(functionName, @"_([a-zA-Z])", m => { return m.Groups[1].Value.ToUpper(); });

            return functionName;
        }
    }
}
