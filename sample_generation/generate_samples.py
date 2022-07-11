import os
import shutil

import numpy as np
import pandas as pd

import configurations


def generate_predictions():
    for n_instances in configurations.N_INSTANCES_LIST:
        print(f'Number of Instances = {n_instances}')
        print(100 * '-')
        for prediction_decimal in configurations.PREDICTION_DECIMALS:
            print(f'Prediction Decimal = {prediction_decimal}')
            predictions_base_address = f'{n_instances}_{prediction_decimal}'
            if os.path.isdir(predictions_base_address):
                shutil.rmtree(predictions_base_address)
            os.mkdir(predictions_base_address)
            for sample_number in range(configurations.N_SAMPLES):
                print(f'Sample {sample_number + 1}')
                predictions_df = pd.DataFrame(data={'real': np.random.randint(2, size=n_instances),
                                                    'class 1': np.round(np.random.rand(n_instances),
                                                                        decimals=prediction_decimal)})
                predictions_address = f'{predictions_base_address}/sample_{sample_number+1}.csv'
                predictions_df.to_csv(predictions_address, index=False)
    return


if __name__ == '__main__':
    generate_predictions()
