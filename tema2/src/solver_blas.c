#include "cblas.h"
#include "utils.h"

double* my_solver(int N, double *A, double *B) {

	double *T = (double *) calloc(N * N, sizeof(double));
	double *A_aux = (double*) calloc(N * N, sizeof(double));
	
	//copiem matricea A in A_aux
	cblas_dcopy(N * N, A, 1, A_aux, 1);
	// se calculeaza T = Bt * Bt;
	cblas_dgemm(CblasRowMajor,CblasTrans,CblasTrans,N,N,N,1.0,B,N,B,N,0.0,T,N);
	//se calculeaza B = AB
	cblas_dtrmm(CblasRowMajor,CblasLeft,CblasUpper,CblasNoTrans,CblasNonUnit,N,N,1.0,A,N,B,N);
        //se calculeaza T = BAt + T
	cblas_dgemm(CblasRowMajor, CblasNoTrans ,CblasTrans,N,N,N,1.0,B,N,A_aux,N,1.0,T,N); 
	
	free(A_aux);
	return T;
       free(T);
}

