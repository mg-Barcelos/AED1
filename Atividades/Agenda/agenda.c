#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* menu(void* pBuffer);
void* criar_no(void* pBuffer);
void* adicionar(void* pBuffer);
void* remover(void* pBuffer);
void* buscar(void* pBuffer);
void* listar(void* pBuffer);
void liberar_lista(void* pBuffer);

int main(){
  void* pBuffer = malloc (3* sizeof(void*) + 80);
  *(void**) pBuffer = NULL;
  *(void**)(pBuffer
  *(void**)
