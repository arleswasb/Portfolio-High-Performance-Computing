#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Definição da estrutura do nó da lista encadeada
typedef struct Node {
    char filename[50];
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(const char* filename) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(1);
    }
    strncpy(newNode->filename, filename, sizeof(newNode->filename) - 1);
    newNode->filename[sizeof(newNode->filename) - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um nó no final da lista
void insertNode(Node** head, const char* filename) {
    Node* newNode = createNode(filename);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Função para processar o nó
void processNode(Node* node) {
    if (node) {
        printf("Processando arquivo: %s, pela thread: %d\n", node->filename, omp_get_thread_num());
    }
}

// Função para liberar a memória da lista
void freeList(Node** head) {
    Node* current = *head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;
    int num_files = 20;
    char filename_buffer[50];

    // Cria a lista encadeada com nomes de arquivos fictícios
    for (int i = 0; i < num_files; i++) {
        snprintf(filename_buffer, sizeof(filename_buffer), "arquivo_%d.txt", i + 1);
        insertNode(&head, filename_buffer);
    }

    // Região paralela para percorrer e processar a lista com tarefas
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("As tarefas foeam processadas pela thread: %d\n", omp_get_thread_num());
            Node* current = head;
            while (current != NULL) {
                #pragma omp taskwait
                {
                    processNode(current);
                }
                current = current->next;
            }
        }
    }

    // Libera a memória alocada para a lista
    freeList(&head);

    return 0;
}