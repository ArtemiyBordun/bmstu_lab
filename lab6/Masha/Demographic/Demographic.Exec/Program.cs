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
            string ageFileName = "D:\\proga\\sem3\\lab6\\InitialAge.csv"; 
            string deathFileName = "D:\\proga\\sem3\\lab6\\DeathRules.csv";
            int startYear = 1970; 
            int endYear = 2021;
            long initialPopulation = 130000000; 

            IFileReader fileReader = new FileReader(ageFileName, deathFileName);
            IFileWriter fileWriter = new FileWriter("D:\\proga\\sem3\\lab6\\populationInfo.csv");
            
            IEngine engine = new Engine(fileReader, fileWriter, initialPopulation, startYear);
            
            engine.StartModeling(startYear, endYear);
            
            
        }
    }
}