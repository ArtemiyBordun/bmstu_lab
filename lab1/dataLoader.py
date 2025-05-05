import pandas as pd
import os

HEADERS = ['year', 'region', 'npg', 'birth_rate', 'death_rate', 'gdw', 'urbanization']
MAXSIZE = 512 * 1024

class DataLoader:

    def __init__(self, file_path):
        self.file_path = self.check_file_path(file_path)

    def check_file_path(self, file_path):
        if file_path[0] == file_path[-1] == '"':
            return file_path[1: -1]
        return file_path

    def load_data(self):
        try:
            if os.path.getsize(self.file_path) >= MAXSIZE:   # path.getsize возвращает в байтах
                raise ValueError("Ошибка: Файл слишком большой.")

            headers = pd.read_csv(self.file_path, nrows=0).columns.tolist()

            if headers != HEADERS:
                raise ValueError(f"Ошибка: Файл не подходит для данной программы.")

            data, excluded_count = self.read_data()

            if len(data) == 0:
                raise ValueError("Ошибка: В файле нет данных.")
            return data, excluded_count

        except FileNotFoundError:
            raise FileNotFoundError("Ошибка: Файл не найден.")
        except pd.errors.EmptyDataError:
            raise ValueError("Ошибка: Файл пуст.")
        except pd.errors.ParserError:
            raise ValueError("Ошибка: Ошибка парсинга файла.")

    def read_data(self):
        data = pd.read_csv(self.file_path)
        original_len = len(data)

        data = data.dropna(thresh=len(HEADERS))  # удаляем строки, в которые есть пустые значения
        data = self.check_type(data)  # удаляем все строки, где значение не float

        new_len = len(data)
        excluded_count = original_len - new_len
        return data, excluded_count

    def check_type(self, data):
        for name_column in enumerate(HEADERS[2:]):  # npg начинается с 3 столбца
            data = data[pd.to_numeric(data[name_column[1]], errors='coerce').notnull()]
        return data


