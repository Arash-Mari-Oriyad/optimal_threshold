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


long double calculate_accuracy(vector<long double> Y, vector<long double> Y_hat, long double threshold)
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


vector<long double> exhaustive_search(string prediction_address)
{
    ifstream prediction_file(prediction_address);
    string line;
    long double real, predicted;
    vector<long double> Y, Y_hat;
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
    set<double> thresholds;
    for (double threshold : Y_hat)
        thresholds.insert(threshold);
    thresholds.insert(0);
    thresholds.insert(1);
    long double optimal_accuracy = -1, accuracy, optimal_threshold;
    for(double threshold : thresholds)
    {
        accuracy = calculate_accuracy(Y, Y_hat, threshold);
        if(accuracy>optimal_accuracy)
        {
            optimal_accuracy = accuracy;
            optimal_threshold = threshold;
        }
    }
    vector<long double> optimal_threshold_accuracy;
    optimal_threshold_accuracy.push_back(optimal_threshold);
    optimal_threshold_accuracy.push_back(optimal_accuracy);
    return optimal_threshold_accuracy;
}


int main()
{
    for(int i=0; i<N_EXPERIMENTS; i++)
        PREDICTION_FILE_ADDRESSES.push_back(BASE_PREDICTION_ADDRESS + "predictions_" + to_string(i+1) + ".csv");
    double elapsed_time = 0;
    ofstream report_file(EXHAUSTIVE_SEARCH_REPORT_FILE_ADDRESS);
    ofstream es_report("es_t_a_report.txt");
    for(int i=0; i<N_EXPERIMENTS; i++)
    {
        cout << "Experiment " << to_string(i+1) << endl;
        clock_t begin = clock();
        vector<long double> optimal_threshold_accuracy = exhaustive_search(PREDICTION_FILE_ADDRESSES[i]);
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        es_report << to_string(optimal_threshold_accuracy[0]) << " " << to_string(optimal_threshold_accuracy[1]) << endl;
        cout << to_string(optimal_threshold_accuracy[0]) << " " << to_string(optimal_threshold_accuracy[1]) << endl;
    }
    report_file << "average_execution_time=" << to_string((double(elapsed_time) / N_EXPERIMENTS)) << endl;
    report_file << "number_of_experiments=" << to_string(N_EXPERIMENTS) << endl;
    return 0;
}