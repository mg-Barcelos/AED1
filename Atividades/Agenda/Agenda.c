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
