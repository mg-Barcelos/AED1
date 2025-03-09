#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Função para criar um novo nó
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

/**
 * Função recursiva para encontrar a menor subárvore que contém todos os nós mais profundos.
 */
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    // Função auxiliar que retorna a profundidade e o nó da menor subárvore com todos os nós mais profundos.
    struct TreeNode* ajuda(struct TreeNode* node, int* profundo) {
        if (node == NULL) {
            *profundo = 0;
            return NULL;
        }
        int leftprofundo = 0, rightprofundo = 0;
        // Recursão nas subárvores esquerda e direita
        struct TreeNode* leftNode = ajuda(node->left, &leftprofundo);
        struct TreeNode* rightNode = ajuda(node->right, &rightprofundo);
        
        // Se a profundidade esquerda for maior, a subárvore esquerda contém os nós mais profundos
        if (leftprofundo > rightprofundo) {
            *profundo = leftprofundo + 1;
            return leftNode;
        }
        // Se a profundidade direita for maior, a subárvore direita contém os nós mais profundos
        if (leftprofundo < rightprofundo) {
            *profundo = rightprofundo + 1;
            return rightNode;
        }
        // Se as profundidades forem iguais, o nó atual é o menor ancestral comum
        *profundo = leftprofundo + 1;
        return node;
    }
    
    int profundo = 0;
    return ajuda(root, &profundo);
}

int main() {
    // Criação da árvore de teste:
    //         3
    //        / \
    //       5   1
    //      / \ / \
    //     6  2 0  8
    //       / \
    //      7   4
   /* struct TreeNode* root = newNode(3);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(6);
    root->left->right = newNode(2);
    root->right->left = newNode(0);
    root->right->right = newNode(8);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(4);*/

    // Criação da árvore de teste:
    //         3
    //        / \
    //       5   1
    //      / \ / \
    //     6  2 0  8
    //    / \
    //   7   4
    /*struct TreeNode* root = newNode(3);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(6);
    root->left->right = newNode(2);
    root->right->left = newNode(0);
    root->right->right = newNode(8);
    root->left->left->left = newNode(7);
    root->left->left->right = newNode(4);*/

    // Chamada da função e impressão do resultado
    struct TreeNode* subtree = subtreeWithAllDeepest(root);
    printf("O valor do nó raiz da menor subárvore que contém todos os nós mais profundos é: %d\n", subtree->val);
    
    // Liberação da memória (não mostrado para todos os nós por simplicidade)
    free(root->left->right->left);
    free(root->left->right->right);
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
    
    return 0;
}
