#!/bin/bash
#SBATCH --partition=amd-512  # partição para a qual o job é enviado
#SBATCH --time=0-0:5
#SBATCH --nodes=2 #número de nós
#SBATCH --ntasks-per-node=1 #número de tarefas por nó
#SBATCH --hint=compute_bound 

#programa a ser executado.
#srun: executa jobs em paralelo
#srun ping_pong_mpi 

#alternativa para casos em que srun não funciona:
mpirun -np 2 ping_pong_mpi
