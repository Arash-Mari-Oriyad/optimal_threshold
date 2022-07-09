#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>
#include <cmath>
using namespace std;

int N_EXPERIMENTS = 50;
int N_INSTANCES = 1000;
int PREDICTION_DECIMAL = 4;
string BASE_PREDICTION_ADDRESS = "predictions/";
string BASE_RESULTS_ADDRESS = "results/";
vector<string> PREDICTION_FILE_ADDRESSES;
string TIME_REPORT_FILE_ADDRESS = "time_report.txt";
string PREDICTION_REPORT_FILE_ADDRESS = "prediction_report.txt";

#endif