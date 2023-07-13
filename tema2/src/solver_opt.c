#include "utils.h"

double *TransUp(double *A, int N) {
	double *res = (double *) calloc(N * N , (sizeof(double)));

	for(int i = 0; i < N; i++) {
		register double *p = &A[i * N];
		for(int j = 0; j < N; j++) {
			res[j * N + i] = *(p + j);
		}
	}
	return res;
	free(res);
}
double *Trans(double *A, int N) {
	register double *res = (double *) calloc(N * N , (sizeof(double)));

	for(int i = 0; i < N; i++) {
		register double *p = &A[i * N];

		for(int j = 0; j < N; j++) {
			res[j * N + i] = *(p + j);
		}
	}
	return res;
	free(res);
}

double* my_solver(int N, double *A, double *B) {

	//Transpusa lui A
	double *ATrans = TransUp(A, N);
	//Transpusa lui B
	double *BTrans = Trans(B, N);
	//Termenul din Stanga
	double *T1 = (double *) calloc(N * N , sizeof(double));
	//Termenul din Dreapta
	double *T2 = (double *) calloc(N * N, sizeof(double));
	// B*A
	double *M = (double *) calloc(N * N , sizeof(double));
	//Result
	double *R = (double *) calloc(N * N , sizeof(double));

	for(int i = 0; i < N; i++) {
		register double *b_i = &B[N * i];
		for(int j = 0; j < N; j++) 
		if(i >= j)
		{
				register double *m_j = &M[N * j];
				register double a_j = A[N * j + i];

				for(int k = 0; k < N; k += 10){
						*(m_j + k + 0) += a_j * *(b_i + k + 0);
						*(m_j + k + 1) += a_j * *(b_i + k + 1);
						*(m_j + k + 2) += a_j * *(b_i + k + 2);
						*(m_j + k + 3) += a_j * *(b_i + k + 3);
						*(m_j + k + 4) += a_j * *(b_i + k + 4);

						*(m_j + k + 5) += a_j * *(b_i + k + 5);
						*(m_j + k + 6) += a_j * *(b_i + k + 6);
						*(m_j + k + 7) += a_j * *(b_i + k + 7);
                                                *(m_j + k + 8) += a_j * *(b_i + k + 8);
						*(m_j + k + 9) += a_j * *(b_i + k + 9);

				}
			}
		}
	//Termenul din stanga
	for(int i = 0; i < N; i++) {
		register double *at_j = &ATrans[N * i];

		for(int j = 0; j < N; j++) {
			if(i < N) {
				register double *t1_j = &T1[N * j];
				register double m_i = M[N * j + i];

				for(int k = 0; k < N; k += 10){
					if(k <= i - 10){
						*(t1_j + k + 0) += m_i * *(at_j + k + 0);
						*(t1_j + k + 1) += m_i * *(at_j + k + 1);
						*(t1_j + k + 2) += m_i * *(at_j + k + 2);
						*(t1_j + k + 3) += m_i * *(at_j + k + 3);
						*(t1_j + k + 4) += m_i * *(at_j + k + 4);

						*(t1_j + k + 5) += m_i * *(at_j + k + 5);
						*(t1_j + k + 6) += m_i * *(at_j + k + 6);
						*(t1_j + k + 7) += m_i * *(at_j + k + 7);
						*(t1_j + k + 8) += m_i * *(at_j + k + 8);
						*(t1_j + k + 9) += m_i * *(at_j + k + 9);						
					continue;
					}
					if(k <= i)
						*(t1_j + k + 0) += m_i * *(at_j + k + 0);
					if(k <= i)
						*(t1_j + k + 1) += m_i * *(at_j + k + 1);
					if(k <= i)
						*(t1_j + k + 2) += m_i * *(at_j + k + 2);
					if(k <= i)
						*(t1_j + k + 3) += m_i * *(at_j + k + 3);
					if(k <= i)
						*(t1_j + k + 4) += m_i * *(at_j + k + 4);
					if(k <= i)
						*(t1_j + k + 5) += m_i * *(at_j + k + 5);
					if(k <= i)
						*(t1_j + k + 6) += m_i * *(at_j + k + 6);
					if(k <= i)
						*(t1_j + k + 7) += m_i * *(at_j + k + 7);
                                        if(k <= i)
						*(t1_j + k + 8) += m_i * *(at_j + k + 8);
					if(k <= i)
						*(t1_j + k + 9) += m_i * *(at_j + k + 9);			
				}
			}
		}
	}
	//Termenul din dreapta
	for(int i = 0; i < N; i++) {
		register double *b_i = &BTrans[N * i];

		for(int j = 0; j < N; j++) {
				register double *t2_j = &T2[N * j];
				register double bt_j = BTrans[N * j + i];
				for(int k = 0; k < N; k += 10) {
						*(t2_j + k + 0) += bt_j * *(b_i + k + 0);
						*(t2_j + k + 1) += bt_j * *(b_i + k + 1);
						*(t2_j + k + 2) += bt_j * *(b_i + k + 2);
						*(t2_j + k + 3) += bt_j * *(b_i + k + 3);
						*(t2_j + k + 4) += bt_j * *(b_i + k + 4);

						*(t2_j + k + 5) += bt_j * *(b_i + k + 5);
						*(t2_j + k + 6) += bt_j * *(b_i + k + 6);
						*(t2_j + k + 7) += bt_j * *(b_i + k + 7);
						*(t2_j + k + 8) += bt_j * *(b_i + k + 8);
						*(t2_j + k + 9) += bt_j * *(b_i + k + 9);
				}
			}
		}

	//Rezultatul
	for(int i = 0; i < N; i++) {
		register double *r = &R[N * i];
		register double *t1_i = &T1[N * i];
		register double *t2_i = &T2[N * i];

		for(int j = 0; j < N; j++) {
			*(r + j) = *(t1_i + j) + *(t2_i + j);
		}
	}

	free(ATrans);
	free(BTrans);
	free(T1);
	free(T2);
	free(M);
	return R;
	free(R);
}

