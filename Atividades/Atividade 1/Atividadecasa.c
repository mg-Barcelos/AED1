#include <stdio.h>
#include <stdbool.h>

bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    int contador = 0;
    for (int i = 0; i < flowerbedSize; i++) {
        // Verifica se o espaço atual está vazio e se os vizinhos também estão vazios
        if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) &&
            (i == flowerbedSize - 1 || flowerbed[i + 1] == 0)) {
            flowerbed[i] = 1; // Plante uma flor aqui
            contador++;
            // Se já plantamos o número necessário de flores, retornamos true
            if (contador >= n) {
                return true;
            }
        }
    }
    return contador >= n;
}

int main() {
    // Exemplo de teste
    int flowerbed[] = {1, 0, 1, 0, 0, 0, 0, 0, 1};
    int flowerbedSize = sizeof(flowerbed) / sizeof(flowerbed[0]);
    int n = 2; // Número de flores que queremos plantar

    if (canPlaceFlowers(flowerbed, flowerbedSize, n)) {
        printf("e possivel plantar %d flores no flowerbed.\n", n);
    } else {
        printf("Nao e possivel plantar %d flores no flowerbed.\n", n);
    }

    /* Outro exemplo de teste
    n = 2; // Tentando plantar 2 flores
    if (canPlaceFlowers(flowerbed, flowerbedSize, n)) {
        printf("e posssvel plantar %d flores no flowerbed.\n", n);
    } else {
        printf("Naoo e possivel plantar %d flores no flowerbed.\n", n);
    }*/

    return 0;
}
