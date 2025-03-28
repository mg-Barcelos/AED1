//2558

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long long pickGifts(int* gifts, int giftsSize, int k) {
    for (int i; i < k; i++) {

        int Maxgif = 0;
        for (int j = 1; j < giftsSize; j++) {
            if (gifts[j] > gifts[Maxgif]) {
                Maxgif = j;
            }
        }
        gifts[Maxgif] = (int)floor(sqrt(gifts[Maxgif]));
    }

    // Calcular a soma dos presentes restantes
    long long sum = 0;
    for (int i = 0; i < giftsSize; i++) {
        sum += gifts[i];
    }

    return sum;
}

