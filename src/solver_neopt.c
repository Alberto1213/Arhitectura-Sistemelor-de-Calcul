/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	int i, j, k;

	double *t1, *aux; 
	double *t2;
	double *res;

	t1 = calloc(N * N, sizeof(double));
	aux = calloc(N * N, sizeof(double));

	t2 = calloc(N * N, sizeof(double));

	/**
	 * each element [i][j] --> i * N + j
	 */

	/**
	 * aux = B * A
	 */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			/**
			 * A - upper triangular
			 *  > A[k][j] in the upper side for k <= j
			 */
			for (k = 0; k <= j; ++k) {
				aux[i * N + j] += B[i * N + k] *
								  A[k * N + j];
			}
		}
	}

	/**
	 * t1 = aux * (A^t)
	 */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			/**
			 * A^t --> (A^t)[k][j] = A[j][k]
			 * 
			 * A - upper triangular
			 * A[j][k] in the upper side for j <= k
			 */
			for (k = j; k < N; ++k) {
				t1[i * N + j] += aux[i * N + k] *
								 A[j * N + k];
			}
		}
	}

    /**
	 * t2 = (B^t) * B
	 */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			/**
			 * B^t --> (B^t)[i][k] = B[k][i]
			 */
			for (k = 0; k < N; ++k) {
				t2[i * N + j] += B[k * N + i] *
							     B[k * N + j];
			}
		}
	}

	res = calloc(N * N, sizeof(double));

	/**
	 * res = t1 + t2
	 */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			res[i * N + j] = t1[i * N + j] +
							 t2[i * N + j];
		}
	}

	// free()
	free(aux);
	free(t1);

	free(t2);

	return res;
}
