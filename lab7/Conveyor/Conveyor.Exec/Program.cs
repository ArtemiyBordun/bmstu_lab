using System;
using System.Collections.Concurrent;
using System.IO;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;

using Conveyor.FileOperation;
using Conveyor.Config;
using Conveyor;

class Program
{
    static async Task Main(string[] args)
    {
        Controller controller = new Controller();
        await controller.Start();
    }
}
