#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#include "configurations.h"

using namespace std;


vector<long double> search_with_space(string prediction_address)
{
    int n = 0;
    int size = int(pow(10, PREDICTION_DECIMAL));
    ifstream prediction_file(prediction_address);
    string line;
    long double real, predicted;
    int Y_hat_counter_0[10000] = {0};
    int Y_hat_counter_1[10000] = {0};
    getline(prediction_file, line);
    while(getline(prediction_file, line))
    {
        n += 1;
        stringstream ss(line);
        ss >> real;
        ss.ignore();
        ss >> predicted;
        if(real==0)
            Y_hat_counter_0[int(predicted * size)] += 1;
        else
            Y_hat_counter_1[int(predicted * size)] += 1;
    }
    int sum = 0, temp = 0;
    for(int i = 0; i <= size; i++)
    {
        temp = Y_hat_counter_0[i];
        Y_hat_counter_0[i] = sum;
        sum += temp;
    }
    sum = 0;
    for(int i = size; i >= 0; i--)
    {
        sum += Y_hat_counter_1[i];
        Y_hat_counter_1[i] = sum;
    }
    long double optimal_accuracy = -1, temp_accuracy, optimal_threshold;
    for(int i = 0; i <= size; i++)
    {
        temp_accuracy = Y_hat_counter_0[i] + Y_hat_counter_1[i];
        if(temp_accuracy > optimal_accuracy)
        {
            optimal_accuracy = temp_accuracy;
            optimal_threshold = i;
        }
    }

    vector<long double> optimal_threshold_accuracy;
    optimal_threshold_accuracy.push_back((long double)(optimal_threshold)/size);
    optimal_threshold_accuracy.push_back((long double)(optimal_accuracy)/n);
    return optimal_threshold_accuracy;
}


int main()
{
    for(int i=0; i<N_EXPERIMENTS; i++)
        PREDICTION_FILE_ADDRESSES.push_back(BASE_PREDICTION_ADDRESS + "predictions_" + to_string(i+1) + ".csv");
    double elapsed_time = 0;
    ofstream report_file(IMPROVED_EXHAUSTIVE_SEARCH_REPORT_FILE_ADDRESS);
    for(int i=0; i<N_EXPERIMENTS; i++)
    {
        cout << "Experiment " << to_string(i+1) << endl;
        clock_t begin = clock();
        vector<long double> optimal_threshold_accuracy = search_with_space(PREDICTION_FILE_ADDRESSES[i]);
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        cout << to_string(optimal_threshold_accuracy[0]) << " " << to_string(optimal_threshold_accuracy[1]) << endl;
    }
    report_file << "average_execution_time=" << to_string((double(elapsed_time) / N_EXPERIMENTS)) << endl;
    report_file << "number_of_experiments=" << to_string(N_EXPERIMENTS) << endl;
    return 0;
}