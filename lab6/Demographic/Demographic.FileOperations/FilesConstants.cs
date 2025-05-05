using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic.FileOperations
{
    internal static class FilesConstants
    {
        internal const string ConfigPath = "D:\\proga\\sem3\\lab6\\config.json";
        internal const long MaxSize = 1048576;    //В байтах

        internal const string HeaderInitialAge = "Возраст, Количество_на_1000";
        internal const string HeaderDeathRules = "Начальный_возраст, Конечный_возраст, Вероятность_смерти_муж, Вероятность_смерти_жен";
        internal const string HeaderPopuliation = "ID,Sex,Birth_Year,Death_Year";

        internal const string pathOutput = "Population.csv";
    }
}
