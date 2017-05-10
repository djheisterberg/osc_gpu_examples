#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Random64.h"
#include "diagCommon.h"
#include "diagImpl.h"

int main(int argc, char** argv) {

   if (argc < 2) {
      printf("USAGE: %s N\n", argv[0]);
      return 1;
   }
   int mn = atoi(argv[1]);
   int mn2 = mn * mn;
   bool verbose = (mn < 10);

   int eDir = getEDir();
   diagInit();
   Random64 rnd = Random64(8675309);

   double* e = dmalloc(mn2);
   double te0 = wall_seconds();
   initE(rnd, mn, e);
   double te1 = wall_seconds() - te0;

   if (verbose) {
      puts("\nE\n");
      printMatrix(mn, e);
      puts("\nE norm\n");
      printNorm(mn, e);
   }

   double* a = dmalloc(mn2);
   double* w = dmalloc(mn2);
   double ta0 = wall_seconds();
   initA(eDir, mn, e, a, w);
   double ta1 = wall_seconds() - ta0;
   mfree(w);

   if (verbose) {
      puts("\nA\n");
      printMatrix(mn, a);
   }

   double* d = dmalloc(mn);
   long lstat;
   double td = diag(mn, a, d, &lstat);

   printf("%15.6lf seconds generation\n", te1);
   printf("%15.6lf seconds orthogonalization\n", ta1);
   printf("%15.6lf seconds diagonalization\n", td);

   if (lstat) {
      printf("\ndiag returned %ld\n", lstat);
   }

   for (int i = 0; i < mn; i++) {
      double dd = getEV(1, mn, i);
      double err = abs(d[i] - getEV(eDir, mn, i)) / dd;
      if (err > 0.00001) {
         printf("\n bad eigenvalue %d, %15.6lf should be %15.6lf\n", i, d[i], dd);
         break;
      }
   }

   if (verbose) {
      puts("\nD\n");
      for (int i = 0; i < mn; i++) {
         printf("%15.6lf", d[i]);
      }
      puts("\n");

      puts("\nV\n");
      printMatrix(mn, a);
      puts("\nV norm\n");
      printNorm(mn, a);
   }

   mfree(d);
   mfree(a);
   mfree(e);

   diagFinalize();
   return 0;
}

