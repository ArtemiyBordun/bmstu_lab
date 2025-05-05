using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DatabaseModels
{
    public class Certificate
    {
        public int Id { get; set; }
        public int DoctorId { get; set; }
        public Doctors? Doctor { get; set; }
        public string? Descriprion { get; set; }
        public DateTime? Date { get; set; }
    }
}
