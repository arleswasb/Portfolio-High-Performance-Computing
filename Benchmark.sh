#!/bin/bash

#SBATCH --partition=amd-512  # partição para a qual o job é enviado
#SBATCH --exclusive
#SBATCH --time=0-0:20
#SBATCH --nodes=2 #número de nós
#SBATCH --ntasks-per-node=64 #número de tarefas por nós

# ======================================================================
# CONFIGURAÇÕES
# ======================================================================

# Nome do seu executável MPI (ex: ./matriz_vetor_quadrada)
MPI_EXEC="./matrix_vetor"

# Arquivo de saída CSV para registrar os resultados
OUTPUT_FILE="benchmark_results_final.csv"

# Array com os NÚMEROS DE PROCESSOS (P) a serem testados
NUM_PROCS_ARRAY=(2 4 8 16 32 64)

# AJUSTE 1: Lista de tamanhos de matriz (M) onde todos os valores
# são múltiplos de 64 para garantir a divisibilidade.
MATRIX_SIZES=(1024 2048 4096 6144 8192 16384)


# ======================================================================
# FUNÇÃO DE CAPTURA DO TEMPO
# ======================================================================
function run_benchmark {
    local M=$1
    local PROCS=$2

    TIME_OUTPUT=$(mpirun -np "$PROCS" "$MPI_EXEC" "$M" 2>&1 | \
                  grep "Tempo de Execução" | \
                  sed 's/.*: //; s/ segundos//')
    
    if [[ "$TIME_OUTPUT" =~ ^[0-9].*\.[0-9]*$ ]]; then
        echo "${M},${M},${PROCS},${TIME_OUTPUT}" >> "$OUTPUT_FILE"
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
    echo "ERRO: Executável '$MPI_EXEC' não encontrado. Compile o código C primeiro."
    exit 1
fi

# Cria/limpa o arquivo de saída e adiciona o cabeçalho CSV
echo "Tamanho(M),Tamanho(N),Processos(P),Tempo(s)" > "$OUTPUT_FILE"

# Loops aninhados para testar todas as combinações
for M in "${MATRIX_SIZES[@]}"; do
    echo -e "\n--- Testando Matriz ${M}x${M} ---"
    
    for PROCS in "${NUM_PROCS_ARRAY[@]}"; do
        # AJUSTE 2: A verificação de divisibilidade foi removida,
        # pois garantimos que todas as combinações são válidas.
        
        run_benchmark "$M" "$PROCS"
    done
done

echo -e "\nBenchmark concluído."
echo "Para analisar os resultados, use o arquivo '$OUTPUT_FILE' com seu script Python."
