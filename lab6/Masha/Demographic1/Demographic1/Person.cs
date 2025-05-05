using System;
using System.Collections.Generic;
using System.Linq;

namespace Demographic
{
    public class Person
    {
        private static double _childBirthProbability = 0.2;
        private static double _genderProbability = 0.55;
        private static int _startBirthAge = 18;
        private static int _endBirthAge = 45;
        public string Gender { get; private set; }
        public int BirthYear { get; private set; } // почему приват
        public int Age { get; private set; }
        public bool IsAlive { get; private set; } = true;
        public int? DeathYear { get; private set; }
        public int CurrentYear { get; private set; }
        
        private static List<DeathRule> _deathRules;

        public event EventHandler ChildBirth;
        
        public Person(int age, string gender, int currentYear)
        {
            Gender = gender;
            Age = age;
            BirthYear = currentYear - age;
            DeathYear = null;
            CurrentYear = currentYear;
        }
        
        public static void SetDeathRules(List<DeathRule> deathRules)
        {
            _deathRules = deathRules;
        }

        public void YearPassed(object sender, EventArgs e)
        {
            var deathRule = _deathRules.FirstOrDefault(rule => Age >= rule.AgeStart && Age <= rule.AgeEnd);

            TryToGiveBirth(CurrentYear);
            if (deathRule != null)
            {
                TryToDie(deathRule, CurrentYear);  // Метод проверяет, жив ли человек в текущем году
            }
            AgeOneYear();
            CurrentYear++;
        }

        public void AgeOneYear()
        {
            if (IsAlive)
            {
                Age++;
            }
        }

        public void PrintCurrent()
        {
            Console.WriteLine(CurrentYear);
        }
        
        public void TryToDie(DeathRule deathRule, int currentYear)
        {
            if (!IsAlive) return;
            double deathProbability = Gender == "Male" ? deathRule.MaleDeathRate : deathRule.FemaleDeathRate;
            
            if (ProbabilityCalculator.IsEventHappened(deathProbability))
            {
                IsAlive = false;
                DeathYear = currentYear; 
            }
        }
        
        public void TryToGiveBirth(int currentYear)
        {
            if (IsAlive && Gender == "Female" && Age >= _startBirthAge && Age <= _endBirthAge)
            {
                if (ProbabilityCalculator.IsEventHappened(_childBirthProbability))
                {
                    string newChildGender = ProbabilityCalculator.IsEventHappened(_genderProbability) ? "Female" : "Male";
                    var newChild = new Person(0, newChildGender, currentYear);
                    ChildBirth?.Invoke(newChild, EventArgs.Empty);
                    if (currentYear >= 1980)
                        Console.WriteLine();
                }
            }
        }
    }
}