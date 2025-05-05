namespace Demographic
{
    public class AgeGroup
    {
        public int Age {get; set;}
        public double PopulationCount {get; set;}

        public AgeGroup(int age, double populationCount)
        {
            Age = age;
            PopulationCount = populationCount;
        }
    }
}