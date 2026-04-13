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

        public static string ChangeToMySqlRowAsFunctionName(string flatBufferType)
        {
            return flatBufferType switch
            {
                "int" => "as_int64())",
                "string" => "as_string()",
                "byte" => "as_int64())",
                "ubyte" => "as_int64())",
                "long" => "as_int64()",
                "ulong" => "as_uint64()",
                "float" => "as_float()",
                "double" => "as_double()",
                _ => "ERROR",
            };
        }

        public static string ChangeToMySqlRowPrefix(string flatBufferType)
        {
            return flatBufferType switch
            {
                "int" => "static_cast<int32_t>(",
                "byte" => "static_cast<int8_t>(",
                "ubyte" => "static_cast<uint8_t>(",
                _ => "",
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

        public static string SnakeToPascalOrCamel(string name, bool isPascal = true)
        {
            if (name.Length <= 1)
            {
                Console.WriteLine($"Too short length. field name - {name}");
                return "";
            }

            var functionName = name;

            if (isPascal)
            {
                var upperFirstChar = char.ToUpper(name[0]);
                functionName = $"{upperFirstChar}{name.Substring(1)}";
            }

            functionName = Regex.Replace(functionName, @"_([a-zA-Z])", m => { return m.Groups[1].Value.ToUpper(); });

            return functionName;
        }

        public static bool IsString(string name)
        {
            return name == "string";
        }

        public static string ChangeStringToFieldType(string typeName)
        {
            return typeName switch
            {
                "int" => "std::stoi",
                "float" => "std::stof",
                "double" => "std::stod",
                "bool" => "boost::lexical_cast<bool>",
                "long" => "std::stol",
                "ulong" => "std::stoul",
                _ => "",
            };
        }
    }
}
