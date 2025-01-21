#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir os offsets dentro do pBuffer
#define P_USEROPTION        ((int *)pBuffer)
#define P_TOTAL_PEOPLE      ((int *)(P_USEROPTION + 1))
#define P_TMP_NODE_NAME     ((char *)(P_TOTAL_PEOPLE + 1))
#define P_TMP_NODE_AGE      ((int *)(P_TMP_NODE_NAME + 50 * sizeof(char)))
#define P_TMP_NODE_EMAIL    ((char *)(P_TMP_NODE_AGE + 1))
#define P_HEAD              ((void **)(P_TMP_NODE_EMAIL + 50 * sizeof(char)))

// Tamanho de uma pessoa armazenada (nome + idade + email)
#define PERSON_SIZE(name, email) (strlen(name) + 1 + sizeof(int) + strlen(email) + 1)

int main() {
    void *pBuffer = NULL; // Buffer genérico

    // Alocar memória inicial para variáveis de controle e temporárias
    pBuffer = malloc(sizeof(int) + sizeof(int) + 50 * sizeof(char) + sizeof(int) + 50 * sizeof(char) + sizeof(void *));
    if (!pBuffer) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Inicializar controle de opções e total de pessoas
    *P_USEROPTION = 0;
    *P_TOTAL_PEOPLE = 0;
    *P_HEAD = NULL; // Início da lista ligada

    // Loop do menu
    do {
        printf("\nAGENDA - MENU:\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar Todos\n");
        printf("5- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", P_USEROPTION);

        switch (*P_USEROPTION) {
            case 1: { // Adicionar pessoa
                printf("Digite o nome (até 50 caracteres): ");
                scanf(" %[^\n]", P_TMP_NODE_NAME);
                printf("Digite a idade: ");
                scanf("%d", P_TMP_NODE_AGE);
                printf("Digite o email (até 50 caracteres): ");
                scanf(" %[^\n]", P_TMP_NODE_EMAIL);

                // Calcular o tamanho necessário para armazenar a nova pessoa
                int pessoaSize = PERSON_SIZE(P_TMP_NODE_NAME, P_TMP_NODE_EMAIL);

                // Criar um novo nó para a lista ligada
                void *newNode = malloc(pessoaSize + sizeof(void *));
                if (!newNode) {
                    printf("Erro ao alocar memória para a nova pessoa.\n");
                    break;
                }

                // Armazenar os dados no novo nó
                char *name = (char *)newNode;
                strcpy(name, P_TMP_NODE_NAME);

                int *age = (int *)(name + strlen(name) + 1);
                *age = *P_TMP_NODE_AGE;

                char *email = (char *)(age + 1);
                strcpy(email, P_TMP_NODE_EMAIL);

                void **next = (void **)(email + strlen(email) + 1);
                *next = NULL;

                // Inserir o novo nó na lista ligada (ordenado por nome)
                void **current = P_HEAD;
                while (*current && strcmp((char *)(*current), name) < 0) {
                    current = (void **)((char *)(*current) + pessoaSize);
                }
                *next = *current;
                *current = newNode;

                // Incrementar o total de pessoas
                (*P_TOTAL_PEOPLE)++;
                printf("Pessoa adicionada com sucesso!\n");
                break;
            }

            case 2: { // Remover pessoa
                if (*P_TOTAL_PEOPLE == 0) {
                    printf("Nenhuma pessoa cadastrada para remover.\n");
                    break;
                }

                printf("Digite o nome da pessoa que deseja remover: ");
                scanf(" %[^\n]", P_TMP_NODE_NAME);

                // Procurar a pessoa na lista ligada
                void **current = P_HEAD;
                void *prev = NULL;
                int found = 0;

                while (*current) {
                    char *name = (char *)(*current);
                    if (strcmp(name, P_TMP_NODE_NAME) == 0) {
                        found = 1;
                        break;
                    }
                    prev = current;
                    current = (void **)((char *)(*current) + PERSON_SIZE(name, (char *)((int *)(name + strlen(name) + 1) + 1)));
                }

                if (found) {
                    // Remover a pessoa da lista
                    void *toDelete = *current;
                    *current = *(void **)((char *)toDelete + PERSON_SIZE((char *)toDelete, (char *)((int *)((char *)toDelete + strlen((char *)toDelete) + 1) + 1)));
                    free(toDelete);

                    // Decrementar o total de pessoas
                    (*P_TOTAL_PEOPLE)--;
                    printf("Pessoa removida com sucesso!\n");
                } else {
                    printf("Pessoa não encontrada.\n");
                }
                break;
            }

            case 3: { // Buscar pessoa
                if (*P_TOTAL_PEOPLE == 0) {
                    printf("Nenhuma pessoa cadastrada para buscar.\n");
                    break;
                }

                printf("Digite o nome da pessoa que deseja buscar: ");
                scanf(" %[^\n]", P_TMP_NODE_NAME);

                // Procurar a pessoa na lista ligada
                void *current = *P_HEAD;
                int found = 0;

                while (current) {
                    char *name = (char *)current;
                    if (strcmp(name, P_TMP_NODE_NAME) == 0) {
                        found = 1;

                        int *age = (int *)(name + strlen(name) + 1);
                        char *email = (char *)(age + 1);

                        printf("Pessoa encontrada:\n");
                        printf("Nome: %s\n", name);
                        printf("Idade: %d\n", *age);
                        printf("Email: %s\n", email);
                        break;
                    }
                    current = *(void **)((char *)current + PERSON_SIZE(name, (char *)((int *)(name + strlen(name) + 1) + 1)));
                }

                if (!found) {
                    printf("Pessoa não encontrada.\n");
                }
                break;
            }

            case 4: { // Listar todas as pessoas
                if (*P_TOTAL_PEOPLE == 0) {
                    printf("Nenhuma pessoa cadastrada.\n");
                    break;
                }

                printf("Lista de pessoas cadastradas:\n");
                void *current = *P_HEAD;

                while (current) {
                    char *name = (char *)current;
                    int *age = (int *)(name + strlen(name) + 1);
                    char *email = (char *)(age + 1);

                    printf("Nome: %s\n", name);
                    printf("Idade: %d\n", *age);
                    printf("Email: %s\n", email);

                    current = *(void **)((char *)current + PERSON_SIZE(name, email));
                }
                break;
            }

            case 5:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (*P_USEROPTION != 5);

    // Liberar toda a memória alocada
    void *current = *P_HEAD;
    while (current) {
        void *toDelete = current;
        current = *(void **)((char *)current + PERSON_SIZE((char *)current, (char *)((int *)((char *)current + strlen((char *)current) + 1) + 1)));
        free(toDelete);
    }

    free(pBuffer);
    return 0;
}
