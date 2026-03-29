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

## Autor

  * **Werbert Arles de Souza Barradas**

-----

**Disciplina:** DCA3-703 - Programação Paralela - T01 (2025.2)  
**Docente:** Professor Doutor Samuel Xavier de Souza  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)


## 💻 imagens

![Terminal com tempos](terminal.png)

![tela do Neohtop com as barras de desempenho da cpu](neohtop.png)
