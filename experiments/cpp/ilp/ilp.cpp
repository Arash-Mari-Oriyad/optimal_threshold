#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <glpk.h>

using namespace std;


double calculate_accuracy(string prediction_address, double threshold)
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
    int n_correct_predictions = 0;
    for(int i=0; i<int(Y.size()); i++)
    {
        if(Y[i]==1 && Y_hat[i] - threshold >= -1e-9)
            n_correct_predictions++;
        if(Y[i]==0 && Y_hat[i] - threshold < -1e-9)
            n_correct_predictions++;
    }
    double accuracy = (double)(n_correct_predictions) / Y.size();
    return accuracy;
}


double optimize(vector<double> Y, vector<double> Y_hat, vector<int> n_repetitions)
{
    int n_variables = int(Y.size());
    glp_prob *ilp = glp_create_prob();
    glp_set_prob_name(ilp, "ilp_problem");
    glp_set_obj_dir(ilp, GLP_MIN);
    glp_add_rows(ilp, 4 * n_variables);
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_row_name(ilp, i+1+0*n_variables, ("z_c_1_" + to_string(i+1)).c_str());
        glp_set_row_bnds(ilp, i+1+0*n_variables, GLP_LO, Y[i], 0);
    }
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_row_name(ilp, i+1+1*n_variables, ("z_c_2_" + to_string(i+1)).c_str());
        glp_set_row_bnds(ilp, i+1+1*n_variables, GLP_LO, -Y[i], 0);
    }
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_row_name(ilp, i+1+2*n_variables, ("yt_c_1_" + to_string(i+1)).c_str());
        glp_set_row_bnds(ilp, i+1+2*n_variables, GLP_LO, Y_hat[i] + 1e-4, 0);
    }
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_row_name(ilp, i+1+3*n_variables, ("yt_c_2_" + to_string(i+1)).c_str());
        glp_set_row_bnds(ilp, i+1+3*n_variables, GLP_LO, -1, 0);
    }

    glp_add_cols(ilp, 2 * n_variables + 1);
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_col_name(ilp, i+1+0*n_variables, ("z_" + to_string(i+1)).c_str());
        glp_set_col_bnds(ilp, i+1+0*n_variables, GLP_FR, 0, 1);
        glp_set_obj_coef(ilp, i+1+0*n_variables, n_repetitions[i]);
        glp_set_col_kind(ilp, i+1+0*n_variables, GLP_CV);
    }
    for(int i = 0; i < n_variables; i++)
    {
        glp_set_col_name(ilp, i+1+1*n_variables, ("yt_" + to_string(i+1)).c_str());
        glp_set_col_bnds(ilp, i+1+1*n_variables, GLP_DB, 0, 1);
        glp_set_obj_coef(ilp, i+1+1*n_variables, 0);
        glp_set_col_kind(ilp, i+1+1*n_variables, GLP_BV);
    }
    glp_set_col_name(ilp, 2*n_variables+1, "t");
    glp_set_col_bnds(ilp, 2*n_variables+1, GLP_DB, 0, 1);
    glp_set_obj_coef(ilp, 2*n_variables+1, 0);
    glp_set_col_kind(ilp, 2*n_variables+1, GLP_CV);
    int ia[8*n_variables+1], ja[8*n_variables+1];
    double ar[8*n_variables+1];
    int counter = 1;
    for(int i = 0; i < n_variables; i++)
    {
        ia[counter]=i+1+0*n_variables, ja[counter]=i+1+0*n_variables, ar[counter]=1;
        counter++;
        ia[counter]=i+1+0*n_variables, ja[counter]=i+1+1*n_variables, ar[counter]=1;
        counter++;
    }
    for(int i = 0; i < n_variables; i++)
    {
        ia[counter]=i+1+1*n_variables, ja[counter]=i+1+0*n_variables, ar[counter]=1;
        counter++;
        ia[counter]=i+1+1*n_variables, ja[counter]=i+1+1*n_variables, ar[counter]=-1;
        counter++;
    }
    for(int i = 0; i < n_variables; i++)
    {
        ia[counter]=i+1+2*n_variables, ja[counter]=i+1+1*n_variables, ar[counter]=Y_hat[i];
        counter++;
        ia[counter]=i+1+2*n_variables, ja[counter]=2*n_variables+1, ar[counter]=1;
        counter++;
    }
    for(int i = 0; i < n_variables; i++)
    {
        ia[counter]=i+1+3*n_variables, ja[counter]=i+1+1*n_variables, ar[counter]=Y_hat[i]-1;
        counter++;
        ia[counter]=i+1+3*n_variables, ja[counter]=2*n_variables+1, ar[counter]=-1;
        counter++;
    }
    glp_load_matrix(ilp, 8*n_variables, ia, ja, ar);
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    parm.msg_lev = GLP_MSG_OFF;
    int err = glp_intopt(ilp, &parm);
    double optimal_threshold = glp_mip_col_val(ilp, 2*n_variables+1);
    return optimal_threshold;
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
        ifstream prediction_file(samples_addresses[i]);
        string line;
        double real, predicted;
        map<pair<double, double>, int> Y_Y_hat_map;
        pair<double, double> y_y_hat_pair;
        getline(prediction_file, line);
        while(getline(prediction_file, line))
        {
            stringstream ss(line);
            ss >> real;
            ss.ignore();
            ss >> predicted;
            y_y_hat_pair.first = real;
            y_y_hat_pair.second = predicted;
            Y_Y_hat_map[y_y_hat_pair]++;
        }
        vector<double> Y, Y_hat;
        vector<int> n_repetitions;
        map<pair<double, double>, int>::iterator it;
        for(it = Y_Y_hat_map.begin(); it != Y_Y_hat_map.end(); it++)
        {
            Y.push_back(it->first.first);
            Y_hat.push_back(it->first.second);
            n_repetitions.push_back(it->second);
        }
        double optimal_threshold = optimize(Y, Y_hat, n_repetitions);
        if(calculate_accuracy(samples_addresses[i], optimal_threshold) < calculate_accuracy(samples_addresses[i], 0))
            optimal_threshold = 0;
        clock_t end = clock();
        elapsed_time += double(end - begin) / CLOCKS_PER_SEC;
        cout << optimal_threshold << " " << calculate_accuracy(samples_addresses[i], optimal_threshold) << endl;
        threshold_accuracy_report_file << optimal_threshold << " " << calculate_accuracy(samples_addresses[i], optimal_threshold) << endl;
    }
    time_report_file << "average_execution_time = " << to_string((double(elapsed_time) / n_samples)) << endl;
    time_report_file << "number_of_samples = " << to_string(n_samples) << endl;
    return 0;
}