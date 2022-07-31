import numpy as np
import matplotlib.pyplot as plt


TIME_REPORT_BASE_ADDRESS = "../experiments/cpp"

x_ticks = ["5", "10", "15", "20", "25", "30", "35", "40", "45", "50"]

ilp_average_time_2 = []
for n_instances in x_ticks:
    time_report_address = f"{TIME_REPORT_BASE_ADDRESS}/ilp/results/" \
                          f"{int(n_instances) * 1000}_{2}/time_report.txt"
    with open(time_report_address, "r") as time_report_file:
        line = time_report_file.readline()
    ilp_average_time_2.append(round(float(line.split()[-1]), 3))

ilp_average_time_3 = []
for n_instances in x_ticks:
    time_report_address = f"{TIME_REPORT_BASE_ADDRESS}/ilp/results/" \
                          f"{int(n_instances) * 1000}_{3}/time_report.txt"
    with open(time_report_address, "r") as time_report_file:
        line = time_report_file.readline()
    ilp_average_time_3.append(round(float(line.split()[-1]), 3))

exhaustive_search_average_time_2 = []
for n_instances in x_ticks:
    time_report_address = f"{TIME_REPORT_BASE_ADDRESS}/exhaustive_search/results/" \
                          f"{int(n_instances) * 1000}_{2}/time_report.txt"
    with open(time_report_address, "r") as time_report_file:
        line = time_report_file.readline()
    exhaustive_search_average_time_2.append(round(float(line.split()[-1]), 3))

exhaustive_search_average_time_3 = []
for n_instances in x_ticks:
    time_report_address = f"{TIME_REPORT_BASE_ADDRESS}/exhaustive_search/results/" \
                          f"{int(n_instances) * 1000}_{3}/time_report.txt"
    with open(time_report_address, "r") as time_report_file:
        line = time_report_file.readline()
    exhaustive_search_average_time_3.append(round(float(line.split()[-1]), 3))

portion_2 = np.log10([ilp_average_time_2[i] / exhaustive_search_average_time_2[i] for i in range(len(x_ticks))])
portion_3 = np.log10([ilp_average_time_3[i] / exhaustive_search_average_time_3[i] for i in range(len(x_ticks))])

plt.plot(x_ticks, portion_2, "--ro", label="Maximum number of decimal digits = 2")
plt.plot(x_ticks, portion_3, "--bo", label="Maximum number of decimal digits = 3")

plt.title("")
plt.ylabel("Log (ILP_average_time / Exhaustive_search_average_time)", size=10)
plt.xlabel("#Instances x 1000", size=10)
plt.legend()
plt.grid()
plt.savefig("figure_1.png", format="png")
plt.savefig("figure_1.svg", format="svg")
