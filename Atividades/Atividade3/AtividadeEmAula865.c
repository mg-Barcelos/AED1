//Miguel Pereira Barcelos
 /* Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 struct Resultado {
    struct TreeNode *node;
    int profundo;
};

//função ajuda a fazer calculo da profundidade
struct Resultado ajuda(struct TreeNode* root) {
    if (root == NULL) {
        return (struct Resultado){NULL, 0}; //no é nulo
    }


    struct Resultado left = ajuda(root->left);
    struct Resultado right = ajuda(root->right);


    struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    }