/* 
 * File:   main.cpp
 * Author: André Luís
 *
 * Created on 5 de abril de 2024, 16:21
 */

/*
 *Calculadora de itens geometricos com base na area e volume.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

int PI = 3.141592;
using namespace std;

// Função para cálculo de área de diferentes formas 2D
float calcular_area(const string& forma, double parametro1, double parametro2 = 0) {
    if (forma == "quadrado")
        return parametro1 * parametro1;
    else if (forma == "retangulo")
        return parametro1 * parametro2;
    else if (forma == "triangulo")
        return (parametro1 * parametro2) / 2;
    else if (forma == "circulo")
        return PI * parametro1 * parametro1;
    else
        return 0.0;
}

// Função para cálculo de volume de diferentes formas 3D
float calcular_volume(const string& forma, double parametro1, double parametro2 = 0, double parametro3 = 0) {
    if (forma == "cubo")
        return parametro1 * parametro1 * parametro1;
    else if (forma == "paralelepipedo")
        return parametro1 * parametro2 * parametro3;
    else if (forma == "cilindro")
        return PI * parametro1 * parametro1 * parametro2;
    else if (forma == "cone")
        return (PI * parametro1 * parametro1 * parametro2) / 3;
    else if (forma == "esfera")
        return (4.0 / 3.0) * PI * pow(parametro1, 3);
    else
        return 0.0;
}

int main() {
    float area_total = 0.0;
    float volume_total = 0.0;
    string linha;

    ifstream arquivo("cenegrafia.txt");

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            string forma;
            float parametro1, parametro2, parametro3;
            
            istringstream iss(linha);
            iss >> forma >> parametro1 >> parametro2 >> parametro3;

            if (forma == "fim")
                break;
            
            float area = calcular_area(forma, parametro1, parametro2);
            float volume = calcular_volume(forma, parametro1, parametro2, parametro3);

            cout << "Item: " << forma << endl;
            cout << "Área: " << area << endl;
            cout << "Volume: " << volume << endl;
            cout << endl;

            area_total += area;
            volume_total += volume;
        }

        arquivo.close();

        ofstream saida("cenegrafia.txt");
        saida << "Área Total: " << area_total << endl;
        saida << "Volume Total: " << volume_total << endl;
        saida.close();

        cout << "Área Total: " << area_total << endl;
        cout << "Volume Total: " << volume_total << endl;
    } else {
        cout << "Não foi possível abrir o arquivo de entrada." << endl;
    }

    return 0;
}






