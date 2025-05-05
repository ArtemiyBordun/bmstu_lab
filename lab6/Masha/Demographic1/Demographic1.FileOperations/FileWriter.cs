using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Demographic.FileOperations
{
    public class FileWriter : IFileWriter
    {
        private string _outputFilePath;

        public FileWriter(string outputFilePath)
        {
            _outputFilePath = outputFilePath;
        }
        
        public void WritePopulationData(List<Person> people)
        {
            using (var writer = new StreamWriter(_outputFilePath, false))
            {
                if (new FileInfo(_outputFilePath).Length == 0)
                {
                    writer.WriteLine("gender,birth_year,death_year");
                }

                foreach (var person in people)
                {
                    writer.WriteLine($"{person.Gender},{person.BirthYear},{person.DeathYear}");
                    
                }
            }
        }
    }
}