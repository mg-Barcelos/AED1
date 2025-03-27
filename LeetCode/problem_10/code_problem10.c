// 
// 739. Daily Temperatures

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
     *returnSize = temperaturesSize;
    int* answer = (int*)calloc(temperaturesSize, sizeof(int)); // Inicializa com zeros
    int* stack = (int*)malloc(temperaturesSize * sizeof(int)); // Pilha para armazenar índices
    int top = -1; // Inicializa o topo da pilha
    
    for (int i = 0; i < temperaturesSize; i++) {
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int prevIndex = stack[top--]; // Pop da pilha
            answer[prevIndex] = i - prevIndex; // Calcula a espera
        }
        stack[++top] = i; // Push na pilha
    }
    
    free(stack); // Libera a memória alocada para a pilha
    return answer;
}
