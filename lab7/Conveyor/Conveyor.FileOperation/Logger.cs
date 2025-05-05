using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Conveyor.FileOperation
{
    public class Logger
    {
        private readonly string _logPath;
        private readonly object _lock = new();

        public Logger(string logPath)
        {
            _logPath = logPath;
        }

        public void Log(string message)
        {
            lock (_lock)
            {
                Console.WriteLine(message);
                File.AppendAllText(_logPath, message + Environment.NewLine);
            }
        }
    }
}
