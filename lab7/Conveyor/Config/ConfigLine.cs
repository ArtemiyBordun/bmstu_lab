namespace Conveyor.Config
{
    public class ConfigLine
    {
        public int MaxOrder { get; set; }
        public Person? Person {  get; set; }
        public Handler? Handler { get; set; }
    }
}
