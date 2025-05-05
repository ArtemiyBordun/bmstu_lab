using DatabaseContext;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using System.Numerics;
using ConsoleTables;

namespace Core
{
    public class SpecializationService
    {
        private readonly AppDbContext _context;
        public SpecializationService(AppDbContext context) 
        {
            _context = context;
        }

        public async Task<string> GetSpecializationById(int? id)
        {
            var specialization = await _context.Specializations
                .FirstOrDefaultAsync(d => d.Id == id);

            if (specialization == null)
            {
                throw new ArgumentException("Специализация с указанным ID не найдена");
            }

            return specialization.Name;
        }
        public void PrintAllSpecializations()
        {
            var specializations = _context.Specializations.ToList();
            var table = new ConsoleTable("ID", "Название");

            foreach (var specialization in specializations)
            {
                table.AddRow(specialization.Id, specialization.Name);
            }

            table.Write();
        }

        public async Task AddNewSpecialization(string name) 
        {
            if (await _context.Specializations.AnyAsync(s => s.Name == name))
            {
                throw new ArgumentException("Данная специальность уже существует");
            }
            else if (name.Length > 32)
            {
                throw new ArgumentException("Название специальности слишком длинное");
            }
            Specializations specialization = new Specializations
            {
                Name = name.Trim()
            };
            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                await _context.Specializations.AddAsync(specialization);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                if (ex.InnerException.Message.Contains("23505"))
                    throw new ArgumentException("Данная специальность уже существует");
                else if (ex.InnerException.Message.Contains("22001"))
                    throw new ArgumentException("Имя слишком длинное");
                else
                    throw new Exception($"Произошла ошибка: {ex.InnerException.Message}");
            }
        }

        public async Task UpdateSpecialization(int id, string? name)
        {
            var specialization = await _context.Specializations.FirstOrDefaultAsync(d => d.Id == id);
            if (specialization == null)
            {
                throw new ArgumentException("Специализация с указанным ID не найден");
            }

            var existingSpecialization = await _context.Specializations.FirstOrDefaultAsync(d => d.Name == name && d.Id != id);

            if (existingSpecialization != null)
            {
                throw new ArgumentException("Данная специальность уже существует.");
            }

            if (name.Length > 32)
                throw new ArgumentException("Новое названние слишком длинное");
            specialization.Name = name.Trim();

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Specializations.Update(specialization);
                await _context.SaveChangesAsync();

                await transaction.CommitAsync();
            }
            catch (Exception ex)
            {
                await transaction.RollbackAsync();
                if (ex.InnerException.Message.Contains("23505"))
                    throw new ArgumentException("Данная специальность уже существует");
            }
        }

        public async Task DeleteSpecialization(int id)
        {
            var specialization = await _context.Specializations.FirstOrDefaultAsync(d => d.Id == id);

            if (specialization == null)
            {
                throw new ArgumentException("Специализация с указанным ID не найдена");
            }

            using var transaction = await _context.Database.BeginTransactionAsync();
            try
            {
                _context.Specializations.Remove(specialization);
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
