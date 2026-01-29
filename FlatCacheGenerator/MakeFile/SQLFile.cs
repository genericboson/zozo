using Antlr4.Runtime.Tree;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public class SQLFile
    {
        public static void Make()
        {
            var sqlContent = new StringBuilder();

            foreach (var typeOne in SC.tree!.m_types)
            {
                var primaryKey = "";
                var indexes = new List<string>();
                var indexQueryElements = new List<string>();
                foreach (var index in typeOne.m_indexes)
                {
                    var keyOne = $"    KEY `{index.Key}` (";
                    var keyElements = new List<string>();
                    foreach (var keyElement in index.Value)
                    {
                        keyElements.Add($"`{keyElement}`");
                    }
                    indexQueryElements.Add($"{keyOne}{string.Join(',', keyElements)})");
                }

                var createQueryElements = new List<string>();
                foreach (var field in typeOne.m_fields)
                {
                    createQueryElements.Add($"    `{field.m_name}` {SC.ChangeToSqlType(field.m_type)}");

                    if (field.m_annotatedAttributes.Contains("PK"))
                    {
                        primaryKey = field.m_name;
                    }
                }

                if (!string.IsNullOrEmpty(primaryKey))
                    createQueryElements.Add($"    PRIMARY KEY(`{primaryKey}`)");

                if (indexQueryElements.Any())
                    createQueryElements.AddRange(indexQueryElements);

                sqlContent.AppendLine($"CREATE TABLE `{typeOne.m_name.ToLower()}` (");
                sqlContent.AppendLine(string.Join(",\n", createQueryElements));
                sqlContent.AppendLine(");");
                sqlContent.AppendLine();
            }

            File.WriteAllText(Path.Combine(SC.serverCacheDir, $"{SC.fileNameOnly}.sql"), sqlContent.ToString());
        }
    }
}
