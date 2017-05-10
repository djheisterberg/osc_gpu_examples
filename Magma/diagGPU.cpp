#include "magma_v2.h"
#include "magma_dlapack.h"

#include "diagCommon.h"
#include "diagImpl.h"

#define E_DIR 1

void diagInit() {
   magma_init();
}

void diagFinalize() {
   magma_finalize();
}

int getEDir() {
   return E_DIR;
}

double diag(int mn, double *a, double *d, long *lstat) {

   int block = magma_get_dsytrd_nb(mn);
   int ldwrk1 = (2 + block) * mn;
   int ldwrk2 = (1 + mn * (6 + 2 * mn));
   int ldwrk = (ldwrk1 > ldwrk2) ? ldwrk1 : ldwrk2;
   int liwrk = 3 + 5 * mn;
   double* dwrk = dmalloc(ldwrk);
   magma_int_t* iwrk = (magma_int_t*) imalloc(liwrk);

   double t0 = wall_seconds();
   magma_int_t lastat_syevd;
   magma_dsyevd(MagmaVec, MagmaUpper, mn, a, mn, d, dwrk, ldwrk, iwrk, liwrk, &lastat_syevd);
   double t1 = wall_seconds() - t0;
   mfree(iwrk);
   mfree(dwrk);

   *lstat = lastat_syevd;
   return t1;
}
