using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    internal class DeathRules
    {
        public int StartAge { get; set; }
        public int EndAge { get; set; }
        public double ProbabilityDeathMale { get; set; }
        public double ProbabilityDeathFemale { get; set; }
    }
}
