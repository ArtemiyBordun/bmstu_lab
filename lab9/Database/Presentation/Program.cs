using System;
using System.Collections.Generic;
using Core;
using DatabaseContext;
using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using Npgsql;
using ConsoleTables;
using Presentation;

class Program
{
    private static AppDbContext? _context;
    static async Task Main(string[] args)
    {
        _context = new AppDbContext();
        try
        {
            _context.Specializations.ToList();
        }
        catch 
        {
            Console.WriteLine("Ошибка подключения к базе данных");
            return;
        }
        Manager manager = new Manager(_context);

        await manager.RunMenu();
    }

}
