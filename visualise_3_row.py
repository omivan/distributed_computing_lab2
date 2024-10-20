import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter

# Завантаження даних
df = pd.read_csv("row_sum_results.csv")
df.replace(0, 1e-6, inplace=True)
print(df)
# Створення графіка
plt.figure(figsize=(10, 6))
plt.plot(df["Розмір матриці"], df["Час 2 потоків (сек.)"], label="2 потоки", marker='o')
plt.plot(df["Розмір матриці"], df["Час 4 потоків (сек.)"], label="4 потоки", marker='o')
plt.plot(df["Розмір матриці"], df["Час 8 потоків (сек.)"], label="8 потоки", marker='o')
plt.plot(df["Розмір матриці"], df["Час 16 потоків (сек.)"], label="16 потоки", marker='o')
plt.plot(df["Розмір матриці"], df["Час послідовно (сек.)"], label="Час послідовно (сек.)", marker='o')

# Додавання підписів і заголовка
plt.xlabel("Розмір матриці")
plt.ylabel("Час (секунди)")
plt.title("Час множення матриці з різною кількістю потоків")
plt.legend()

# Логарифмічна шкала для осей
plt.xscale('log')  # Логарифмічна шкала для осі X
plt.yscale('log')  # Логарифмічна шкала для осі Y

# Форматування підписів осі X для відображення абсолютних значень
x_formatter = FuncFormatter(lambda x, _: '{:g}'.format(x))
plt.gca().xaxis.set_major_formatter(x_formatter)

# Форматування підписів осі Y для відображення абсолютних значень
y_formatter = FuncFormatter(lambda y, _: '{:g}'.format(y))
plt.gca().yaxis.set_major_formatter(y_formatter)

# Встановлення підписів для осі X
plt.xticks(df["Розмір матриці"], labels=df["Розмір матриці"].astype(str))

# Додавання сітки
# plt.grid(True, which="both", ls="--")
plt.grid(True)
plt.savefig('images/plot_task3_row')
plt.show()
