using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public enum TypeKind
    {
        None,
        Table,
        Struct,
    }

    public class FlatBufferType
    {
        public string m_name = "";
        public TypeKind m_kind = TypeKind.None;
        public List<FlatBufferField> m_fields = new();
        public List<Dictionary<string,List<string>>> m_indexes = new();
    }
}
