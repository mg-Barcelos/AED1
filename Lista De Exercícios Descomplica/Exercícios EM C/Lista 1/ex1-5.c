//ex 1 ao 5
#include <stdio.h>

void Numero_inteiro_imprimir(){
    int x;
    printf("Digite um numero para imprimir:");
    scanf("%d",&x);
    printf("Seu Numero:%d\n",x);
}

void Imprimira_Numero_real(){
    float x;
    printf("Digite um numero real:");
    scanf("%f",&x);
    printf("Seu Numero:%f\n",x);
}

void Soma_de_tres_inteiros(){
    int x,y,z;
    printf("Digite tres numeros para serem somados:");
    scanf("%d%d%d",&x,&y,&z);
    int soma = x+y+z;
    printf("Resultado:%d\n",soma);
}

void Quadrado_do_numero(){
    float x;
    printf("Digite o numero:");
    scanf("%f",&x);
    float quadrado=x*x;
    printf("numero em quadrado:%f\n",quadrado);
}

void Imprima_quinta_parte(){
    float x;
    printf("Digite o numero:");
    scanf("%f",&x);
    float som=x/5;
    printf("quinta parte do numero enumero:%f\n",som);
}

int main(){
    int p;

    do{
        printf("\nMenu:\n"); 
        printf("1. imprimir numero inteiro\n"); 
        printf("2. imprimir numero real\n"); 
        printf("3. soma de 3 numeros\n"); 
        printf("4. quadrado de um numero\n"); 
        printf("5. imprimir quinta parte\n"); 
        printf("Escolha uma opcao: "); 
        scanf("%d", &p);
        
        switch(p){
            case 1:
            Numero_inteiro_imprimir();
            break;
            case 2:
            Imprimira_Numero_real();
            break;
            case 3:
            Soma_de_tres_inteiros();
            break;
            case 4:
            Quadrado_do_numero();
            break;
            case 5:
            Imprima_quinta_parte();
            break;
            default:
            printf("opcao invalida");
            break;
        }
    }while (p!=5);
    return 0;

}