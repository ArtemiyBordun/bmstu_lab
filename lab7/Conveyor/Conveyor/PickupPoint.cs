using Conveyor.FileOperation;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Conveyor
{
    internal class PickupPoint
    {
        private readonly Config.PickupPoint _config;
        private readonly ConcurrentQueue<Order> _queue;
        private readonly Logger _logger;
        private readonly int _pointId;

        internal event EventHandler? orderFinished;

        internal PickupPoint(Config.PickupPoint config, int pointId, ConcurrentQueue<Order> queue, Logger logger)
        {
            _config = config;
            _pointId = pointId;
            _queue = queue;
            _logger = logger;
        }

        internal Task Start(CancellationToken token)
        {
            return Task.Run(async () =>
            {
                var rnd = new Random();
                while (!token.IsCancellationRequested)
                {
                    if (_queue.TryDequeue(out var order))
                    {
                        var delay = GetRandomTime(_config.BaseFrequency, _config.RandomFrequency, rnd);
                        await Task.Delay(TimeSpan.FromSeconds(delay), token);
                        _logger.Log($"{DateTime.Now} - Pickup Point {_pointId} delivered order {order.Id}");
                        orderFinished?.Invoke(this, EventArgs.Empty);
                    }
                }
            }, token);
        }

        private int GetRandomTime(int mean, int variance, Random rnd) => mean + rnd.Next(-variance, variance + 1);
}
}
