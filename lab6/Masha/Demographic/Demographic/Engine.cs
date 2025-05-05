using System;
using System.Collections.Generic;
using System.Linq;

namespace Demographic
{
    public class Engine : IEngine
    {
        private IFileReader _fileReader;
        private IFileWriter _fileWriter;
        
        private List<AgeGroup> _ageGroups;
        public List<DeathRule> _deathRules;
        
        public event EventHandler YearTicked;
        private List<Person> Population { get; set; } =  new List<Person>();
        
        public Engine(IFileReader fileReader, IFileWriter fileWriter, long totalPopulation, int currentYear)
        {
            _fileReader = fileReader;
            _fileWriter = fileWriter;
            
            _ageGroups = _fileReader.ReadInitialAgeData();
            _deathRules = _fileReader.ReadDeathRules();
            Person.SetDeathRules(_deathRules);
            
            InitializePopulation(_ageGroups, totalPopulation, currentYear);
        }
        

        public void StartModeling(int startYear, int endYear)
        {
            for (int year = startYear; year <= endYear; year++)
            {
                YearTicked?.Invoke(this, EventArgs.Empty);
            }
            _fileWriter.WritePopulationData(Population);

            Console.WriteLine($"Population: {Population.Count - Population.Count(p => !p.IsAlive)}");
            Console.WriteLine($"Alive: {Population.Count(p => p.IsAlive)}");
            Console.WriteLine($"Dead: {Population.Count(p => !p.IsAlive)}");
            Console.WriteLine($">65: {Population.Count(p => p.IsAlive && p.Age > 65)}");
            Console.WriteLine($"male: {Population.Count(p => p.IsAlive && p.Gender == "Male" && p.Age < 16)}");
        }

        private void InitializePopulation(List<AgeGroup> ageGroups, long totalPopulation, int currentYear)
        {
            Population.Clear();
            
            totalPopulation /= 1000;
            totalPopulation /= 1000;
            foreach (var ageGroup in ageGroups)
            {
                long peopleInGroup = (long)(totalPopulation * ageGroup.PopulationCount);
                for (int i = 0; i < peopleInGroup; i++)
                {
                    string gender = i % 2 == 0 ? "Male" : "Female";
                    var person = new Person(ageGroup.Age, gender, currentYear);
                    person.ChildBirth += HappenedChildBirth;
                    YearTicked += person.YearPassed;
                    Population.Add(person);
                }
            }
            Console.WriteLine($"Total Population: {Population.Count}");
            
        }
        private void HappenedChildBirth(object sender, EventArgs e)
        {
            var newChild = sender as Person;
            if (newChild != null)
            {
                Population.Add(newChild);
                newChild.ChildBirth += HappenedChildBirth;
                YearTicked += newChild.YearPassed;
            }
        }
    }
}