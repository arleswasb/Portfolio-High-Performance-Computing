<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
# Projeto PP 04

Breve descrição do que este projeto faz e qual problema ele resolve.

*(Exemplo: Este é o quarto projeto da disciplina de Programação Paralela. O objetivo é analisar o desempenho de algoritmos limitados por CPU (CPU-bound) e por memória (Memory-bound) utilizando OpenMP.)*

## 📝 Sumário

- [Sobre](#-sobre)
- [Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [Pré-requisitos](#-pré-requisitos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Autores](#-autores)

## 📖 Sobre

Forneça uma descrição mais detalhada do projeto aqui. Explique a abordagem utilizada, os algoritmos implementados e os objetivos alcançados.

## 💻 Tecnologias Utilizadas

- **Linguagem:** C
- **Paralelismo:** OpenMP
- **Compilador:** GCC
- **Build System:** Make

## ✅ Pré-requisitos

Antes de começar, você vai precisar ter instalado em sua máquina as seguintes ferramentas:
- Um compilador C com suporte a OpenMP (como o [GCC](https://gcc.gnu.org/))
- [Git](https://git-scm.com)
- [Make](https://www.gnu.org/software/make/)

## 🚀 Como Compilar e Executar

Este projeto utiliza um `Makefile` para simplificar o processo de compilação.

```bash
# 1. Clone este repositório
$ git clone <https://github.com/arleswasb/projeto_PP_04.git>

# 2. Acesse a pasta do projeto
$ cd projeto_PP_04

# 3. Compile todos os programas utilizando o Makefile
# Este comando irá gerar os executáveis: memory_bound, memory_bound_v1, memory_bound_v2 e cpu_bound
$ make -f makefile.mk all

# 4. Execute um dos programas gerados
# Exemplo para o 'memory_bound':
$ ./memory_bound_V2

# Exemplo para o 'cpu_bound':
$ ./cpu_bound

# Para limpar os arquivos compilados, execute:
$ make -f makefile.mk clean
```

## 📁 Estrutura do Projeto

A estrutura de pastas do projeto está organizada da seguinte forma:

```
/
├── main.c        # Arquivo principal do código-fonte
├── .gitignore    # Arquivos e pastas a serem ignorados pelo Git
└── README.md     # Documentação do projeto
```
=======

# Projeto 08: Análise de Desempenho da Estimativa Estocástica de π com OpenMP
=======
# Projeto 09: Análise de Estratégias de Sincronização em OpenMP
### Regiões Críticas Nomeadas vs. Locks Explícitos em Listas Encadeadas
>>>>>>> temp_repo/main
=======
# Projeto 08: Análise de Desempenho e Produtividade em OpenMP
### Comparativo de Mecanismos de Sincronização na Estimação de Pi
>>>>>>> temp_repo/main

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Framework](https://img.shields.io/badge/Framework-OpenMP-orange.svg)
![Licença](https://img.shields.io/badge/Licença-MIT-green.svg)

## Descrição do Projeto

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
Este projeto, desenvolvido para a disciplina de Programação Paralela (DCA3703), explora e compara diferentes estratégias de sincronização para gerenciar o acesso concorrente a listas encadeadas. O objetivo é analisar o impacto de duas abordagens distintas do OpenMP para resolver o problema clássico de condições de corrida durante múltiplas inserções paralelas em estruturas de dados compartilhadas.

Foram implementadas duas versões para investigar cenários de gerenciamento de recursos:
1.  **Cenário Estático:** Com um número fixo de listas, utilizando regiões críticas nomeadas.
2.  **Cenário Dinâmico:** Com um número `M` de listas definido pelo usuário, exigindo o uso de locks explícitos.
=======
Este projeto, desenvolvido para a disciplina de Programação Paralela (DCA3703), realiza uma análise comparativa de diferentes estratégias de sincronização em OpenMP para resolver um problema clássico de acumulação paralela. O objetivo é avaliar o impacto no desempenho e na produtividade de cinco abordagens distintas para evitar condições de corrida na estimação do número Pi ($\pi$) pelo método de Monte Carlo.

Foram implementadas cinco versões para investigar o custo da contenção e a eficiência das abstrações do OpenMP:
1.  **Contador Compartilhado com Região Crítica (`critical`)**: Sincronização de baixa granularidade interna ao laço.
2.  **Contador Compartilhado com Operação Atômica (`atomic`)**: Alternativa de baixo nível com menor overhead, mas ainda com alta contenção.
3.  **Contador Privado com Sincronização Externa**: Padrão manual de alta granularidade para minimizar a contenção.
4.  **Cláusula `reduction`**: A abordagem idiomática e de mais alto nível do OpenMP para operações de redução.
>>>>>>> temp_repo/main

## Conceitos Abordados

* Paralelismo de Dados com a diretiva `#pragma omp parallel for`.
* Sincronização para evitar Condições de Corrida.
<<<<<<< HEAD
* **Regiões Críticas Nomeadas** (`#pragma omp critical (name)`) para múltiplos locks estáticos.
* **Locks Explícitos** (`omp_lock_t`) para sincronização dinâmica e granular.
* Análise comparativa entre Sincronização Estática vs. Dinâmica.
* Locking de Alta Granularidade (*Fine-Grained Locking*).

## Estrutura dos Arquivos

O repositório contém as duas versões do programa, cada uma focada em uma estratégia de sincronização:

* `Duas_listas.c`: Implementação para o cenário estático com **2 listas** e **regiões críticas nomeadas**. Demonstra uma solução de alto nível para um número fixo de recursos.
* `N_listas.c`: Implementação generalizada para **M listas** com **locks explícitos**. Demonstra uma solução flexível e escalável para um número dinâmico de recursos.
>>>>>>> temp_repo/main
=======
* Método de Monte Carlo para estimação de $\pi$.
* Função reentrante `rand_r()` para geração de números aleatórios em paralelo.
* Comparativo entre **`#pragma omp critical`**, **`#pragma omp atomic`** e a cláusula **`reduction`**.
* Locking de Alta Granularidade (*Fine-Grained*) vs. Baixa Granularidade (*Coarse-Grained*).
* Análise de trade-offs entre Desempenho e Produtividade.

## Estrutura dos Arquivos

O repositório contém as implementações das diferentes estratégias de sincronização. Recomenda-se separar cada abordagem em um arquivo para clareza:

* `pi_critical_compartilhado.c`: Implementação com contador compartilhado e `#pragma omp critical` (Baixo Desempenho).
* `pi_atomic_compartilhado.c`: Implementação com contador compartilhado e `#pragma omp atomic` (Baixo Desempenho).
* `pi_privado_critical.c`: Implementação com contador privado e sincronização externa com `#pragma omp critical` (Alto Desempenho).
* `pi_reduction.c`: Implementação com a cláusula `reduction` (Melhor Desempenho e Produtividade).
>>>>>>> temp_repo/main

## Como Compilar e Executar

O projeto foi desenvolvido em C e utiliza a biblioteca OpenMP. É necessário um compilador com suporte a OpenMP (como o GCC) e a flag `-fopenmp`.

### Compilação

```bash
<<<<<<< HEAD
<<<<<<< HEAD
# Versão 1
gcc -fopenmp -o v1_rand_critical paralelo_rand.c

# Versão 2
gcc -fopenmp -o v2_rand_vetor paralelo_rand_vetor.c

# Versão 3
gcc -fopenmp -o v3_rand_r_critical paralelo_rand_r.c

# Versão 4
gcc -fopenmp -o v4_rand_r_vetor paralelo_rand_r_vetor.c
=======
# Para a versão de 2 listas (estática)
gcc -fopenmp -o duas_listas Duas_listas.c

# Para a versão de M listas (dinâmica)
gcc -fopenmp -o m_listas N_listas.c
>>>>>>> temp_repo/main
````
=======
# Exemplo para a versão com reduction (a mais eficiente)
gcc -o pi_reduction -fopenmp pi_reduction.c -lm

# Exemplo para a versão com critical em contador compartilhado (a menos eficiente)
gcc -o pi_critical_comp -fopenmp pi_critical_compartilhado.c -lm
```
>>>>>>> temp_repo/main

### Execução

```bash
<<<<<<< HEAD
<<<<<<< HEAD
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
>>>>>>> temp_repo/main
=======
# Executar a versão estática
./duas_listas

# Executar a versão dinâmica (o programa solicitará o número de listas)
./m_listas
=======
# Executar a versão com reduction
./pi_reduction

# Executar a versão com critical compartilhado para comparar o tempo
./pi_critical_comp
>>>>>>> temp_repo/main
```

## Abordagens Implementadas

<<<<<<< HEAD
### Versão 1: Cenário Estático com Regiões Críticas Nomeadas

Esta versão aborda o problema para um número fixo de duas listas. A sincronização utiliza a diretiva `#pragma omp critical (name)`, fornecendo nomes distintos para os locks de cada lista (`lock_A` e `lock_B`). Isso permite que inserções em listas diferentes ocorram de forma totalmente concorrente, já que os locks são independentes.

### Versão 2: Cenário Dinâmico com Locks Explícitos

Esta versão generaliza o problema para um número `M` de listas definido pelo usuário em tempo de execução. Como as regiões críticas nomeadas não podem ser criadas dinamicamente, a solução utiliza um array de locks do tipo `omp_lock_t`. Um array de `M` locks é alocado, e o `lock[i]` é usado para proteger a `lista[i]`, permitindo um travamento granular e dinâmico.

## Análise e Conclusões

A análise das duas implementações, detalhada no relatório, leva às seguintes conclusões:

  * A escolha do mecanismo de sincronização é uma **decisão de design** ditada pela natureza do problema (recursos estáticos vs. dinâmicos).
  * **Regiões Críticas Nomeadas** são uma abstração simples e eficaz, mas sua aplicabilidade é restrita a cenários onde os recursos são fixos e conhecidos em tempo de compilação.
  * **Locks Explícitos** são essenciais para cenários dinâmicos, oferecendo flexibilidade e escalabilidade ao custo de uma maior complexidade de gerenciamento (ciclo de vida do lock).
  * Em ambos os casos, a estratégia de **alta granularidade** (um lock por lista) é crucial para minimizar a contenção e maximizar o desempenho, evitando a serialização desnecessária das tarefas.
>>>>>>> temp_repo/main

## Autor

  * **Werbert Arles de Souza Barradas**

-----

<<<<<<< HEAD
<<<<<<< HEAD
**Disciplina:** DCA3-703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)


## 💻 imagens

![Terminal com tempos](terminal.png)

![tela do Neohtop com as barras de desempenho da cpu](neohtop.png)
=======
=======
>>>>>>> temp_repo/main
**Disciplina:** DCA3703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

```
```
<<<<<<< HEAD
>>>>>>> temp_repo/main
=======
>>>>>>> temp_repo/main
=======
### Versões 1 e 2: Contador Compartilhado (Sincronização Interna)

Estas versões utilizam um único contador global. A proteção (`critical` ou `atomic`) ocorre **dentro** do laço principal, a cada vez que um ponto aleatório cai dentro do círculo. Esta abordagem de baixa granularidade cria um enorme gargalo de contenção, serializando as atualizações e anulando os ganhos do paralelismo.

### Versões 3 e 4: Contador Privado (Sincronização Externa)

Este padrão implementa uma estratégia de alta granularidade. Cada thread acumula o resultado em uma variável local privada, eliminando a contenção durante a execução do laço. A sincronização (`critical` ou `atomic`) ocorre apenas uma vez por thread, **após** o término do laço, para somar os subtotais ao contador global. O resultado é um desempenho drasticamente superior.

### Versão 5: Cláusula `reduction`

Esta versão utiliza a abstração de mais alto nível do OpenMP para este problema. A cláusula `reduction(+:contador)` instrui o compilador a aplicar o padrão de contador privado de forma automática e otimizada. É a abordagem que combina o melhor desempenho com o código mais limpo e produtivo.

## Análise e Conclusões

A análise das cinco implementações, detalhada no relatório e na apresentação, leva às seguintes conclusões:

* A **contenção de recursos** é o principal fator limitante de desempenho. A localização da sincronização (interna vs. externa ao laço) é mais crucial do que a diretiva específica (`atomic` vs. `critical`).
* A estratégia de **alta granularidade** (um contador por thread, seja manual ou via `reduction`) é fundamental para alcançar a escalabilidade em problemas de acumulação.
* A cláusula **`reduction`** é superior em todos os aspectos: oferece o melhor desempenho, resulta no código mais conciso e seguro, e aumenta a produtividade do programador.
* **Regra Geral:** Sempre prefira a abstração de mais alto nível que o OpenMP oferece para resolver o seu problema, pois ela geralmente encapsula as melhores práticas de desempenho.

## Autor

* **Werbert Arles de Souza Barradas**
=======

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
>>>>>>> temp_repo/main

-----

**Disciplina:** DCA3703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)
<<<<<<< HEAD
>>>>>>> temp_repo/main
=======
# projeto_PP_13
>>>>>>> temp_repo/main
=======
>>>>>>> temp_repo/main
