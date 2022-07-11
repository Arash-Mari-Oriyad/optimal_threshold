#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


long double calculate_accuracy(vector<double> Y, vector<double> Y_hat, double threshold)
{
    int n_correct_prediction = 0;
    for(int i=0; i<int(Y.size()); i++)
    {
        if(Y[i]==1 && Y_hat[i] - threshold >= -1e-9)
            n_correct_prediction++;
        if(Y[i]==0 && Y_hat[i] - threshold < -1e-9)
            n_correct_prediction++;
    }
    long double accuracy = (long double)(n_correct_prediction) / Y.size();
    return accuracy;
}


pair<double, long double> exhaustive_search(string sample_address)
{
    ifstream prediction_file(sample_address);
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


int main(int argc, char **argv)
{
    string samples_base_address = argv[1];
    int n_samples = atoi(argv[2]);
    int n_instances = atoi(argv[3]);
    int prediction_decimal = atoi(argv[4]);
    vector<string> samples_addresses;
    for(int i=0; i<n_samples; i++)
        samples_addresses.push_back(samples_base_address + "/sample_" + to_string(i+1) + ".csv");
    ofstream time_report_file("results/" + to_string(n_instances) + "_" + to_string(prediction_decimal) + "/time_report.txt");
    ofstream threshold_accuracy_report_file("results/" + to_string(n_instances) + "_" + to_string(prediction_decimal) + "/threshold_accuracy_report.txt");
    double elapsed_time = 0;
    for(int i=0; i<n_samples; i++)
    {
        cout << "Sample " << to_string(i+1) << endl;
        clock_t begin = clock();
        pair<double, long double> optimal_threshold_accuracy = exhaustive_search(samples_addresses[i]);
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        threshold_accuracy_report_file << to_string(optimal_threshold_accuracy.first) << " " << to_string(optimal_threshold_accuracy.second) << endl;
        cout << optimal_threshold_accuracy.first << " " << optimal_threshold_accuracy.second << endl;
    }
    time_report_file << "average_execution_time = " << to_string((double(elapsed_time) / n_samples)) << endl;
    time_report_file << "number_of_samples = " << to_string(n_samples) << endl;
    return 0;
}
