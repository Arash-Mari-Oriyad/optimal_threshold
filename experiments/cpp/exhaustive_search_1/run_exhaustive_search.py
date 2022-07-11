import os
import shutil

from configurations import N_SAMPLES, N_INSTANCES_LIST, PREDICTION_DECIMALS, SAMPLES_DIRECTORY_ADDRESS


def main():
    os.system('g++ exhaustive_search.cpp -Wall -lglpk -o exhaustive_search.out')
    if not os.path.exists('results'):
        os.makedirs('results')
    for n_instances in N_INSTANCES_LIST:
        for prediction_decimal in PREDICTION_DECIMALS:
            if os.path.exists(f'results/{n_instances}_{prediction_decimal}'):
                shutil.rmtree(f'results/{n_instances}_{prediction_decimal}')
            os.makedirs(f'results/{n_instances}_{prediction_decimal}')
            os.system(f'./exhaustive_search.out {SAMPLES_DIRECTORY_ADDRESS}/{n_instances}_{prediction_decimal} '
                      f'{N_SAMPLES} {n_instances} {prediction_decimal}')
    os.remove('exhaustive_search.out')


if __name__ == '__main__':
    main()
