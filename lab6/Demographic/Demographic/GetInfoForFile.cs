using Demographic.FileOperations;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    internal static class GetInfoForFile
    {
        internal static void TranslateList(List<Person> people)
        {
            var data = new List<string[]>();
            for (int i = 0; i < people.Count; i++)
            {
                data.Add(new string[] {
                    i.ToString(),
                    people[i].Sex.ToString(), 
                    people[i].BirthYear.ToString(), 
                    people[i].DeathYear.ToString()
                });
            }
            FileOutput.WriteFile(data);
        }

        internal static void OutputError(string error) 
        {
            FileOutput.WriteError(error);
        }
    }
}
