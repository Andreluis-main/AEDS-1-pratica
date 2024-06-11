#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL) / 2); 

    float alturas[1000]; 
    float soma = 0; 
    float media = 0; 
    float maiorAltura;
    float menorAltura;
    int contadorPessoasMaiores = 0; 

    maiorAltura = menorAltura = alturas[0] = (rand() % 801 + 1500) / 1000.0;

    for (int i = 1; i < 1000; i++) {
        alturas[i] = (rand() % 801 + 1500) / 1000.0; 
        soma += alturas[i]; 

        if (alturas[i] > maiorAltura) {
            maiorAltura = alturas[i]; 
        }

        if (alturas[i] < menorAltura) {
            menorAltura = alturas[i]; 
        }

        if (alturas[i] > 2.0) {
            contadorPessoasMaiores++; 
        }
    }

    media = soma / 1000; 

    cout << "Média das alturas: " << media << " metros" << endl;
    cout << "Maior altura: " << maiorAltura << " metros" << endl;
    cout << "Menor altura: " << menorAltura << " metros" << endl;
    cout << "Porcentagem de pessoas maiores que 2.0 metros: " << (float) contadorPessoasMaiores / 10 << "%" << endl;

    return 0;
}

