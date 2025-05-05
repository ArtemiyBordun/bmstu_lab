using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demographic.FileOperations
{
    public static class FileOutput
    {
        public static void WriteFile(List<string[]> _people)
        {
            string path = FilesConstants.pathOutput;    
            StreamWriter writter = new StreamWriter(path);
            writter.WriteLine(FilesConstants.HeaderPopuliation);
            foreach (var people in _people)
            {
                writter.WriteLine(string.Join(",", people));
            }
            writter.Close();
            Console.WriteLine($"CSV-файл создан: \n{path}");
        }

        public static void WriteError(string error)
        {
            string path = FilesConstants.pathOutput;
            StreamWriter writter = new StreamWriter(path);
            writter.Write(error);
            writter.Close();
            Console.WriteLine($"CSV-файл с ошибкой создан: \n{path}");
        }
    }
}
