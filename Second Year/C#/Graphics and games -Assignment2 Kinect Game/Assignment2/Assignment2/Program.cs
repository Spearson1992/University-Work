using System;

namespace Assignment2
{
#if WINDOWS || XBOX
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            using (Assignment2 game = new Assignment2())
            {
                game.Run();
            }
        }
    }
#endif
}

