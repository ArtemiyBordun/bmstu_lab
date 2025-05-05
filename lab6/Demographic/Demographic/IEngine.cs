using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    public interface IEngine
    {
        public event EventHandler YearTick;
        public int Current { get; }
        public double ProbabilityBirth { get; }
        public void StartSimulation();
    }
}
