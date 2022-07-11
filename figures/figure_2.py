import matplotlib.pyplot as plt

x_ticks = ['1', '2', '5', '10', '20', '50', '100', '200', '500', '1000', '2000']
ilp_time = [0.067, 0.076, 0.098, 0.127, 0.179, 0.314, 0.539, 0.966, 2.254, 4.451, 8.692]
exhaustive_search_time = [0.006, 0.013, 0.030, 0.063, 0.130, 0.330, 0.642, 1.370, 3.642, 7.088, 17.500]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_time, '--bo', label='ILP')
plt.plot(x, exhaustive_search_time, '--go', label='Search')

plt.title("Prediction Decimal = 2")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_2.png', format='png')
