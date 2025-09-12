
# Projeto 08: Análise de Desempenho da Estimativa Estocástica de π com OpenMP

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Framework](https://img.shields.io/badge/Framework-OpenMP-orange.svg)
![Licença](https://img.shields.io/badge/Licença-MIT-green.svg)

## Descrição do Projeto

Este projeto, desenvolvido para a disciplina de Programação Paralela (DCA3703), realiza uma análise de desempenho de um problema clássico da computação, a estimação da constante matemática π através de métodos estocásticos (Monte Carlo). A tarefa consiste em gerar um grande volume de pontos aleatórios e verificar se eles se encontram dentro de um círculo, uma carga de trabalho inerentemente paralelizável.

O objetivo é analisar o impacto de diferentes estratégias de implementação paralela em OpenMP, combinando duas abordagens para a geração de números aleatórios (`rand()` e `rand_r()`) e duas para a acumulação de resultados (seção crítica e vetor compartilhado).

## Conceitos Abordados

* **Computação Paralela com OpenMP**: Uso de diretivas para paralelizar laços de repetição.
* **Thread-Safety**: Análise do impacto de desempenho ao usar funções não seguras para threads (`rand()`) em comparação com alternativas reentrantes (`rand_r()`).
* **Estratégias de Sincronização**: Comparação entre um mecanismo de bloqueio de software (`#pragma omp critical`) e uma abordagem "lock-free" com vetor compartilhado.
* **Arquitetura de Hardware**: Investigação de como fenômenos de baixo nível, como a **Coerência de Cache** e o **Falso Compartilhamento** (*False Sharing*), afetam o desempenho do código paralelo.

## Estrutura dos Arquivos

O repositório contém as quatro versões do programa, cada uma explorando uma combinação diferente de gargalos de software e hardware:

* `paralelo_rand.c` (Versão 1): Utiliza `rand()` (não thread-safe) para geração de números e `#pragma omp critical` para acumulação.
* `paralelo_rand_vetor.c` (Versão 2): Utiliza `rand()` e um vetor compartilhado para acumulação.
* `paralelo_rand_r.c` (Versão 3): Utiliza `rand_r()` (thread-safe) e `#pragma omp critical`.
* `paralelo_rand_r_vetor.c` (Versão 4): Utiliza `rand_r()` e um vetor compartilhado.

## Como Compilar e Executar

O projeto foi desenvolvido em C e utiliza a biblioteca OpenMP. É necessário um compilador com suporte a OpenMP (como o GCC) e a flag `-fopenmp`.

### Compilação

```bash
# Versão 1
gcc -fopenmp -o v1_rand_critical paralelo_rand.c

# Versão 2
gcc -fopenmp -o v2_rand_vetor paralelo_rand_vetor.c

# Versão 3
gcc -fopenmp -o v3_rand_r_critical paralelo_rand_r.c

# Versão 4
gcc -fopenmp -o v4_rand_r_vetor paralelo_rand_r_vetor.c
````

### Execução

```bash
# Executar cada uma das versões
./v1_rand_critical
./v2_rand_vetor
./v3_rand_r_critical
./v4_rand_r_vetor
```

## Análise e Principais Conclusões

A análise comparativa do tempo de execução das quatro versões revelou insights importantes sobre gargalos em programação paralela. Todas as versões executaram 100.000.000 de iterações.

### Resultados de Desempenho

| Versão | Estratégia | Tempo de Execução (s) |
| :--- | :--- | :--- |
| 1 | `rand()` + Seção Crítica | 15.08 |
| 2 | `rand()` + Vetor | 13.80 |
| 4 | `rand_r()` + Vetor | 0.7613 |
| 3 | `rand_r()` + Seção Crítica | **0.3874** |

### Principais Conclusões

1.  **O Custo de Funções Não Thread-Safe**: O uso da função `rand()`, que não é reentrante, foi o principal gargalo nas Versões 1 e 2. Suas chamadas são serializadas por um lock interno, o que anula quase que completamente os ganhos do paralelismo. A mudança para `rand_r()` resultou em uma melhora drástica de desempenho.

2.  **Falso Compartilhamento (*False Sharing*)**: O resultado mais contraintuitivo foi o desempenho inferior da Versão 4 em comparação com a Versão 3. Embora a Versão 4 seja "livre de locks" em software, ela sofre de um severo gargalo de hardware. O vetor `acertos_por_thread` armazena contadores de threads adjacentes na mesma linha de cache (geralmente 64 bytes). Quando uma thread atualiza seu contador, o protocolo de coerência de cache invalida a linha inteira para as outras threads, forçando-as a recarregar os dados da memória principal, um processo extremamente lento. Esse "ping-pong" da linha de cache entre os núcleos aniquilou os benefícios da abordagem com vetor.

3.  **Gargalos de Hardware vs. Software**: O experimento demonstrou que eliminar um gargalo de software (como uma seção crítica) pode expor um gargalo de hardware ainda mais severo (como o falso compartilhamento). A Versão 3, que utilizou uma função thread-safe e uma sincronização de software simples, foi a mais rápida porque o custo da seção crítica foi menor que o custo da contenção massiva de cache na Versão 4.

## Autor

  * **Werbert Arles de Souza Barradas**

-----

**Disciplina:** DCA3703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

```
```
