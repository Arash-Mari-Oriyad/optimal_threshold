import matplotlib.pyplot as plt
import numpy as np

x_ticks = ['100', '200', '500', '1000', '2000', '5000', '10000', '20000', '50000']
ilp_time_3 = [7.351, 8.462, 10.771, 13.010, 17.751, 32.412, 54.738, 100.162, 242.539]
exhaustive_search_time_3 = [0.275, 0.506, 1.251, 2.685, 5.391, 12.406, 24.885, 50.242, 130.451]
proportion_3 = [ilp_time_3[i]/exhaustive_search_time_3[i] for i in range(len(x_ticks))]
ilp_time_2 = [0.539, 0.966, 2.254, 4.451, 8.692, 21.703, 42.343, 85.005, 212.805]
exhaustive_search_time_2 = [0.216, 0.425, 1.055, 2.135, 4.308, 10.493, 21.191, 44.151, 104.877]
proportion_2 = [ilp_time_2[i]/exhaustive_search_time_2[i] for i in range(len(x_ticks))]
x = [i for i in range(len(x_ticks))]

plt.plot(x, proportion_3, '--bo', label='Prediction Decimal = 3')
plt.plot(x, proportion_2, '--ro', label='Prediction Decimal = 2')

plt.title("")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
plt.yticks(np.arange(0, 30, 2))
# plt.xlim((0, 13))
# plt.ylim((0, 27))
plt.legend()
plt.savefig('figure_4_temp.png', format='png')
