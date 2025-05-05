using ConsoleTables;
using DatabaseContext;
using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Core
{
    public class CertificateService
    {
        private readonly AppDbContext _context;

        public CertificateService(AppDbContext context)
        {
            _context = context;
        }

        public async Task<string> GetCertificateById(int id)
        {
            var certificate = await _context.Certificate
                .FirstOrDefaultAsync(d => d.Id == id);

            if (certificate == null)
            {
                throw new ArgumentException("Сертификат с указанным ID не найдена");
            }

            return certificate.Descriprion;
        }

        public async Task<int> GetCertificateDoctorId(int id)
        {
            var certificate = await _context.Certificate
                .FirstOrDefaultAsync(d => d.Id == id);

            if (certificate == null)
            {
                throw new ArgumentException("Сертификат с указанным ID не найдена");
            }

            return certificate.DoctorId;
        }

        public void PrintAllCertificates()
        {
            var certificates = _context.Certificate.Include(d => d.Doctor).ToList();
            var table = new ConsoleTable("ID", "Id врача", "Имя врача", "Описание", "Дата выдачи");

            foreach (var certificate in certificates)
            {
                table.AddRow(certificate.Id, certificate.Doctor?.Id, certificate.Doctor?.Name, certificate.Descriprion, certificate.Date.Value.ToShortDateString());
            }

            table.Write();
        }

        public async Task AddNewCertificate(int doctorId, string descriprion, DateTime date)
        {
            if (descriprion.Length > 128)
            {
                throw new ArgumentException("Описание сертификата слишком длинное");
            }
            Certificate certificate = new Certificate
            {
                DoctorId = doctorId,
                Descriprion = descriprion.Trim(),
                Date = DateTime.SpecifyKind(date.Date, DateTimeKind.Utc)
            };
            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                await _context.Certificate.AddAsync(certificate);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                if (ex.InnerException.Message.Contains("22001"))
                    throw new ArgumentException("Описание сертификата слишком длинное");
                else
                    throw new Exception($"Произошла ошибка: {ex.InnerException.Message}");
            }
        }
        public async Task UpdateCertificate(int id, int? newDoctorId = null, string? newDescription = null, DateTime? newDate = null)
        {
            var certificate = await _context.Certificate.FirstOrDefaultAsync(c => c.Id == id);

            if (certificate == null)
            {
                throw new ArgumentException("Сертификат с указанным ID не найден");
            }

            if (newDoctorId != null && newDoctorId.HasValue)
            {
                var doctorExists = await _context.Doctors.AnyAsync(d => d.Id == newDoctorId.Value);
                if (!doctorExists)
                {
                    throw new ArgumentException("Доктор с указанным ID не найден");
                }

                certificate.DoctorId = newDoctorId.Value;
            }

            if (!string.IsNullOrWhiteSpace(newDescription))
            {
                if (newDescription.Length > 128)
                {
                    throw new ArgumentException("Новое описание сертификата слишком длинное");
                }
                certificate.Descriprion = newDescription.Trim();
            }

            if (newDate != null && newDate.HasValue)
            {
                certificate.Date = DateTime.SpecifyKind(newDate.Value, DateTimeKind.Utc);
            }

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Certificate.Update(certificate);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                throw new Exception("Произошла ошибка при обновлении сертификата", ex);
            }
        }
        public async Task DeleteCertificate(int id)
        {
            var certificate = await _context.Certificate.FirstOrDefaultAsync(d => d.Id == id);

            if (certificate == null)
            {
                throw new ArgumentException("Сертификат с указанным ID не найдена");
            }

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Certificate.Remove(certificate);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                throw new Exception("Произошла ошибка при удалении записи", ex);
            }
        }
    }
}
