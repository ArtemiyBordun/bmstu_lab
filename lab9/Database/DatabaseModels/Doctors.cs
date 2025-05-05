namespace DatabaseModels
{
    public class Doctors
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public int SpecializationId { get; set; }
        public Specializations? Specialization { get; set; }
        public ICollection<Certificate>? Certificates { get; set; } //Потом удалить
    }
}