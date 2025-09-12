
# Projeto 07: Sincronização com o Modelo de Tarefas do OpenMP
### Processamento Paralelo de Listas Encadeadas

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Framework](https://img.shields.io/badge/Framework-OpenMP-orange.svg)
![Licença](https://img.shields.io/badge/Licença-MIT-green.svg)

## Descrição do Projeto

Este projeto, desenvolvido para a disciplina de Programação Paralela (DCA3703), explora a eficácia do modelo de tarefas (`task`) da API OpenMP para o processamento de estruturas de dados dinâmicas, como listas encadeadas. Diferente de laços iterativos com um número fixo de repetições, o processamento de nós de uma lista exige um modelo de paralelismo mais flexível, onde unidades de trabalho podem ser criadas e agendadas dinamicamente.

O programa implementado cria uma lista encadeada de "arquivos" fictícios e utiliza uma região paralela para criar uma tarefa para processar cada nó da lista, demonstrando uma abordagem robusta para paralelizar cargas de trabalho não estruturadas.

## Conceitos Abordados

* **Modelo de Tarefas do OpenMP**: Uso da diretiva `#pragma omp task` para criar unidades de trabalho independentes.
* **Paralelismo em Estruturas de Dados Dinâmicas**: Aplicação de técnicas de paralelismo a estruturas como listas encadeadas.
* **Sincronização de Tarefas**: Uso da diretiva `#pragma omp single` para serializar a criação de tarefas e evitar condições de corrida[cite: 817, 818].
* **Não-Determinismo**: Análise da ordem de execução das tarefas, que varia a cada execução do programa.
* **Barreiras Implícitas**: Compreensão de como o final de uma região `#pragma omp parallel` age como um ponto de sincronização para todas as tarefas geradas dentro dela.

## Estrutura do Projeto

O repositório contém um único arquivo-fonte principal:

* `list_task.c`: Contém a implementação completa, incluindo a definição da estrutura da lista encadeada, as funções de manipulação (criar, inserir, liberar) e a lógica de processamento paralelo com o modelo de tarefas do OpenMP.

## Como Compilar e Executar

O projeto foi desenvolvido em C e utiliza a biblioteca OpenMP. É necessário um compilador com suporte a OpenMP (como o GCC) e a flag `-fopenmp`.

### Compilação

```bash
gcc -fopenmp -o list_task list_task.c
````

### Execução

```bash
./list_task
```

[cite\_start]A saída do programa mostrará qual thread foi responsável por criar as tarefas e, em seguida, a ordem (não determinística) em que cada "arquivo" (nó) foi processado pelas threads disponíveis[cite: 907].

## Análise da Implementação

A solução se baseia na combinação estratégica de três diretivas OpenMP para garantir a correção e a eficiência:

1.  [cite\_start]`#pragma omp parallel`: Cria uma equipe de threads que executará o trabalho[cite: 816, 827].
2.  [cite\_start]`#pragma omp single`: Garante que o bloco de código que percorre a lista encadeada seja executado por **apenas uma thread**[cite: 817, 830]. [cite\_start]Isso é crucial para evitar que múltiplas threads tentem percorrer a lista ao mesmo tempo, o que causaria uma condição de corrida e a criação de tarefas duplicadas[cite: 818, 902].
3.  [cite\_start]`#pragma omp task`: Dentro do bloco `single`, para cada nó encontrado na lista, esta diretiva empacota a função de processamento (`processNode`) como uma tarefa independente[cite: 819, 833]. [cite\_start]Essas tarefas são colocadas em um "pool" e distribuídas dinamicamente pelo runtime do OpenMP para qualquer thread ociosa da equipe[cite: 834].

### Principais Conclusões do Experimento

  * **Todos os nós são processados?** Sim. [cite\_start]A travessia da lista dentro de uma região `single` garante que cada nó seja visitado e uma tarefa seja criada para ele[cite: 896, 897].
  * **Algum nó é processado mais de uma vez?** Não. [cite\_start]A diretiva `single` é a chave para a unicidade, pois apenas uma thread gera as tarefas, evitando duplicação[cite: 900, 901].
  * **A ordem de execução muda?** Sim. [cite\_start]A ordem em que os nós são processados é não-determinística, pois o OpenMP agenda as tarefas com base na disponibilidade das threads, o que pode variar a cada execução[cite: 906, 909].
  * [cite\_start]**Como a correção é garantida?** Pela combinação da criação serial de tarefas (`single`) com a execução paralela das mesmas (`task`), e pela barreira implícita no final da região `parallel`, que assegura que o programa só prossiga após a conclusão de todas as tarefas[cite: 914, 917].

## Autor

  * **Werbert Arles de Souza Barradas** ---
    **Disciplina:** DCA3703 - Programação Paralela - T01 (2025.2)  
    **Docente:** Professor Doutor Samuel Xavier de Souza  
    **Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

<!-- end list -->

```
```