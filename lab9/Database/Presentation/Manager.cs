using DatabaseContext;
using Presentation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core
{
    public class Manager
    {
        private readonly AppDbContext? _context;

        private DoctorRepository _doctor;
        private SpecializationsRepository _specialization;
        private CertificateRepository _certificate;
        private LabTaskRepository _labTask;

        public Manager(AppDbContext context)
        {
            _context = context;

            _doctor = new DoctorRepository(_context);
            _specialization = new SpecializationsRepository(_context);
            _certificate = new CertificateRepository(_context);
            _labTask = new LabTaskRepository(_context);
        }
        public async Task RunMenu()
        {
            while (true)
            {
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("1. Добавить");
                Console.WriteLine("2. Изменить");
                Console.WriteLine("3. Удалить");
                Console.WriteLine("4. Вывести");
                Console.WriteLine("5. Задание лабораторной");
                Console.WriteLine("0. Выйти");
                
                string? choice = Console.ReadLine();

                switch (choice)
                {
                    case "1":
                        await AddMenu();
                        break;
                    case "2":
                        await UpdateMenu();
                        break;
                    case "3":
                        await DeleteMenu();
                        break;
                    case "4":
                        PrintMenu();
                        break;
                    case "5":
                        await LabTaskMenu();
                        break;
                    case "0":
                        return;
                    default:
                        Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                        break;
                }
            }
        }

        private async Task AddMenu()
        {
            Console.WriteLine("Добавить:");
            Console.WriteLine("1. Специализацию");
            Console.WriteLine("2. Врача");
            Console.WriteLine("3. Сертификат");
            string? choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    await _specialization.AddSpecialization();
                    break;
                case "2":
                    await _doctor.AddDoctor();
                    break;
                case "3":
                    await _certificate.AddCertificate();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;

            }
        }

        private async Task UpdateMenu()
        {
            Console.WriteLine("Изменить:");
            Console.WriteLine("1. Специализацию");
            Console.WriteLine("2. Врача");
            Console.WriteLine("3. Сертификат");
            string? choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    await _specialization.UpdateSpecialization();
                    break;
                case "2":
                    await _doctor.UpdateDoctors();
                    break;
                case "3":
                    await _certificate.UpdateCertificate();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;

            }
        }

        private async Task DeleteMenu()
        {
            Console.WriteLine("Удалить:");
            Console.WriteLine("1. Специализацию");
            Console.WriteLine("2. Врача");
            Console.WriteLine("3. Сертификат");
            string? choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    await _specialization.DeleteSpecialization();
                    break;
                case "2":
                    await _doctor.DeleteDoctor();
                    break;
                case "3":
                    await _certificate.DeleteCertificate();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;

            }
        }

        private void PrintMenu()
        {
            Console.WriteLine("Вывести:");
            Console.WriteLine("1. Специализацию");
            Console.WriteLine("2. Врача");
            Console.WriteLine("3. Сертификат");
            Console.WriteLine("4. Все");
            string? choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    _specialization.PrintAll();
                    break;
                case "2":
                    _doctor.PrintAll();
                    break;
                case "3":
                    _certificate.PrintAll();
                    break;
                case "4":
                    PrintAll();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;
            }
        }
        private void PrintAll()
        {
            _specialization.PrintAll();
            _doctor.PrintAll();
            _certificate.PrintAll();
        }
        private async Task LabTaskMenu()
        {
            Console.WriteLine("Задания:");
            Console.WriteLine("1. Сколько всего врачей обладают специализацией с заданным идентификатором?");
            Console.WriteLine("2. Как называется специализация (Name), по которой выдан сертификат с заданным идентификатором?");
            Console.WriteLine("3. Когда был выдан (Date) хронологически последний сертификат для врача с заданным идентификатором?");
            string? choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    await _labTask.CountDoctorWithSpecialization();
                    break;
                case "2":
                    _labTask.SpecializationByCertificate();
                    break;
                case "3":
                    await _labTask.LatestCertificateDateByDoctorId();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор. Попробуйте снова.");
                    break;
            }
        }
    }

}
