using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Assignment_2_to_do_list
{
    class fileIo: IfileIO
    {
        // save task data to file
        public void save(ListView toStore)
        {
            StreamWriter writer = new StreamWriter("Tasks.userdata");
            writer.WriteLine(toStore.Items.Count);

            foreach (ListViewItem lv in toStore.Items)
            {
                // explicit cast necessary, should be safe as tag cannot 
                // be any other object in this list view 
                Task taskToSave = (Task)lv.Tag; 
                writer.WriteLine(taskToSave.taskName);
                writer.WriteLine(taskToSave.taskDescription);
                writer.WriteLine(taskToSave.due);
                writer.WriteLine(taskToSave.taskComplete);
            }
            writer.Close();
        }
        //Loadtask data from file
        public ListViewItem[] load()
        {
            StreamReader sr = new StreamReader("Tasks.userdata");
            ListViewItem[] lv = new ListViewItem[Convert.ToInt32(sr.ReadLine())];
            string line;
            int arrIndex = 0;
            while ((line = sr.ReadLine()) != null)
            {
                // explicit cast necessary, should be safe as tag cannot 
                // be any other object in this list view
                Task temp = new Task();
                temp.taskName = line;
                temp.taskDescription = sr.ReadLine();
                temp.due = Convert.ToDateTime(sr.ReadLine());
                temp.taskComplete = Convert.ToBoolean(sr.ReadLine());               
                ListViewItem tempList = new ListViewItem(temp.taskName);
                tempList.Tag = temp;
                lv[arrIndex] =tempList;
                arrIndex++;
            }
            sr.Close();
            return lv;
            
        }
    }
}
