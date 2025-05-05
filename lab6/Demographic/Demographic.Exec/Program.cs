using Demographic;
using System;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        IEngine engine = new Engine();  // Запуск симуляции
        engine.StartSimulation();
    }
}