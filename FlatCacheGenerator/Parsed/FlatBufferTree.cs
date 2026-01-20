using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public class FlatBufferTree
    {
        public List<string> m_includes = new();
        public List<string> m_namespaces = new();
        public List<FlatBufferType> m_types = new();
    }
}
