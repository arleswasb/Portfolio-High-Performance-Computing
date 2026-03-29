
# Tarefa 14: Análise de Latência e Largura de Banda (MPI Ping-Pong)

## 🎯 Objetivo

Implementar um *benchmark* de comunicação **MPI Ping-Pong** para medir o tempo de troca de mensagens em função do seu tamanho. O objetivo é analisar graficamente os resultados para identificar os regimes de comunicação onde a **Latência ($\\tau$)** e a **Largura de Banda ($\\beta$)** dominam o desempenho.

O projeto utiliza o modelo de comunicação $T = \\tau + \\frac{L}{\\beta}$.

## 🛠️ Pré-Requisitos

Para compilar e executar este programa, você precisa ter:

1.  Um compilador C compatível (geralmente GCC).
2.  A biblioteca \\textbf{MPI} (Message Passing Interface) instalada (e.g., OpenMPI ou MPICH).
3.  As ferramentas \\textbf{Python} (\\texttt{pandas} e \\texttt{matplotlib}) para processamento e visualização dos dados.

## 📁 Estrutura do Projeto

```
.
├── ping_pong_mpi.c      # Código-fonte da simulação MPI (versão com printf).
├── run_test.sh          # Script para execução e captura da saída de texto.
├── plotar_grafico.py    # Script Python que processa a saída de texto e gera o gráfico.
├── README.md            # Este arquivo.
└── saida_raw.txt        # Arquivo de saída de texto gerado após a execução.
```

## 🚀 Como Compilar e Executar (Versão com Saída de Texto Bruta)

O fluxo de trabalho envolve compilar o código, executar o programa MPI e, em seguida, redirecionar sua saída de texto para um arquivo que o script Python possa ler e processar.

### 1\. Compilação do Executável

Compile o código C utilizando o *wrapper* \\texttt{mpicc} para criar o executável:

```bash
mpicc -o ping_pong_mpi ping_pong_mpi.c
```

### 2\. Execução e Captura da Saída de Dados

Crie um script de execução simples (\\texttt{run\_test.sh}) para garantir que o resultado seja capturado em um arquivo de texto.

**Conteúdo de \\texttt{run\_test.sh}:**

```bash
#!/bin/bash
echo "Executando o benchmark MPI e capturando a saída..."

# O número de iterações (e.g., 1000) é o argumento da sua versão C
mpirun -np 2 ./ping_pong_mpi 1000 > saida_raw.txt

echo "Dados brutos salvos em saida_raw.txt"
```

**Comandos para Rodar:**

```bash
chmod +x run_test.sh
./run_test.sh
```

### 3\. Geração do Gráfico

O script Python (\\texttt{plotar\_grafico.py}) deve ser modificado para ler e fazer o *parsing* do arquivo \\texttt{saida\_raw.txt}.

Execute o script Python:

```bash
python3 plotar_grafico.py
```

**Resultado:** Criação do arquivo de imagem \\texttt{tempo\_mensagem.png}, base para sua análise.

## 📊 Parâmetros de Teste

| Parâmetro | Detalhe | Função |
| :--- | :--- | :--- |
| **Executável** | \\texttt{ping\_pong\_mpi} | Versão que imprime o resultado no console. |
| **Tamanho da Mensagem** ($L$) | $16, 32, 64, \\ldots, 4194304$ (4 MB) | Sequência completa de tamanhos para a análise. |
| **Captura** | Redirecionamento de saída (\\texttt{\>}) | Captura o texto \\texttt{"Tamanho da Mensagem: X bytes..."} para o arquivo. |

-----

**Disciplina:** DCA3703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)
