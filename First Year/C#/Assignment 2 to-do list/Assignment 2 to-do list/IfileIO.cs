using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace Assignment_2_to_do_list
{
    interface IfileIO
    {
        void save(ListView toStore);
        ListViewItem[] load();
    }
}
