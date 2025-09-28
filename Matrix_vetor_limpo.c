#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

// Protótipo da função de inicialização
void initialize_matrix_and_vector(double *A, double *x, int M, int N);

int main(int argc, char *argv[]) {
    int rank, size;
    double start_time, end_time;

    // 1. Inicialização do ambiente MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0) {
            fprintf(stderr, "Uso: %s <M_linhas> <N_colunas>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    int M_GLOBAL = atoi(argv[1]);
    int N_GLOBAL = atoi(argv[2]);
    int M = M_GLOBAL;
    int N = N_GLOBAL;

    // Para um Scatter simples, M deve ser divisível pelo número de processos.
    // O código ajusta M para o maior múltiplo de 'size' menor que o M original.
    if (M % size != 0) {
        if (rank == 0) {
            fprintf(stderr, "AVISO: M (%d) não é divisível por %d. Ajustando M para %d.\n", M, size, M - (M % size));
        }
        M -= (M % size);
    }
    
    // O número de linhas que cada processo irá gerenciar
    int local_M = M / size;

    // Alocação de memória
    double *A_global = NULL; // Matriz completa (somente no rank 0)
    double *y_global = NULL; // Vetor resultado (somente no rank 0)
    double *x = (double *)malloc(N * sizeof(double)); // Vetor x (em todos os processos)
    double *A_local = (double *)malloc(local_M * N * sizeof(double));  // Bloco local da matriz A
    double *y_local = (double *)malloc(local_M * sizeof(double));  // Bloco local do resultado y

    // O processo raiz (rank 0) aloca e inicializa os dados completos
    if (rank == 0) {
        A_global = (double *)malloc(M * N * sizeof(double));
        y_global = (double *)malloc(M * sizeof(double));
        initialize_matrix_and_vector(A_global, x, M, N);
        
        // Início da contagem de tempo
        start_time = MPI_Wtime();
    }
    
    // 2. Distribuição de Dados
    // Envia o vetor 'x' completo para todos os processos
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Distribui as linhas da matriz 'A_global' entre todos os processos
    MPI_Scatter(A_global, local_M * N, MPI_DOUBLE, 
                A_local, local_M * N, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);

    // Sincroniza todos os processos antes da computação
    MPI_Barrier(MPI_COMM_WORLD);

    // 3. Computação Local
    // Cada processo calcula o produto para sua porção local da matriz
    for (int i = 0; i < local_M; i++) {
        y_local[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y_local[i] += A_local[i * N + j] * x[j];
        }
    }

    // 4. Agregação de Resultados
    // Reúne os resultados locais 'y_local' de cada processo no vetor 'y_global' do processo raiz
    MPI_Gather(y_local, local_M, MPI_DOUBLE, 
               y_global, local_M, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);

    // 5. Finalização e Saída
    // O processo raiz finaliza a contagem de tempo e exibe os resultados
    if (rank == 0) {
        end_time = MPI_Wtime();
        double elapsed_time = end_time - start_time;

        printf("--- Produto Matriz-Vetor Distribuído ---\n");
        printf("Tamanho da Matriz A: %d x %d\n", M_GLOBAL, N_GLOBAL);
        printf("Número de Processos: %d\n", size);
        printf("Linhas por Processo (M/size): %d\n", local_M);
        printf("Tempo de Execução (Computação + Comunicação): %.6f segundos\n", elapsed_time);
    }

    // Liberação de memória
    free(A_local);
    free(y_local);
    free(x);
    if (rank == 0) {
        free(A_global);
        free(y_global);
    }

    MPI_Finalize();
    return 0;
}

// Função para inicializar a matriz A e o vetor x com valores determinísticos
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