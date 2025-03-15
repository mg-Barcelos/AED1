//Miguel Barcelos
#include <stdio.h>
#include <stdlib.h>

// Função de comparação para a função qqsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    // vai  criar uma array que armazenar os trabalhos que seria as (dificuldades e lucros)
    int jobs[difficultySize][2];

    // Preencher array com dificuldades e lucrossssss
    for (int i = 0; i < difficultySize; i++) {
        jobs[i][0] = difficulty[i]; // dificuldade do trabalho
        jobs[i][1] = profit[i];     // Lucro de trabalho
    }

    // vai Ordenar os trabalhos com base na dificuldade com o quicksort
    qsort(jobs, difficultySize, sizeof(jobs[0]), compare);

    long totalProfit = 0; // aaqui uma variável para acumular o lucro total

    for (int i = 0; i < workerSize; i++) {
        int maxProfit = 0; 
        
        for (int j = 0; j < difficultySize; j++) {
            if (worker[i] >= jobs[j][0]) {
                if (jobs[j][1] > maxProfit) {
                    maxProfit = jobs[j][1]; // atualiza o lucro máximo
                }
            } else {
                break; // se a dificuldade do trabalho for muita pra habilidade do trabalhador,ele vai sair do loop
            }
        }
        
        // adicionar o maior lucro encontrado para este trabalhador ao lucro total
        totalProfit += maxProfit; 
    }

    return totalProfit; // retornar o lucro maaximo
}

// funçao para testes
int main() {
    int difficulty[] = {2, 4, 6, 8, 10}; // dificuldades trabalho
    int profit[] = {10, 20, 30, 40, 50}; // lucros correspondente
    int worker[] = {4, 5, 6, 7}; // habilidades do trabalhador

    // exibir a dificuldades e lucro para referência
    printf("Dificuldades: ");
    for (int i = 0; i < sizeof(difficulty) / sizeof(difficulty[0]); i++) {
        printf("%d ", difficulty[i]);
    }
    printf("\n");

    printf("Lucros: ");
    for (int i = 0; i < sizeof(profit) / sizeof(profit[0]); i++) {
        printf("%d ", profit[i]);
    }
    printf("\n");

    // vai hamar a função maxProfitAssignment e armazenar o resultado
    int result = maxProfitAssignment(difficulty, sizeof(difficulty) / sizeof(difficulty[0]),profit, sizeof(profit) / sizeof(profit[0]),worker, sizeof(worker) / sizeof(worker[0]));

    // Exibir o resultado total
    printf("Lucro Total Máximo: %d\n", result);

    return 0;
}