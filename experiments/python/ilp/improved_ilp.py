import sys
import datetime
from collections import Counter

import pandas as pd
import pulp

import configurations


def optimize(Y_Y_hat_values, Y_Y_hat_counter):
    n_variables = len(Y_Y_hat_values)
    ilp_problem = pulp.LpProblem(sense=pulp.LpMinimize, name='ILP_Problem')
    z_variables = [
        pulp.LpVariable(name='z_{}'.format(i), cat='Continuous')
        for i in range(n_variables)
    ]
    y_prime_variables = [
        pulp.LpVariable(name='y_prime_{}'.format(i), cat='Binary')
        for i in range(n_variables)
    ]
    t_variable = pulp.LpVariable(name='t', cat='Continuous', lowBound=0, upBound=1)
    ilp_problem += pulp.lpSum([Y_Y_hat_counter[index] * z_variable for index, z_variable in enumerate(z_variables)])
    for i in range(n_variables):
        ilp_problem += pulp.LpConstraint(e=z_variables[i] + y_prime_variables[i],
                                         rhs=Y_Y_hat_values[i][0],
                                         sense=pulp.LpConstraintGE)
        ilp_problem += pulp.LpConstraint(e=z_variables[i] - y_prime_variables[i],
                                         rhs=-Y_Y_hat_values[i][0],
                                         sense=pulp.LpConstraintGE)
    for i in range(n_variables):
        ilp_problem += pulp.LpConstraint(e=t_variable + Y_Y_hat_values[i][1] * y_prime_variables[i],
                                         rhs=Y_Y_hat_values[i][1] + configurations.EPSILON,
                                         sense=pulp.LpConstraintGE)
        ilp_problem += pulp.LpConstraint(e=t_variable + (1 - Y_Y_hat_values[i][1]) * y_prime_variables[i],
                                         rhs=1,
                                         sense=pulp.LpConstraintLE)
    ilp_problem_status = ilp_problem.solve(pulp.GLPK_CMD(msg=False))
    if pulp.value(ilp_problem_status) != 1:
        sys.exit('An error has occurred in the ILP solving process!')
    optimal_threshold = t_variable.varValue
    del ilp_problem
    return optimal_threshold


def calculate_accuracy(prediction_data, threshold):
    n_samples = prediction_data.shape[0]
    prediction_data['new'] = 0
    prediction_data.loc[(prediction_data['real'] == 1) & (prediction_data['class 1'] >= threshold), 'new'] = 1
    prediction_data.loc[(prediction_data['real'] == 0) & (prediction_data['class 1'] < threshold), 'new'] = 1
    return prediction_data['new'].sum() / n_samples


def main():
    total_time = 0
    for i in range(configurations.N_EXPERIMENTS):
        print(f'Experiment {i+1}')
        start_time = datetime.datetime.now()
        prediction_data = pd.read_csv(configurations.PREDICTION_FILE_ADDRESSES[i])
        Y_Y_hat_dict = Counter(prediction_data.itertuples(index=False, name=None))
        Y_Y_hat_values = list(Y_Y_hat_dict.keys())
        Y_Y_hat_counter = list(Y_Y_hat_dict.values())
        optimal_threshold = optimize(Y_Y_hat_values=Y_Y_hat_values, Y_Y_hat_counter=Y_Y_hat_counter)
        if calculate_accuracy(prediction_data, optimal_threshold) < calculate_accuracy(prediction_data, 0):
            optimal_threshold = 0
        print(optimal_threshold, calculate_accuracy(prediction_data, optimal_threshold))
        end_time = datetime.datetime.now()
        total_time += (end_time - start_time).total_seconds()
    report_file = open(configurations.ILP_REPORT_FILE_ADDRESS, 'w')
    report_file.write(f'average_execution_time='
                      f'{total_time / configurations.N_EXPERIMENTS}\n'
                      f'number_of_experiments={configurations.N_EXPERIMENTS}\n')
    return


if __name__ == '__main__':
    main()
