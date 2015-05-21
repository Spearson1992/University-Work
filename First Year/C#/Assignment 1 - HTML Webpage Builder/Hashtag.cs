//#define TEST
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace Assignment
{

    class HTMLWriter
    {

        static void Main(string[] args)
        {
#if TEST
            TextWriter logWriter;//declare log writer
            if (File.Exists("Test_log.txt")) // if test log already exists append to it else create new
            {
               logWriter = File.AppendText("Test_log.txt");
            }
            else
            {
                logWriter = new StreamWriter("Test_log.txt");
            }
            logWriter.Close();
#endif
#if TEST
            logWriter = File.AppendText("Test_log.txt");// append to log file for testing purposes
            logWriter.WriteLine("==========={0}==========", System.DateTime.Now);
            logWriter.WriteLine("Leaving non hashtags in");
            logWriter.Close();
#endif
            HTMLWriter writer;//declare HTMLWriter object
            Console.WriteLine("Would you like non-hashtags to be removed from the list?\nEnter Y for yes or n for no");
            String choice;
            choice = Console.ReadLine();// read in users choice 
            try// if HTMLWriter is initialised properly contnue else catch and deal with exception
            {
                writer = new HTMLWriter();
                writer.readFile(choice);
#if TEST
                logWriter = File.AppendText("Test_log.txt");
                logWriter.WriteLine("Execution complete");
                logWriter.Close();
#endif
            }
            catch(NullReferenceException)
            {
                Console.WriteLine("Error object creation failed");
                    return;
            }
            
        }

        /*********************************
         * Function reads in a text file
         * and populates a dictionary with
         * entries from the file
         *********************************/
        public void readFile(String choice)
        {
#if TEST
            TextWriter logWriter = File.AppendText("Test_log.txt");
            logWriter.WriteLine("readFile function executing...");
#endif
            TextReader tr; // delcare text reader object
            Dictionary<String, int> di = new Dictionary<string, int>(); // delcare and intialise dictionary
            try
            {
                tr = new StreamReader("tweets.txt");

            }
            catch (FileNotFoundException)
            {
                Console.WriteLine("Error tweets.txt not found.");

#if TEST
                logWriter.WriteLine("Catch block executing, file not found exception");
                logWriter.Close();
#endif
                return;
            }
            catch (IOException)
            {
                Console.WriteLine("Error IO Exception occured");
#if TEST
                logWriter.WriteLine("File read failed");
                logWriter.Close();
#endif
                return;
            }
#if TEST
            Boolean logged = false;
#endif
            String line = "";
            double count = 0;//keeps a count of the total number of hashtags in the file
            int value = 0; // used to hold the result of try get value
            while (line != null)
            {
#if TEST
                if (!logged)
                    logWriter.WriteLine("Populating Dictionary");
                
#endif
#if TEST
                if (!logged)
                    logWriter.WriteLine("Removing blank lines");
                if (line == "")
                    logged = true;
#endif
                line = tr.ReadLine();
                if (line != "" & line != null)//removes blank lines, needed for removing non-hashtags to prevent the nullReferencEexcpetion
                {

                    if (choice == "Y" || choice == "y")//removes non-hashtags if the user wishes
                    {
#if TEST
                        if (!logged)
                            logWriter.WriteLine("Removing non-hashtags");
                        logged = true;
#endif
                        if (line.Substring(0, 1) == "#")
                        {
                            count++;
                            if (di.TryGetValue(line, out value) == true)//increments the key count if the key already exists
                            {
                                di[line] = value + 1;
                            }
                            else
                            {
                                di.Add(line, 1);//adds a new key to the dicionary
                            }
                        }
                    }
                    else
                    {
                        count++;
                        if (di.TryGetValue(line, out value) == true)//TryGetValue does one less hash comparison than compareKey
                        {
                            di[line] = value + 1;
                        }
                        else
                        {
                            di.Add(line, 1);
                        }
                    }
                }

            }


            tr.Close();
#if TEST
           
            logWriter.WriteLine("File read successfully, dictionary populated");
            logWriter.WriteLine("Number of hashtags in dictionary: {0}", count);
            logWriter.Close();
#endif
            writeFile(di, count);// calls the writeFile method if readFile executes sucessfully

        }
        /****************************************************************
         * 
        *****************************************************************/
        public void writeFile(Dictionary<String, int> di, double totalTweets)
        {
#if TEST
            TextWriter logWriter = File.AppendText("Test_log.txt");
            logWriter.WriteLine("writeFile function executing");
#endif
            int rowsPrinted = 0;//used for formating the html table, makes row colour alternate
            double totalChars = 0;//count of the total number of characters in the file
            int totalUniqueTweets = 0;
            int topTwentyPrinted = 0;
            TextWriter txtWriter;
#if TEST
            logWriter.WriteLine("Counting unique tweets and total characters...");
#endif
            foreach (KeyValuePair<String, int> kvp in di)
            {

                totalChars += (kvp.Key.Length * kvp.Value);
                totalUniqueTweets++;
            }
#if TEST
            logWriter.WriteLine("Counting complete, test passed");
            logWriter.WriteLine("Total unique tags: {0}", totalUniqueTweets);
#endif
            try
            {
            
                txtWriter = new StreamWriter("tweets.html");

            }
            catch (IOException)
            {
#if TEST
                    logWriter.WriteLine("IO Exception caught, file creation failed");
                    logWriter.Close();
#endif
                Console.WriteLine("File creation failed, is your hard drive full?");
                return;
            }
#if TEST
            logWriter.WriteLine("Writing HTML file...");
#endif
            //write initial formatting information for the html tables
            txtWriter.WriteLine("<html>\r\n" +
                                "<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\" width=\"800\" >\r\n" +
                                "<tr>" +
                                "<th width =\"450\"> Hashtags </th>\r\n" +
                                "<th width =\"150\"> Top Twenty </th>\r\n" +
                                "<th width =\"200\"> Miscellaneous data </th>\r\n" +
                                "</tr>\r\n" +
                                "<tr>\r\n" +
                                "<td width=\"450\">\r\n" +
                                "<div style=\"width:476px; height:600px; overflow:auto;\">\r\n" +
                                "<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\" width=\"450px\" >\r\n");
            foreach (KeyValuePair<String,int> kvp in di.OrderByDescending(key => key.Value))// orders dictionary output and prints each key and value
            {//write contents of dictionary to the scrollable first column of the html table
                if (rowsPrinted % 2 == 0)
                {
                    txtWriter.WriteLine("<tr bgcolor = \"#CCCFFF\">");
                    txtWriter.WriteLine("<td> {0}, {1} tags </td>", kvp.Key, kvp.Value);
                    txtWriter.WriteLine("</tr>");
                }
                else
                {
                    txtWriter.WriteLine("<tr>");
                    txtWriter.WriteLine("<td> {0}, {1} tags </td>", kvp.Key, kvp.Value);
                    txtWriter.WriteLine("</tr>");
                }
                rowsPrinted++;
                
            }
                txtWriter.WriteLine("</table>\r\n" +
                "</div>\r\n" +
                "</td>\r\n" +
                "<td valign=\"top\">\r\n" +
                "<table width=\"150\">\r\n");
                foreach (KeyValuePair<String, int> kvp in di.OrderByDescending(key => key.Value))
                {//print out top twent values from the dictionary
                    if (topTwentyPrinted < 20)
                    {
                        if (topTwentyPrinted % 2 == 0)
                        {
                            txtWriter.WriteLine("<tr bgcolor = \"#CCCFFF\">");
                            txtWriter.WriteLine("<td> {0}, {1} tags </td>", kvp.Key, kvp.Value);
                            txtWriter.WriteLine("</tr>");
                        }
                        else
                        {
                            txtWriter.WriteLine("<tr>");
                            txtWriter.WriteLine("<td> {0}, {1} tags </td>", kvp.Key, kvp.Value);
                            txtWriter.WriteLine("</tr>");
                        }
                    }
                    else
                    {
                        break;
                    }
                    topTwentyPrinted++;
                }
                txtWriter.Write("</table>\r\n" +
                                "</td>\r\n" +
                                "<td valign=\"top\"; width=\"200\">\r\n");
                txtWriter.WriteLine("<p> Total number of tweets: {0}</p>",totalTweets);
                txtWriter.WriteLine("<p> Total unique tweets: {0}</p>",totalUniqueTweets);
                /*****************************************************************************
                * needs exception handling due to possibility of divide by zero excpetion when 
                * dealing with a file with nothing but empty lines
                * ****************************************************************************/
                try
                {
                    txtWriter.WriteLine("<p> Average number of characters: {0}</p>", totalChars / totalTweets);
                }
                catch (DivideByZeroException)
                {
                    Console.WriteLine("Error tried to divide by zero, file cannot consist of only empty lines");
#if TEST
                    logWriter.WriteLine("Divide by zero exception caught, blank file read");
                    logWriter.Close();
#endif
                    return;
                }
                txtWriter.WriteLine("</tr>\r\n" +
                                    "</table>\r\n" +
                                    "</html>\r\n");
                txtWriter.Close();
#if TEST
                logWriter.WriteLine("file created successfully");
                logWriter.Close();
#endif
  
                //creates a file info object to hold the absolute path of the file
                FileInfo file = new FileInfo("tweets.html");
                
                /* Creates a new internet explorer process and passes it the absolute
                 * path of the html file
                 */
                try
                {
                    System.Diagnostics.Process.Start(
                    "C:\\Program Files\\Internet Explorer\\IExplore.exe",
                    file.FullName);
                }
                catch(System.ComponentModel.Win32Exception)//deals with exception thrown when the browser exe isn't in program files
                {
                    Console.WriteLine("Error browser not found");
                    return;
                }

            }
        }
    }
