
STEP = 5

class StatisticsCalculator:

    def __init__(self, data):
        self.data = data

    def get_filtered_data(self, data, region):
        regions = self.data.iloc[:, 1].unique()
        filtered_data = self.data[
            self.data['region'] == regions[int(region)]]  # получаем новый список с нужным регионом
        self.data = filtered_data
        return filtered_data

    def get_statistics(self, column_id):
        filtered_data = self.data

        if column_id not in filtered_data.columns:
            raise ValueError("Ошибка: Указано некорректное название колонки.")

        column_data = filtered_data[column_id].dropna()     # получаем новый список с нужным регионом и колонкой

        max_value, min_value, mean_value, median_value = self.calculation_metrics(column_data)
        percentiles = self.calculation_percentiles(column_data)

        return max_value, min_value, mean_value, median_value, percentiles

    def calculation_metrics(self, column_data):
        max_value = column_data.max()
        min_value = column_data.min()
        mean_value = column_data.mean()
        median_value = column_data.median()
        return max_value, min_value, mean_value, median_value

    def calculation_percentiles(self, column_data):
        percentiles = [column_data.quantile(p / 100) for p in range(0, 101, STEP)]
        return percentiles

    def check_region(self, index):
        if index.isdigit():
            regions = self.data.iloc[:, 1].unique()
            index = int(index)
            if 0 <= index < len(regions):
                return

        raise ValueError("Ошибка: Введен неверный индекс региона.")

