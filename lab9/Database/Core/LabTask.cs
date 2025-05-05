using DatabaseContext;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core
{
    public class LabTask
    {
        private readonly AppDbContext _context;

        public LabTask(AppDbContext context)
        {
            _context = context;
        }

        public async Task<int> GetDoctorsCountBySpecializationId(int specializationId)
        {
            return await _context.Doctors.CountAsync(d => d.SpecializationId == specializationId);
        }

        public string? GetSpecializationNameByCertificateId(int certificateId)
        {
            var certificate = _context.Certificate.FirstOrDefault(c => c.Id == certificateId);
            if (certificate == null)
            {
                throw new ArgumentException("Сертификат с указанным ID не найден");
            }
            var specializationName = _context.Certificate
                .Include(c => c.Doctor) 
                .ThenInclude(d => d.Specialization)
                .Where(c => c.Id == certificateId)
                .Select(c => c.Doctor!.Specialization!.Name)
                .FirstOrDefault();

            return specializationName;
        }

        public DateTime? GetLatestCertificateDateByDoctorId(int doctorId)
        {
            var doctor = _context.Doctors.FirstOrDefault(d => d.Id == doctorId);

            if (doctor == null)
            {
                throw new ArgumentException("Доктор с указанным ID не найден");
            }
            return _context.Certificate
                .Where(c => c.DoctorId == doctorId)
                .OrderByDescending(c => c.Date)
                .Select(c => c.Date)
                .FirstOrDefault();
        }
    }
}
