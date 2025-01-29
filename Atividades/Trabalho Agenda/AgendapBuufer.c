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

    *(int*)(pBuffer + 3 * sizeof(void*) + 80) = 0; // opcao
    *(int*)(pBuffer + 3 * sizeof(void*) + 80  + sizeof(int)) = 0;// count
    *(int*)(pBuffer + 3 * sizeof(void*) + 80 + 2 * sizeof(int)) = 0; //i
    *(int*)(pBuffer + 3 * sizeof(void*) + 80 + 3 * sizeof(int)) = 0; //j
    
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
    
    int* opcaoPtr = (int*)(pBuffer + 3 * sizeof(void*) + 80);// opção pra ferificar o menu
    scanf("%d", opcaoPtr);
    getchar(); 

    switch (*opcaoPtr) {
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
     void* novo_no = malloc(2 * sizeof(void*) + 80);
    // utilizamos aqui pra cria o no temporario 
    *(void**)novo_no = NULL; 
    //aqui o ponteiro começa next do novo no como null (ou seja nao vai apontar pra nenhum outro no no momento)
    *(void**) (novo_no + sizeof (void*) ) = NULL; 
    // mesma coisa vai começa o ponteiro prev do no como null (entao nao vai ter nada antes)
    memcpy(novo_no + 2 * sizeof(void*), pBuffer + 3 * sizeof(void*),80);
    /*aqui vai fazer nada mais que copia os dados que sao (nome,idade,email) do buffer para
    um novo no, os dados comecam a partir do pBuffer + 3 * sizeof(void*) é onde os dados estao armazenados*/
    /*valor 80 é o nuemro de bytes apra ser copiado que sao o tamanho dos dados o valor 80 é assumindo que o nome tenha 39 carectes(40bytes)
    idade nuemro inteiro(4bytes) e email assumindo que tenha 35 caracretes(36bytes)=80*/
    return novo_no;
}

//funçao para adicionar uma pessoa na lista
void* adicionar(void* pBuffer){
    printf("\nNome:");
    scanf(" %[^\n]",(char*)(pBuffer + 3 * sizeof(void*)));
    printf("\nIdade:");
    char idadeInput[10];
    //vai le a entrda do nuemro que é a idade como string
    scanf(" %[^\n]", idadeInput);
    getchar();

    // Verifica se a entrada para idade contém apenas números
    for (int i = 0; idadeInput[i] != '\0'; i++) {
        if (idadeInput[i] < '0' || idadeInput[i] > '9') {
            //caso nao tenha numero exibi a mensagem
            printf("\nErro: Apenas numeros sao permitidos para a idade.\n");
            getchar();
            return pBuffer;
        }
    }

    // funçao para coverter string para int
   int* idadePtr = (int*)(pBuffer + 3 * sizeof(void*) + 40);
    *idadePtr = 0;
    for (int i = 0; idadeInput[i] != '\0'; i++) {
        *idadePtr = *idadePtr * 10 + (idadeInput[i] - '0');
    }
    //armazena a idade no buffer e deslocaa posiçao certa
    printf("\nEmail:");
    scanf(" %[^\n]",(char*)(pBuffer + 3 * sizeof(void*)+44));
    getchar();

    void* novo_no = criar_no(pBuffer);
    //vai criar um novo com os dados inseridos
    void** head = (void**)(pBuffer);
    //vai obter o primeiro no da lista
    void** tail = (void**)(pBuffer + sizeof(void*));
    //e aqui o ultimo no da lista
    
    if (*head == NULL) {
        *head = novo_no;
        *tail = novo_no;
    } else {
        *(void**)novo_no = NULL;
        *(void**)(novo_no + sizeof(void*)) = *tail;
        *(void**)*tail = novo_no;
        *tail = novo_no;
    }
    printf("\nContato adicionado!\n");
    getchar();
    return pBuffer;
}
    
    printf("\nContato adicionado!\n");
    getchar();
    return pBuffer;
}

void* remover (void* pBuffer){
    void** head = (void**)(pBuffer);
    if (*head == NULL) {
    printf("\nA lista esta vazia! Nenhum contato para remover.\n");
    getchar();
    return pBuffer;
}
    printf("\nNome para remover: ");
    scanf(" %[^\n]", (char*)(pBuffer + 3 * sizeof(void*)));
    getchar();

    void* atual = *head
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

    void* prev = *(void**)(atual + sizeof(void*));
    void* next = *(void**)atual;

if (atual == *head && atual == tail) {
        *head = NULL;
        tail = NULL;
    }
    else if (atual == *head) {
        *head = next;
        *(void**)(next + sizeof(void*)) = NULL;
    }
    // Case 3:remove o ultimo no
    else if (atual == tail) {
        *(void**)prev = NULL;
        tail = prev;
    }
    // Case 4: remover o no o meio
   else {
        *(void**)prev = next;
        *(void**)(next + sizeof(void*)) = prev;
    }

    free(atual); // Libera a memória do nó
    printf("\nContato removido!\n");
    getchar();
    return pBuffer;
}

void* buscar (void* pBuffer){
    void* head = *(void**)pBuffer
    if (head == NULL) {
    printf("\nA lista esta vazia! Nenhum contato para buscar.\n");
    getchar();
    return pBuffer;
    //funçao verifica se a lista esta vazia se tiver exibi a mensagem
}
    printf("\nNome para Buscar: ");
    scanf(" %[^\n]", (char*)(pBuffer + 3 * sizeof(void*)));
    getchar();
    //funçao pro usuario digigtar o nome

    void* atual = head; // Ponteiro atual vai ser começado apontado para o primeiro da lista o (head)
    
    while(atual != NULL) {
        if (strstr((char*)(atual + 2 * sizeof(void*)), (char*)(pBuffer + 3 * sizeof(void*))) != NULL) {
            printf("\nContato encontrado:\n");
            printf("\nNome %s\n", (char*)(atual + 2 * sizeof(void*)));
            printf("\nIdade %d\n", *(int*)(atual + 2 * sizeof(void*)+40));
            printf("\nNome %s\n", (char*)(atual + 2 * sizeof(void*)+44));
            getchar();
            return pBuffer;
            /*a qui o while entra em laço de repetiçao ele vai percorrera lista apatir do head 
            vai ir ate encontra o no com o nome que a pessoa quer procurar*/
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
        printf("\n lista vazia\n");
        getchar();
        return pBuffer;
        //ponteiro aula aponta pro head da lista,a lista esta vazia entao retorna
    }
/*abaixo o ponteiro temp é usado pra pecorrer alista iniciado pelo head o count o contator para cada no visitado
quanto o temp chega no final da lista ele se tornal null, o count tem o nuemro total de nos da lista*/
    int* count = (int*)(pBuffer + 3 * sizeof(void*) + 80 + sizeof(int));
    *count = 0;
    void* temp = atual;
    while (temp != NULL){
        (*count)++;
        temp = *(void**)temp;
    }
    void** nos = malloc(*count * sizeof(void*));//array dinamica chama nos para armazenar todo os nos da lista
    temp = atual;
    for (int* i = (int*)(pBuffer + 3 * sizeof(void*) + 80 + 2 * sizeof(int)); 
         *i < *count; (*i)++) {
        nos[*i] = temp;
        temp = *(void**)temp;
        /*aqui o ponteiro temp é reinicializado para o head,entra no for o pont temp é armazenado no nos[i] do array
        e por fim o temp é atualizado para o proximo no acessado por *(void**)temp.*/
    }
    *(int*)(pBuffer + 3 * sizeof(void*) + 80 + 2 * sizeof(int)) = 0;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            char* nome1 = (char*)(nos[j] + 2 * sizeof(void*));
            char* nome2 = (char*)(nos[j + 1] + 2 * sizeof(void*));
            if (strcmp(nome1, nome2) > 0) {
                void* tempNode = nos[j];//o ponteiro atual é armazenado tempoaralmente em tempNode vai sevir pra nao mexe no valor atual
                nos[j] = nos[j + 1];// o no é movimo pra essa posiçao
                nos[j + 1] = tempNode;
                //bem a ordenaçao funciona da seguinte maneira ordem alfabetica baseada no valor ASCII
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

    free(nos); //os nos é liberado para nao ter vazamento de memoria

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

