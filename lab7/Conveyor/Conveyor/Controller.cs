using Conveyor.FileOperation;
using Conveyor.Config;
using System.Threading;
using System.Collections.Concurrent;

namespace Conveyor
{
    public class Controller
    {
        private CancellationTokenSource _cancellationTokenSource;
        private readonly Logger _logger;
        private readonly ConfigLine _config;

        private List<Emitter> _users;
        private List<Worker> _workers;
        private List<PickupPoint> _pickupPoints;

        private ConcurrentQueue<Order> _eventQueue;
        private ConcurrentQueue<Order> _pickupQueue;

        private int _countOrderFinished { get; set; }
        private int _countOrderCreated { get; set; }
        private int _countOrderProccesed { get; set; }

        public Controller()
        {
            _cancellationTokenSource = new CancellationTokenSource();
            _logger = new Logger("D:\\proga\\sem3\\lab7\\log.txt");
            _config = ReadConfig.ReadFile() ?? throw new Exception("Failed to load configuration.");

            _users = new List<Emitter>();
            _workers = new List<Worker>();
            _pickupPoints = new List<PickupPoint>();

            _eventQueue = new ConcurrentQueue<Order>();
            _pickupQueue = new ConcurrentQueue<Order>();
        }

        public async Task Start()
        {
            _logger.Log($"{DateTime.Now} - Simulation started.");

            var usersTask = new Task[_config.Person.Count];
            var workerTask = new Task[_config.Handler.Worker.Count];
            var pickupPointTask = new Task[_config.Handler.PickupPoint.Count];

            for (int i = 0; i < _config.Person.Count; i++)
            {
                _users.Add(new Emitter(_config.Person, i + 1, _eventQueue, _logger));
                usersTask[i] = _users[i].Start(_cancellationTokenSource.Token);
            }
            for (int i = 0; i < _config.Handler.Worker.Count; i++)
            {
                _workers.Add(new Worker(_config.Handler.Worker, i + 1, _eventQueue, _pickupQueue, _logger));
                workerTask[i] = _workers[i].Start(_cancellationTokenSource.Token);
            }
            for (int i = 0; i < _config.Handler.PickupPoint.Count; i++)
            {
                _pickupPoints.Add(new PickupPoint(_config.Handler.PickupPoint, i + 1, _pickupQueue, _logger));
                Subscribe();
                pickupPointTask[i] = _pickupPoints[i].Start(_cancellationTokenSource.Token);
            }
            Console.WriteLine("Press Enter to stop simulation...");
            Console.ReadLine();
            _cancellationTokenSource.Cancel();
            try
            {
                await Task.WhenAll(usersTask);
                await Task.WhenAll(workerTask);
                await Task.WhenAll(pickupPointTask);
            }
            catch (TaskCanceledException)
            {
                _logger.Log("Simulation stopped.");
            }

            _logger.Log($"Simulation completed. Orders left in queues: EventQueue = {_eventQueue.Count}, PickupQueue = {_pickupQueue.Count}\n" +
                $"Order is created {_countOrderCreated}, is proccesed {_countOrderProccesed}, is finished = {_countOrderFinished}");
        }
        private void Subscribe()
        {
            foreach (var user in _users)
            {
                user.orderCreated += AddCountCreated;
            }
            foreach (var worker in _workers) 
            {
                worker.orderProcessed += AddCountProcessed;
            }
            foreach (var point in _pickupPoints)
            {
                point.orderFinished += AddCountFinished;
            }
        }

        private void AddCountFinished(object? sender, EventArgs e)
        {
            _countOrderFinished++;
            if (_countOrderFinished >= _config.MaxOrder)
            {
                _logger.Log("Reached the maximum number of completed orders. Stopping simulation...");
                _cancellationTokenSource.Cancel();

            }
        }
        private void AddCountCreated(object? sender, EventArgs e)
        {
            _countOrderCreated++;
        }
        private void AddCountProcessed(object? sender, EventArgs e)
        {
            _countOrderProccesed++;
        }
    }
}
