import matplotlib.pyplot as plt

x_ticks = ['100', '200', '500', '1000', '2000', '5000', '10000', '20000', '50000']
ilp_time = [7.351, 8.462, 10.771, 13.010, 17.751, 32.412, 54.738, 100.162, 242.539]
exhaustive_search_time = [0.275, 0.506, 1.251, 2.685, 5.391, 12.406, 24.885, 50.242, 130.451]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_time, '--bo', label='ILP')
plt.plot(x, exhaustive_search_time, '--go', label='Improved Search')

plt.title("Prediction Decimal = 3")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_4.png', format='png')
