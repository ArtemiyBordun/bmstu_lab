using Core;
using DatabaseContext;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Presentation
{
    internal class CertificateRepository
    {
        private CertificateService _service;
        private AppDbContext _context;

        internal CertificateRepository(AppDbContext context)
        {
            _context = context;
            _service = new CertificateService(_context);
        }

        internal async Task AddCertificate()
        {
            var doctor = new DoctorService(_context);
            doctor.PrintAllDoctors();
            Console.WriteLine("Введите какому врачу (id) хотите добавить сертификат:");
            int doctorId = Convert.ToInt16(Console.ReadLine());

            Console.WriteLine("Введите описание:");
            string? descriprion = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(descriprion))
            {
                Console.WriteLine("Описание сертификата не может быть пустым");
                return;
            }

            Console.WriteLine("Введите когда был выдан сертификат (дд.мм.гггг):");
            string? input = Console.ReadLine();

            DateTime date;
            DateTime.TryParseExact(input, "dd.MM.yyyy", null, System.Globalization.DateTimeStyles.None, out date);

            try
            {
                await _service.AddNewCertificate(doctorId, descriprion, date);
                Console.WriteLine($"Добавлен сертификат: Врач - {await doctor.GetDoctorNameById(doctorId)} (Id - {doctorId})," +
                    $"\n\t{descriprion},\n\tот {date.ToString("dd.MM.yyyy")}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при добавлении сертификата: {ex.Message}");
            }
        }

        internal async Task UpdateCertificate()
        {
            _service.PrintAllCertificates();

            Console.WriteLine("Введите ID сертификата, который хотите изменить:");
            if (!int.TryParse(Console.ReadLine(), out int certificateId))
            {
                Console.WriteLine("Некорректный ввод ID сертификата.");
                return;
            }

            Console.WriteLine("Введите новый ID врача (enter, если не нужно):");
            string? doctorInput = Console.ReadLine();
            int? doctorId = null;

            if (!string.IsNullOrEmpty(doctorInput))
            {
                if (int.TryParse(doctorInput, out int parsedDoctorId))
                {
                    doctorId = parsedDoctorId;
                }
                else
                {
                    Console.WriteLine("Некорректный ввод ID врача.");
                    return;
                }
            }

            Console.WriteLine("Введите новое описание сертификата (enter, если не нужно):");
            string? description = Console.ReadLine();

            Console.WriteLine("Введите новую дату (yyyy-MM-dd) (enter, если не нужно):");
            string dateInput = Console.ReadLine();
            DateTime? date = null;

            if (!string.IsNullOrEmpty(dateInput))
            {
                if (DateTime.TryParse(dateInput, out DateTime parsedDate))
                {
                    date = parsedDate;
                }
                else
                {
                    Console.WriteLine("Некорректный ввод даты");
                    return;
                }
            }
            try
            {
                await _service.UpdateCertificate(certificateId, doctorId, description, date);

                var doctor = new DoctorService(_context);
                var doctorName = await doctor.GetDoctorNameById(await _service.GetCertificateDoctorId(certificateId));
                Console.WriteLine($"Сертификат {certificateId} обновлён: Доктор - {doctorName}, Описание - {description}, Дата - {date?.ToString("yyyy-MM-dd") ?? "не изменена"}.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при обновлении сертификата: {ex.Message}");
            }
        }

        internal async Task DeleteCertificate()
        {
            _service.PrintAllCertificates();

            Console.WriteLine("Введите id сертификата для удаления:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id");
                return;
            }
            try
            {
                await _service.DeleteCertificate(id);
                Console.WriteLine($"Сертификат {id} удалена");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при удалении сертификата: {ex.Message}");
            }
        }
        internal void PrintAll()
        {
            _service.PrintAllCertificates();
        }
    }
}
