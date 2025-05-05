using Core;
using DatabaseContext;
using DatabaseModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Presentation
{
    internal class SpecializationsRepository
    {
        private SpecializationService _service;
        private AppDbContext _context;

        internal SpecializationsRepository(AppDbContext context)
        {
            _context = context;
            _service = new SpecializationService(_context);
        }

        internal async Task AddSpecialization()
        {
            _service.PrintAllSpecializations();
            Console.WriteLine("Введите название специальности:");
            string? specialization = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(specialization))
            {
                Console.WriteLine("Специальность не может быть пустой.");
                return;
            }

            try
            {
                await _service.AddNewSpecialization(specialization);
                Console.WriteLine($"Добавлена специальность: {specialization}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при добавлении специальности: {ex.Message}");
            }
        }

        internal async Task UpdateSpecialization()
        {
            _service.PrintAllSpecializations();
            Console.WriteLine("Введите id специальности для обновления:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id");
                return;
            }
            Console.WriteLine("Введите новое название специальности:");
            string specialization = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(specialization))
            {
                Console.WriteLine("Специальность не может быть пустой.");
                return;
            }
            try
            {
                await _service.UpdateSpecialization(id, specialization);
                Console.WriteLine($"Данные о специальности {id} обновлены: {specialization}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при изменение специализации: {ex.Message}");
            }
        }
        internal async Task DeleteSpecialization()
        {
            _service.PrintAllSpecializations();

            Console.WriteLine("Введите id специальности для удаления:");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Console.WriteLine("Некорректный ввод id");
                return;
            }
            try
            {
                await _service.DeleteSpecialization(id);
                Console.WriteLine($"Специализация {id} удалена");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при удалении специализации: {ex.Message}");
            }
        }
        internal void PrintAll()
        {
            _service.PrintAllSpecializations();
        }
    }
}
