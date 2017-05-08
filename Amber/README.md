## Amber PMEMD

This is the 'STMV NPT HMR 4fs' case from http://ambermd.org/gpus/benchmarks.htm

There are six run configurations:

`stmv.1.1.1.pbs  -- GPU run, 1 node, 1 cpu, 1 gpu`  
`stmv.1.2.2.pbs  -- GPU run, 1 node, 2 cpus, 2 gpus (per node)`  
`stmv.1.28.0.pbs -- CPU run, 1 node, 28 cpus`  
`stmv.1.28.1.pbs -- mixed, 1 node, 28 cpus, 1 gpu`  
`stmv.2.1.1.pbs  -- GPU run, 2 nodes, 1 cpu, 1 gpu (per node)`  
`stmv.2.28.0.pbs -- CPU run, 2 nodes, 28 cpus (per node)`  

(Two gpus per node is not generally available at this time.)

Amber takes the approach of using different executables for CPU/GPU runs,
and doing the computation pretty much exclusively on the CPU or GPU.  The
mixed configuration is just for reference, it doesn't perform like you'd
hope.

The GPU runs request all the CPUs (but don't use them) for exclusive
access to the node.

### Sample wallclock times for the runs:

`stmv.1.1.1.pbs  -- 00:18:59`  
`stmv.1.2.2.pbs  -- 00:27:20`  
`stmv.1.28.0.pbs -- 03:48:25`  
`stmv.1.28.1.pbs -- don't run this!`  
`stmv.2.1.1.pbs  -- 00:23:20`  
`stmv.2.28.0.pbs -- 02:14:12`  

* Multi-node performance is pretty good.
* Single gpu performance is great.
* Amber doesn't split well over multiple GPUs, except maybe for really big runs.
