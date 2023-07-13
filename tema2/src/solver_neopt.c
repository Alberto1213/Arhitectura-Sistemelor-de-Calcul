#include "utils.h"

//functie pentru a calcula transpusa unei matrici
double *trans(int N,double *M){
	//matricea Mt este matricea in care se retine transpusa
	double *Mt = (double *) calloc (N * N , sizeof(double));
	
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			Mt[j * N + i] = M[i * N + j];
		
	return Mt;
	free(Mt);
}
//functie pentru a calcula transpusa unei matrici superior triunghiulare
double *trans_triangular(int N, double *M){
	//matricea transpusa
	double *Mt = (double *) calloc(N * N , sizeof(double));

	for (int i = 0; i < N; i++) 
		for (int j = i; j < N; j++) 
			Mt[j * N + i] = M[i * N + j];

	return Mt;
	free(Mt);
}
//functie pentru a calcula produsul a doua matrici oarecare
double *mult(int N,double *M1,double *M2){
	//matricea in care se va retine produsul
	double *P = (double *) calloc(N * N , sizeof(double));

	for(int i = 0; i < N; i++) 
		for(int j = 0; j < N; j++) 
			for(int k = 0; k < N; k++) 
				P[i * N + j] += M1[i * N + k] * M2[k * N + j];
		
	return P;
	free(P);
}
//funtie pentru a calcula produsul dintre o mat superior triunghiulara si o mat oarecare
double *mult_superior_triangular(int N,double *M,double *M_sup){
	//matrice in care se va retine produsul celor doua matrici
	double *P = (double *) calloc(N * N , sizeof(double));

	for(int i = 0; i < N; i++) 
		for(int j = 0; j < N; j++) 
			for(int k = i; k < N; k++) 
				P[i * N + j] += M[i * N + k] * M_sup[k * N + j];

	return P;
	free(P);
}
//avem nevoie de inmultire intre oarecare X inf triunghiulara
double *mult_inferior_triangular(int N,double *M,double *M_inf){
	//matrice in care se retine produsul celor doua matrici
	double *P = (double *) calloc(N * N , sizeof(double));

	for(int i = 0; i < N; i++) 
		for(int j = 0; j < N; j++) 
			for(int k = j; k < N; k++) 
				P[N * i + j] += M[i * N + k] * M_inf[k * N + j];
			
	return P;
	free(P);
}
double *my_solver(int N,double* A,double* B){
	//matricea in care se retine produsul AB
	double *P1;
	//matricea in care se retine produsul ABAt = P1At
	double *T1;
	//matricea in care se retine produsul BtBt
	double *T2;
	//matricea trasnpusa lui A
	double *At;
	//matricea transpusa lui B
	double *Bt;

	//produsul AB
	P1 = mult_superior_triangular(N,A,B);
	//transpusa lui A
	At = trans_triangular(N,A);
	//produsul ABAt
	T1 = mult_inferior_triangular(N,P1,At);
	//matricea transpusa lui B
	Bt = trans(N,B);
	//produsul BtBt
	T2 = mult(N,Bt,Bt);

	//calculam rezultatul final
	double *R = (double *) calloc(N * N , sizeof(double));
	for(int i = 0; i < N; i++) 
		for(int j = 0; j < N; j++) 
			R[N * i + j] += T1[N * i + j] + T2[N * i + j];
		
	

	free(P1);
	free(T1);
	free(T2);
	free(At);
	free(Bt);

	return R;
	free(R);
}

