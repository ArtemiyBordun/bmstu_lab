namespace Demographic
{
    public class DeathRule
    {
        public int AgeStart { get; set; }
        public int AgeEnd { get; set; }
        public double MaleDeathRate { get; set; }
        public double FemaleDeathRate { get; set; }

        public DeathRule(int ageStart, int ageEnd, double maleDeathRate, double femaleDeathRate)
        {
            AgeStart = ageStart;
            AgeEnd = ageEnd;
            MaleDeathRate = maleDeathRate;
            FemaleDeathRate = femaleDeathRate;
        }

        public double GetDeathRate(string gender, int age)
        {
            if (age >= AgeStart && age <= AgeEnd)
            {
                return gender == "Male" ? MaleDeathRate : FemaleDeathRate;
            }
            return 0.0;
        }
    }
}