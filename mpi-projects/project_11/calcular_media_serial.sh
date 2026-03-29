#!/bin/bash

# --- PARÂMETROS DE CONFIGURAÇÃO ---
# Nome do arquivo de código-fonte C que será compilado.
CODIGO_C="navier_stokes_serial.c"

# Nome que daremos ao programa executável após a compilação.
EXECUTAVEL="./navier_stokes_serial"

# Número de vezes que cada configuração será executada para calcular a média.
NUM_REPETICOES=5

# Lista de números de threads para testar.
LISTA_THREADS="1"

# Parâmetro do tamanho da grade a ser passado para o executável.
#                                    
TAMANHO_GRADE=512


# --- 1. COMPILAÇÃO DO CÓDIGO ---
echo "Compilando o código '$CODIGO_C' com otimização (-O3) e OpenMP..."
if ! gcc -o $EXECUTAVEL $CODIGO_C -lm -fopenmp -O3; then
    echo "Erro de compilação. Abortando."
    exit 1
fi
echo "Compilação bem-sucedida."
echo


# --- 2. EXECUÇÃO E CÁLCULO DA MÉDIA ---
for threads in $LISTA_THREADS
do
    echo "-------------------------------------"
    echo "Iniciando testes com $threads thread(s) e grade $TAMANHO_GRADE..."
    
    TOTAL_TIME=0.0
    
    for i in $(seq 1 $NUM_REPETICOES)
    do
        # Executa o programa passando o TAMANHO_GRADE como argumento
        #                                   
        TEMPO_EXECUCAO=$(OMP_NUM_THREADS=$threads $EXECUTAVEL $TAMANHO_GRADE)
        
        echo "  -> Repetição $i: $TEMPO_EXECUCAO s"
        
        TOTAL_TIME=$(echo "$TOTAL_TIME + $TEMPO_EXECUCAO" | bc)
    done
    
    MEDIA=$(echo "scale=6; $TOTAL_TIME / $NUM_REPETICOES" | bc)
    echo ""
    echo "Tempo Médio para $threads thread(s): $MEDIA s"
done


# --- 3. LIMPEZA ---
echo "-------------------------------------"
echo "Bateria de testes concluída."
rm $EXECUTAVEL
echo "Executável temporário '$EXECUTAVEL' removido."