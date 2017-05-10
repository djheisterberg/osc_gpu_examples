#ifndef DIAG_IMPL_H
#define DIAG_IMPL_H

void diagInit();
void diagFinalize();
int getEDir();
double diag(int mn, double *a, double *d, long *lstat);

#endif /* DIAG_IMPL_H */
