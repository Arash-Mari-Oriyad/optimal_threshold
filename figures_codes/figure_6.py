import matplotlib.pyplot as plt

x_ticks = ['100', '200', '500', '1000', '2000', '5000', '10000', '20000', '50000']
ilp_time = [0.539, 0.966, 2.254, 4.451, 8.692, 21.703, 42.343, 85.005, 212.805]
exhaustive_search_time = [0.216, 0.425, 1.055, 2.135, 4.308, 10.493, 21.191, 44.151, 104.877]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_time, '--bo', label='ILP')
plt.plot(x, exhaustive_search_time, '--go', label='Improved Search')

plt.title("Prediction Decimal = 2")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_6.png', format='png')
