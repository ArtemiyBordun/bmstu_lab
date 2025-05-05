using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using Demographic;

namespace Demographic.FileOperations
{
    public class FileReader : IFileReader
    {
        private string _initialAgeFilePath;
        private string _deathRulesFilePath;

        public FileReader(string initialAgeFilePath, string deathRulesFilePath)
        {
            _initialAgeFilePath = initialAgeFilePath;
            _deathRulesFilePath = deathRulesFilePath;
        }
        public List<AgeGroup> ReadInitialAgeData()
        {
            var ageGroups = new List<AgeGroup>();
            var lines = File.ReadAllLines(_initialAgeFilePath);

            for (int i = 1; i < lines.Length; i++)
            {
                var line = lines[i];
                var cols = line.Split(new[] { ", " }, StringSplitOptions.None);
                int age = int.Parse(cols[0]);
                double population = Convert.ToDouble(cols[1], CultureInfo.InvariantCulture);
                ageGroups.Add(new AgeGroup(age, population));
            }
            return ageGroups;
        }

        public List<DeathRule> ReadDeathRules()
        {
            var deathRules = new List<DeathRule>();
            var lines = File.ReadAllLines(_deathRulesFilePath);

            foreach (var line in lines.Skip(1))
            {
                var cols = line.Split(new[] { ", " }, StringSplitOptions.None);
                int startAge = Convert.ToInt32(cols[0]);
                int endAge = Convert.ToInt32(cols[1]);
                double maleDeathRate = Convert.ToDouble(cols[2], CultureInfo.InvariantCulture);
                double femaleDeathRate = Convert.ToDouble(cols[3], CultureInfo.InvariantCulture);
                deathRules.Add(new DeathRule(startAge, endAge, maleDeathRate, femaleDeathRate));
            }
            return deathRules;
        }
    }
}