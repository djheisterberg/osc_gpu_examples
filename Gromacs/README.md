## Gromacs

This is the 'water-cut1.0_GMX50_bare/3072' case from http://www.nvidia.com/object/running-jobs-in-gromacs.html

There are four run configurations:

`water3072-pme.1.28.0.pbs -- CPU run, 1 node, 28 cpus`  
`water3072-pme.1.28.1.pbs -- GPU run, 1 node, 28 cpus, 1 gpu`  
`water3072-pme.2.28.0.pbs -- CPU run, 2 nodes, 28 cpus (per node)`  
`water3072-pme.2.28.1.pbs -- GPU run, 2 nodes, 1 cpu, 1 gpu (per node)`  

Gromacs takes the approach of using different executables for CPU/GPU runs.
The GPU is used for PP (non-bonded, near-field, particle-particle) interactions.
The CPU is used for bonded and PME (far-field, particle-mesh) interactions.

### Sample wallclock times for the runs:

`water3072-pme.1.28.0.pbs -- 00:28:47`
`water3072-pme.1.28.1.pbs -- 00:12:25
`water3072-pme.2.28.0.pbs -- 00:14:45`
`water3072-pme.2.28.1.pbs -- 00:06:02

* Scaling across multiple nodes and GPUs is very good.

The GPU runs use -ntomp 1, which may not be optimal, but trying to use multiple
openMP threads results in out-of-memory errors.
