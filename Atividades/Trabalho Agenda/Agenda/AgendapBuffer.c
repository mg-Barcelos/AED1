// Bibliotecas
#include <stdio.h> //padrao
#include <stdlib.h>
#include <string.h>

// Macro para limpar a tela
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// usei pra definições de tamanhos
#define NOME_TAM 40
#define EMAIL_TAM 40
#define NODE_TAM (2 * sizeof(int) + NOME_TAM + sizeof(int) + EMAIL_TAM)
#define BUFFER_TAM (9 * sizeof(int) + NOME_TAM + sizeof(int) + EMAIL_TAM)  

// vai ajudar 
#define CABECA 0
#define CAUDA sizeof(int)
#define ATUAL (2 * sizeof(int))
#define ANTERIOR (3 * sizeof(int))
#define TAM_BUFFER (4 * sizeof(int))
#define LISTA_LIVRE (5 * sizeof(int))
#define ENTRADA (6 * sizeof(int))
#define ENTRADA_NOME (ENTRADA + sizeof(int))
#define ENTRADA_IDADE (ENTRADA_NOME + NOME_TAM)
#define ENTRADA_EMAIL (ENTRADA_IDADE + sizeof(int))
#define ENCONTRADO (ENTRADA_EMAIL + EMAIL_TAM) 
#define PROXIMO_TEMP (ENCONTRADO + sizeof(int))

void* pBuffer = NULL;

void menu() {
    system(CLEAR);
    printf("=== AGENDA ===\n1. Adicionar\n2. Remover\n3. Buscar\n4. Listar\n5. Sair\nOpcao: ");
    scanf("%d", (int*)((char*)pBuffer + ENTRADA));
    getchar();
}

void adicionar_contato() {
    printf("\nNome: ");
    fgets((char*)pBuffer + ENTRADA_NOME, NOME_TAM + 1, stdin);
    ((char*)pBuffer + ENTRADA_NOME)[strcspn((char*)pBuffer + ENTRADA_NOME, "\n")] = '\0';

    printf("Idade: ");
    fgets((char*)pBuffer + ENTRADA_IDADE, 10, stdin);
    ((char*)pBuffer + ENTRADA_IDADE)[strcspn((char*)pBuffer + ENTRADA_IDADE, "\n")] = '\0';

    // Valiação da idade 
    for (*(int*)((char*)pBuffer + ATUAL) = 0; ((char*)pBuffer + ENTRADA_IDADE)[*(int*)((char*)pBuffer + ATUAL)]; (*(int*)((char*)pBuffer + ATUAL))++) {
        if (((char*)pBuffer + ENTRADA_IDADE)[*(int*)((char*)pBuffer + ATUAL)] < '0' ||
            ((char*)pBuffer + ENTRADA_IDADE)[*(int*)((char*)pBuffer + ATUAL)] > '9') {
            printf("Idade invalida! apenas nuemros");
            getchar();
            return;
        }
    }
    *(int*)((char*)pBuffer + ENTRADA_IDADE) = atoi((char*)pBuffer + ENTRADA_IDADE);

    printf("Email: ");
    fgets((char*)pBuffer + ENTRADA_EMAIL, EMAIL_TAM + 1, stdin);
    ((char*)pBuffer + ENTRADA_EMAIL)[strcspn((char*)pBuffer + ENTRADA_EMAIL, "\n")] = '\0';

    // Alocação de espaço
    if (*(int*)((char*)pBuffer + LISTA_LIVRE)) {
        *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + LISTA_LIVRE);
        *(int*)((char*)pBuffer + LISTA_LIVRE) = *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL));
    } else {
        *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + TAM_BUFFER);
        *(int*)((char*)pBuffer + TAM_BUFFER) += NODE_TAM;
        void* novo_buffer = realloc(pBuffer, *(int*)((char*)pBuffer + TAM_BUFFER));
        if (!novo_buffer) return;
        pBuffer = novo_buffer;
    }

    // preenchi o nó
    memset((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL), 0, NODE_TAM);
    memcpy(
        (char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int), 
        (char*)pBuffer + ENTRADA_NOME, 
        NOME_TAM + sizeof(int) + EMAIL_TAM
    );

    // atualiza a lista
    if (*(int*)((char*)pBuffer + CABECA)) {
        *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + CAUDA)) = *(int*)((char*)pBuffer + ATUAL);
        *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + sizeof(int)) = *(int*)((char*)pBuffer + CAUDA);
    } else {
        *(int*)((char*)pBuffer + CABECA) = *(int*)((char*)pBuffer + ATUAL);
    }
    *(int*)((char*)pBuffer + CAUDA) = *(int*)((char*)pBuffer + ATUAL);

    printf("Contato adicionado!");
    getchar();
}

void remover_contato() {
    if (!*(int*)((char*)pBuffer + CABECA)) {
        printf("\nLista vazia!");
        getchar();
        return;
    }

    printf("\nNome para remover: ");
    fgets((char*)pBuffer + ENTRADA_NOME, NOME_TAM + 1, stdin);
    ((char*)pBuffer + ENTRADA_NOME)[strcspn((char*)pBuffer + ENTRADA_NOME, "\n")] = '\0';

    *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + CABECA);
    *(int*)((char*)pBuffer + ANTERIOR) = 0;

    while (*(int*)((char*)pBuffer + ATUAL)) {
        char* nome = (char*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int));
        if (strcmp(nome, (char*)pBuffer + ENTRADA_NOME) == 0) {
            
            *(int*)((char*)pBuffer + PROXIMO_TEMP) = *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL));

            if (*(int*)((char*)pBuffer + ANTERIOR)) {
                *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ANTERIOR)) = *(int*)((char*)pBuffer + PROXIMO_TEMP);
            } else {
                *(int*)((char*)pBuffer + CABECA) = *(int*)((char*)pBuffer + PROXIMO_TEMP);
            }

            if (*(int*)((char*)pBuffer + PROXIMO_TEMP)) {
                *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + PROXIMO_TEMP) + sizeof(int)) = *(int*)((char*)pBuffer + ANTERIOR);
            } else {
                *(int*)((char*)pBuffer + CAUDA) = *(int*)((char*)pBuffer + ANTERIOR);
            }

            // vai atualizar a listra live
            *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL)) = *(int*)((char*)pBuffer + LISTA_LIVRE);
            *(int*)((char*)pBuffer + LISTA_LIVRE) = *(int*)((char*)pBuffer + ATUAL);

            printf("Contato removido!");
            getchar();
            return;
        }
        *(int*)((char*)pBuffer + ANTERIOR) = *(int*)((char*)pBuffer + ATUAL);
        *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL));
    }

    printf("Contato nao encontrado!");
    getchar();
}

//[cab]->joao<->maria<->joao<-cauda

void buscar_contato() {
    if (!*(int*)((char*)pBuffer + CABECA)) {
        printf("\nLista vazia!");
        getchar();
        return;
    }

    printf("\nNome para buscar: ");
    fgets((char*)pBuffer + ENTRADA_NOME, NOME_TAM + 1, stdin);
    ((char*)pBuffer + ENTRADA_NOME)[strcspn((char*)pBuffer + ENTRADA_NOME, "\n")] = '\0';

    *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + CABECA);
    *(int*)((char*)pBuffer + ENCONTRADO) = 0; 

    while (*(int*)((char*)pBuffer + ATUAL)) {
        char* nome = (char*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int));
        if (strstr(nome, (char*)pBuffer + ENTRADA_NOME)) {//joao e o joao da silva
            printf("\nNome: %s\nIdade: %d\nEmail: %s\n", 
                nome,
                *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int) + NOME_TAM),
                (char*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int) + NOME_TAM + sizeof(int))
            );
            *(int*)((char*)pBuffer + ENCONTRADO) = 1; 
        }
        *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL));
    }

    if (!*(int*)((char*)pBuffer + ENCONTRADO)) printf("Nenhum contato encontrado!");
    getchar();
}

void listar_contatos() {
    if (!*(int*)((char*)pBuffer + CABECA)) {
        printf("\nLista vazia!");
        getchar();
        return;
    }

    *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + CABECA);
    //cab->joao
        //atual
    while (*(int*)((char*)pBuffer + ATUAL)) {
        printf("\nNome: %s\nIdade: %d\nEmail: %s\n",
            (char*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int)),
            *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int) + NOME_TAM),
            (char*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL) + 2*sizeof(int) + NOME_TAM + sizeof(int))
        );
        *(int*)((char*)pBuffer + ATUAL) = *(int*)((char*)pBuffer + *(int*)((char*)pBuffer + ATUAL));
    }
    getchar();
}

int main() {
    pBuffer = malloc(BUFFER_TAM);
    memset(pBuffer, 0, BUFFER_TAM);
    *(int*)((char*)pBuffer + TAM_BUFFER) = BUFFER_TAM;

    while (1) {
        menu();
        switch (*(int*)((char*)pBuffer + ENTRADA)) {
            case 1: adicionar_contato(); break;
            case 2: remover_contato(); break;
            case 3: buscar_contato(); break;
            case 4: listar_contatos(); break;
            case 5: free(pBuffer); exit(0);
            default: printf("Opcao invalida!"); getchar();
        }
    }
}