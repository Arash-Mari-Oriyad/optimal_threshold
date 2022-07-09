report_1 = open('cpp/exhaustive_search_1/results/1000_4/prediction_report.txt', 'r')
report_1_lines = report_1.readlines()
report_1_lines = [line.strip().split(' ') for line in report_1_lines]
report_1_lines = [[float(line[0]), float(line[1])] for line in report_1_lines]

report_2 = open('cpp/ilp/results/1000_4/prediction_report.txt', 'r')
report_2_lines = report_2.readlines()
report_2_lines = [line.strip().split(' ') for line in report_2_lines]
report_2_lines = [[float(line[0]), float(line[1])] for line in report_2_lines]

for i in range(50):
    if report_1_lines[i][1] != report_2_lines[i][1]:
    # if c_t_a_report_lines[i][0] != p_t_a_report_lines[i][0] or c_t_a_report_lines[i][1] != p_t_a_report_lines[i][1]:
        print(i+1, report_1_lines[i][0], report_1_lines[i][1], report_2_lines[i][0], report_2_lines[i][1])
