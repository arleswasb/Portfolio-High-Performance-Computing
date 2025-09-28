#!/bin/bash

# --- PARÂMETROS DE CONFIGURAÇÃO ---
# Nome do arquivo de código-fonte C
CODIGO_C="navier_stokes_simul_serial_tempo.c"
# Nome que daremos ao programa executável
EXECUTAVEL="./solver_serial_temp"
# Número de vezes que o código será executado
NUM_REPETICOES=5


# --- 1. COMPILAÇÃO DO CÓDIGO ---
echo "Compilando o código '$CODIGO_C'..."
# Usamos -O3 para otimização e -fopenmp para ter acesso à função de tempo
if ! gcc -o $EXECUTAVEL $CODIGO_C -lm -fopenmp -O3; then
    echo "Erro de compilação. Abortando."
    exit 1
fi
echo "Compilação bem-sucedida."
echo


# --- 2. EXECUÇÃO EM LAÇO ---
# Inicializa a variável para somar os tempos
TOTAL_TIME=0.0
echo "Executando o programa $NUM_REPETICOES vezes para calcular a média..."

for i in $(seq 1 $NUM_REPETICOES)
do
    # Executa o programa e captura a saída (o tempo) em uma variável
    TEMPO_EXECUCAO=$($EXECUTAVEL)
    
    echo "  -> Execução $i: $TEMPO_EXECUCAO s"
    
    # Soma o tempo da execução atual ao total, usando 'bc' para cálculos decimais
    TOTAL_TIME=$(echo "$TOTAL_TIME + $TEMPO_EXECUCAO" | bc)
done


# --- 3. CÁLCULO E EXIBIÇÃO DA MÉDIA ---
echo "-------------------------------------"
echo "Cálculo da média final..."

# Usa 'bc' para dividir o tempo total pelo número de repetições
# 'scale=6' define o número de casas decimais
MEDIA=$(echo "scale=6; $TOTAL_TIME / $NUM_REPETICOES" | bc)

echo "Tempo total acumulado: $TOTAL_TIME s"
echo "Número de execuções: $NUM_REPETICOES"
echo
echo "Tempo Médio de Execução: $MEDIA s"
echo


# --- 4. LIMPEZA ---
# Remove o arquivo executável que foi criado
rm $EXECUTAVEL
echo "Executável temporário '$EXECUTAVEL' removido."