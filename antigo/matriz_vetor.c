#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

// Definições de tamanho (para fins de teste rápido)
//#define M_GLOBAL 32000 // Número total de linhas da matriz A
//#define N_GLOBAL 16000  // Número total de colunas da matriz A e tamanho do vetor x

// Protótipo para inicialização
void initialize_matrix_and_vector(double *A, double *x, int M, int N);

int main(int argc, char *argv[]) {
    int rank, size;
    double start_time, end_time;

    // Inicialização do MPI
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

    // --- Determinação da Distribuição de Dados ---
    // O número de linhas distribuídas para cada processo
    int rows_per_proc = M / size;
    int local_M = rows_per_proc;
    // O processo raiz (rank 0) pode precisar lidar com o resto
    int rest_rows = M % size;

    // Ajusta o local_M (linhas locais) se houver um resto.
    // Neste modelo, faremos o rank 0 lidar com o resto.
    // É uma simplificação comum para evitar complexidade na lógica de scatter/gather.
    // Para simplificar o uso do MPI_Scatter, faremos o ajuste manual de rows_per_proc
    // para que a divisão seja igual ou tratemos o resto *após* a distribuição.
    // No código abaixo, vamos assumir que M é divisível por size para usar o MPI_Scatter
    // de forma mais limpa, ou que o resto será descartado/ignorado temporariamente,
    // mas para um resultado correto: M DEVE SER DIVISÍVEL POR size.
    if (M % size != 0) {
        if (rank == 0) {
            fprintf(stderr, "AVISO: M (%d) não é divisível pelo número de processos (%d). ", M, size);
            fprintf(stderr, "O programa funcionará com M' = %d (M' = M - (M %% size)).\n", M - rest_rows);
        }
        M -= rest_rows; // Reduz M para o maior múltiplo de size
        local_M = M / size;
    }

    // --- Alocação de Memória ---
    double *A_global = NULL; // Matriz completa A (somente no rank 0)
    double *x_global = NULL; // Vetor x (em todos os processos após Bcast)
    double *y_global = NULL; // Vetor resultado y (somente no rank 0)
    double *A_local = NULL;  // Bloco local de linhas de A
    double *y_local = NULL;  // Bloco local de resultados y

    // Alocação no Processo Raiz (rank 0)
    if (rank == 0) {
        A_global = (double *)malloc(M * N * sizeof(double));
        x_global = (double *)malloc(N * sizeof(double));
        y_global = (double *)malloc(M * sizeof(double));
        
        // Inicialização de A e x
        initialize_matrix_and_vector(A_global, x_global, M, N);
        
        // Início da contagem de tempo
        start_time = MPI_Wtime();
    }
    
    // Alocação em Todos os Processos
    A_local = (double *)malloc(local_M * N * sizeof(double));
    // Mesmo que x_global seja alocado no rank 0, ele será substituído pelo Bcast
    // Alocamos x_global aqui para que todos os processos tenham o buffer de destino para Bcast
    if (rank != 0) {
        x_global = (double *)malloc(N * sizeof(double));
    }
    y_local = (double *)malloc(local_M * sizeof(double));

    // ----------------------------------------------------------------------
    // 1. DISTRIBUIÇÃO DO VETOR x com MPI_Bcast
    // Aclausula MPI_Bcast: Envia o vetor x_global completo para todos os processos
    // ----------------------------------------------------------------------
    MPI_Bcast(
        x_global,       // Buffer de envio/recebimento
        N,              // Contagem de elementos
        MPI_DOUBLE,     // Tipo de dado
        0,              // Rank do processo raiz
        MPI_COMM_WORLD  // Comunicador
    );

    // ----------------------------------------------------------------------
    // 2. DISTRIBUIÇÃO DA MATRIZ A com MPI_Scatter
    // Aclausula MPI_Scatter: Divide A por linhas (local_M * N elementos)
    // ----------------------------------------------------------------------
    MPI_Scatter(
        A_global,       // Buffer de envio (somente no rank 0)
        local_M * N,    // Contagem de elementos para CADA processo
        MPI_DOUBLE,     // Tipo de dado
        A_local,        // Buffer de recebimento
        local_M * N,    // Contagem de elementos recebidos
        MPI_DOUBLE,     // Tipo de dado
        0,              // Rank do processo raiz
        MPI_COMM_WORLD  // Comunicador
    );

    // ----------------------------------------------------------------------
    // 3. CÁLCULO LOCAL: y_local = A_local * x_global
    // Cada processo calcula o produto para as suas linhas
    // ----------------------------------------------------------------------
    for (int i = 0; i < local_M; i++) {
        y_local[i] = 0.0;
        for (int j = 0; j < N; j++) {
            // A_local[i * N + j] é A[linha_local][coluna]
            y_local[i] += A_local[i * N + j] * x_global[j];
        }
    }

    // --- BARREIRA para sincronizar antes do gather ---
    MPI_Barrier(MPI_COMM_WORLD);

    // ----------------------------------------------------------------------
    // 4. AGREGAÇÃO DO RESULTADO com MPI_Gather
    // Aclausula MPI_Gather: Recolhe os blocos y_local para o vetor y_global no rank 0
    // ----------------------------------------------------------------------
    MPI_Gather(
        y_local,        // Buffer de envio (o resultado local)
        local_M,        // Contagem de elementos enviados por CADA processo
        MPI_DOUBLE,     // Tipo de dado
        y_global,       // Buffer de recebimento (somente no rank 0)
        local_M,        // Contagem de elementos recebidos de CADA processo
        MPI_DOUBLE,     // Tipo de dado
        0,              // Rank do processo raiz
        MPI_COMM_WORLD  // Comunicador
    );

    // ----------------------------------------------------------------------
    // 5. FINALIZAÇÃO e Análise de Tempo (somente no rank 0)
    // ----------------------------------------------------------------------
    if (rank == 0) {
        end_time = MPI_Wtime();
        double elapsed_time = end_time - start_time;

        printf("--- Produto Matriz-Vetor Distribuído ---\n");
        printf("Tamanho da Matriz A: %d x %d\n", M_GLOBAL, N_GLOBAL);
        printf("Número de Processos: %d\n", size);
        printf("Linhas por Processo (M/size): %d\n", local_M);
        printf("Tempo de Execução (Computação + Comunicação): %.6f segundos\n", elapsed_time);
        
    }

    // --- Liberação de Memória ---
    free(A_local);
    free(y_local);
    if (rank == 0) {
        free(A_global);
        free(y_global);
        free(x_global); 
    } else {
        free(x_global); 

    // Finalização do MPI
    MPI_Finalize();

    return 0;
}

// Função auxiliar para inicializar a matriz e o vetor
void initialize_matrix_and_vector(double *A, double *x, int M, int N) {
    // Inicialização determinística para reprodutibilidade
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Exemplo simples: A[i][j] = i + j
            A[i * N + j] = (double)(i % 10 + j % 10) / 10.0;
        }
    }
    for (int j = 0; j < N; j++) {
        // Exemplo simples: x[j] = 1
        x[j] = 1.0;
    }
}
