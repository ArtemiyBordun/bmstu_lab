using System.IO;
using System.Reflection.PortableExecutable;
using System.Globalization;
using Newtonsoft.Json;
using System.Diagnostics;

namespace Demographic.FileOperations
{
    public static class FileReader
    {
        public static List<double[]> ReadFileCsv(string path)
        {
            path = CorrectionPath(path);

            StreamReader reader = CheckFileCsv(path);

            reader.DiscardBufferedData();
            reader.BaseStream.Seek(0, System.IO.SeekOrigin.Begin);  //возврат к началу

            var header = reader.ReadLine();

            if (header == FilesConstants.HeaderInitialAge)
                return ReadIntialAge(reader);
            else
                return ReadDeathRules(reader);
        }
        private static List<double[]> ReadIntialAge(StreamReader reader)
        {
            List<double[]> list = new List<double[]>();

            var lines = "";
            while ((lines = reader.ReadLine()) != null)
            {
                var line = lines.Split(", ");
                list.Add(AddNewLine(line));
            }

            return list;
        }
        private static List<double[]> ReadDeathRules(StreamReader reader)
        {
            List<double[]> list = new List<double[]>();

            var lines = "";
            while ((lines = reader.ReadLine()) != null)
            {
                var line = lines.Split(", ");
                list.Add(AddNewLine(line));
            }

            return list;
        }

        public static void ReadConfig(ref string[] userArgs, ref string[] appArgs)
        {
            string path = FilesConstants.ConfigPath;
            CheckConfigFile(path);
            string json = File.ReadAllText(path);
            Config? config = JsonConvert.DeserializeObject<Config>(json);

            string[] args = new string[6];

            userArgs[0] = config.UserParameters.PathInitialAge;
            userArgs[1] = config.UserParameters.PathDeathRules;
            userArgs[2] = config.UserParameters.StartYear.ToString();
            userArgs[3] = config.UserParameters.EndYear.ToString();
            userArgs[4] = config.UserParameters.OriginalPopulation.ToString();

            appArgs[0] = config.AppParameters.Scale.ToString();
            appArgs[1] = config.AppParameters.ProbabilityBirth.ToString();
            appArgs[2] = config.AppParameters.ProbabilityBirthGender.ToString();
        }

        private static string CorrectionPath(string path)
        {
            string newPath;
            newPath = path.Trim('\"');           //удаляем кавычки
            return newPath;
        }
        private static double[] AddNewLine(string[] lines)
        {
            double[] line = new double[lines.Length];
            for (int i = 0; i < lines.Length; i++)
            {
                line[i] = Convert.ToDouble(lines[i], CultureInfo.InvariantCulture);
            }
            return line;
        }
        private static StreamReader CheckFileCsv(string path)
        {
            FileInfo fileInfo = new FileInfo(path);
            if (!fileInfo.Exists)
                throw new ArgumentException($"Ошибка: Файл не найден");

            if (fileInfo.Length > FilesConstants.MaxSize)
                throw new ArgumentException("Ошибка: Файл слишком большой");

            if (fileInfo.Extension != ".csv")
                throw new ArgumentException("Ошибка: Формат файла должен быть .csv");

            StreamReader reader = new StreamReader(path);
            var header = reader.ReadLine();
            if (header == null)
                throw new ArgumentException("Ошибка: Файл пустой");
            else
            {
                if (header != FilesConstants.HeaderInitialAge && header != FilesConstants.HeaderDeathRules)
                    throw new ArgumentException("Ошибка: Данный файл не подходит для данной программы");
            }
            return reader;
        }

        private static void CheckConfigFile(string path)
        {
            FileInfo fileInfo = new FileInfo(path);
            if (!fileInfo.Exists)
                throw new ArgumentException($"Ошибка: Файл с конфигом не найден");

            if (fileInfo.Length > FilesConstants.MaxSize)
                throw new ArgumentException("Ошибка: Файл конфига слишком большой");

            if (fileInfo.Extension != ".json")
                throw new ArgumentException("Ошибка: Формат файла с конфигом должен быть .json");
        }
    }

}
