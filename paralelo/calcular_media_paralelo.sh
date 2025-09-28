#!/bin/bash

# --- PARÂMETROS DE CONFIGURAÇÃO ---
# Nome do arquivo de código-fonte C PARALELO
CODIGO_C="navier_stokes_paralelo_otm1.c"
# Nome que daremos ao programa executável
EXECUTAVEL="./navier_stokes_paralelo_colapse_auto_otm1"
# Número de vezes que cada configuração será executada
NUM_REPETICOES=5
# Lista de números de threads para testar
LISTA_THREADS="16"


# --- 1. COMPILAÇÃO DO CÓDIGO ---
echo "Compilando o código '$CODIGO_C'..."
if ! gcc -o $EXECUTAVEL $CODIGO_C -lm -fopenmp -O3; then
    echo "Erro de compilação. Abortando."
    exit 1
fi
echo "Compilação bem-sucedida."
echo


# --- 2. EXECUÇÃO EM LAÇO PARA CADA N. DE THREAD ---
# Laço externo: itera sobre a lista de threads
for threads in $LISTA_THREADS
do
    echo "-------------------------------------"
    echo "Iniciando testes com $threads thread(s)..."
    
    # Inicializa a variável para somar os tempos para esta contagem de threads
    TOTAL_TIME=0.0
    
    # Laço interno: repete a execução 5 vezes
    for i in $(seq 1 $NUM_REPETICOES)
    do
        # Define a variável de ambiente e executa o programa
        TEMPO_EXECUCAO=$(OMP_NUM_THREADS=$threads $EXECUTAVEL)
        
        echo "  -> Repetição $i: $TEMPO_EXECUCAO s"
        
        # Soma o tempo da execução atual ao total
        TOTAL_TIME=$(echo "$TOTAL_TIME + $TEMPO_EXECUCAO" | bc)
    done
    
    # Calcula a média para a contagem de threads atual
    MEDIA=$(echo "scale=6; $TOTAL_TIME / $NUM_REPETICOES" | bc)
    echo "Tempo Médio para $threads thread(s): $MEDIA s"
done


# --- 3. LIMPEZA ---
echo "-------------------------------------"
echo "Bateria de testes concluída."
rm $EXECUTAVEL
echo "Executável temporário '$EXECUTAVEL' removido."