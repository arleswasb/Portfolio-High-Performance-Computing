#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

// Protótipo para inicialização
void initialize_matrix_and_vector(double *A, double *x, int M, int N);

int main(int argc, char *argv[]) {
    int rank, size;
    double start_time, end_time;

    // Inicialização do MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // --- AJUSTE 1: Receber apenas um argumento (M) ---
    if (argc < 2) {
        if (rank == 0) {
            fprintf(stderr, "Uso: %s <M_tamanho_matriz_quadrada>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    int M_GLOBAL = atoi(argv[1]);
    int N_GLOBAL = M_GLOBAL; // Força a matriz a ser quadrada
    // ----------------------------------------------------

    // Validação da divisibilidade
    if (rank == 0) {
        if (M_GLOBAL % size != 0) {
            fprintf(stderr, "ERRO: O tamanho da matriz M (%d) não é divisível pelo número de processos (%d).\n", M_GLOBAL, size);
            fprintf(stderr, "Por favor, ajuste os parâmetros para garantir a divisibilidade.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }
    
    int local_M = M_GLOBAL / size;

    // --- Alocação de Memória ---
    double *A_global = NULL;
    double *x_global = NULL;
    double *y_global = NULL;
    
    if (rank == 0) {
        A_global = (double *)malloc(M_GLOBAL * N_GLOBAL * sizeof(double));
        x_global = (double *)malloc(N_GLOBAL * sizeof(double));
        y_global = (double *)malloc(M_GLOBAL * sizeof(double));
        
        initialize_matrix_and_vector(A_global, x_global, M_GLOBAL, N_GLOBAL);
        
        start_time = MPI_Wtime();
    }
    
    // Alocação em Todos os Processos
    double *A_local = (double *)malloc(local_M * N_GLOBAL * sizeof(double));
    x_global = (double *)malloc(N_GLOBAL * sizeof(double));
    double *y_local = (double *)malloc(local_M * sizeof(double));

    // 1. DISTRIBUIÇÃO DO VETOR x com MPI_Bcast
    MPI_Bcast(x_global, N_GLOBAL, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // 2. DISTRIBUIÇÃO DA MATRIZ A com MPI_Scatter
    MPI_Scatter(
        A_global,
        local_M * N_GLOBAL,
        MPI_DOUBLE,
        A_local,
        local_M * N_GLOBAL,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    // 3. CÁLCULO LOCAL
    for (int i = 0; i < local_M; i++) {
        y_local[i] = 0.0;
        for (int j = 0; j < N_GLOBAL; j++) {
            y_local[i] += A_local[i * N_GLOBAL + j] * x_global[j];
        }
    }

    // 4. AGREGAÇÃO DO RESULTADO com MPI_Gather
    MPI_Gather(
        y_local,
        local_M,
        MPI_DOUBLE,
        y_global,
        local_M,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    // 5. FINALIZAÇÃO e Análise de Tempo
    if (rank == 0) {
        end_time = MPI_Wtime();
        double elapsed_time = end_time - start_time;

        // --- AJUSTE 2: Atualizar a mensagem de saída ---
        printf("--- Produto Matriz-Vetor Distribuído (Matriz Quadrada) ---\n");
        printf("Tamanho da Matriz A: %d x %d\n", M_GLOBAL, M_GLOBAL);
        printf("Número de Processos: %d\n", size);
        printf("Linhas por Processo (M/size): %d\n", local_M);
        printf("Tempo de Execução (Computação + Comunicação): %.6f segundos\n", elapsed_time);
        // ---------------------------------------------
    }

    // --- Liberação de Memória ---
    free(A_local);
    free(y_local);
    free(x_global); 
    if (rank == 0) {
        free(A_global);
        free(y_global);
    }

    MPI_Finalize();
    return 0;
}

// Função auxiliar para inicializar a matriz e o vetor
void initialize_matrix_and_vector(double *A, double *x, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i % 10 + j % 10) / 10.0;
        }
    }
    for (int j = 0; j < N; j++) {
        x[j] = 1.0;
    }
}
