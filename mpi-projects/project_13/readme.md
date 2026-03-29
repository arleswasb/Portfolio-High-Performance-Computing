Projeto 13: Avaliando o Impacto da Afinidade de Threads
Otimizando a Interação entre Software e Hardware no NPAD
📌 Descrição do Projeto

Este projeto investiga o conceito de Afinidade de Thread (Thread Affinity), que consiste em "prender" ou "amarrar" uma thread de software a um recurso de hardware específico, como um núcleo de CPU. O objetivo principal é mitigar os problemas causados pela migração arbitrária de threads pelo Sistema Operacional, que resultam em perda de localidade de cache e ineficiências em arquiteturas NUMA.

Utilizando a simulação de Navier-Stokes como benchmark, este projeto avalia como diferentes políticas de posicionamento impactam a escalabilidade e a eficiência em um nó de computação de alto desempenho.
🔬 Conceitos Abordados

    Migração de Threads: O problema do deslocamento de threads entre núcleos, gerando buscas lentas na RAM por perda de cache L1/L2.

    Arquitetura NUMA: A importância de manter a thread próxima ao seu soquete de memória local para minimizar a latência.

    Variáveis de Controle OpenMP: Uso de OMP_PROC_BIND e OMP_PLACES para gerenciar o posicionamento.

🛠️ Políticas de Afinidade Analisadas

O experimento compara quatro estados da variável OMP_PROC_BIND:
Política	Comportamento	Impacto Esperado
false	Afinidade desligada.	

Desempenho instável devido a migrações.
close	Threads agrupadas em núcleos próximos.	

Alta localidade de cache L3; ideal para poucas threads.
spread	Threads espalhadas uniformemente.	

Maximiza a largura de banda de memória entre soquetes.
master	Threads fixas no local da thread mestre.	

Risco de alta contenção em um único núcleo.
📊 Metodologia e Resultados

O teste foi executado no cluster NPAD utilizando o código navier_stokes_paralelo_otm2.c. Foram gerados heatmaps de escalabilidade para cada política.

Principais Conclusões:

    close (Otimizada para Latência): Apresentou a melhor eficiência para problemas pequenos e médios ao maximizar o reuso da cache L3.

    spread (Otimizada para Largura de Banda): Vantajosa em cenários de escalabilidade fraca com alta contagem de núcleos, distribuindo melhor o acesso à RAM.

    master: Comportou-se de forma similar à close neste cenário específico, mas limitou a utilização do segundo soquete do nó.

🚀 Como Executar

Para testar as diferentes políticas sem alterar o código, utilize as variáveis de ambiente no terminal:
Bash

# Exemplo para política spread com foco nos núcleos físicos
export OMP_PLACES=cores
export OMP_PROC_BIND=spread
./navier_stokes_paralelo_otm2 512

Autor

    Werbert Arles de Souza Barradas 

Disciplina: DCA3703 - Programação Paralela 

Instituição: Universidade Federal do Rio Grande do Norte (UFRN) 

Data: 03 de Outubro de 2025
