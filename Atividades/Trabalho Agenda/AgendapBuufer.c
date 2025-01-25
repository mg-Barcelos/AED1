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

void* remover (void* pBuffer){
    printf("\nNome para remover: ");
    scanf(" %[^\n]", (char*)(pBuffer + 3 * sizeof(void*)));
    getchar();

    void* atual = *(void**)pBuffer; // Ponteiro para o head da lista

    while (atual != NULL && strcmp((char*)(atual + 2 * sizeof(void*)), (char*)(pBuffer + 3 * sizeof(void*))) != 0) {
        atual = *(void**)atual; // Avança para o próximo nó
    }

    if (atual == NULL) { // Se não encontrado
        printf("\nContato nao encontrado!\n");
        getchar();
        return pBuffer;
    }
    if (atual == *(void**)pBuffer) {
        *(void**)pBuffer = *(void**)atual;
        if (*(void**)atual != NULL) {
            *(void**)(*(void**)atual + sizeof(void*)) = NULL; 
        } else {
            *(void**)(pBuffer + sizeof(void*)) = NULL; 
        }
    } 
    // Caso especial: Remover o último nó
    else if (atual == *(void**)(pBuffer + sizeof(void*))) {
        *(void**)(*(void**)(atual + sizeof(void*)) + sizeof(void*)) = NULL; // Tail fica vazio
        *(void**)(pBuffer + sizeof(void*)) = *(void**)(atual + sizeof(void*)); // Atualiza tail
    } 
    // Caso geral: Remover no meio
    else {
        *(void**)(*(void**)(atual + sizeof(void*)) + sizeof(void*)) = *(void**)atual;
        *(void**)(*(void**)atual + sizeof(void*)) = *(void**)(atual + sizeof(void*));
    }

    free(atual); // Libera a memória do nó
    printf("\nContato removido!\n");
    getchar();
    return pBuffer;
}

void* buscar (void* pBuffer){
    printf("\nNome para Buscar: ");
    scanf(" %[^\n]", (char*)(pBuffer + 3 * sizeof(void*)));
    getchar();

    void* atual = *(void**)pBuffer; // Ponteiro aponta pra head da lista

    while(atual != NULL) {
        if (strstr((char*)(atual + 2 * sizeof(void*)), (char*)(pBuffer + 3 * sizeof(void*))) != NULL) {
            printf("\nContato encontrado:\n");
            printf("\nNome %s\n", (char*)(atual + 2 * sizeof(void*)));
            printf("\nIdade %d\n", *(int*)(atual + 2 * sizeof(void*)+40));
            printf("\nNome %s\n", (char*)(atual + 2 * sizeof(void*)+44));
            getchar();
            return pBuffer;
        }
        atual = *(void**)atual;
    }
    printf("\nContato encontrado:\n");
    getchar();
    return pBuffer;
}

void* listar(void* pBuffer){
    void* atual = *(void**)pBuffer;

    if(atual == NULL){
        printf("\n A LISTA ESTA VAZIA\n");
        getchar();
        return pBuffer;
    }

    int count=0;
    void* temp = atual;
    while (temp != NULL){
        count++;
        temp = *(void**)temp;
    }
    void** nos = malloc(count * sizeof(void*));
    temp = atual;
    for(int i =0;i<count;i++){
        nos[i] = temp;
        temp = *(void**)temp;//
    }
// Ordenar os ponteiros para os nós usando bubble sort com base nos nomes
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            char* nome1 = (char*)(nos[j] + 2 * sizeof(void*));
            char* nome2 = (char*)(nos[j + 1] + 2 * sizeof(void*));
            if (strcmp(nome1, nome2) > 0) {
                void* tempNode = nos[j];
                nos[j] = nos[j + 1];
                nos[j + 1] = tempNode;
            }
        }
    }
    // Exibir os contatos em ordem alfabética
    printf("\nLista de contatos:\n");
    for (int i = 0; i < count; i++) {
        printf("Nome: %s\n", (char*)(nos[i] + 2 * sizeof(void*)));
        printf("Idade: %d\n", *(int*)(nos[i] + 2 * sizeof(void*) + 40));
        printf("Email: %s\n", (char*)(nos[i] + 2 * sizeof(void*) + 44));
        printf("----------------\n");
    }

    // Liberar a lista temporária
    free(nos);

    getchar();
    return pBuffer;
}

void liberar_lista(void* pBuffer){
    void* atual = *(void**)pBuffer;

    while (atual != NULL){
        void* temp = atual;
        atual = *(void**)atual;
        free(temp);
    }
}

