import matplotlib.pyplot as plt

x_ticks = ['1', '2', '5', '10', '20', '50', '100', '200', '500', '1000', '2000']
ilp_time = [0.802, 2.152, 5.060, 5.527, 6.227, 7.115, 7.351, 8.462, 10.771, 13.010, 17.751]
exhaustive_search_time = [0.028, 0.076, 0.234, 0.397, 0.181, 2.059, 5.014, 10.518, 29.151, 60.555, 166.988]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_time, '--bo', label='ILP')
plt.plot(x, exhaustive_search_time, '--go', label='Search')

plt.title("Prediction Decimal = 3")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_3.png', format='png')
