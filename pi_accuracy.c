/**
 * @file pi_accuracy_comparison.c
 * @brief Compara o desempenho de duas implementações do cálculo de Pi
 * usando a série de Leibniz: uma sequencial e uma otimizada para ILP.
 * @author [Seu Nome]
 * @date 20 de Agosto de 2025
 *
 * Compilação: gcc pi_accuracy_comparison.c -o pi_comparison -lm
 * Execução:   ./pi_comparison
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // Necessário para M_PI

/**
 * @brief Calcula uma aproximação de Pi usando a série de Leibniz (versão sequencial).
 * Esta versão sofre de dependência de dados na variável 'sum'.
 * @param num_iterations O número de termos da série a serem calculados.
 * @return A aproximação de Pi.
 */
double calculate_pi_sequential(long long num_iterations) {
    double sum = 0.0;
    int sign = 1;

    for (long long i = 0; i < num_iterations; i++) {
        double term = (double)sign / (2.0 * i + 1.0);
        sum += term;
        sign *= -1;
    }

    return 4.0 * sum;
}

/**
 * @brief Calcula uma aproximação de Pi usando a série de Leibniz,
 * otimizada para Paralelismo em Nível de Instrução (ILP).
 * @param num_iterations O número de termos da série a serem calculados.
 * @return A aproximação de Pi.
 */
double calculate_pi_ilp(long long num_iterations) {
    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;

    for (long long i = 0; i < num_iterations; i += 4) {
        sum1 += 1.0 / (2.0 * i + 1.0);
        sum2 -= 1.0 / (2.0 * i + 3.0);
        sum3 += 1.0 / (2.0 * i + 5.0);
        sum4 -= 1.0 / (2.0 * i + 7.0);
    }

    double total_sum = sum1 + sum2 + sum3 + sum4;
    
    return 4.0 * total_sum;
}


int main() {
    long long iterations[] = {
        10, 100, 1000, 10000, 100000, 1000000, 
        10000000, 100000000, 1000000000
    };
    int num_tests = sizeof(iterations) / sizeof(iterations[0]);

    // --- Tabela para a Versão Sequencial ---
    printf("--- Resultados - Versão Sequencial (com Dependência de Dados) ---\n");
    printf("+-----------------+----------------------+----------------------+--------------------+\n");
    printf("| Iterações       | Pi Calculado         | Erro Absoluto        | Tempo (segundos)   |\n");
    printf("+-----------------+----------------------+----------------------+--------------------+\n");

    for (int i = 0; i < num_tests; i++) {
        long long current_iterations = iterations[i];
        struct timespec start_time, end_time;
        
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        double pi_approximation = calculate_pi_sequential(current_iterations);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        
        double time_spent = (end_time.tv_sec - start_time.tv_sec) +
                            (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        double error = fabs(M_PI - pi_approximation);
        
        printf("| %-15lld | %.18f | %.18f | %-18.9f |\n", 
               current_iterations, pi_approximation, error, time_spent);
    }
    printf("+-----------------+----------------------+----------------------+--------------------+\n\n");

    // --- Tabela para a Versão Otimizada com ILP ---
    printf("--- Resultados - Versão Otimizada com ILP (4 Acumuladores) ---\n");
    printf("+-----------------+----------------------+----------------------+--------------------+\n");
    printf("| Iterações       | Pi Calculado         | Erro Absoluto        | Tempo (segundos)   |\n");
    printf("+-----------------+----------------------+----------------------+--------------------+\n");

    for (int i = 0; i < num_tests; i++) {
        long long current_iterations = iterations[i];
        struct timespec start_time, end_time;
        
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        double pi_approximation = calculate_pi_ilp(current_iterations);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        
        double time_spent = (end_time.tv_sec - start_time.tv_sec) +
                            (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        double error = fabs(M_PI - pi_approximation);
        
        printf("| %-15lld | %.18f | %.18f | %-18.9f |\n", 
               current_iterations, pi_approximation, error, time_spent);
    }
    printf("+-----------------+----------------------+----------------------+--------------------+\n");
    printf("Valor de referência de M_PI: %.18f\n", M_PI);

    return 0;
}
