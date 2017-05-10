## Magma diagonalization

Before building or running execute

`module load cuda/8.0.44`  
`module load mkl`  
`module load magma/2.2.0`  

There are two make targets

* diagGPU -- the magma GPU version
* diagMKL -- the Intel MKL multi-threaded CPU version

Run either with ./diagXXX N where N is the matrix size.  If N < 10 the
matrix, eigenvalues and eigenvectors are printed.  A size of 8192 shows
about a 2-to-1 speedup of the gpu vs. 28 cpus on owens (about 1 to 2
minutes).

For either version an initial matrix is generated using OpenMP and MKL.
Set the OMP_NUM_THREADS environment variable to control the number of
cpus used in generation and MKL diagonalization.
