using Microsoft.EntityFrameworkCore;
using System.Numerics;
using DatabaseModels;

namespace DatabaseContext
{
    public class AppDbContext : DbContext
    {
        public DbSet<Doctors> Doctors { get; set; }
        public DbSet<Specializations> Specializations { get; set; }
        public DbSet<Certificate> Certificate { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql("Host=localhost;Port=5432;Database=lab7_db;Username=postgres;Password=111");
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Doctors>()
                .HasOne(d => d.Specialization)
                .WithMany(s => s.Doctors)
                .HasForeignKey(d => d.SpecializationId);

            modelBuilder.Entity<Certificate>()
                .HasOne(c => c.Doctor)
                .WithMany(d => d.Certificates)
                .HasForeignKey(c => c.DoctorId);
        }
    }
}
