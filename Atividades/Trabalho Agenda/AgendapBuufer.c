
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//macro pra facilitar a limpeza do terminal
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void* menu(void* pBuffer);
void* criar_no(void* pBuffer);
void* adicionar(void* pBuffer);
void* remover(void* pBuffer);
void* buscar(void* pBuffer);
void* listar(void* pBuffer);
void liberar_lista(void* pBuffer);

// Função principal
int main() {
    void* pBuffer = malloc(3 * sizeof(void*) + 80); 

    *(void**)pBuffer = NULL; // head
    *(void**)(pBuffer + sizeof(void*)) = NULL; // tail
    *(void**)(pBuffer + 2 * sizeof(void*)) = NULL; // nó temporário

    while (1) {
        pBuffer = menu(pBuffer);
    }

    free(pBuffer);
    return 0;
}

// Exibe o menu e direciona para a funcionalidade selecionada
void* menu(void* pBuffer) {
    system(CLEAR);
    printf("=== AGENDA ===\n");
    printf("1. Adicionar Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Buscar Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Sair\n");
    printf("Opcao: ");
    
    int opcao = 0; // opção temporária para verificar o menu
    scanf("%d", &opcao);
    getchar(); // Consumir newline

    switch (opcao) {
        case 1:
            pBuffer = adicionar(pBuffer); // Adiciona uma nova pessoa
            break;
        case 2:
            pBuffer = remover(pBuffer); // Remove uma pessoa pelo nome
            break;
        case 3:
            pBuffer = buscar(pBuffer); // Busca uma pessoa pelo nome
            break;
        case 4:
            pBuffer = listar(pBuffer); // Lista todas as pessoas
            break;
        case 5:
            liberar_lista(pBuffer);
            free(pBuffer); // Libera o buffer principal
            exit(0);
        default:
            printf("Opcao invalida! Tente novamente.\n");
            getchar();
    }

    return pBuffer;
}
void* criar_no(void* pBuffer){
    *(void**)novo_no = NULL;
    *(void**) (novo_no + sizeof (void*) ) = NULL;
    //copia os dados de entra o nome, idade e o email
    memcpy(novo_no + 2 * sizeof(void*), pBuffer + 3 * sizeof(void*),80);

    return novo_no;
}

//funçao para adicionar uma pessoa na lista
void* adicionar(void* pBuffer){
    printf("\nNome:");
    scanf(" %[^\n]",(char*)(pBuffer + 3 * sizeof(void*)));
    printf("\nIdade:");
    scanf(" %d",(int*)(pBuffer + 3 * sizeof(void*)+40));
    printf("\nEmail:");
    scanf(" %[^\n]",(char*)(pBuffer + 3 * sizeof(void*)+44));
    getchar();

    void* novo_no = criar_no(pBuffer);
    void* head = *(void**)pBuffer;
    void* tail = *(void**)(pBuffer + sizeof(void*));

    if(head==NULL){
    *(void**)pBuffer = novo_no; // Define o novo nó como head
    *(void**)(pBuffer + sizeof(void*)) = novo_no;
    printf("\nContato adicionado!\n");
    getchar();
    return pBuffer;
}
    *(void**)novo_no = NULL; // Next do novo nó aponta para NULL
    *(void**)(novo_no + sizeof(void*)) = tail; // Prev do novo nó aponta para o tail atual
    *(void**)tail = novo_no; // Tail atual aponta para o novo nó
    *(void**)(pBuffer + sizeof(void*)) = novo_no; // Atualiza o tail no buffer principal

    printf("\nContato adicionado!\n");
    getchar();
    return pBuffer;
}

void* adicionar(void* pBuffer){}