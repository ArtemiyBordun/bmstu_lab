using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.PortableExecutable;
using System.Security.Cryptography;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Demographic.FileOperations;

namespace Demographic
{
    public class Engine : IEngine
    {
        private string _pathIntialAge;
        private string _pathDeathRules;
        private int _year;
        private int _endYear;
        private int _population;
        private int _scale;
        private bool _error;

        private int _currentYear;
        public int Current => _currentYear;
        public double ProbabilityBirth { get; private set; }
        private double _probabilityBirthGender;

        private List<AgeData> _ageData;
        private List<DeathRules> _deathRules;
        private List<Person> _people;

        public event EventHandler? YearTick;
        public Engine() 
        {
            _people = new List<Person>();
            _ageData = new List<AgeData>();
            _deathRules = new List<DeathRules>();

            try
            {
                string[] userArgs = new string[5];
                string[] appArgs = new string[3];
                GetInfoFromFile readConfig = new GetInfoFromFile(ref userArgs, ref appArgs);
                CheckParameters check = new CheckParameters(userArgs, appArgs);

                SetUserParameters(userArgs);
                SetAppParameters(appArgs);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                GetInfoForFile.OutputError(ex.Message);
                _error = true;
                return;
            }
            _currentYear = _year;
            InitializePeople();
            Console.WriteLine(_people.Count);
        }

        private void SetUserParameters(string[] args)
        {
            string pathIntialAge = args[0];
            string pathDeathRules = args[1];

            GetInfoFromFile readFile = new GetInfoFromFile(pathIntialAge, ref _ageData, pathDeathRules, ref _deathRules);

            _year = Convert.ToInt32(args[2]);
            _endYear = Convert.ToInt32(args[3]);
            _population = Convert.ToInt32(args[4]);

        }
        private void SetAppParameters(string[] args)
        {
            _scale = Convert.ToInt32(args[0]);
            ProbabilityBirth = Convert.ToDouble(args[1]);
            _probabilityBirthGender = Convert.ToDouble(args[2]);
        }
        private void InitializePeople()
        {
            double totalPopulationPerThousand = _population / _scale;
            for (int i = 0; i < _ageData.Count; i++)
            {
                int age = _ageData[i].Age;
                double population = _ageData[i].Population / _scale;
                int actualPopulation = Convert.ToInt32(population * totalPopulationPerThousand);

                //Console.WriteLine("Процесс для " + age + " завершен");

                for (int j = 0; j < actualPopulation / 2; j++)
                {
                    AddPerson(Gender.Male, _currentYear - age, age, _deathRules);
                    AddPerson(Gender.Female, _currentYear - age, age, _deathRules);
                }
            }
            Subscribe();
        }

        private void AddPerson(Gender gender, int birthYear, int age, List<DeathRules> deathRules)
        {
            _people.Add(new Person(gender, birthYear, age, this, deathRules));
        }

        private void Subscribe()
        {
            for (int i = 0; i < _people.Count; i++)
            {
                if (_people[i].Sex == Gender.Female)
                    _people[i].ChildBirth += OnChildBirth;
            }
        }
        private void Unsubscribe()
        {
            for (int i = 0; i < _people.Count; i++)
            {
                if (_people[i].Sex == Gender.Female)
                    _people[i].ChildBirth -= OnChildBirth;
            }
        }
        private void OnChildBirth(object? sender, EventArgs e)
        {
            Gender childGender = ProbabilityCalculator.IsEventHappened(_probabilityBirthGender) ? Gender.Female : Gender.Male;
            AddPerson(childGender, _currentYear, 0, _deathRules);

            var newChild = _people.Last();
            if (newChild.Sex == Gender.Female)
                newChild.ChildBirth += OnChildBirth; //Подписываем детей на возможность иметь детей (да это плохо)
        }
        public void StartSimulation()
        {
            if (_error)
                return;
            for (int i = _year; i <= _endYear; i++, _currentYear++)
            {
                //Console.WriteLine("Наступил новый год");
                YearTick?.Invoke(this, EventArgs.Empty);

            }

            PrintResult();

            Unsubscribe();
            GetInfoForFile.TranslateList(_people);
        }
        private void PrintResult()
        {
            Console.WriteLine($"Population Famele: {_people.Count(p => p.IsAlive && p.Sex == Gender.Female && p.Age >= 18 && p.Age <= 45)}");
            Console.WriteLine($"Population: {_people.Count - _people.Count(p => !p.IsAlive)}");
            Console.WriteLine($"Alive: {_people.Count(p => p.IsAlive)}");
            Console.WriteLine($"Dead: {_people.Count(p => !p.IsAlive)}");
            Console.WriteLine($">65: {_people.Count(p => p.IsAlive && p.Age > 65)}");
            Console.WriteLine($"male: {_people.Count(p => p.IsAlive && p.Sex == Gender.Male && p.Age < 16)}");
        }
    }
}
