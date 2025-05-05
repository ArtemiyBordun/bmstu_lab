using Demographic.FileOperations;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    internal class GetInfoFromFile
    {
        internal GetInfoFromFile(ref string[] userArgs, ref string[] appArgs)
        {
            FileReader.ReadConfig(ref userArgs, ref appArgs);
        }
        internal GetInfoFromFile(string pathIntialAge, ref List<AgeData> ageData, string pathDeathRules, ref List<DeathRules> deathData) 
        {
            List<double[]> intialAge = FileReader.ReadFileCsv(pathIntialAge);
            List<double[]> deathRules = FileReader.ReadFileCsv(pathDeathRules);
            TranslateToAgeDataList(intialAge, ref ageData);
            TranslateToDeathRulesList(deathRules, ref deathData);
        }

        private void TranslateToAgeDataList(List<double[]> intialAge, ref List<AgeData> ageData)
        {
            for (int i = 0; i < intialAge.Count; i++)
            {
                var data = new AgeData { 
                    Age = Convert.ToInt32(intialAge[i][0]), 
                    Population = intialAge[i][1] 
                };
                ageData.Add(data);   
            }
        }

        private void TranslateToDeathRulesList(List<double[]> deathRules, ref List<DeathRules> listDeathRules)
        {
            for (int i = 0; i < deathRules.Count; i++)
            {
                var data = new DeathRules { 
                    StartAge = Convert.ToInt32(deathRules[i][0]), 
                    EndAge = Convert.ToInt32(deathRules[i][1]), 
                    ProbabilityDeathMale = deathRules[i][2],
                    ProbabilityDeathFemale = deathRules[i][3]
                };
                listDeathRules.Add(data);
            }
        }
    }
}
