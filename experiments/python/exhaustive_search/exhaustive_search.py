import datetime

import pandas as pd

import configurations


def calculate_accuracy(prediction_data, threshold):
    n_samples = prediction_data.shape[0]
    prediction_data['new'] = 0
    prediction_data.loc[(prediction_data['real'] == 1) & (prediction_data['class 1'] >= threshold), 'new'] = 1
    prediction_data.loc[(prediction_data['real'] == 0) & (prediction_data['class 1'] < threshold), 'new'] = 1
    return prediction_data['new'].sum() / n_samples


def calculate_accuracy_2(prediction_data, threshold):
    n_samples = prediction_data.shape[0]
    n_correct_predictions = 0
    for index, row in prediction_data.iterrows():
        if row['real'] == 1 and row['class 1'] >= threshold:
            n_correct_predictions += 1
        if row['real'] == 0 and row['class 1'] < threshold:
            n_correct_predictions += 1
    return n_correct_predictions / n_samples


def exhaustive_search(prediction_address):
    prediction_data = pd.read_csv(prediction_address)
    Y_hat = prediction_data['class 1'].to_numpy()
    thresholds = set(Y_hat)
    thresholds.add(0)
    thresholds.add(1)
    optimal_accuracy = -configurations.INF
    optimal_threshold = None
    for threshold in thresholds:
        accuracy = calculate_accuracy(prediction_data, threshold)
        if accuracy >= optimal_accuracy:
            optimal_accuracy = accuracy
            optimal_threshold = threshold
    return optimal_threshold, optimal_accuracy


def main():
    total_time = 0
    for i in range(configurations.N_EXPERIMENTS):
        print(f'Experiment {i+1}')
        start_time = datetime.datetime.now()
        optimal_threshold, optimal_accuracy = exhaustive_search(configurations.PREDICTION_FILE_ADDRESSES[i])
        end_time = datetime.datetime.now()
        print(optimal_threshold, optimal_accuracy)
        total_time += (end_time - start_time).total_seconds()
    report_file = open(configurations.EXHAUSTIVE_SEARCH_REPORT_FILE_ADDRESS, 'w')
    report_file.write(f'average_execution_time='
                      f'{total_time / configurations.N_EXPERIMENTS}\n'
                      f'number_of_experiments={configurations.N_EXPERIMENTS}\n')
    report_file.close()
    return


if __name__ == '__main__':
    main()
