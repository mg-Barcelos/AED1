#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir os offsets no pBuffer
#define MENU_OPTION       ((int *)pBuffer)                      // Opção do menu
#define PEOPLE_COUNT      ((int *)(MENU_OPTION + 1))            // Contador de pessoas
#define TEMP_NAME         ((char *)(PEOPLE_COUNT + 1))          // Nome temporário
#define TEMP_AGE          ((int *)(TEMP_NAME + 50 * sizeof(char))) // Idade temporária
#define TEMP_EMAIL        ((char *)(TEMP_AGE + 1))              // Email temporário
#define LIST_HEAD         ((void **)(TEMP_EMAIL + 50 * sizeof(char))) // Cabeça da lista ligada
#define TEMP_PTR          ((void **)(LIST_HEAD + 1))            // Ponteiro temporário

// Calcular o tamanho de uma pessoa
#define PERSON_SIZE(name, email) (strlen(name) + 1 + sizeof(int) + strlen(email) + 1 + sizeof(void *))

void push(void *pBuffer) {
    // Solicitar dados do usuário
    printf("Digite o nome (até 50 caracteres): ");
    scanf(" %[^\n]", TEMP_NAME);
    printf("Digite a idade: ");
    scanf("%d", TEMP_AGE);
    printf("Digite o email (até 50 caracteres): ");
    scanf(" %[^\n]", TEMP_EMAIL);

    // Calcular tamanho do nó
    int personSize = PERSON_SIZE(TEMP_NAME, TEMP_EMAIL);

    // Alocar memória para a nova pessoa dentro de um nó
    *TEMP_PTR = malloc(personSize);
    if (!*TEMP_PTR) {
        printf("Erro ao alocar memória para a nova pessoa.\n");
        return;
    }

    // Copiar os dados para o nó
    char *name = (char *)(*TEMP_PTR);
    strcpy(name, TEMP_NAME);

    int *age = (int *)(name + strlen(name) + 1);
    *age = *TEMP_AGE;

    char *email = (char *)(age + 1);
    strcpy(email, TEMP_EMAIL);

    void **next = (void **)(email + strlen(email) + 1);
    *next = NULL;

    // Inserir o nó na lista em ordem alfabética
    void **current = LIST_HEAD;
    while (*current && strcmp((char *)(*current), name) < 0) {
        current = (void **)((char *)(*current) + PERSON_SIZE((char *)(*current), (char *)((int *)((char *)(*current) + strlen((char *)(*current)) + 1) + 1)));
    }
    *next = *current;
    *current = *TEMP_PTR;

    // Incrementar o contador de pessoas
    (*PEOPLE_COUNT)++;
    printf("Pessoa adicionada com sucesso!\n");
}

void pop(void *pBuffer) {
    if (*PEOPLE_COUNT == 0) {
        printf("Nenhuma pessoa cadastrada para remover.\n");
        return;
    }

    printf("Digite o nome da pessoa que deseja remover: ");
    scanf(" %[^\n]", TEMP_NAME);

    void **current = LIST_HEAD;
    void **prev = LIST_HEAD;

    // Procurar a pessoa pelo nome
    while (*current) {
        char *name = (char *)(*current);
        if (strcmp(name, TEMP_NAME) == 0) {
            // Pessoa encontrada
            void *toDelete = *current;
            *current = *(void **)((char *)toDelete + PERSON_SIZE(name, (char *)((int *)(name + strlen(name) + 1) + 1)));
            free(toDelete);

            (*PEOPLE_COUNT)--;
            printf("Pessoa removida com sucesso!\n");
            return;
        }
        prev = current;
        current = (void **)((char *)(*current) + PERSON_SIZE((char *)(*current), (char *)((int *)((char *)(*current) + strlen((char *)(*current)) + 1) + 1)));
    }

    printf("Pessoa nao encontrada.\n");
}

void search(void *pBuffer) {
    if (*PEOPLE_COUNT == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    printf("Digite o nome da pessoa que deseja buscar: ");
    scanf(" %[^\n]", TEMP_NAME);

    void *current = *LIST_HEAD;

    while (current) {
        char *name = (char *)current;
        if (strcmp(name, TEMP_NAME) == 0) {
            // Pessoa encontrada
            int *age = (int *)(name + strlen(name) + 1);
            char *email = (char *)(age + 1);

            printf("Pessoa encontrada:\n");
            printf("Nome: %s\n", name);
            printf("Idade: %d\n", *age);
            printf("Email: %s\n", email);
            return;
        }
        current = *(void **)((char *)current + PERSON_SIZE(name, (char *)((int *)(name + strlen(name) + 1) + 1)));
    }

    printf("Pessoa não encontrada.\n");
}

void listAll(void *pBuffer) {
    if (*PEOPLE_COUNT == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    printf("Lista de pessoas cadastradas:\n");
    void *current = *LIST_HEAD;

    while (current) {
        char *name = (char *)current;
        int *age = (int *)(name + strlen(name) + 1);
        char *email = (char *)(age + 1);

        printf("Nome: %s\n", name);
        printf("Idade: %d\n", *age);
        printf("Email: %s\n", email);

        current = *(void **)((char *)current + PERSON_SIZE(name, email));
    }
}

int main() {
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + 50 * sizeof(char) + sizeof(int) + 50 * sizeof(char) + sizeof(void *) + sizeof(void *));
    if (!pBuffer) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    *MENU_OPTION = 0;
    *PEOPLE_COUNT = 0;
    *LIST_HEAD = NULL;

    do {
        printf("\nAGENDA - MENU:\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar Todos\n");
        printf("5- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", MENU_OPTION);

        switch (*MENU_OPTION) {
            case 1:
                push(pBuffer);
                break;
            case 2:
                pop(pBuffer);
                break;
            case 3:
                search(pBuffer);
                break;
            case 4:
                listAll(pBuffer);
                break;
            case 5:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (*MENU_OPTION != 5);

    // Limpar memória
    void *current = *LIST_HEAD;
    while (current) {
        void *toDelete = current;
        current = *(void **)((char *)current + PERSON_SIZE((char *)toDelete, (char *)((int *)((char *)toDelete + strlen((char *)toDelete) + 1) + 1)));
        free(toDelete);
    }
    free(pBuffer);
    return 0;
}