using System.Collections.Generic;

namespace Demographic
{
    public interface IFileReader
    {
        List<AgeGroup> ReadInitialAgeData();
        List<DeathRule> ReadDeathRules();
        
    }
    
}