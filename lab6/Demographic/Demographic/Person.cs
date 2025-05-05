using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    internal class Person
    {
        private int _age;
        internal event EventHandler? ChildBirth;
        internal Gender Sex { get; private set; }
        internal int BirthYear { get; private set; }
        internal int Age => _age;
        internal int? DeathYear { get; private set; }
        internal bool IsAlive { get { return DeathYear == null; } }

        private List<DeathRules> _deathRules;
        private IEngine _engine;
        internal Person(Gender sex, int birthYear, int age, IEngine engine, List<DeathRules> deathRules)
        {
            Sex = sex;
            BirthYear = birthYear;
            _age = age;
            _engine = engine;
            _engine.YearTick += Update;
            _deathRules = deathRules;
        }

        private void CheckDead()
        {
            for (int i = 0; i < _deathRules.Count; i++)
            {
                if (_age >= _deathRules[i].StartAge && _age <= _deathRules[i].EndAge)
                {
                    if (Sex == Gender.Male && ProbabilityCalculator.IsEventHappened(_deathRules[i].ProbabilityDeathMale))
                    {
                        DeathYear = _engine.Current;
                        Unsubscribe();
                    }
                    else if (Sex == Gender.Female && ProbabilityCalculator.IsEventHappened(_deathRules[i].ProbabilityDeathFemale))
                    {
                        DeathYear = _engine.Current;
                        Unsubscribe();
                    }
                    break;
                }
            }
        }

        private void CheckBirthChild()
        {
            if (Sex == Gender.Female && ProbabilityCalculator.IsEventHappened(_engine.ProbabilityBirth))
            {
                ChildBirth?.Invoke(this, EventArgs.Empty);
            }
        }

        internal void Unsubscribe()
        {
            //_engine.YearTick -= Update;     // Слишком долго........
        }

        internal void Update(object? sender, EventArgs e)
        {
            if (IsAlive)
            {
                _age++;
                CheckBirthChild();
                CheckDead(); 
            }
        }
    }
}
