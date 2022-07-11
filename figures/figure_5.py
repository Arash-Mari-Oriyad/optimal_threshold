import matplotlib.pyplot as plt

x_ticks = ['100', '200', '500', '1000', '2000', '5000', '10000', '20000']
ilp_1_time = [7.351, 8.462, 10.771, 13.010, 17.751, 32.412, 54.738, 100.162]
ilp_2_time = [3.964, 4.856, 6.029, 8.178, 13.079, 25.539, 50.199, 96.225]
x = [i for i in range(len(x_ticks))]

plt.plot(x, ilp_1_time, '--bo', label='ILP (Uniform)')
plt.plot(x, ilp_2_time, '--go', label='ILP (Weighted Uniform)')

plt.title("Prediction Decimal = 3")
plt.ylabel("Execution Time (s)", size=10)
plt.xlabel("#Instances * 1000", size=10)
plt.xticks(x, x_ticks)
# plt.xlim((0, 13))
# plt.ylim((69, 74))
plt.legend()
plt.savefig('figure_5.png', format='png')
