
# Projeto 06: Sincronização e Gerenciamento de Escopo em OpenMP

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Framework](https://img.shields.io/badge/Framework-OpenMP-orange.svg)
![Licença](https://img.shields.io/badge/Licença-MIT-green.svg)

## Descrição do Projeto

Este projeto, desenvolvido para a disciplina de Programação Paralela (DCA3703), explora a paralelização do algoritmo de Monte Carlo para a estimação de π. O foco é demonstrar a evolução de uma implementação sequencial para uma paralela otimizada, destacando os desafios comuns como condições de corrida e gargalos de sincronização.

O projeto compara quatro abordagens distintas para ilustrar os ganhos de desempenho do paralelismo, a importância de gerenciar o acesso a recursos compartilhados e o papel fundamental das cláusulas de escopo de variáveis do OpenMP.

## Conceitos Abordados

* **Condição de Corrida**: Demonstração prática de como o acesso concorrente e não protegido a uma variável compartilhada leva a resultados incorretos.
* **Sincronização com a Diretiva `#pragma omp critical`**: Uso de seções críticas para garantir a exclusão mútua e corrigir a condição de corrida, analisando seu impacto no desempenho.
* **Padrão de Redução Manual**: Implementação de uma estratégia otimizada onde cada thread utiliza uma variável privada para contagens locais, minimizando a sincronização e a contenção.
* **Cláusulas de Escopo do OpenMP**: Análise do uso de `default(none)`, `shared` e `private` para gerenciar explicitamente o escopo das variáveis e escrever um código paralelo mais seguro e claro.

## Estrutura do Projeto

O projeto é composto por um único arquivo C que implementa quatro funções, cada uma representando uma etapa na evolução da paralelização do algoritmo:

1.  **Função Sequencial**: A implementação base (*baseline*) de thread única.
2.  **Função Paralela Ingênua**: Versão com uma condição de corrida intencional.
3.  **Função Paralela com `critical`**: Versão corrigida, mas com um gargalo de desempenho.
4.  **Função Paralela Otimizada**: Versão correta e com ganho de desempenho significativo.

## Como Compilar e Executar

O projeto foi desenvolvido em C e utiliza a biblioteca OpenMP. É necessário um compilador com suporte a OpenMP (como o GCC) e a flag `-fopenmp`.

### Compilação

```bash
# O nome do arquivo pode variar, ajuste conforme a versão do codigo
gcc -fopenmp -o prog_paralel_for_critical.c prog_paralel_for_critical
````

### Execução

```bash
./prog_paralel_for_critical
```

O programa executará todas as quatro versões em sequência e imprimirá o tempo de execução e o valor de π estimado para cada uma.

## Análise e Principais Conclusões

A análise comparativa do tempo de execução e da correção das quatro versões, com **100.000.000 de iterações**, revelou os seguintes resultados:

### Resultados de Desempenho

| Versão | Estratégia | Tempo de Execução (s) | π Estimado | Correto? |
| :--- | :--- | :--- | :--- | :--- |
| 1 | Sequencial | 1.069 | 3.141518 | **Sim** |
| 2 | Paralela Ingênua | 1.050 | \~0.983680 | **Não** |
| 3 | Paralela com `critical` | 5.176 | 3.141977 | **Sim** |
| 4 | Paralela Otimizada | **0.390** | 3.141521 | **Sim** |

### Principais Conclusões

1.  **Condição de Corrida é Silenciosa e Destrutiva**: A Versão Ingênua produziu um resultado completamente errado e inconsistente a cada execução. Isso demonstra que a falta de sincronização em variáveis compartilhadas invalida o resultado do programa.

2.  **Sincronização Inadequada é Pior que Nenhuma Paralelização**: A Versão com `critical` corrigiu o resultado, mas foi **quase 5 vezes mais lenta** que a versão sequencial. O uso da seção crítica em cada iteração do laço serializou o acesso ao contador, criando um gargalo que eliminou todos os benefícios do paralelismo.

3.  **Redução Manual é a Chave para o Desempenho**: A Versão Otimizada, que utiliza uma variável privada para a contagem em cada thread e realiza a soma em uma seção crítica apenas uma vez por thread, foi a única que alcançou correção e desempenho. Esta abordagem minimiza a contenção e é um padrão fundamental para otimização em OpenMP. O **speedup** alcançado foi de aproximadamente **2.74x** em relação à versão sequencial.

4.  **Gerenciamento de Escopo é Crucial**: O uso de `default(none)` força o programador a definir explicitamente o escopo de cada variável, prevenindo erros de compartilhamento acidental e tornando o código mais robusto e legível.

## Autor

  * **Werbert Arles de Souza Barradas**

-----

**Disciplina:** DCA3-703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

```
```