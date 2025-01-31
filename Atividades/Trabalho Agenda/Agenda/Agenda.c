#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define NOME_MAX 40
#define EMAIL_MAX 40
#define CONTATO_TAM (2 * sizeof(size_t) + NOME_MAX + sizeof(int) + EMAIL_MAX)
#define TAM_INICIAL (4 * sizeof(size_t) + NOME_MAX + sizeof(int) + EMAIL_MAX)

#define CABECA_OFFSET 0
#define CAUDA_OFFSET sizeof(size_t)
#define TEMP_OFFSET (2 * sizeof(size_t))
#define TAM_BUFFER_OFFSET (3 * sizeof(size_t))
#define DADOS_OFFSET (4 * sizeof(size_t))

void* menu(void* pBuffer);
void* adicionar(void* pBuffer);
void* remover(void* pBuffer);
void* buscar(void* pBuffer);
void* listar(void* pBuffer);

int main() {
    void* pBuffer = malloc(TAM_INICIAL);
    memset(pBuffer, 0, TAM_INICIAL);
    *(size_t*)(pBuffer + TAM_BUFFER_OFFSET) = TAM_INICIAL;

    while (1) pBuffer = menu(pBuffer);
    
    free(pBuffer);
    return 0;
}

void* menu(void* pBuffer) {
    system(CLEAR);
    printf("=== AGENDA ===\n1. Adicionar\n2. Remover\n3. Buscar\n4. Listar\n5. Sair\nOpcao: ");
    
    scanf("%d", (int*)(pBuffer + DADOS_OFFSET));
    getchar();

    switch (*(int*)(pBuffer + DADOS_OFFSET)) {
        case 1: return adicionar(pBuffer);
        case 2: return remover(pBuffer);
        case 3: return buscar(pBuffer);
        case 4: return listar(pBuffer);
        case 5:
            free(pBuffer);
            exit(0);
        default:
            printf("Opcao invalida!");
            getchar();
            return pBuffer;
    }
}

void* adicionar(void* pBuffer) {
    printf("\nNome: ");
    fgets(pBuffer + DADOS_OFFSET, NOME_MAX, stdin);
    ((char*)pBuffer + DADOS_OFFSET)[strcspn(pBuffer + DADOS_OFFSET, "\n")] = '\0';

    printf("Idade: ");
    char* idadeStr = pBuffer + DADOS_OFFSET + NOME_MAX;
    fgets(idadeStr, 10, stdin);
    idadeStr[strcspn(idadeStr, "\n")] = '\0';

    size_t* i = pBuffer + TEMP_OFFSET;
    for (*i = 0; ((char*)idadeStr)[*i]; (*i)++)
        if (((char*)idadeStr)[*i] < '0' || ((char*)idadeStr)[*i] > '9') {
            printf("Idade invalida!");
            getchar();
            return pBuffer;
        }

    *(int*)(pBuffer + DADOS_OFFSET + NOME_MAX) = atoi(idadeStr);

    printf("Email: ");
    char* email = pBuffer + DADOS_OFFSET + NOME_MAX + sizeof(int);
    fgets(email, EMAIL_MAX, stdin);
    email[strcspn(email, "\n")] = '\0';

    size_t novoTamanho = *(size_t*)(pBuffer + TAM_BUFFER_OFFSET) + CONTATO_TAM;
    void* novoBuffer = realloc(pBuffer, novoTamanho);
    if (!novoBuffer) return pBuffer;

    size_t offset = novoTamanho - CONTATO_TAM;
    *(size_t*)(novoBuffer + offset) = 0; // Próximo
    *(size_t*)(novoBuffer + offset + sizeof(size_t)) = *(size_t*)(novoBuffer + CAUDA_OFFSET); // Anterior

    memcpy(novoBuffer + offset + 2*sizeof(size_t), novoBuffer + DADOS_OFFSET, NOME_MAX);
    memcpy(novoBuffer + offset + 2*sizeof(size_t) + NOME_MAX, novoBuffer + DADOS_OFFSET + NOME_MAX, sizeof(int));
    memcpy(novoBuffer + offset + 2*sizeof(size_t) + NOME_MAX + sizeof(int), novoBuffer + DADOS_OFFSET + NOME_MAX + sizeof(int), EMAIL_MAX);

    if (*(size_t*)(novoBuffer + CABECA_OFFSET) == 0)
        *(size_t*)(novoBuffer + CABECA_OFFSET) = offset;
    else
        *(size_t*)(novoBuffer + *(size_t*)(novoBuffer + CAUDA_OFFSET)) = offset;

    *(size_t*)(novoBuffer + CAUDA_OFFSET) = offset;
    *(size_t*)(novoBuffer + TAM_BUFFER_OFFSET) = novoTamanho;

    printf("Contato adicionado!");
    getchar();
    return novoBuffer;
}

void* remover(void* pBuffer) {
    if (*(size_t*)(pBuffer + CABECA_OFFSET) == 0) {
        printf("\nLista vazia!");
        getchar();
        return pBuffer;
    }
    printf("\nNome para remover: ");
    fgets(pBuffer + DADOS_OFFSET, NOME_MAX, stdin);
    ((char*)pBuffer + DADOS_OFFSET)[strcspn(pBuffer + DADOS_OFFSET, "\n")] = '\0';

    size_t* atual_ptr = pBuffer + CABECA_OFFSET;
    size_t anterior = 0;

    while (*atual_ptr) {
        char* nome = (char*)(pBuffer + *atual_ptr + 2*sizeof(size_t));
        if (strcmp(nome, pBuffer + DADOS_OFFSET) == 0) {
            size_t proximo = *(size_t*)(pBuffer + *atual_ptr);
            
            if (anterior) {
                *(size_t*)(pBuffer + anterior) = proximo;
            } else {
                *(size_t*)(pBuffer + CABECA_OFFSET) = proximo;
            }

            if (proximo) {
                *(size_t*)(pBuffer + proximo + sizeof(size_t)) = anterior;
            } else {
                *(size_t*)(pBuffer + CAUDA_OFFSET) = anterior;
            }

            printf("Contato removido!");
            getchar();
            return pBuffer;
        }
        anterior = *atual_ptr;
        atual_ptr = pBuffer + *atual_ptr;
    }

    printf("Contato nao encontrado!");
    getchar();
    return pBuffer;
}

void* buscar(void* pBuffer) {
    if (*(size_t*)(pBuffer + CABECA_OFFSET) == 0) {
        printf("\nLista vazia!");
        getchar();
        return pBuffer;
    }
    printf("\nNome para buscar: ");
    fgets(pBuffer + DADOS_OFFSET, NOME_MAX, stdin);
    ((char*)pBuffer + DADOS_OFFSET)[strcspn(pBuffer + DADOS_OFFSET, "\n")] = '\0';

    size_t* atual_ptr = pBuffer + CABECA_OFFSET;
    int encontrado = 0;

    while (*atual_ptr) {
        char* nome = (char*)(pBuffer + *atual_ptr + 2*sizeof(size_t));
        if (strstr(nome, pBuffer + DADOS_OFFSET)) {
            printf("\nNome: %s\nIdade: %d\nEmail: %s\n", nome,
                   *(int*)(pBuffer + *atual_ptr + 2*sizeof(size_t) + NOME_MAX),
                   (char*)(pBuffer + *atual_ptr + 2*sizeof(size_t) + NOME_MAX + sizeof(int)));
            encontrado = 1;
        }
        atual_ptr = pBuffer + *atual_ptr;
    }

    if (!encontrado) printf("Nenhum contato encontrado!");
    getchar();
    return pBuffer;
}

void* listar(void* pBuffer) {
    if (*(size_t*)(pBuffer + CABECA_OFFSET) == 0) {
        printf("\nLista vazia!");
        getchar();
        return pBuffer;
    }
    size_t* atual_ptr = pBuffer + CABECA_OFFSET;

    while (*atual_ptr) {
        printf("\nNome: %s\nIdade: %d\nEmail: %s\n",
               (char*)(pBuffer + *atual_ptr + 2*sizeof(size_t)),
               *(int*)(pBuffer + *atual_ptr + 2*sizeof(size_t) + NOME_MAX),
               (char*)(pBuffer + *atual_ptr + 2*sizeof(size_t) + NOME_MAX + sizeof(int)));
        atual_ptr = pBuffer + *atual_ptr;
    }

    getchar();
    return pBuffer;
}
