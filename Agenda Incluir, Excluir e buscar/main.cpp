/*
Agenda funcional para adiconar, excluir e buscar contatos 
autor: André Luís da Silva Souza 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Amigo {
    string nome;
    string celular;
    string cidade;
    string email;
    bool valido;
};

int main() {
    Amigo amigos[100];
    int tamanho = 0;
    string nomeArquivo = "agenda.txt";

    ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        while (arquivo >> amigos[tamanho].nome >> amigos[tamanho].celular >> amigos[tamanho].cidade >> amigos[tamanho].email) {
            amigos[tamanho].valido = true;
            tamanho++;
            if (tamanho >= 100) {
                break;
            }
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo de dados dos amigos." << endl;
        return 1;
    }

    ofstream arquivo_saida;
    int opcao;
    int i;

    do {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Incluir contato" << endl;
        cout << "2. Excluir contato" << endl;
        cout << "3. Buscar contato" << endl;
        cout << "4. Sair" << endl;
        cin >> opcao;

        string nome;
        switch(opcao) {
            case 1:
                if (tamanho >= 100) {
                    cout << "A agenda está cheia." << endl;
                } else {
                    cout << "Nome: ";
                    cin >> amigos[tamanho].nome;
                    cout << "Celular: ";
                    cin >> amigos[tamanho].celular;
                    cout << "Cidade: ";
                    cin >> amigos[tamanho].cidade;
                    cout << "Email: ";
                    cin >> amigos[tamanho].email;
                    amigos[tamanho].valido = true;
                    tamanho++;
                    cout << "Contato incluído com sucesso." << endl;
                }
                break;
            case 2:
                cout << "Digite o nome do contato a ser excluído: ";
                cin >> nome;
                for (i = 0; i < tamanho; i++) { // Movendo 'i' para fora do loop
                    if (amigos[i].valido && amigos[i].nome == nome) {
                        amigos[i].valido = false;
                        cout << "Contato excluído com sucesso." << endl;
                        break;
                    }
                }
                if (i == tamanho) {
                    cout << "Contato não encontrado." << endl;
                }
                break;
            case 3:
                cout << "Digite o nome do contato a ser buscado: ";
                cin >> nome;
                for (i = 0; i < tamanho; i++) { // Movendo 'i' para fora do loop
                    if (amigos[i].valido && amigos[i].nome == nome) {
                        cout << "Contato encontrado:" << endl;
                        cout << "Nome: " << amigos[i].nome << endl;
                        cout << "Celular: " << amigos[i].celular << endl;
                        cout << "Cidade: " << amigos[i].cidade << endl;
                        cout << "Email: " << amigos[i].email << endl;
                        break;
                    }
                }
                if (i == tamanho) {
                    cout << "Contato não encontrado." << endl;
                }
                break;
            case 4:
                arquivo_saida.open(nomeArquivo);
                if (arquivo_saida.is_open()) {
                    for (i = 0; i < tamanho; i++) { // Movendo 'i' para fora do loop
                        if (amigos[i].valido) {
                            arquivo_saida << amigos[i].nome << " "
                                    << amigos[i].celular << " "
                                    << amigos[i].cidade << " "
                                    << amigos[i].email << endl;
                        }
                    }
                    arquivo_saida.close();
                    cout << "Dados salvos com sucesso." << endl;
                } else {
                    cout << "Erro ao abrir o arquivo para salvar os dados." << endl;
                }
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while(opcao != 4);

    return 0;
}
