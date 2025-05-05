using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DatabaseModels
{
    public class Specializations
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public ICollection<Doctors>? Doctors { get; set; }
    }
}
