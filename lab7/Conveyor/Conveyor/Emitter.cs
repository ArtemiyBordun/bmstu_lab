using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Conveyor.Config;
using Conveyor.FileOperation;

namespace Conveyor
{
    internal class Emitter
    {

        private readonly Person _config;
        private readonly ConcurrentQueue<Order> _queue;
        private readonly Logger _logger;
        private readonly int _userId;
        int userId { get; set; }

        internal event EventHandler? orderCreated;

        public Emitter(Person config, int userId, ConcurrentQueue<Order> queue, Logger logger)
        {
            _config = config;
            _userId = userId;
            _queue = queue;
            _logger = logger;
        }

        public Task Start(CancellationToken token)
        {
            return Task.Run(async () =>
            {
                var rnd = new Random();
                while (!token.IsCancellationRequested)
                {
                    var delay = GetRandomTime(_config.BaseFrequency, _config.RandomFrequency, rnd);
                    await Task.Delay(TimeSpan.FromSeconds(delay), token);
                    var order = new Order { Id = Guid.NewGuid(), UserId = _userId };
                    _queue.Enqueue(order);
                    _logger.Log($"{DateTime.Now} - User {_userId} generated order {order.Id}");
                    orderCreated?.Invoke(this, EventArgs.Empty);
                }
            }, token);
        }

        private int GetRandomTime(int mean, int variance, Random rnd) => mean + rnd.Next(-variance, variance + 1);
    }
}
