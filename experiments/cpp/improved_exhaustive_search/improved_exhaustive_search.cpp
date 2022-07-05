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


vector<long double> improved_exhaustive_search(string prediction_address)
{
    int n = 0;
    ifstream prediction_file(prediction_address);
    string line;
    long double real, predicted;
    set<long double> thresholds;
    map<pair<int, long double>, int> Y_Y_hat_map;
    pair<int, long double> temp_pair;
    getline(prediction_file, line);
    while(getline(prediction_file, line))
    {
        n += 1;
        stringstream ss(line);
        ss >> real;
        ss.ignore();
        ss >> predicted;
        temp_pair.first = real;
        temp_pair.second = predicted;
        Y_Y_hat_map[temp_pair]++;
        thresholds.insert(predicted);
    }
    thresholds.insert(0);
    thresholds.insert(1);
    set<long double>::iterator set_it;
    for (set_it = thresholds.begin(); set_it != thresholds.end(); set_it++)
    {
        temp_pair.first = 1;
        temp_pair.second = *set_it;
        if(Y_Y_hat_map.find(temp_pair) == Y_Y_hat_map.end())
            Y_Y_hat_map[temp_pair] = 0;
        temp_pair.first = 0;
        if(Y_Y_hat_map.find(temp_pair) == Y_Y_hat_map.end())
            Y_Y_hat_map[temp_pair] = 0;
    }
    int sum = 0, temp = 0;
    temp_pair.first = 0;
    for(set_it = thresholds.begin(); set_it != thresholds.end(); set_it++)
    {
        temp_pair.second = *set_it;
        temp = Y_Y_hat_map[temp_pair];
        Y_Y_hat_map[temp_pair] = sum;
        sum += temp;
    }
    temp_pair.first = 1;
    sum = 0;
    set<long double>::reverse_iterator reversed_set_it;
    for(reversed_set_it = thresholds.rbegin(); reversed_set_it != thresholds.rend(); reversed_set_it++)
    {
        temp_pair.second = *reversed_set_it;
        sum += Y_Y_hat_map[temp_pair];
        Y_Y_hat_map[temp_pair] = sum;
    }
    long double optimal_accuracy = -1, temp_accuracy, optimal_threshold;
    for(set_it = thresholds.begin(); set_it != thresholds.end(); set_it++)
    {
        temp_accuracy = 0;
        temp_pair.second = *set_it;
        temp_pair.first = 1;
        temp_accuracy += Y_Y_hat_map[temp_pair];
        temp_pair.first = 0;
        temp_accuracy += Y_Y_hat_map[temp_pair];
        if(temp_accuracy > optimal_accuracy)
        {
            optimal_accuracy = temp_accuracy;
            optimal_threshold = *set_it;
        }
    }
    vector<long double> optimal_threshold_accuracy;
    optimal_threshold_accuracy.push_back(optimal_threshold);
    optimal_threshold_accuracy.push_back((long double)(optimal_accuracy)/n);
    return optimal_threshold_accuracy;
}


int main()
{
    for(int i=0; i<N_EXPERIMENTS; i++)
        PREDICTION_FILE_ADDRESSES.push_back(BASE_PREDICTION_ADDRESS + "predictions_" + to_string(i+1) + ".csv");
    double elapsed_time = 0;
    ofstream report_file(IMPROVED_EXHAUSTIVE_SEARCH_REPORT_FILE_ADDRESS);
    ofstream es_report("ies_t_a_report.txt");
    for(int i=0; i<N_EXPERIMENTS; i++)
    {
        cout << "Experiment " << to_string(i+1) << endl;
        clock_t begin = clock();
        vector<long double> optimal_threshold_accuracy = improved_exhaustive_search(PREDICTION_FILE_ADDRESSES[i]);
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        es_report << to_string(optimal_threshold_accuracy[0]) << " " << to_string(optimal_threshold_accuracy[1]) << endl;
        cout << to_string(optimal_threshold_accuracy[0]) << " " << to_string(optimal_threshold_accuracy[1]) << endl;
    }
    report_file << "average_execution_time=" << to_string((double(elapsed_time) / N_EXPERIMENTS)) << endl;
    report_file << "number_of_experiments=" << to_string(N_EXPERIMENTS) << endl;
    return 0;
}