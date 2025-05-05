using Core;
using DatabaseContext;
using DatabaseModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Presentation
{
    internal class LabTaskRepository
    {
        private AppDbContext _context;
        private LabTask _task;
        internal LabTaskRepository(AppDbContext context)
        {
            _context = context;
            _task = new LabTask(_context);
        }

        internal async Task CountDoctorWithSpecialization()
        {
            var specialization = new SpecializationService(_context);
            specialization.PrintAllSpecializations();
            Console.WriteLine("Введите специальность (id) врача:");
            if (!int.TryParse(Console.ReadLine(), out int specializationId))
            {
                Console.WriteLine("Некорректный ввод id специальности");
                return;
            }
            try
            {
                Console.WriteLine($"Врачей со специальностью {await specialization.GetSpecializationById(specializationId)}: " +
                    $"{await _task.GetDoctorsCountBySpecializationId(specializationId)}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }

        }

        internal void SpecializationByCertificate() 
        {
            var certificate = new CertificateService(_context);
            certificate.PrintAllCertificates();
            Console.WriteLine("Введите сертификат (id) врача:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id сертификата");
                return;
            }
            try
            {
                Console.WriteLine($"Сертификат {id} был выдан врачу со специальностью: {_task.GetSpecializationNameByCertificateId(id)}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }
        }
        internal async Task LatestCertificateDateByDoctorId()
        {
            var doctor = new DoctorService(_context);
            doctor.PrintAllDoctors();
            Console.WriteLine("Введите id врача:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id врача");
                return;
            }

            try
            {
                var date = _task.GetLatestCertificateDateByDoctorId(id);
                Console.WriteLine($"Для врача {await doctor.GetDoctorNameById(id)} ({id}) последний сертификат был выдан: " +
                    $"{date.Value.ToShortDateString()}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }

        }
    }
}
