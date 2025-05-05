using Core;
using DatabaseContext;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Presentation
{
    internal class DoctorRepository
    {
        private DoctorService _service;
        private AppDbContext _context;

        internal DoctorRepository(AppDbContext context)
        {
            _context = context;
            _service = new DoctorService(_context);
        }

        internal async Task AddDoctor()
        {
            Console.WriteLine("Введите имя врача:");
            string? name = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(name))
            {
                Console.WriteLine("Имя врача не может быть пустым.");
                return;
            }

            var specialization = new SpecializationService(_context);
            specialization.PrintAllSpecializations();
            Console.WriteLine("Введите его специальность (id):");
            if (!int.TryParse(Console.ReadLine(), out int specializationId))
            {
                Console.WriteLine("Некорректный ввод id специальности.");
                return;
            }

            try
            {
                await _service.AddNewDoctor(name, specializationId);
                string specializationName = await specialization.GetSpecializationById(specializationId);
                Console.WriteLine($"Добавлен врач: {name}, специальность: {specializationName}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при добавлении врача: {ex.Message}");
            }
        }

        internal async Task UpdateDoctors()
        {
            _service.PrintAllDoctors();

            Console.WriteLine("Введите врача, которого хотите изменить (id):");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id врача");
                return;
            }

            Console.WriteLine("Введите новое имя врача (enter, если не нужно):");
            string? name = Console.ReadLine();

            var specialization = new SpecializationService(_context);
            specialization.PrintAllSpecializations();
            Console.WriteLine("Введите его специальность (id) (enter, если не нужно):");
            string? input = Console.ReadLine();
            int? specializationId = null;

            if (!string.IsNullOrEmpty(input))
            {
                if (int.TryParse(input, out int parsedId))
                {
                    specializationId = parsedId;
                }
                else
                {
                    Console.WriteLine("Некорректный ввод id специальности");
                    return;
                }
            }
            try
            {
                await _service.UpdateDoctorAsync(id, name, specializationId);
                string specializationName = await specialization.GetSpecializationById(await _service.GetDoctorSpecialById(id));
                Console.WriteLine($"Данные о враче {id} обновлены: {await _service.GetDoctorNameById(id)}, специальность: {specializationName}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при обновлении врача: {ex.Message}");
            }
        }

        internal async Task DeleteDoctor()
        {
            _service.PrintAllDoctors();
            Console.WriteLine("Введите id врача:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id врача");
                return;
            }
            try
            {
                await _service.DeleteDoctorById(id);
                Console.WriteLine($"Врач {id} удален");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при удалении врача: {ex.Message}");
            }
        }

        internal void PrintAll()
        {
            _service.PrintAllDoctors();
        }
    }
}
