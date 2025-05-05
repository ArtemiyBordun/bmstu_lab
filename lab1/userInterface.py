from dataLoader import DataLoader
from statisticsCalculator import StatisticsCalculator


class UserInterface:

    def __init__(self):
        self.file_path = self.read_path()

    def run(self):
        while True:
            try:
                if self.file_path == 'exit':
                    break
                data_loader = DataLoader(self.file_path)
                data, excluded_count = data_loader.load_data()

                if data is not None:
                    stats_calculator = StatisticsCalculator(data)
                    region = input(
                        "Введите id региона ('list' для вывода списка регионов или 'exit' для выхода): ")
                    if region.lower() == 'list':
                        self.print_regions(data)
                        continue
                    if region.lower() == 'exit':
                        break

                    try:
                        stats_calculator.check_region(region)
                    except Exception as e:
                        print(e)
                        continue

                    filtered_data = stats_calculator.get_filtered_data(data, region)
                    self.print_filtered_regions(filtered_data, excluded_count)

                    column_id = input(
                        "Введите название колонки для анализа (npg, birth_rate, death_rate, gdw, urbanization,"
                        " либо 'back', чтобы выбрать новый регион): ")

                    if column_id.lower() == 'back':
                        continue

                    try:
                        max_value, min_value, mean_value, median_value, percentiles = stats_calculator.get_statistics(column_id)
                        self.print_result(max_value, min_value, mean_value, median_value, percentiles)
                    except ValueError as e:
                        print(e)

            except Exception as e:
                print(e)
                self.file_path = self.read_path()

    def read_path(self):
        file_path = input("Введите путь к CSV файлу (или 'exit' для выхода): ")
        return file_path

    def print_filtered_regions(seft, filtered_data, excluded_count):
        print("\n\033[1mТаблица значений по региону:\033[0m")
        print(filtered_data)
        print(f"Количество строк с ошибками в файле: {excluded_count}\n")

    def print_result(self, max_value, min_value, mean_value, median_value, percentiles):
        print("\n\033[1mСтатистические метрики:\033[0m")
        print(f" Максимум: {round(max_value, 2)}")
        print(f" Минимум: {round(min_value, 2)}")
        print(f" Среднее значение: {round(mean_value, 2)}")
        print(f" Медиана: {round(median_value, 2)}")

        print("\n\033[1mТаблица перцентилей (0-100 с шагом 5):\033[0m")
        for i, percentile in enumerate(percentiles):
            print(f" {i * 5}-й перцентиль: {round(percentile, 2)}")

    def print_regions(self, data):
        regions = data.iloc[:, 1].unique()
        print("\n\033[1mСписок регионов:\033[0m")
        for i, region in enumerate(regions):
            print(f" {i}: {region}")
