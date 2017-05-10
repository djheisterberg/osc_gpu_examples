#include <mkl.h>

#include "diagCommon.h"
#include "diagImpl.h"

#define E_DIR 1

void diagInit() {
}

void diagFinalize() {
}

int getEDir() {
   return E_DIR;
}

double diag(int mn, double *a, double *d, long *lstat) {

   double t0 = wall_seconds();
   *lstat = LAPACKE_dsyevd(LAPACK_ROW_MAJOR, 'V', 'U', mn, a, mn, d);
   double t1 = wall_seconds() - t0;

   return t1;
}
