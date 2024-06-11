#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
int main(int argc, char** argv) {
    int segredo, chute;
    int tentativas = 1;
    srand(time(NULL));
    segredo = rand()%100;
    cout <<"\n\t\tTente adivinhar o número!\n";
    cout <<"\n\tChute um número de 1 a 100: ";
            cin >> chute;
     while(chute < 1 || chute > 100){
        cout <<"\n\tO chute deve ser de 1 a 100, digite novamente: ";
        cin >> chute;
    }
    while(chute != segredo){
        if (chute < segredo){
            cout <<"\n\tERROU!!\n";
            cout <<"\tO segredo é maior que "<<chute<<"! Tente novamente:  ";
        }else{
            cout <<"\n\tERROU!!\n";
            cout <<"\tO segredo é menor que "<<chute<<"! Tente novamente: ";
        };
        cin >> chute;
         while(chute < 1 || chute > 100){
        cout <<"\tO chute deve ser de 1 a 100, digite novamente: ";
        cin >> chute;
    }
        tentativas= tentativas + 1;
    }       
        cout << "\n\tPARABÉNS!!\n" ;
        cout << "\tVocê descobriu o segredo com "<<tentativas<<" tentativas!!"<<endl;
          
    return 0;
}