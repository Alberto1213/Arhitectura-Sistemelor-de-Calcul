/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	int i, j, k;

	double *t1, *aux;

	t1 = calloc(N * N, sizeof(double));
	aux = calloc(N * N, sizeof(double));

	/**
	 * each element [i][j] --> i * N + j
	*/

	/**
	 * aux = B * A
	*/
	double *ob_init = &B[0];
	double *oaux_init = &aux[0];

	for (i = 0; i < N; ++i) {
		double *opb = ob_init;
		double *opa = &A[0];
		double *oaux = oaux_init;

		for (k = 0; k < N; ++k) {
			double *pa = opa;
			double *paux = oaux;

			register double pb = *opb;

			/**
			 * A - upper triangular
			 *  > A[k][j] in the upper side for k <= j
			*/
			for (j = k; j < N; ++j) {
				*paux += pb * *pa;

				++paux;
				++pa;
			}

			++opb;

			/**
			 * next step
			 *  > starts with A[k + 1][k + 1]
			 *  > (k * N + _N_) + (k + _1_)
			*/
			++opa;
			opa += N;

			++oaux;
		}

		ob_init += N;
		oaux_init += N;
	}

	/**
	 * t1 += aux * (A^t)
	*/
	double *opaux = &aux[0];
	double *ot1 = &t1[0];

	for (i = 0; i < N; ++i) {
		double *opat = &A[0];

		for (j = 0; j < N; ++j) {
			double *paux = opaux + j;
			double *pat = opat;

			register double curr = 0.0;

			/**
			 * A^t --> (A^t)[k][j] = A[j][k]
			 * 
			 * A - upper triangular
			 * A[j][k] in the upper side for j <= k
			*/
			for (k = j; k < N; ++k) {
				curr += *paux *
						*pat;

				++paux;
				++pat;
			}

			// t1[i * N + j] += curr;
			*(ot1 + j) += curr;

			// next from A[j + 1][j + 1]
			++opat;
			opat += N;
		}

		opaux += N;
		ot1 += N;
	}

	/**
	 * t1 += (B^t) * B
	*/
	double *opbt_init = &B[0];
	double *opb_init = &B[0];
	double *opt1 = &t1[0];

	for (i = 0; i < N; ++i) {
		double *opbt = opbt_init;
		double *opb = opb_init;

		for (k = 0; k < N; ++k) {
			register double pbt = *opbt;
			double *pb = opb;
			double *pt1 = opt1;

			/**
			 * B^t --> (B^t)[i][k] = B[k][i]
			*/
			for (j = 0; j < N; ++j) {
				*pt1 += pbt *
						*pb;
				
				++pb;
				++pt1;
			}

			opb += N;
			opbt += N;
		}

		++opbt_init;
		opt1 += N;
	}

	// free()
	free(aux);

	return t1;
}
