/*
 * conhecer e implementar as operações básicas sobre conjuntos de valores.
 */

/* File:   main.cpp
 * Author: André Luís
 *
 * Created on 23 de abril de 2024, 15:42
 */

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    int conjunto1[10] = {5, 4, 2, 5, 3, 2, 4, 8, 2, 9};
    int conjunto2[10] = {7, 1, 12, 10, 9, 2, 8, 1, 2, 7};
    
    int tam1 = 10, tam2 = 10;
    
    cout << "Operações em conjuntos de valores." << endl;
    
    // Remove os valores repetidos
    int novoConjunto1[10], novoConjunto2[10];
    int tamNovo1 = 0, tamNovo2 = 0;

    for (int i = 0; i < tam1; i++) {
        int valor = conjunto1[i];
        int j = 0;
        while (j < tamNovo1 && novoConjunto1[j] != valor) {
            j++;
        }
        if (j == tamNovo1) {
            novoConjunto1[tamNovo1] = valor;
            tamNovo1++;
        }
    }

    for (int i = 0; i < tam2; i++) {
        int valor = conjunto2[i];
        int j = 0;
        while (j < tamNovo2 && novoConjunto2[j] != valor) {
            j++;
        }
        if (j == tamNovo2) {
            novoConjunto2[tamNovo2] = valor;
            tamNovo2++;
        }
    }

    // justa os conjuntos
    int uniao[20];
    int tamUniao = tamNovo1;

    for (int i = 0; i < tamNovo1; i++) {
        uniao[i] = novoConjunto1[i];
    }

    for (int i = 0; i < tamNovo2; i++) {
        int valor = novoConjunto2[i];
        int j = 0;
        while (j < tamNovo1 && novoConjunto1[j] != valor) {
            j++;
        }
        if (j == tamNovo1) {
            uniao[tamUniao] = valor;
            tamUniao++;
        }
    }

    // Interseção dos conjuntos
    int intersecao[10];
    int tamIntersecao = 0;

    for (int i = 0; i < tamNovo1; i++) {
        for (int j = 0; j < tamNovo2; j++) {
            if (novoConjunto1[i] == novoConjunto2[j]) {
                intersecao[tamIntersecao] = novoConjunto1[i];
                tamIntersecao++;
                break;
            }
        }
    }

    //resultados
    cout << "Conjunto 1 sem repetições: ";
    for (int i = 0; i < tamNovo1; i++) {
        cout << novoConjunto1[i] << " ";
    }
    cout << endl;

    cout << "Conjunto 2 sem repetições: ";
    for (int i = 0; i < tamNovo2; i++) {
        cout << novoConjunto2[i] << " ";
    }
    cout << endl;

    cout << "União dos conjuntos: ";
    for (int i = 0; i < tamUniao; i++) {
        cout << uniao[i] << " ";
    }
    cout << endl;

    cout << "Interseção dos conjuntos: ";
    for (int i = 0; i < tamIntersecao; i++) {
        cout << intersecao[i] << " ";
    }
    cout << endl;
    
    return 0;
} 


