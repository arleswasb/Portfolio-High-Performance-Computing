
/////////////////////////////////////////////////////
////////////////VERSÃO 02////////////////////////////
/////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Definição global do número de passos para consistência
const long NUM_PASSOS = 100000000;
long pontos_no_circulo_total = 0;

void pi_paralelo_vetor_compartilhado() {
    long *acertos_por_thread; // Ponteiro para o nosso vetor compartilhado
    int num_threads;

    // Pega o número de threads que o OpenMP decidiu usar
    num_threads = omp_get_max_threads();
    // Aloca o vetor com o tamanho exato do número de threads.
    // calloc já inicializa o vetor com zeros.
    acertos_por_thread = (long *)calloc(num_threads, sizeof(long));
    if (acertos_por_thread == NULL) {
        printf("Falha ao alocar memoria.\n");
        exit(1);
    }

    // Início da região paralela
    #pragma omp parallel
    {

        // Pega o identificador (ID) da thread atual
        int tid = omp_get_thread_num();
        
        #pragma omp for
        for (long i = 0; i < NUM_PASSOS; i++){
            // O gerador rand() não é "thread-safe".
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            if (x * x + y * y < 1.0) {
                // Cada thread incrementa APENAS a sua própria posição no vetor.
                acertos_por_thread[tid]++;
            }
        }
    } // Fim da região paralela

    for (int i = 0; i < num_threads; i++) {
        pontos_no_circulo_total += acertos_por_thread[i];
    }
    
    // Libera a memória alocada para o vetor
    free(acertos_por_thread);
}


int main() {
    double start_time, end_time;

    printf("Iniciando analise de desempenho para %ld passos.\n", NUM_PASSOS);
    
    // --- Executando a nova versão ---
    pontos_no_circulo_total = 0; // Reseta a contagem global
    start_time = omp_get_wtime();
    pi_paralelo_vetor_compartilhado();
    end_time = omp_get_wtime();
    
    double tempo_paralelo_vetor = end_time - start_time;
    double pi_estimado = 4.0 * pontos_no_circulo_total / NUM_PASSOS;
    
    printf("\n--- Versao com Vetor Compartilhado ---\n");
    printf("Estimativa paralela de pi = %f\n", pi_estimado);
    printf("Tempo Paralelo: %f segundos\n", tempo_paralelo_vetor);

    return 0;
}
