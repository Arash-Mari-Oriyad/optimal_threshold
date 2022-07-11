import matplotlib.pyplot as plt
import numpy as np

# x_ticks = ['1', '2', '5', '10', '20', '50', '100', '200', '500', '1000']
x_ticks = ['1', '2', '5', '10', '20', '50']
# ilp_time_3 = [0.498, 1.352, 3.041, 3.852, 4.244, 4.648, 5.189, 6.138, 7.427, 9.408]
ilp_time_3 = [0.498, 1.352, 3.041, 3.852, 4.244, 4.648]
exhaustive_search_time_3 = [0.026, 0.105, 0.666, 2.648, 10.854, 68.787]
proportion_3 = [ilp_time_3[i]-exhaustive_search_time_3[i] for i in range(len(x_ticks))]
ilp_time_2 = [1, 1, 1, 1, 1, 1]
exhaustive_search_time_2 = [1, 1, 1, 1, 1, 1]
proportion_2 = [ilp_time_2[i]-exhaustive_search_time_2[i] for i in range(len(x_ticks))]
x = [i for i in range(len(x_ticks))]

plt.plot(x, proportion_3, '--bo', label='Prediction Decimal = 3')
plt.plot(x, proportion_2, '--ro', label='Prediction Decimal = 2')

plt.title("ILP - Exhaustive Search")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.yticks(np.arange(0, 20, 1))
# plt.xlim((0, 13))
# plt.ylim((0, 27))
plt.legend()
plt.savefig('figure_7.png', format='png')
