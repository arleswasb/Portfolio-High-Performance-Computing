Com certeza\! Um bom arquivo `README.md` é essencial para documentar o projeto, explicar como usá-lo e apresentar os resultados. Baseado em todo o trabalho que fizemos, preparei um `README.md` completo para o "Projeto 16".

Você pode copiar e colar o texto abaixo em um novo arquivo chamado `README.md` no diretório do seu projeto.

-----

# Projeto 16: Análise de Desempenho de Multiplicação Matriz-Vetor com MPI

Este projeto implementa e avalia o desempenho de um algoritmo paralelo para a multiplicação de matriz-vetor ($y = A \cdot x$) utilizando a Interface de Passagem de Mensagens (MPI). O objetivo é analisar a escalabilidade e a eficiência da solução em um ambiente de computação de alto desempenho (HPC), observando como o tempo de execução é impactado pelo aumento do tamanho do problema e do número de processos.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos principais:

  * `matrix_vetor_quadrada.c`: Código-fonte em C da implementação MPI. Ele distribui uma matriz `A` por linhas entre os processos, transmite o vetor `x` para todos e calcula o produto de forma distribuída.
  * `Benchmark.sh`: Script de automação (Bash) para executar os benchmarks. Ele compila o código C e o executa para várias combinações de tamanhos de matriz e número de processos, salvando os resultados em um arquivo CSV.
  * `analise_resultados.py`: Script em Python para processar os dados do benchmark. Ele lê o arquivo CSV e gera gráficos de desempenho para a análise dos resultados.
  * `benchmark_results_final.csv`: Arquivo CSV gerado pelo script de benchmark, contendo os dados brutos de tempo de execução.

## Pré-requisitos

Para compilar e executar este projeto, você precisará de:

  * Um compilador C e uma implementação MPI (ex: `mpicc`, Open MPI, MPICH)
  * Um ambiente Shell (Bash)
  * Python 3.x
  * Bibliotecas Python: `pandas`, `matplotlib`, `seaborn`. Para instalá-las, execute:
    ```sh
    pip install pandas matplotlib seaborn
    ```

## Como Usar

Siga estes passos para reproduzir os resultados:

**1. Compilar o Código C:**
Compile o programa MPI usando o `mpicc`.

```sh
mpicc matrix_vetor_quadrada.c -o matriz_vetor_quadrada
```

**2. Dar Permissão de Execução ao Script de Benchmark:**

```sh
chmod +x Benchmark.sh
```

**3. Executar o Benchmark:**
Rode o script para coletar os dados de tempo. Este processo pode levar um tempo considerável, dependendo do hardware.

```sh
./Benchmark.sh
```

Ao final, um arquivo chamado `benchmark_results_final.csv` será criado.

**4. Gerar os Gráficos de Análise:**
Execute o script Python para gerar os gráficos a partir dos dados coletados.

```sh
python3 analise_resultados.py
```

Isso irá gerar os gráficos de análise, como `figure_desempenho_facetado.png`, no mesmo diretório.

## Análise dos Resultados

A análise dos dados coletados revela o comportamento clássico de algoritmos paralelos, onde o desempenho é um balanço entre o poder de cálculo distribuído e o custo da comunicação.

  * **Tempo de Execução:** Conforme esperado, o tempo de execução diminuiu consistentemente com o aumento do número de processos para **todos os tamanhos de matriz**. O maior ganho de velocidade foi observado ao passar de 2 para 16 processos.

  * **Eficiência e Granularidade:** A eficiência da paralelização foi mais baixa para a matriz menor (1024x1024). Isso ocorre porque a *granularidade* do problema é baixa: o tempo de comunicação da MPI é significativo em comparação com o pouco trabalho de cálculo que cada processo realiza.

  * **Ganhos Decrescentes:** Para as matrizes maiores (a partir de 8192x8192), o ganho de desempenho ao saltar de 32 para 64 processos foi menor do que os saltos iniciais. Isso indica que, com muitos processos, o *overhead* de comunicação das cláusulas `MPI_Scatter` e `MPI_Gather` começa a limitar a escalabilidade.

## Conclusão

A paralelização do produto matriz-vetor com MPI foi implementada com sucesso, provando ser uma abordagem altamente vantajosa para problemas de grande escala, onde o tempo de cálculo domina o custo da comunicação. O projeto demonstra na prática os ganhos e os limites de escalabilidade inerentes a sistemas de memória distribuída.

-----
