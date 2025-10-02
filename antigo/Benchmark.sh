#!/bin/bash

# ======================================================================
# CONFIGURAÇÕES
# ======================================================================

# Nome do seu executável MPI
# Altere se o nome for diferente de 'matriz_vetorA'
MPI_EXEC="./matriz_vetorA"

# Arquivo de saída CSV para registrar os resultados
OUTPUT_FILE="benchmark_results.csv"

# Array com os NÚMEROS DE PROCESSOS (P) a serem testados
# Se você só testou 2, 4, 8, mantenha esta configuração.
NUM_PROCS_ARRAY=( 2 4 8 )

# Array com os TAMANHOS DE MATRIZ (M_N) a serem testados
# IMPORTANTE: Garanta que M seja divisível pelo maior número de processos (8).
MATRIX_SIZES=( 1000_1000 2000_2000 4000_4000 6000_6000 8000_8000 10000_10000)


# ======================================================================
# FUNÇÃO DE CAPTURA DO TEMPO
# ======================================================================
function run_benchmark {
    local M=$1
    local N=$2
    local PROCS=$3

    # Comando de execução do MPI.
    # 2>&1 redireciona stderr (warnings/erros) para stdout.
    # grep filtra a linha exata de tempo.
    # sed remove o texto "Tempo de Execução..." e " segundos" para isolar o número.
    
    # Executa o MPI, passando M e N como argumentos, e captura a saída
    TIME_OUTPUT=$(mpirun -np "$PROCS" "$MPI_EXEC" "$M" "$N" 2>&1 | \
                  grep "Tempo de Execução" | \
                  sed 's/.*: //; s/ segundos//')
    
    # Garante que o valor capturado é um número válido (ignora strings de erro)
    if [[ "$TIME_OUTPUT" =~ ^[0-9]*\.[0-9]*$ ]]; then
        # Escreve a linha de resultado no CSV: M, N, P, Tempo
        echo "${M},${N},${PROCS},${TIME_OUTPUT}" >> "$OUTPUT_FILE"
        echo "  [OK] P=$PROCS | Tempo: ${TIME_OUTPUT}s"
    else
        echo "  [FAIL] P=$PROCS | Erro na captura do tempo. Saída: '$TIME_OUTPUT'"
    fi
}


# ======================================================================
# FLUXO PRINCIPAL
# ======================================================================

echo "Iniciando o Benchmark MPI. Resultados em $OUTPUT_FILE"

# Verifica se o executável existe
if [ ! -f "$MPI_EXEC" ]; then
    echo "ERRO: Executável '$MPI_EXEC' não encontrado. Compile o 'matvec.c' primeiro."
    exit 1
fi

# 1. Cria/limpa o arquivo de saída e adiciona o cabeçalho CSV
echo "Linhas(M),Colunas(N),Processos(P),Tempo(s)" > "$OUTPUT_FILE"

# 2. Loops aninhados para testar todas as combinações
for SIZE_PAIR in "${MATRIX_SIZES[@]}"; do
    M=$(echo "$SIZE_PAIR" | cut -d'_' -f1)
    N=$(echo "$SIZE_PAIR" | cut -d'_' -f2)

    echo -e "\n--- Testando Matriz ${M}x${N} ---"
    
    for PROCS in "${NUM_PROCS_ARRAY[@]}"; do
        # Verifica se M é divisível por PROCS para evitar erros no MPI_Scatter
        if (( M % PROCS != 0 )); then
             echo "  [SKIP] P=$PROCS | M ($M) não é divisível por P. Pulando."
             continue
        fi
        
        # Chama a função de benchmark
        run_benchmark "$M" "$N" "$PROCS"
    done
done

echo -e "\nBenchmark concluído."
echo "Para analisar os resultados, execute o script Python."
