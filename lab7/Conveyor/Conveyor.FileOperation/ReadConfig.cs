using System;
using System.IO;
using System.Text.Json;
using Conveyor.Config;

namespace Conveyor.FileOperation
{
    public static class ReadConfig
    {
        public static ConfigLine? ReadFile()
        {
            string jsonPath = "D:\\proga\\sem3\\lab7\\config.json";
            string jsonString = File.ReadAllText(jsonPath);

            JsonSerializerOptions options = new JsonSerializerOptions();
            options.PropertyNameCaseInsensitive = true;
            ConfigLine? config = JsonSerializer.Deserialize<ConfigLine>(jsonString, options);

            return config;
        }
    }
}
