using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using DatabaseModels;
using DatabaseContext;
using ConsoleTables;

namespace Core
{
    public class DoctorService
    {
        private readonly AppDbContext _context;

        public DoctorService(AppDbContext context)
        {
            _context = context;
        }

        public async Task<string> GetDoctorNameById(int id)
        {
            var doctor = await _context.Doctors.FirstOrDefaultAsync(d => d.Id == id);

            if (doctor == null)
            {
                throw new ArgumentException("Доктор с указанным ID не найден");
            }

            return doctor.Name;
        }
        public async Task<int> GetDoctorSpecialById(int? id)
        {
            var doctor = await _context.Doctors.FirstOrDefaultAsync(d => d.Id == id);

            if (doctor == null)
            {
                throw new ArgumentException("Доктор с указанным ID не найден");
            }

            return doctor.SpecializationId;
        }

        public async Task AddNewDoctor(string name, int specializationsId)
        {
            if (!await _context.Specializations.AnyAsync(s => s.Id == specializationsId))
            {
                throw new ArgumentException("Специализация с указанным ID не найдена");
            }
            else if (name.Length > 32)
            {
                throw new ArgumentException("Имя слишком длинное");
            }
            var doctor = new Doctors
            {
                Name = name.Trim(),
                SpecializationId = specializationsId
            };
            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                await _context.Doctors.AddAsync(doctor);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                if (ex.InnerException.Message.Contains("22001"))
                    throw new ArgumentException("Имя слишком длинное");
                else
                    throw new Exception($"Произошла ошибка: {ex.InnerException.Message}");
            }

        }

        public async Task DeleteDoctorById(int id)
        {
            var doctor = await _context.Doctors.FirstOrDefaultAsync(d => d.Id == id);

            if (doctor == null)
            {
                throw new ArgumentException("Доктор с указанным ID не найден");
            }

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Doctors.Remove(doctor);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                throw new Exception("Произошла ошибка при удалении записи", ex);
            }
        }

        public async Task UpdateDoctorAsync(int id, string? newName = null, int? newSpecializationId = null)
        {
            var doctor = await _context.Doctors.FirstOrDefaultAsync(d => d.Id == id);

            if (doctor == null)
            {
                throw new ArgumentException("Доктор с указанным ID не найден");
            }

            if (newSpecializationId != null && newSpecializationId.HasValue)
            {
                var specializationExists = await _context.Specializations.AnyAsync(s => s.Id == newSpecializationId.Value);
                if (!specializationExists)
                {
                    throw new ArgumentException("Специализация с указанным ID не найдена");
                }

                doctor.SpecializationId = newSpecializationId.Value;
            }

            if (!string.IsNullOrWhiteSpace(newName))
            {
                if (newName.Length > 32)
                    throw new ArgumentException("Новое имя слишком длинное");
                doctor.Name = newName.Trim();
            }

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Doctors.Update(doctor);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                throw new Exception("Произошла ошибка при обновлении данных", ex);
            }
        }
        public void PrintAllDoctors()
        {
            var doctors = _context.Doctors.Include(d => d.Specialization).Include(d => d.Certificates).ToList();
            var table = new ConsoleTable("ID", "Имя", "Специализация", "Кол-во сертификатов");

            foreach (var doctor in doctors)
            {
                table.AddRow(doctor.Id, doctor.Name, doctor.Specialization?.Name, doctor.Certificates?.Count ?? 0);
            }

            table.Write();
        }
    }

}
