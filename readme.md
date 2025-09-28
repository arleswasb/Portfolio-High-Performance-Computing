# Análise de Desempenho das Cláusulas `collapse` e `schedule` em OpenMP

### Estudo de Caso: Simulação da Equação de Difusão 2D

Este repositório contém o código-fonte e a análise de desempenho para a Tarefa 11 da disciplina de Programação Paralela (DCA3703) da Universidade Federal do Rio Grande do Norte (UFRN). O projeto explora a otimização de um simulador de difusão 2D em C utilizando OpenMP.

---

## Sobre o Projeto

O objetivo deste projeto é analisar e comparar o impacto de diferentes estratégias de paralelização de laços aninhados oferecidas pelo OpenMP. O estudo de caso é um simulador que resolve a equação da difusão (uma forma simplificada da equação de Navier-Stokes) em uma grade 2D, um problema comum em computação científica cujo desempenho é dominado por laços aninhados (padrão de estêncil).

As principais otimizações analisadas são:
* A cláusula `collapse`, para aumentar o escopo do paralelismo em laços aninhados.
* A cláusula `schedule`, para controlar como as iterações do laço são distribuídas entre as threads, com foco nas políticas `static`, `dynamic` e `guided`.

## Implementações

O repositório inclui várias versões do simulador para permitir uma análise comparativa:

* **`navier_stokes_simul_serial_tempo.c`**: A implementação puramente sequencial, utilizada como *baseline* para os cálculos de speedup.
* **`navier_stokes_paralelo_ingenua.c`**: Uma versão paralela "ingênua, mas correta", que paraleliza os laços espaciais de forma independente, incorrendo em alto overhead de fork/join.
* **`navier_stokes_paralelo_otm.c`**: A versão otimizada, que utiliza uma única região paralela por passo de tempo e a cláusula `collapse(2)` para maximizar o desempenho. É a base para os testes de `schedule`.
* **`navier_stokes_simul_serial_graficos.c`**: Uma versão serial modificada para gerar arquivos `.dat` para a validação visual da simulação.

## Como Compilar e Executar

### Pré-requisitos
* Um compilador C com suporte a OpenMP (ex: GCC).
* A ferramenta `bc` para os scripts de cálculo de média (padrão na maioria dos sistemas Linux).

### Compilação
```bash
# Para compilar a versão serial (baseline)
gcc -o navier_stokes_simul_serial_tempo.c -lm -fopenmp -O3

# Para compilar a versão paralela otimizada
gcc -o navier_stokes_paralelo_otm.c -lm -fopenmp -O3

```

### Autor

  * **Werbert Arles de Souza Barradas**

-----

**Disciplina:** DCA3-703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)
