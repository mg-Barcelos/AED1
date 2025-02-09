typedef struct {
    bool* cadeira;  // Ponteiro para um array de booleanos que representa as cadeiras (reservadas ou não)
    int quantidade; // aqui é a quantindade de assentos (incluindo posição 0 que não é usada)
    int min; // aqui vai  indica o indice da próxima cadeira disponível (mínimo disponível)
} SeatManager;

SeatManager* seatManagerCreate(int n) {
    // aqui aloca memória para um novo objeto SeatManager
    SeatManager* obj = malloc(sizeof(SeatManager));
    // alooca memória para um array de cadeiras e comça com 0 (false) por causa da bool
    obj->cadeira = calloc((n + 1), sizeof(bool));
    // define o total de cadeiras (n + 1 para considerar a indexação a partir de 1)
    obj->quantidade = n + 1;
    // vai inicia o índice da próx cadeira que esta disponivel para 1 (a menor)
    obj->min = 1;
    return obj;
}

int seatManagerReserve(SeatManager* obj) {
    // a intidade 'linha' que criei ira armazena o índice da cadeira que será reservada
    int acento = obj->min;
    // vai marca a cadeira na posição 'acento' como reservada
    (obj->cadeira)[acento] =
        true
        /* quando a cadeira atual min ('min') for menor que a quantidade total
        e a cadeira na posição 'min' estiver reservada (true)*/
        while (obj->min < obj->quantidade && obj->cadeira[obj->min] != false)
        // ira incrementa min para encontrar a próxima cadeira disponível
        obj->min++;
    // vaie rtorna a posição da cadeira
    return acento;
}
void seatManagerUnreserve(SeatManager* obj, int seatNumber) {}

void seatManagerFree(SeatManager* obj) {}
