#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <ctime>
#include "configurations.h"

using namespace std;


long double calculate_accuracy(vector<double> Y, vector<double> Y_hat, double threshold)
{
    int n_correct_prediction = 0;
    for(int i=0; i<Y.size(); i++)
    {
        if(Y[i]==1 && Y_hat[i] - threshold >= -1e-9)
            n_correct_prediction++;
        if(Y[i]==0 && Y_hat[i] - threshold < -1e-9)
            n_correct_prediction++;
    }
    long double accuracy = (long double)(n_correct_prediction) / Y.size();
    return accuracy;
}


pair<double, long double> exhaustive_search(string prediction_address)
{
    ifstream prediction_file(prediction_address);
    string line;
    double real, predicted;
    vector<double> Y, Y_hat;
    getline(prediction_file, line);
    while(getline(prediction_file, line))
    {
        stringstream ss(line);
        ss >> real;
        ss.ignore();
        ss >> predicted;
        Y.push_back(real);
        Y_hat.push_back(predicted);
    }
    long double optimal_accuracy = -1, accuracy;
    double optimal_threshold;
    for(double threshold : Y_hat)
    {
        accuracy = calculate_accuracy(Y, Y_hat, threshold);
        if(accuracy>optimal_accuracy)
        {
            optimal_accuracy = accuracy;
            optimal_threshold = threshold;
        }
    }
    accuracy = calculate_accuracy(Y, Y_hat, 0);
    if(accuracy>optimal_accuracy)
    {
        optimal_accuracy = accuracy;
        optimal_threshold = 0;
    }
    accuracy = calculate_accuracy(Y, Y_hat, 1);
    if(accuracy>optimal_accuracy)
    {
        optimal_accuracy = accuracy;
        optimal_threshold = 1;
    }
    pair<double, long double> optimal_threshold_accuracy;
    optimal_threshold_accuracy.first = optimal_threshold;
    optimal_threshold_accuracy.second = optimal_accuracy;
    return optimal_threshold_accuracy;
}


int main()
{
    for(int i=0; i<N_EXPERIMENTS; i++)
        PREDICTION_FILE_ADDRESSES.push_back(BASE_PREDICTION_ADDRESS + "predictions_" + to_string(i+1) + ".csv");
    ofstream time_report_file(BASE_RESULTS_ADDRESS + to_string(N_INSTANCES) + "_" + to_string(PREDICTION_DECIMAL) + "/" + TIME_REPORT_FILE_ADDRESS);
    ofstream prediction_report_file(BASE_RESULTS_ADDRESS + to_string(N_INSTANCES) + "_" + to_string(PREDICTION_DECIMAL) + "/" + PREDICTION_REPORT_FILE_ADDRESS);
    double elapsed_time = 0;
    for(int i=0; i<N_EXPERIMENTS; i++)
    {
        cout << "Experiment " << to_string(i+1) << endl;
        clock_t begin = clock();
        pair<double, long double> optimal_threshold_accuracy = exhaustive_search(PREDICTION_FILE_ADDRESSES[i]);
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        prediction_report_file << to_string(optimal_threshold_accuracy.first) << " " << to_string(optimal_threshold_accuracy.second) << endl;
        cout << optimal_threshold_accuracy.first << " " << optimal_threshold_accuracy.second << endl;
    }
    time_report_file << "average_execution_time=" << to_string((double(elapsed_time) / N_EXPERIMENTS)) << endl;
    time_report_file << "number_of_experiments=" << to_string(N_EXPERIMENTS) << endl;
    return 0;
}