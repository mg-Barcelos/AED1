#include <stdio.h>

void Converter_C_pra_F(){
    float c;
    printf("Diigite a temperatura em Celsius para converter para Fahrenheit");
    scanf("%f",&c);
    float soma= c*(9.0/5.0)+32.0;
    printf("a temperatura em fahrenheit e:%f\n",soma);
}
void Converter_F_pra_C(){
    float f;
    printf("Diigite a temperatura em Celsius para converter para Fahrenheit");
    scanf("%f",&f);
    float soma= 5.0*(f-32.0)/9.0;
    printf("a temperatura em fahrenheit e:%f\n",soma);
}
void Converter_K_pra_C(){
    float f;
    printf("Diigite a temperatura em kevin para converter para celsius");
    scanf("%f",&f);
    float soma= f-273.15;
    printf("a temperatura em fahrenheit e:%f\n",soma);
}
void Converter_C_pra_K(){
    float f;
    printf("Digite a temperatura em Celsius para converter para kevin");
    scanf("%f",&f);
    float soma= f+273.15;
    printf("a temperatura em fahrenheit e:%f\n",soma);
}
void velocidadeKM_pra_MS(){
    int m;
    printf("Digite a Velocidade em KM que ira converte para ms:");
    scanf("%d",&m);
    int soma=m/3.6;
    printf("km para ms %d",soma);

}
void metrospors_para_km(){
    int m;
    printf("Digite a Velocidade em metros por segundo que ira converte para km:");
    scanf("%d",&m);
    int soma=m*3.6;
    printf("metros por s para km %d",soma);

}
void quilometros_para_milhas(){
    int m;
    printf("quilometro para km");
    scanf("%d",&m);
    int soma=m/1.61;
    printf("quilometros para milhas %d",soma);
}
void radianos_para_graus(){
    float r;
    float pi=3.14;
    printf("Digite os radianos que queres coverter para graus:");
    scanf("%f",&r);
    float soma=r*pi/180;
    printf("resultado da conversao %f",soma);
}
void metrosquadradosparahectres(){
    int h;
    printf("Digite em metros para converte em hectares");
    scanf("%d",&h);
    int soma=h*0.247000;
    printf("metros para hectares:%d",soma);
}

int main(){
    int p;

    do{
        printf("\nMenu:\n"); 
        printf("1. Celsius para Fahrenheit:\n"); 
        printf("2. Fahrenheit para Celsius\n");
        printf("3. kelvin para celsiius:\n"); 
        printf("4. Celsius para kelvin\n"); 
        printf("5. velocidadekm para ms\n"); 
        printf("6. metros pro segundo para km\n"); 
        printf("7. quilometros por milha\n"); 
        printf("8. radianos_para_graus\n"); 
        printf("9. metros quadrados para hectres \n"); 
        scanf("%d", &p);
        
        switch(p){
            case 1:
            Converter_C_pra_F();
            break;
            case 2:
            Converter_F_pra_C();
            break;
            case 3:
            Converter_K_pra_C();
            break;
            case 4:
            Converter_C_pra_K();
            break;
            case 5:
            velocidadeKM_pra_MS();
            break;
            case 6:
            metrospors_para_km();
            break;
            case 7:
            quilometros_para_milhas();
            break;
            case 8:
            radianos_para_graus();
            break;
            case 9:
            metrosquadradosparahectres();
            break;
            default:
            printf("opcao invalida");
            break;
        }
    }while (p!=10);
    return 0;

}