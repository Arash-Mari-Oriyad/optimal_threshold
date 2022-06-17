import numpy as np
import pandas as pd

import configurations


def generate_predictions():
    for i in range(configurations.N_EXPERIMENTS):
        print(f'Experiment {i + 1}')
        predictions_df = pd.DataFrame(data={'real': np.random.randint(2, size=configurations.N_INSTANCES),
                                            'class 1': np.round(np.random.rand(configurations.N_INSTANCES),
                                                                decimals=configurations.PREDICTION_DECIMAL)})
        predictions_df.to_csv(configurations.PREDICTION_FILE_ADDRESSES[i], index=False)
    return


if __name__ == '__main__':
    generate_predictions()
