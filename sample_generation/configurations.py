N_EXPERIMENTS = 5
N_INSTANCES = 20000000
PREDICTION_DECIMAL = 1

BASE_PREDICTION_ADDRESS = 'predictions/'
PREDICTION_FILE_ADDRESSES = [BASE_PREDICTION_ADDRESS + f'predictions_{i+1}.csv'
                             for i in range(N_EXPERIMENTS)]
