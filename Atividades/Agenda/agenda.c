#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *pBuffer = NULL; // Ponteiro genérico para o buffer
    void *temp;           // Ponteiro temporário para manipular dados no buffer

    // Alocar espaço inicial para o menu e o contador de pessoas
    pBuffer = malloc(sizeof(int) + sizeof(int)); // [opção (int)] + [contador de pessoas (int)]
    if (!pBuffer) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Inicializar os valores do buffer
    *(int *)pBuffer = 0;                          // Opção do menu
    *(int *)(pBuffer + sizeof(int)) = 0;          // Contador de pessoas

    // Loop do menu
    do {
        printf("\nAGENDA - MENU:\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar Todos\n");
        printf("5- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", (int *)pBuffer); // Ler a opção diretamente no buffer

        switch (*(int *)pBuffer) {
            case 1: { // Adicionar pessoa
                char nome[50], email[50];
                int idade;

                printf("Digite o nome: ");
                scanf(" %[^\n]", nome);
                printf("Digite a idade: ");
                scanf("%d", &idade);
                printf("Digite o email: ");
                scanf(" %[^\n]", email);

                // Calcular o tamanho da nova pessoa
                int pessoaSize = strlen(nome) + 1 + sizeof(int) + strlen(email) + 1;

                // Realocar o buffer para armazenar os dados da nova pessoa
                int totalPessoas = *(int *)(pBuffer + sizeof(int));
                pBuffer = realloc(pBuffer, sizeof(int) + sizeof(int) + (totalPessoas * pessoaSize) + pessoaSize);
                if (!pBuffer) {
                    printf("Erro ao alocar memória.\n");
                    return 1;
                }

                // Atualizar o ponteiro para o total de pessoas
                int *contador = (int *)(pBuffer + sizeof(int));

                // Posicionar o ponteiro no início do espaço da nova pessoa
                temp = pBuffer + sizeof(int) + sizeof(int) + (totalPessoas * pessoaSize);

                // Armazenar os dados da pessoa no buffer
                strcpy((char *)temp, nome);                       // Nome
                temp += strlen(nome) + 1;                        // Pular o nome
                *(int *)temp = idade;                            // Idade
                temp += sizeof(int);                             // Pular a idade
                strcpy((char *)temp, email);                     // Email

                // Incrementar o total de pessoas
                (*contador)++;
                printf("Pessoa adicionada com sucesso!\n");
                break;
            }

            case 2: { // Remover pessoa
                if (*(int *)(pBuffer + sizeof(int)) == 0) {
                    printf("Nenhuma pessoa cadastrada para remover.\n");
                    break;
                }

                char nome[50];
                printf("Digite o nome da pessoa que deseja remover: ");
                scanf(" %[^\n]", nome);

                // Procurar a pessoa no buffer
                int totalPessoas = *(int *)(pBuffer + sizeof(int));
                temp = pBuffer + sizeof(int) + sizeof(int);
                void *anterior = temp;
                int pessoaSize = 0;
                int found = 0;

                for (int i = 0; i < totalPessoas; i++) {
                    // Calcular o tamanho da pessoa atual
                    pessoaSize = strlen((char *)temp) + 1 + sizeof(int) + strlen((char *)(temp + strlen((char *)temp) + 1 + sizeof(int))) + 1;

                    if (strcmp((char *)temp, nome) == 0) {
                        found = 1;
                        void *proximaPessoa = temp + pessoaSize;
                        int remainingSize = (pBuffer + sizeof(int) + sizeof(int) + (totalPessoas * pessoaSize)) - proximaPessoa;

                        // Mover os dados para remover a pessoa
                        memmove(temp, proximaPessoa, remainingSize);

                        // Atualizar o total de pessoas
                        (*(int *)(pBuffer + sizeof(int)))--;
                        break;
                    }

                    // Avançar para a próxima pessoa
                    anterior = temp;
                    temp += pessoaSize;
                }

                if (found) {
                    // Realocar o buffer para reduzir o tamanho
                    pBuffer = realloc(pBuffer, sizeof(int) + sizeof(int) + ((*(int *)(pBuffer + sizeof(int))) * pessoaSize));
                    if (!pBuffer) {
                        printf("Erro ao alocar memória.\n");
                        return 1;
                    }
                    printf("Pessoa removida com sucesso!\n");
                } else {
                    printf("Pessoa não encontrada.\n");
                }
                break;
            }

            case 3: { // Buscar pessoa
                if (*(int *)(pBuffer + sizeof(int)) == 0) {
                    printf("Nenhuma pessoa cadastrada para buscar.\n");
                    break;
                }

                char nome[50];
                printf("Digite o nome da pessoa que deseja buscar: ");
                scanf(" %[^\n]", nome);

                // Procurar a pessoa no buffer
                temp = pBuffer + sizeof(int) + sizeof(int);
                int found = 0;

                for (int i = 0; i < *(int *)(pBuffer + sizeof(int)); i++) {
                    char *nomeAtual = (char *)temp;
                    int *idadeAtual = (int *)(temp + strlen(nomeAtual) + 1);
                    char *emailAtual = (char *)(idadeAtual + 1);

                    if (strcmp(nomeAtual, nome) == 0) {
                        found = 1;
                        printf("Pessoa encontrada:\n");
                        printf("Nome: %s\n", nomeAtual);
                        printf("Idade: %d\n", *idadeAtual);
                        printf("Email: %s\n", emailAtual);
                        break;
                    }

                    // Avançar para a próxima pessoa
                    temp = emailAtual + strlen(emailAtual) + 1;
                }

                if (!found) {
                    printf("Pessoa não encontrada.\n");
                }
                break;
            }

            case 4: { // Listar todas as pessoas
                if (*(int *)(pBuffer + sizeof(int)) == 0) {
                    printf("Nenhuma pessoa cadastrada.\n");
                    break;
                }

                printf("Lista de pessoas cadastradas:\n");
                temp = pBuffer + sizeof(int) + sizeof(int);

                for (int i = 0; i < *(int *)(pBuffer + sizeof(int)); i++) {
                    char *nomeAtual = (char *)temp;
                    int *idadeAtual = (int *)(temp + strlen(nomeAtual) + 1);
                    char *emailAtual = (char *)(idadeAtual + 1);

                    printf("Nome: %s\n", nomeAtual);
                    printf("Idade: %d\n", *idadeAtual);
                    printf("Email: %s\n", emailAtual);

                    // Avançar para a próxima pessoa
                    temp = emailAtual + strlen(emailAtual) + 1;
                }
                break;
            }

            case 5:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (*(int *)pBuffer != 5);

    // Liberar o buffer
    free(pBuffer);

    return 0;
}
