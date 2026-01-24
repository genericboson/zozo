using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlatCacheGenerator
{
    public class FlatBufferField
    {
        public string m_name = "";
        public string m_type = "";
        public string m_defaultValue = "";
        public List<string> m_annotatedAttributes = new();
    }
}
