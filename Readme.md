High Performance Computing Portfolio 🚀
Engenharia de Computação | UFRN

Este repositório é um compêndio técnico de 17 projetos desenvolvidos para a disciplina de Programação Paralela (DCA3703). O portfólio documenta a jornada de otimização de software, explorando desde a hierarquia de memória e paralelismo de instrução até o processamento massivo em clusters de memória distribuída.
🛠️ Stack Tecnológica e Infraestrutura

    Linguagens: C (Sistemas/HPC) e Python (Análise de Dados e Visualização).

    Paralelismo: OpenMP (Multicore) e MPI (Multi-node).

    Ambiente: Supercomputador NPAD/UFRN (Ambiente de produção HPC).

    Ferramentas: Slurm, GCC (O3, SIMD), Make, Valgrind, GDB.

📂 Índice de Projetos

Abaixo, a progressão técnica detalhada dos experimentos realizados:
ID	Projeto	Foco Técnico	Destaque de Engenharia
01	MxV & Cache	Localidade de Dados	Demonstração de lentidão de 15x por cache misses no L3.
02	ILP & Otimização	Paralelismo de Instrução	Quebra de dependências para saturar as ALUs do processador.
03	Cálculo de π	Trade-off Custo x Precisão	Otimização ILP e análise de interpolação visual (Lanczos).
04	CPU vs Memory	Perfilamento de Carga	Identificação de gargalos de largura de banda vs. processamento.
05	Contagem de Primos	Condição de Corrida	Uso de reduction para garantir integridade; Speedup de 2.01x.
06	Monte Carlo π	Sincronização Crítica	Análise do custo de critical vs. redução manual (Speedup 2.74x).
07	List Tasking	Estruturas Dinâmicas	Paralelização de listas encadeadas usando omp task.
08	Atomicidade	Nível de Registrador	Estudo de operações não-atômicas e inconsistência de dados.
09	Locks Dinâmicos	Fine-Grained Locking	Uso de omp_lock_t para escalonabilidade em múltiplas listas.
10	Productivity	Abstrações OpenMP	Comparativo entre atomic, critical e reduction.
11	Navier-Stokes	Simulação CFD	Otimização de laços aninhados com collapse e schedule.
12	Project Rescue	Gestão de Repositórios	Integração e manutenção de código legado para HPC.
13	Afinidade (NUMA)	Hardware Pinning	Impacto de OMP_PROC_BIND e localidade em nós multicore.
14	MPI Ping-Pong	Comunicação Distribuída	Medição de Latência (τ) e Largura de Banda (β).
15	Overlap MPI	Escondendo Latência	Ganho de 37% usando MPI_Isend/Irecv para sobrepor cálculo.
16	MxV (MPI)	Escalabilidade Global	Multiplicação de matrizes em cluster com Scatter/Gather.
17	Desafio Final	Consolidação HPC	Aplicação final de conceitos de alto desempenho em larga escala.
🔬 Destaques de Engenharia
1. Hierarquia de Memória e Afinidade

Nos projetos 01 e 13, exploramos como o layout dos dados e o posicionamento das threads nos núcleos (Afinidade) impactam o tempo de resposta. A compreensão da arquitetura NUMA permitiu otimizar simulações complexas como as de Fluidodinâmica (CFD).
2. Sincronização e Escalabilidade

A evolução do projeto 05 ao 10 demonstra o domínio sobre a gestão de recursos compartilhados. O foco não foi apenas "fazer funcionar", mas encontrar o equilíbrio entre corretude e performance, minimizando a contenção de barramento.
3. Computação Distribuída (MPI)

Nos projetos finais, a barreira do nó único foi superada. Implementamos estratégias de Hiding Latency (Projeto 15), onde a CPU processa dados locais enquanto a placa de rede (NIC) transmite dados de borda, maximizando a eficiência do cluster.
👤 Autor

Werbert Arles de Souza Barradas Engenheiro de Computação pela UFRN e Oficial da Reserva da Força Aérea Brasileira (FAB). Especialista em sistemas de missão crítica, baixo nível e infraestrutura de alta disponibilidade.
Como navegar neste repositório:

Cada pasta projeto_XX contém seu próprio README.md detalhado com gráficos de performance, análise de código e instruções de compilação via Makefile.
