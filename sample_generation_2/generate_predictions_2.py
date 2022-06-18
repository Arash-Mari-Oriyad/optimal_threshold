import numpy as np
import pandas as pd
from random import uniform

import configurations


def generate_predictions():
    for i in range(configurations.N_EXPERIMENTS):
        print(f'Experiment {i + 1}')
        real_values = np.random.randint(2, size=configurations.N_INSTANCES)
        random_numbers = np.round(np.random.rand(configurations.N_INSTANCES), decimals=2)
        predicted_values_1_0 = np.where(((real_values==1) & (random_numbers < 0.33)), np.round(np.random.uniform(0, 0.5, configurations.N_INSTANCES), configurations.PREDICTION_DECIMAL), 0)
        predicted_values_1_1 = np.where(((real_values==1) & (random_numbers >= 0.33)), np.round(np.random.uniform(0.5, 1, configurations.N_INSTANCES), configurations.PREDICTION_DECIMAL), 0)
        predicted_values_0_0 = np.where(((real_values==0) & (random_numbers < 0.66)), np.round(np.random.uniform(0, 0.5, configurations.N_INSTANCES), configurations.PREDICTION_DECIMAL), 0)
        predicted_values_0_1 = np.where(((real_values==0) & (random_numbers >= 0.66)), np.round(np.random.uniform(0.5, 1, configurations.N_INSTANCES), configurations.PREDICTION_DECIMAL), 0)
        predictions_df = pd.DataFrame(data={'real': real_values,
                                            'class 1': predicted_values_1_0 + predicted_values_1_1 + predicted_values_0_0 + predicted_values_0_1})
        predictions_df.to_csv(configurations.PREDICTION_FILE_ADDRESSES[i], index=False)
    return


if __name__ == '__main__':
    generate_predictions()
