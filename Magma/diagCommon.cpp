#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <mkl.h>

#include "diagCommon.h"
#include "Random64.h"

#define ALIGN 64

double *dmalloc(int n) {
   return (double *) mkl_malloc(n * sizeof(double), ALIGN);
}

int *imalloc(int n) {
   return (int *) mkl_malloc(n * sizeof(long), ALIGN);
}

void mfree(void *p) {
   mkl_free(p);
}

void initE(Random64& rnd0, int n, double *ep) {
   MATRIX(n, ep, e);

   // initial, random fill
   #pragma omp parallel
   {
      Random64 rnd = rnd0;
      int tid = omp_get_thread_num();
      for (int i = 0; i < tid + 1; i++) {
         rnd.jump();
      }

      #pragma omp for
      for (int j = 0; j < n; j++) {
         for (int i = 0; i < n; i++) {
            e[j][i] = rnd.nextDouble();
         }
      }
   }

   // normalize each row, project out of subsequent rows
   for (int k = 0; k < n; k++) {
      double t = cblas_dnrm2(n, e[k], 1);
      cblas_dscal(n, 1.0 / t, e[k], 1);

      #pragma omp parallel for
      for (int j = k + 1; j < n; j++) {
         double t = cblas_ddot(n, e[k], 1, e[j], 1);
         cblas_daxpy(n, -t, e[k], 1, e[j], 1);
      }
   }
}

double getEV(int dir, int n, int i) {
   return (dir >= 0) ? (i + 0.5) / n : (n - i - 0.5) / n;
}

void initA(int dir, int n, double *ep, double *ap, double *wp) {
   MATRIX(n, ep, e);
   MATRIX(n, ap, a);
   MATRIX(n, wp, w);
   
   #pragma omp parallel for
   for (int j = 0; j < n; j++) {
      cblas_dcopy(n, e[j], 1, w[j], 1);
      double d = getEV(dir, n, j);
      cblas_dscal(n, d, w[j], 1);
   }

   cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, n, 1.0, (double*) e, n, (double*) w, n, 0.0, (double*) a, n);
}

void printMatrix(int n, double *ap) {
   MATRIX(n, ap, a);

   for (int j = 0; j < n; j++) {
      for (int i = 0; i < n; i++) {
         printf("%15.6lf", a[j][i]);
      }
      puts("\n");
   }
}

void printNorm(int n, double *ap) {
   MATRIX(n, ap, a);

   for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
         double t = cblas_ddot(n, a[k], 1, a[j], 1);
         printf("%15.6lf", t);
      }
      puts("\n");
   }
}

double wall_seconds() {
   struct timeval time;
   gettimeofday(&time, NULL);
   return time.tv_sec + 0.000001 * time.tv_usec;
}
