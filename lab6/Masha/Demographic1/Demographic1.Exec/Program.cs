using System;
using System.Data.SqlClient;
using System.IO;
using Demographic.FileOperations;

namespace Demographic.Exec
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            if (args.Length != 5)
            {
                Console.WriteLine("Usage: Demographic.Exec.exe <connection string>");
            }
            
            string ageFileName = args[0];//
            string deathFileName = args[1];
            int startYear = Convert.ToInt32(args[2]);//
            int endYear = Convert.ToInt32(args[3]);
            long initialPopulation = Convert.ToInt64(args[4]);
            
            
            IFileReader fileReader = new FileReader(ageFileName, deathFileName);
            IFileWriter fileWriter = new FileWriter(GeneralInfo.OutputFile);
            
            IEngine engine = new Engine(fileReader, fileWriter, initialPopulation, startYear);
            
            engine.StartModeling(startYear, endYear);
        }
    }
}