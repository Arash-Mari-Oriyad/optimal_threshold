import matplotlib.pyplot as plt

x_ticks = ['1', '2', '5', '10', '20', '50', '100', '200', '500', '1000', '2000']
ilp_time = [0.007, 0.010, 0.023, 0.043, 0.086, 0.212, 0.429, 0.866, 2.108, 4.131, 8.198]
exhaustive_search_time = [0.002, 0.004, 0.010, 0.021, 0.042, 0.115, 0.218, 0.439, 1.102, 2.229, 4.703]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_time, '--bo', label='ILP')
plt.plot(x, exhaustive_search_time, '--go', label='Search')

plt.title("Prediction Decimal = 1")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_1.png', format='png')
