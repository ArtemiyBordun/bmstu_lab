using System;

namespace Demographic
{
    public interface IEngine
    {
        void StartModeling(int startYear, int endYear);
        event EventHandler YearTicked; // событие которое уведомляет что наступил новый год
        
    }
}