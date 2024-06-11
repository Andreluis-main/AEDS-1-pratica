/* 
 * File:   main.cpp
 * Author: André Luís
 *
 * Created on 11 de abril de 2024, 12:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int escolha; //variavel que guarda oq o usuario escolheu 
    int vetor[1000];
    
    // Seed para a função rand() usando o tempo atual
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        int aleatorio = rand();
        int numero_certo = (aleatorio % 101) + 100;
        vetor[i] = numero_certo;
    }
    
    do { //abre estrutura de repetição 
        printf("Escolha uma opcao:\n"); // abre as opções pra escolhar 
        printf("1 - Informe se um valor existe no vetor, e qual sua posição.\n"); //op1 
        printf("2 - Conte quantas vezes um valor aparece no vetor, e quais as suas posições.\n"); //op 2
        printf("3 - Conte quantas vezes os valores de um intervalo aparecem no vetor.\n"); //op3
        scanf("%d", &escolha); //entra valor de escolha 

        switch (escolha) {
            case 1: {
                int valor;
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &valor);
                int encontrado = 0;
                for (int i = 0; i < 1000; i++) {
                    if (vetor[i] == valor) {
                        printf("O valor %d foi encontrado na posicao %d.\n", valor, i);
                        encontrado = 1; //1 pq é verdadeiro 
                        break;
                    }
                }
                if (!encontrado) {
                    printf("O valor %d nao foi encontrado no vetor.\n", valor); //caso não ternha gerado o valor
                }
                break;
            }
            case 2: {
                int valor_contagem;
                printf("Digite o valor que deseja contar: ");
                scanf("%d", &valor_contagem);
                int ocorrencias = 0;
                printf("O valor %d aparece nas seguintes posicoes: ", valor_contagem);
                for (int i = 0; i < 1000; i++) {
                    if (vetor[i] == valor_contagem) {
                        printf("%d ", i);
                        ocorrencias++;
                    }
                }
                printf("\nTotal de ocorrencias do valor %d: %d\n", valor_contagem, ocorrencias);
                break;
            }
            case 3: {
                int inicio_intervalo, fim_intervalo;
                printf("Digite o inicio do intervalo: ");
                scanf("%d", &inicio_intervalo);
                printf("Digite o fim do intervalo: ");
                scanf("%d", &fim_intervalo);
                int ocorrencias_intervalo = 0;
                printf("Valores no intervalo [%d, %d] encontrados nas posicoes: ", inicio_intervalo, fim_intervalo);
                for (int i = 0; i < 1000; i++) {
                    if (vetor[i] >= inicio_intervalo && vetor[i] <= fim_intervalo) {
                        printf("%d ", i);
                        ocorrencias_intervalo++;
                    }
                }
                printf("\nTotal de ocorrencias no intervalo [%d, %d]: %d\n", inicio_intervalo, fim_intervalo, ocorrencias_intervalo);
                break;
            }
            default:
                printf("Opcao invalida. Escolha uma das 3 alternativas.\n");
        }
    } while (escolha < 1 || escolha > 3);

    return 0;
}



