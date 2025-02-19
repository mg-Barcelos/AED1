//Problema 1281 -- Leetcode
int subtractProductAndSum(int n){
    int aux = n;
    int soma = 0;
    int multi = 1;
    while(aux != 0){
        int temp = aux % 10;
        soma += temp;
        multi *= temp;
        aux = aux/10;
    }
return multi - soma;
}
