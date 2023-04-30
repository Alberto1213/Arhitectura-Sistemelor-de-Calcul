/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	double *C;

	/**
	 * DTRMM(A, B) -> B = alpha * B * op(A)
	 *  > B = A
	 *  > A = A -- op(A) = A^t
	 *   -----------------------
	 *  >> A = A * A^t
	*/
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.f, A, N, A, N);

	C = (double *)calloc(N * N, sizeof(double));

	/**
	 * DSYRK(A, C) -> C = alpha * A^t * A
	 *  > A = B
	 *  > C = C
	*/
	cblas_dsyrk(CblasRowMajor, CblasUpper, CblasTrans, N, N, 1.f, B, N, 0.f, C, N);
	cblas_dsyrk(CblasRowMajor, CblasLower, CblasTrans, N, N, 1.f, B, N, 0.f, C, N);

	/**
	 * DGEMM(A, B, C)
	 *  > A = B
	 *  > B = A
	 *  > C = C
	*/
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.f, B, N, A, N, 1.f, C, N);

	return C;
}
