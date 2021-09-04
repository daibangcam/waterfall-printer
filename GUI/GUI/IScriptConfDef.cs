using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IScriptConfDef
{
    public struct UScriptParams
    {
        public uint repeat;
        public uint dlbefore;
        public uint dlrepeat;
        public uint dlafter;
        public uint align;
    }

    public interface IScriptConf
    {
        UScriptParams usc { get; set; }
    }
}
