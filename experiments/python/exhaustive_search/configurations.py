N_EXPERIMENTS = 100
BASE_PREDICTION_ADDRESS = 'predictions/'
PREDICTION_FILE_ADDRESSES = [BASE_PREDICTION_ADDRESS + f'predictions_{i+1}.csv'
                             for i in range(N_EXPERIMENTS)]
EXHAUSTIVE_SEARCH_REPORT_FILE_ADDRESS = 'exhaustive_search_report.txt'
INF = pow(10, 12)
