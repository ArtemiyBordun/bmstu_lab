using Conveyor.FileOperation;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Conveyor
{
    internal class Worker
    {
        private readonly Config.Worker _config;
        private readonly ConcurrentQueue<Order> _inputQueue;
        private readonly ConcurrentQueue<Order> _outputQueue;
        private readonly Logger _logger;
        private readonly int _workerId;

        internal event EventHandler? orderProcessed;

        public Worker(Config.Worker config, int workerId, ConcurrentQueue<Order> inputQueue, ConcurrentQueue<Order> outputQueue, Logger logger)
        {
            _config = config;
            _workerId = workerId;
            _inputQueue = inputQueue;
            _outputQueue = outputQueue;
            _logger = logger;
        }

        public Task Start(CancellationToken token)
        {
            return Task.Run(async () =>
            {
                var rnd = new Random();
                while (!token.IsCancellationRequested)
                {
                    if (_inputQueue.TryDequeue(out var order))
                    {
                        var delay = GetRandomTime(_config.BaseFrequency, _config.RandomFrequency, rnd);
                        await Task.Delay(TimeSpan.FromSeconds(delay), token);
                        _outputQueue.Enqueue(order);
                        _logger.Log($"{DateTime.Now} - Worker {_workerId} processed order {order.Id}");
                        orderProcessed?.Invoke(this, EventArgs.Empty);
                    }
                }
            }, token);
        }
        private int GetRandomTime(int mean, int variance, Random rnd) => mean + rnd.Next(-variance, variance + 1);
    }
}
