using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
//////////////////////////////////
using AForge;
using AForge.Imaging;
using AForge.Imaging.Filters;
using System.Drawing;
using System.Diagnostics;

namespace Workshop_2___Forms
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]

        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new ImageViewer());
            
        }
    }
}
