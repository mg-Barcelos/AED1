bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    int contador = 0;
    for (int i = 0; i < flowerbedSize; i++) {
        // vai Verifica se o espaço atual está vazio e se os vizinhos também
        // estão vazios
        if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) &&
            (i == flowerbedSize - 1 || flowerbed[i + 1] == 0)) {
            return flowerbed;}else{
                return flowerbedSize;
            }
    }
    return 0;
}