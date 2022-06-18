import numpy as np
import pandas as pd
from random import uniform

import configurations


def generate_predictions():
    for i in range(configurations.N_EXPERIMENTS):
        print(f'Experiment {i + 1}')
        real_values = np.random.randint(2, size=configurations.N_INSTANCES)
        predicted_values = np.zeros(configurations.N_INSTANCES)
        random_numbers = np.round(np.random.rand(configurations.N_INSTANCES), decimals=2)
        print(random_numbers)
        for index, real_value in enumerate(real_values):
            if real_value == 1:
                if random_numbers[index] < 0.33:
                    predicted_values[index] = np.round(uniform(0, 0.5), configurations.PREDICTION_DECIMAL)
                if random_numbers[index] >= 0.33:
                    predicted_values[index] = np.round(uniform(0.5, 1), configurations.PREDICTION_DECIMAL)
            else:
                if random_numbers[index] < 0.66:
                    predicted_values[index] = np.round(uniform(0, 0.5), configurations.PREDICTION_DECIMAL)
                if random_numbers[index] >= 0.66:
                    predicted_values[index] = np.round(uniform(0.5, 1), configurations.PREDICTION_DECIMAL)
        predictions_df = pd.DataFrame(data={'real': real_values,
                                            'class 1': predicted_values})
        predictions_df.to_csv(configurations.PREDICTION_FILE_ADDRESSES[i], index=False)
    return


if __name__ == '__main__':
    generate_predictions()
