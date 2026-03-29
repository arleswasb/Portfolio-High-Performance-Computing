 High Performance Computing Portfolio 
### Engenharia de Computação | UFRN


Este repositório centraliza o desenvolvimento técnico de **17 projetos** especializados, realizados para a disciplina de **Programação Paralela (DCA3703)** na Universidade Federal do Rio Grande do Norte[cite: 3, 261, 263]. [cite_start]O portfólio documenta a evolução prática em otimização de sistemas, explorando desde a microarquitetura de processadores até a computação distribuída em larga escala no supercomputador **NPAD**.

---

## 🛠️ Stack Tecnológica e Infraestrutura
**Linguagens:** C (Desenvolvimento de Sistemas/HPC) e Python (Análise Estatística e Visualização).
**Paralelismo de Memória Compartilhada:** OpenMP (Multicore, Afinidade de Threads e Tasks).
**Paralelismo de Memória Distribuída:** MPI (Comunicações Coletivas e Ponto-a-Ponto).
**Ambiente de Execução:** Cluster de alto desempenho do **NPAD/UFRN** com escalonamento via **SLURM**.

---

## 📂 Índice de Projetos (`mpi-projects/`)

| ID | Projeto | Foco Técnico | Conceitos Chave |
| :--- | :--- | :--- | :--- |
| **01** | **MxV & Cache** | Localidade de Dados | Impacto de *Cache Misses* e layout *Row-Major* na performance. |
| **02** | **ILP & Otimização** | Paralelismo de Instrução | Exploração de *Pipelining* e quebra de dependências de dados. |
| **03** | **Cálculo de $\pi$** | Precisão Numérica | Trade-off entre custo computacional e convergência matemática. |
| **04** | **CPU vs Memory** | Perfilamento de Carga | Identificação de algoritmos *CPU-bound* vs *Memory-bound*. |
| **05** | **Contagem de Primos** | Integridade de Dados | Resolução de *Race Conditions* e uso de `reduction`. |
| **06** | **Monte Carlo $\pi$** | Sincronização | Análise do overhead de seções críticas (`critical`). |
| **07** | **List Tasking** | Estruturas Dinâmicas | Paralelização de listas encadeadas usando `omp task`. |
| **08** | **Atomicidade** | Baixo Nível | Operações não-atômicas e inconsistência em nível de registrador. |
| **09** | **Locks Dinâmicos** | Granularidade Fina | Uso de `omp_lock_t` para escalonabilidade de múltiplas listas. |
| **10** | **Productivity** | Abstrações OpenMP | Comparativo entre `atomic`, `critical` e `reduction`. |
| **11** | **Navier-Stokes** | Simulação CFD | Otimização de laços aninhados com `collapse` e `schedule`. |
| **12** | **Project Rescue** | Gestão de Repositórios | Integração e restauração de projetos HPC via Git. |
| **13** | **Afinidade (NUMA)** | Hardware Pinning | Uso de `OMP_PROC_BIND` e `OMP_PLACES` no NPAD. |
| **14** | **MPI Ping-Pong** | Redes HPC | Medição de Latência ($\tau$) e Largura de Banda ($\beta$). |
| **15** | **Overlap MPI** | Hiding Latency | Sobreposição de comunicação e computação (`MPI_Isend/Irecv`). |
| **16** | **MxV (MPI)** | Escalabilidade Distribuída | Multiplicação de matrizes com `Scatter` e `Gather`. |
| **17** | **Desafio Final** | Consolidação HPC | Aplicação integrada de conceitos de alta performance. |

---

## 🔬 Destaques de Engenharia

### ⚡ Afinidade e Localidade (Projeto 13)
Análise profunda sobre o "aprisionamento" (*pinning*) de threads em núcleos específicos para evitar a migração pelo Sistema Operacional. O uso das políticas `close` e `spread` permitiu maximizar o reuso da cache L3 e otimizar o acesso em arquiteturas **NUMA**.

### 🔄 Sobreposição de Comunicação (Projeto 15)
Implementação de técnicas não-bloqueantes para esconder a latência de rede. Através da sobreposição de computação útil com a troca de bordas (*Halo Exchange*), alcançou-se uma redução significativa no tempo total de execução em simulações de difusão.

### 📊 Rigor Científico
Todos os resultados apresentados foram validados através de:
1. **Benchmarks Automatizados:** Scripts Bash para múltiplas execuções e coleta de dados.
2. **Análise Estatística:** Processamento de resultados via Python (Pandas/Matplotlib) com foco na mediana para mitigar ruídos.
3. **Análise de Escalabilidade:** Gráficos de *Speedup* e Eficiência para identificar o limite de Amdahl.

---

## 👤 Autor
**Werbert Arles de Souza Barradas** 
Engenheiro de Computação (UFRN) e Oficial da Reserva da Força Aérea Brasileira (FAB).
Especialista em computação de baixo nível, sistemas de missão crítica e HPC.

---
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)  
**Disciplina:** DCA3703 - Programação Paralela
