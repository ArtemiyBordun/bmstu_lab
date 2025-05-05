using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic.FileOperations
{
    public class Config
    {
        public UserParameters? UserParameters { get; set; }
        public AppParameters? AppParameters { get; set; }
    }

    public class UserParameters
    {
        public string PathInitialAge { get; set; }
        public string PathDeathRules { get; set; }
        public int StartYear { get; set; }
        public int EndYear { get; set; }
        public long OriginalPopulation { get; set; }
    }

    public class AppParameters
    {
        public int Scale { get; set; }
        public double ProbabilityBirth { get; set; }
        public double ProbabilityBirthGender { get; set; }
    }
}
