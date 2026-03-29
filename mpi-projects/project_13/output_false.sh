#!/bin/bash
#SBATCH --job-name=multithreading_navier
#SBATCH --time=0-2:00     
#SBATCH --partition=amd-512
#SBATCH --cpus-per-task=64
#SBATCH --exclusive       

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export OMP_PROC_BIND=false
export OMP_PLACES=sockets


pascalanalyzer ./navier_stokes_false -c 1,2,4,8,16,32,64 -i 32,64,128,512,1024,2048,4096 --inst aut -o output_false.json 
