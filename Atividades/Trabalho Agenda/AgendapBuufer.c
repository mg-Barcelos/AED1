#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macro que vai limpar a tela e nao deixa acumula monte de texto; o que a pessoa escolher ou fazer depois do menu é apagado e volta printa o menu denovo
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
//funçoes para fazer a manipulçao da lista encadeada
void* menu(void* pBuffer);//funçao vai exibir o menu pra a pessoa escolher
void* criar_no(void* pBuffer);//a funçao cria um no na lista que recebe um ponteiro do buffer de dados que vai ser amarzenado no no
void* adicionar(void* pBuffer);//vai adiciona uma pessoa em um novo no na lista
void* remover(void* pBuffer);//vai remove uma pessoa de um no na lista. ex: ele vai utuilizar um buffer encontrar o no que quer ser removido
void* buscar(void* pBuffer);//vai uma  procurar uma pessoa(no) na lista,vai percorrer na lista que correponde o valor daquele no
void* listar(void* pBuffer);//vai pecorrer toda a lista e vai printa toda as pessoas que foram adicionadas
void liberar_lista(void* pBuffer);//vai libera a memoria a memoria alocada que vai funciona para que nao tenha vazamento na memoria

// função principal que começa o programa 
int main() {
    void* pBuffer = malloc(3 * sizeof(void*) + 80); //80 byts para cada dado de cada no
//3 ponteiros head,tail e um no temporario
    *(void**)pBuffer = NULL; // head começa como null que vai dizer que esta vazia no começo
    *(void**)(pBuffer + sizeof(void*)) = NULL; // o ponteiro tail que vai falar que a lista esta vazia 
    *(void**)(pBuffer + 2 * sizeof(void*)) = NULL; // e o nó temporário que vai usar ele para fazer operaçoes de coloca e remover
    

    while (1) {
        pBuffer = menu(pBuffer);
    }

    free(pBuffer);//ja libera a memoria antes de começa o codigo
    return 0;
}

// exibe o menu pra pessao escolher o que ela quer
void* menu(void* pBuffer) {
    system(CLEAR);
    printf("=== AGENDA ===\n");
    printf("1. Adicionar Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Buscar Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Sair\n");
    printf("Opcao: ");
    
    int opcao = 0; // opção pra ferificar o menu
    scanf("%d", &opcao);
    getchar(); 

    switch (opcao) {
        case 1:
            pBuffer = adicionar(pBuffer); // opçcao pra adiconar uma pessoa
            break;
        case 2:
            pBuffer = remover(pBuffer); // opçcao pra remover uma pessoa
            break;
        case 3:
            pBuffer = buscar(pBuffer); // opçcao pra buscar uma pessoa
            break;
        case 4:
            pBuffer = listar(pBuffer); // opçcao pra listar utodas as pessoas
            break;
        case 5:
            liberar_lista(pBuffer);
            free(pBuffer); // vai liebrar o buffer principal
            exit(0);
        default:
            printf("Opcao invalida! Tente novamente.\n");
            getchar();
    }

    return pBuffer;
}
void* criar_no(void* pBuffer){
     void* novo_no = malloc(2 * sizeof(void*) + 80);// utilizamos aqui pra cria o no temporario 
    *(void**)novo_no = NULL;
    *(void**) (novo_no + sizeof (void*) ) = NULL;
    memcpy(novo_no + 2 * sizeof(void*), pBuffer + 3 * sizeof(void*),80);

    return novo_no;
}

//funçao para adicionar uma pessoa na lista
void* adicionar(void* pBuffer){
    printf("\nNome:");
    scanf(" %[^\n]",(char*)(pBuffer + 3 * sizeof(void*)));
    printf("\nIdade:");
    char idadeInput[10];
    scanf(" %[^\n]", idadeInput);
    getchar();

    // Verifica se a entrada para idade contém apenas números
    for (int i = 0; idadeInput[i] != '\0'; i++) {
        if (idadeInput[i] < '0' || idadeInput[i] > '9') {
            printf("\nErro: Apenas numeros sao permitidos para a idade.\n");
            printf("Pressione Enter para voltar ao menu.\n");
            getchar();
            return pBuffer;
        }
    }

    // Função personalizada para converter string para inteiro
    int idade = 0;
    for (int i = 0; idadeInput[i] != '\0'; i++) {
        idade = idade * 10 + (idadeInput[i] - '0');
    }
    *(int*)(pBuffer + 3 * sizeof(void*) + 40) = idade;
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
    if (*(void**)pBuffer == NULL) {
    printf("\nA lista esta vazia! Nenhum contato para remover.\n");
    getchar();
    return pBuffer;
}
    printf("\nNome para remover: ");
    scanf(" %[^\n]", (char*)(pBuffer + 3 * sizeof(void*)));
    getchar();

    void* atual = *(void**)pBuffer; // Head
    void* tail = *(void**)(pBuffer + sizeof(void*));
    
    while (atual != NULL && strcmp((char*)(atual + 2 * sizeof(void*)), 
           (char*)(pBuffer + 3 * sizeof(void*))) != 0) {
        atual = *(void**)atual;
    }

    if (atual == NULL) { // Se não encontrado
        printf("\nContato nao encontrado!\n");
        getchar();
        return pBuffer;
    }
if (atual == *(void**)pBuffer && atual == tail) {
        *(void**)pBuffer = NULL;  // Head = NULL
        *(void**)(pBuffer + sizeof(void*)) = NULL;  // Tail = NULL
    }
    // Case 2: First node
    else if (atual == *(void**)pBuffer) {
        *(void**)pBuffer = *(void**)atual;  // Head = atual->next
        *(void**)(*(void**)pBuffer + sizeof(void*)) = NULL;  // New head->prev = NULL
    }
    // Case 3: Last node
    else if (atual == tail) {
        void* prev = *(void**)(atual + sizeof(void*));
        *(void**)prev = NULL;  // prev->next = NULL
        *(void**)(pBuffer + sizeof(void*)) = prev;  // tail = prev
    }
    // Case 4: Middle node
    else {
        void* prev = *(void**)(atual + sizeof(void*));
        void* next = *(void**)atual;
        *(void**)prev = next;  // prev->next = next
        *(void**)(next + sizeof(void*)) = prev;  // next->prev = prev
    }

    free(atual); // Libera a memória do nó
    printf("\nContato removido!\n");
    getchar();
    return pBuffer;
}

void* buscar (void* pBuffer){
    if (*(void**)pBuffer == NULL) {
    printf("\nA lista esta vazia! Nenhum contato para buscar.\n");
    getchar();
    return pBuffer;
}
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
        
        if (atual == NULL) { // Se não encontrado
        printf("\nContato nao encontrado!\n");
        getchar();
        return pBuffer;
        }
    }
    printf("\nContato encontrado:\n");
    getchar();
    return pBuffer;
}

void* listar(void* pBuffer){
    void* atual = *(void**)pBuffer;

    if(atual == NULL){
        printf("\n lista vazia\n");
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
// aqui faz uma ordenaçao dos ponteiros para os nos usando um dos "melhores" algoritmos de ordenaçao o bubble sort com base nos nomes para lista em ordem alfabetica
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

