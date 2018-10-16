#ifndef X_H
#define X_H

#include "matlab_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void qrsolve(const double A[1536], const double B[512], double Y[3], int *
                    rankR);
int rankFromQR(const double A[1024]);

void b_xgeqp3(double A[1536], double tau[3], int jpvt[3]);
void xgeqp3(double A[1024], double tau[2], int jpvt[2]);

void b_xgemv(int m, int n, const double A[1536], int ia0, const double x
                    [1536], int ix0, double y[3]);
void xgemv(int m, int n, const double A[1024], int ia0, const double x
                  [1024], int ix0, double y[2]);

void b_xswap(double x[1536], int ix0, int iy0);
void xswap(double x[1024], int ix0, int iy0);

int b_ixamax(int n, const double x[3], int ix0);
int ixamax(int n, const double x[2], int ix0);

double b_xnrm2(int n, const double x[1024], int ix0);
double c_xnrm2(const double x[1536], int ix0);
double d_xnrm2(int n, const double x[1536], int ix0);
double xnrm2(const double x[1024], int ix0);

void b_xzlarf(int m, int n, int iv0, double tau, double C[1536], int ic0,
                     double work[3]);
void xzlarf(int m, int n, int iv0, double tau, double C[1024], int ic0,
                   double work[2]);

double b_xzlarfg(int n, double *alpha1, double x[1536], int ix0);
double xzlarfg(int n, double *alpha1, double x[1024], int ix0);

void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                    double A[1536], int ia0);
void xgerc(int m, int n, double alpha1, int ix0, const double y[2],
                  double A[1024], int ia0);

#endif // X_H

