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
                Population[1].PrintCurrent();
                if (year == 2021)
                    Console.WriteLine();
                YearTicked?.Invoke(this, EventArgs.Empty);
            }
            Console.WriteLine("huy");
            foreach (Person person in Population)
            {

            }


            _fileWriter.WritePopulationData(Population);
            Console.WriteLine("help " + Population.Count(p => p.IsAlive));
            Console.WriteLine("help " + Population.Count(p => p.IsAlive && p.Gender == "Female" && p.Age >= 18 && p.Age <= 45));
            Console.WriteLine("help " + Population.Count(p => p.IsAlive && p.Gender == "Female"));
            Console.WriteLine(Population.Count(p => p.IsAlive && p.BirthYear >= 2021));
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

        private void Unsubscribe(Person person)
        {
            person.ChildBirth -= HappenedChildBirth;
            YearTicked -= person.YearPassed;
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