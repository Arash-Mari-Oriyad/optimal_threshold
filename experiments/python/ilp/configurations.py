N_EXPERIMENTS = 1
N_INSTANCES = 5000
BASE_PREDICTION_ADDRESS = 'predictions/'
PREDICTION_FILE_ADDRESSES = [BASE_PREDICTION_ADDRESS + f'predictions_{i+1}.csv'
                             for i in range(N_EXPERIMENTS)]
EPSILON = pow(10, -6)
INF = pow(10, 12)
ILP_REPORT_FILE_ADDRESS = 'ilp_report.txt'
