using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic
{
    internal class CheckParameters
    {
        public CheckParameters(string[] userParameters, string[] appParametrs) 
        {
            CheckUserParameters(userParameters);
            CheckAppParameters(appParametrs);
        }

        private void CheckUserParameters(string[] args)
        { 
            if (args.Length < 5)
                throw new ArgumentException("Ошибка: Количество параметров должно быть 5");

            int year, endYear, population;
            if (!Int32.TryParse(args[2], out year))
                throw new ArgumentException("Ошибка: Год начала моделирования введён неверно");
            if (!Int32.TryParse(args[3], out endYear))
                throw new ArgumentException("Ошибка: Год конца моделирования введён неверно");
            if (!Int32.TryParse(args[4], out population))
                throw new ArgumentException("Ошибка: Население слишком большое");

            if (endYear - year >= 100)
                throw new ArgumentException("Ошибка: Разница между годами моделирования слишком большая");
           
            if (year >= endYear) 
                throw new ArgumentException("Ошибка: Год окончания должен быть после года начала моделирования");
            if (population < 1000000)
                throw new ArgumentException("Ошибка: Население должно быть больше миллиона");
        }

        private void CheckAppParameters(string[] args)
        {
            int scale;
            double probability, probabilityGender;
            if (!Int32.TryParse(args[0], out scale))
                throw new ArgumentException("Ошибка: Масштабирование некорректное");
            if (!Double.TryParse(args[1], out probability))
                throw new ArgumentException("Ошибка: Вероятность смерти некорректная");
            if (!Double.TryParse(args[2], out probabilityGender))
                throw new ArgumentException("Ошибка: Вероятность выбора пола некорректная");

            if (scale < 1000 || scale >= 100000)
                throw new ArgumentException("Ошибка: Некоректный параметр масштабирования");

            if (probability <= 0 || probability >= 1)
                throw new ArgumentException("Ошибка: Некоректный параметр вероятности рождения ребенка");
            if (probabilityGender <= 0 || probabilityGender >= 1)
                throw new ArgumentException("Ошибка: Некоректный параметр вероятности выбора пола");

        }
    }
}
