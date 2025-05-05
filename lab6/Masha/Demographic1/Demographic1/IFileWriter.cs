using System.Collections.Generic;

namespace Demographic
{
    public interface IFileWriter
    {
        void WritePopulationData(List<Person> people);
    }
}