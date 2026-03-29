Com base na apresentação `apt_pj_PP_05.pdf`, aqui está o conteúdo do projeto formatado como um arquivo `README.md`, ideal para um repositório Git.

-----

# Paralelização da Contagem de Números Primos

> Um Estudo sobre Condições de Corrida e Speedup com OpenMP

**Autor:** Werbert Arles de Souza Barradas 
**Disciplina:** Programação Paralela - DCA3703  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)  
**Data:** 20 de agosto de 2025 

-----

## 📝 Introdução

A contagem de números primos em um grande intervalo é uma tarefa computacionalmente intensiva, ideal para testar os limites do paralelismo.

O objetivo deste estudo é analisar o ganho de desempenho (speedup) e demonstrar experimentalmente o problema da **condição de corrida** e sua solução em OpenMP. Para isso, o projeto compara uma execução sequencial, que serve como baseline, com uma execução paralela, que busca reduzir o tempo de execução mas introduz desafios de sincronização.

## ⚙️ Metodologia: As Três Implementações

O projeto foi desenvolvido em três versões distintas para ilustrar a evolução da paralelização.

### Função de Verificação de Primalidade

O núcleo de todas as versões é uma função otimizada que determina se um número é primo. Ela trata casos base e utiliza o fato de que todo primo maior que 3 pode ser expresso na forma `6k ± 1` para reduzir o número de divisores a serem testados.

```c
// Retorna 1 se for primo, 0 caso contrario.
int is_prime(int num) {
    if (num <= 1) return 0; 
    if (num <= 3) return 1; 
    if (num % 2 == 0 || num % 3 == 0) return 0;
    
    // Um numero primo (maior que 3) pode ser expresso como 6k +/- 1.
    // Verificamos divisores a partir de 5.
    for (int i = 5; i * i <= num; i = i + 6) { 
        if (num % i == 0 || num % (i + 2) == 0) { 
            return 0; 
        }
    }
    return 1; 
}
```

### 1\. Versão Sequencial (Baseline)

Uma implementação de thread única que serve como referência para corretude e desempenho. Um laço `for` percorre o intervalo e incrementa um contador para cada primo encontrado.

```c
int total_primes_seq = 0; 
start_time = omp_get_wtime(); 
for (int i = 2; i <= n; i++) { 
    [cite_start]if (is_prime(i)) { 
        [cite_start]total_primes_seq++; 
    }
}
```

### 2\. Versão Paralela Ingênua

Utiliza a diretiva `#pragma omp parallel for` para dividir as iterações do laço entre as threads. Esta abordagem, no entanto, introduz um erro crítico.

```c
int total_primes_par = 0; 
#pragma omp parallel for 
for (int i = 2; i <= n; i++) { 
    [cite_start]if (is_prime(i)) { 
        // Condicao de corrida!
        [cite_start]total_primes_par++; 
    }
}
```

### 3\. Versão Paralela Corrigida

Resolve a condição de corrida de forma eficiente utilizando a cláusula `reduction` do OpenMP. O OpenMP cria uma cópia privada do contador para cada thread e, ao final, soma (`+`) todos os subtotais na variável original.

```c
total_primes_par = 0; 
#pragma omp parallel for reduction(+:total_primes_par) 
for (int i = 2; i <= n; i++) { 
    if (is_prime(i)) { 
        total_primes_par++; 
    }
}
```

## 🔬 Por que a Versão Ingênua Falha? A Condição de Corrida

#### A Operação Não-Atômica

A instrução `x++` não é uma operação única. O processador a executa em três passos:

1.  **Ler** o valor de `x` da memória.
2.  **Incrementar** o valor em um registrador.
3.  **Escrever** o novo valor de volta na memória.

Múltiplas threads podem executar o passo 1 antes que qualquer uma chegue ao passo 3.

#### Cenário de Conflito

  * Thread A lê `total` (ex: 100).
  * Thread B lê `total` (ainda 100).
  * Thread A escreve `101`.
  * Thread B escreve `101`.

**Resultado:** Dois primos foram encontrados, mas o contador foi incrementado apenas uma vez.

## 📊 Resultados e Análise

Os testes foram realizados contando primos no intervalo de 2 a 20.000.000.

| Versão | Primos Encontrados | Tempo de Execução (s) |
| :--- | :--- | :--- |
| **Sequencial** | 1.270.607  | 4.510 |
| **Paralela (Ingênua)** | 1.251.167  | 2.115  |
| **Paralela (Corrigida)** | 1.270.607 | 2.237  |

### Análise de Correção

  * A versão Paralela (Ingênua), embora rápida, produz um resultado incorreto (1.251.167 primos).
  * Apenas as versões Sequencial e Paralela (Corrigida) chegam ao valor correto de 1.270.607 primos.

### Análise de Desempenho (Speedup)

Comparando as duas versões corretas:
$S = \\frac{T\_{sequencial}}{T\_{paralelo}} = \\frac{4.510s}{2.237s} \\approx 2.01$

A paralelização correta resultou em um programa **2.01 vezes mais rápido**.

## 🚀 Como Compilar e Executar

#### Pré-requisitos

  - Um compilador C com suporte a OpenMP (por exemplo, **GCC**).

#### Compilação

Abra um terminal na pasta do projeto e use o seguinte comando (supondo que o arquivo-fonte se chame `primos_omp.c'):

```bash
gcc -o primos_omp primos_omp.c -fopenmp -lm
```

  - `-fopenmp`: Flag essencial que habilita a compilação com as bibliotecas OpenMP.
  - `-lm`: Link para a biblioteca matemática.

#### Execução

Após a compilação bem-sucedida, execute o programa com:

```bash
./primos_omp
```

## 📚 Conclusão

O experimento demonstrou claramente o potencial de ganho de desempenho do OpenMP, gerando um speedup de 2.01x. Ficou evidente que o acesso não sincronizado a recursos compartilhados leva a resultados incorretos. Compreender e aplicar mecanismos de sincronização, como a cláusula `reduction`, é fundamental para o desenvolvimento de software paralelo que seja não apenas rápido, mas também correto.

## Autor

  * **Werbert Arles de Souza Barradas**

-----

**Disciplina:** DCA3-703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)
