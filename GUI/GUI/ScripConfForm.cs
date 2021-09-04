using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


using IScriptConfDef;

namespace BKWGen3
{
    public partial class ScripConfForm : Form, IScriptConf
    {
        private IScriptConfDef.UScriptParams conf;

        public ScripConfForm()
        {
            InitializeComponent();
        }

        public UScriptParams usc
        {
            set 
            { 

                numRepeat.Value = value.repeat;
                numDlbefore.Value = value.dlbefore;
                numDlrepeat.Value = value.dlrepeat;
                numDlafter.Value = value.dlafter;
                conf.align = value.align;
                switch (value.align)
                {
                    case 0x01:
                        cbbAlign.Text = "Right";
                        break;
                    case 0x02:
                        cbbAlign.Text = "Center";
                        break;
                    default:
                        cbbAlign.Text = "Left";
                        conf.align = 0x00;
                        break;
                }
                /*
                conf.repeat = value.repeat;
                conf.dlbefore = value.dlbefore;
                conf.dlrepeat = value.dlrepeat;
                conf.dlafter = value.dlafter;
                 */ 
                
            }

            get 
            {
                return conf;                
            }
        }

        private void butOk_Click(object sender, EventArgs e)
        {
            conf.repeat = (uint)numRepeat.Value;
            conf.dlbefore = (uint)numDlbefore.Value;
            conf.dlrepeat = (uint)numDlrepeat.Value;
            conf.dlafter = (uint)numDlafter.Value;
            switch (cbbAlign.Text)
            {
                case "Right":
                    conf.align = 0x01;
                    break;
                case "Center":
                    conf.align = 0x02;
                    break;
                default:
                    conf.align = 0x00;
                    break;
            }
            this.Close();
        }

        private void butCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
        
    }
}
