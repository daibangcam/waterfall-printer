using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace GPS_Form1
{
    static class MainProgram
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new BKWGen3.MainForm());
        }
    }
}
