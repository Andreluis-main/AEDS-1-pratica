/*
 Banco de Dados de veiculos com as seugintes funções: 
 *inclusão de um novo veículo na base de dados;
 *busca de um veículo pela placa, com opção de exclusão da base de dados;
 *busca de veículos pelo tipo;
 *busca de veículos pelo câmbio;
 *busca de veículos por um faixa de valores;
 *relatório do banco de dados.
 Criado por: André Luís//2024.1.08.002
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
#define tam 100 //dedfine tamanho maximo do banco de dados

using namespace std;

struct Veiculo { 
    string modelo;
    string marca;
    string tipo;
    int ano;
    int km;
    float potencia_do_motor;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    int portas;
    string placa;
    float valor;
    bool valido;
}; //o que compeo a estrutura do veiculo

int main() {
    //variaveis e onde estão sendo usadas
    Veiculo veiculo[tam]; //define
    int qtde = 0; //conta quantos veiculos tem no banco de dados
    string nomeArquivo = "BD_veiculos.txt"; //chamar como 'nomeArquivo'
    int opcao = 0; //opção que o usuário escolher
    string tipo_busca; //case 2
    bool encontrado = false; //case 3
    string cambio_busca; //case 4
    float valor_minimo, valor_maximo; //case 5

    //abre o arquivo e bota ordem na hora de ler e determina o que é cada coisa
    ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
       
        string aux;
        arquivo >> aux;
        qtde = 0;
        while (aux != "fim") {
            veiculo[qtde].modelo = aux;
            arquivo >> veiculo[qtde].marca >> veiculo[qtde].tipo
                    >> veiculo[qtde].ano >> veiculo[qtde].km >> veiculo[qtde].potencia_do_motor
                    >> veiculo[qtde].combustivel >> veiculo[qtde].cambio >> veiculo[qtde].direcao
                    >> veiculo[qtde].cor >> veiculo[qtde].portas >> veiculo[qtde].placa >> veiculo[qtde].valor;
            veiculo[qtde].valido = true;
            qtde++;
            arquivo >> aux;
        }
    } else {
        cout << "Erro ao abrir o Banco de Dados." << endl;
        return 1;
    }
    do { //opções para o usuario escolher
        cout << "Escolha uma opção:" << endl;
        cout << "1. Incluir veiculo" << endl;
        cout << "2. Buscar veículo pela placa e excluir" << endl;
        cout << "3. Buscar veículos pelo tipo" << endl;
        cout << "4. Buscar veículos pelo câmbio" << endl;
        cout << "5. Buscar veículos por uma faixa de valores" << endl;
        cout << "6. Relatório do banco de dados" << endl;
        cout << "7. Sair do Banco de Dados" << endl;
        cin >> opcao;
        switch (opcao) { //o que cada op vai fazer em resposta a opcao
            case 1:
                if (qtde >= tam) {
                    cout << "Banco de Dados cheio" << endl;
                } else {
                    int i;
                    for(i=0 ; veiculo[i].valido && i < qtde; i++){}
                    cout << "Modelo: ";
                    cin >> veiculo[i].modelo;
                    cout << "Marca: ";
                    cin >> veiculo[i].marca;
                    cout << "Tipo: ";
                    cin >> veiculo[i].tipo;
                    cout << "Ano: ";
                    cin >> veiculo[i].ano;
                    cout << "KM: ";
                    cin >> veiculo[i].km;
                    cout << "Potência do motor: ";
                    cin >> veiculo[i].potencia_do_motor;
                    cout << "Combustível: ";
                    cin >> veiculo[i].combustivel;
                    cout << "Câmbio: ";
                    cin >> veiculo[i].cambio;
                    cout << "Direção: ";
                    cin >> veiculo[i].direcao;
                    cout << "Cor do veiculo: ";
                    cin >> veiculo[i].cor;
                    cout << "Número de portas: ";
                    cin >> veiculo[i].portas;
                    cout << "Placa: ";
                    cin >> veiculo[i].placa;
                    cout << "Valor de mercado do veiculo: ";
                    cin >> veiculo[i].valor;
                    veiculo[i].valido = true;
                    if(qtde == i);
                    qtde++;
                    cout << "Veículo incluído com sucesso." << endl;
                }
                break;
            case 2:
                { //abre as strings do case 2
                string placa_busca;
                bool encontrado = false;
                cout << "Digite a placa do veículo que deseja buscar e possivelmente excluir: ";
                cin >> placa_busca;
                for (int i = 0; i < qtde; ++i) {
                    if (veiculo[i].placa == placa_busca) {
                        encontrado = true;
                        cout << "Veículo encontrado:" << endl;
                        cout << "Modelo: " << veiculo[i].modelo << endl;
                        cout << "Marca: " << veiculo[i].marca << endl;
                        cout << "Placa: " << veiculo[i].placa << endl;
                        cout << "Deseja excluir este veículo? (S/N): ";
                        char resposta;
                        cin >> resposta;
                            if (resposta == 'S' || resposta == 's') { //Min. e Mai. em caso do usuario colocar para excluir.
                                veiculo[i].valido = false;
                                cout << "Veículo excluído com sucesso." << endl;
                        } else {
                            cout << "Exclusão cancelada." << endl;
                        } 
                    }
                }//fecha o carro encontrado
                    if (!encontrado) { // se não encontrar
                        cout << "Veículo não encontrado." << endl;
                    }// fecha caso nao encontre veiculo  
                } // fecha
                break;
            case 3:
                { //abre as strings do case 3
                    cout << "Digite o tipo de veículo que deseja buscar (Hatch, SUV, Sedan, Pick-up, Passeio, Van): ";
                    cin >> tipo_busca;
                    // Verifica se o tipo de busca está entre os tipos permitidos
                    if (tipo_busca == "Hatch" || tipo_busca == "SUV" || tipo_busca == "Sedan" ||
                        tipo_busca == "Pick-up" || tipo_busca == "Passeio" || tipo_busca == "Van") {
                        // Procura pelo veículo com o tipo fornecido
                        for (int i = 0; i < qtde; ++i) {
                            string tipo_veiculo = veiculo[i].tipo;
                            if (tipo_veiculo == tipo_busca) {
                                encontrado = true;
                                cout << "Veículo encontrado:" << endl;
                                cout << "Modelo: " << veiculo[i].modelo << endl;
                                cout << "Marca: " << veiculo[i].marca << endl;
                                cout << "Tipo: " << veiculo[i].tipo << endl;
                                cout << "Ano: " << veiculo[i].ano << endl;
                                cout << "KM: " << veiculo[i].km << endl;
                                cout << "Potência do motor: " << veiculo[i].potencia_do_motor << endl;
                                cout << "Combustível: " << veiculo[i].combustivel << endl;
                                cout << "Câmbio: " << veiculo[i].cambio << endl;
                                cout << "Direção: " << veiculo[i].direcao << endl;
                                cout << "Cor do veículo: " << veiculo[i].cor << endl;
                                cout << "Número de portas: " << veiculo[i].portas << endl;
                                cout << "Placa: " << veiculo[i].placa << endl;
                                cout << "Valor de mercado do veículo: " << veiculo[i].valor << endl;
                                cout << "----------------------------------------" << endl;
                            i++;
                            }
                        }
                        // Se nenhum veículo for encontrado com o tipo especificado
                        if (!encontrado) {
                            cout << "Nenhum veículo encontrado com o tipo '" << tipo_busca << "'." << endl;
                        }
                    } else { //caso o tipo dado for inválido ele retorna ao menu de opções do usuário
                        cout << "Tipo de veículo inválido. Por favor, escolha entre as opções fornecidas." << endl;
                    }
                } // fecha
                break;
            case 4:
                {
                    cout << "Digite o tipo de câmbio que deseja buscar (Manual, Automático): ";
                    cin >> cambio_busca;
                    // Procura pelos veículos com o tipo de câmbio 
                    for (int i = 0; i < qtde; ++i) {
                        if (veiculo[i].cambio == cambio_busca) {
                            encontrado = true;
                            cout << "Veículo encontrado:" << endl;
                            cout << "Modelo: " << veiculo[i].modelo << endl;
                            cout << "Marca: " << veiculo[i].marca << endl;
                            cout << "Tipo: " << veiculo[i].tipo << endl;
                            cout << "Ano: " << veiculo[i].ano << endl;
                            cout << "KM: " << veiculo[i].km << endl;
                            cout << "Potência do motor: " << veiculo[i].potencia_do_motor << endl;
                            cout << "Combustível: " << veiculo[i].combustivel << endl;
                            cout << "Câmbio: " << veiculo[i].cambio << endl;
                            cout << "Direção: " << veiculo[i].direcao << endl;
                            cout << "Cor do veículo: " << veiculo[i].cor << endl;
                            cout << "Número de portas: " << veiculo[i].portas << endl;
                            cout << "Placa: " << veiculo[i].placa << endl;
                            cout << "Valor de mercado do veículo: " << veiculo[i].valor << endl;
                            cout << "----------------------------------------" << endl;
                        }
                    }
                    if (!encontrado) { // Se nenhum veículo for encontrado com o tipo de câmbio especificado
                        cout << "Nenhum veículo encontrado com o câmbio '" << cambio_busca << "'." << endl;
                    }
                }    
                break;
            case 5:
                { //abre strings do case 5
                    cout << "Digite o valor mínimo: ";
                    cin >> valor_minimo;
                    cout << "Digite o valor máximo: ";
                    cin >> valor_maximo;
                    cout << "Veículos na faixa de valores de R$" << valor_minimo << " a R$" << valor_maximo << ":" << endl;
                    for (int i = 0; i < qtde; ++i) {
                        if (veiculo[i].valor >= valor_minimo && veiculo[i].valor <= valor_maximo) {
                            encontrado = true;
                            cout << "Modelo: " << veiculo[i].modelo << endl;
                            cout << "Marca: " << veiculo[i].marca << endl;
                            cout << "Valor: R$" << veiculo[i].valor << endl;
                            cout << "----------------------------------------" << endl;
                        }
                    } //fecha
                    if (!encontrado) { //caso de não achar nenhum na faixa
                        cout << "Nenhum veículo encontrado na faixa de valores de R$" << valor_minimo << " a R$" << valor_maximo << "." << endl;
                    }
                } //fecha
                break;
            case 6:
            {
                int total_veiculos = qtde;  //total de veículos carregados
                int contagem_tipos[tam] = {0};  //contar os veículos por tipo
                int contagem_combustivel[tam] = {0};  //contar os veículos por combustível
                string tipos_unicos[tam];  //armazenar tipos únicos
                string combustivel_unico[tam];  //armazenar combustíveis únicos
                int num_tipos = 0;  //número de tipos únicos
                int num_combustiveis = 0;  //número de combustíveis únicos
                float menor_valor = -1; //guarda menor valor que encontrou 
                int indice_mais_barato = -1; //guarda o veiculo mais barado
                float valorMaximo = 0; // Inicializa o valor máximo como zero
                string placaMaisCara; //guarda o veiculo mais caro pela placa
                float totalQuilometragem = 0; //tira média KM de todos os veiculos
                int quantidadeVeiculos = 0; //acima de 2019 
                
                // Contar veículos por tipo
                for (int i = 0; i < qtde; ++i) {
                    bool tipo_encontrado = false;
                    for (int j = 0; j < num_tipos; j++) {
                        if (veiculo[i].tipo == tipos_unicos[j]) {
                            contagem_tipos[j]++;
                            tipo_encontrado = true;
                            break;
                        }
                    }//fora do padr~ão
                    if (!tipo_encontrado) {
                        tipos_unicos[num_tipos] = veiculo[i].tipo;
                        contagem_tipos[num_tipos]++;
                        num_tipos++;
                    }
                }
                // Imprimir 
                cout << "Porcentagens de Veículos por Tipo:" << endl;
                for (int i = 0; i < num_tipos; i++) {
                    float porcentagem = (float)contagem_tipos[i] / total_veiculos * 100;
                    cout << tipos_unicos[i] << ": " << porcentagem << "%" << endl;
                }
                // Contar veículos por combustível
                for (int i = 0; i < qtde; ++i) {
                    bool combustivel_encontrado = false;
                    for (int j = 0; j < num_combustiveis; j++) {
                        if (veiculo[i].combustivel == combustivel_unico[j]) {
                            contagem_combustivel[j]++;
                            combustivel_encontrado = true;
                            break;
                        }
                    }//fora do padrão
                    if (!combustivel_encontrado) {
                        combustivel_unico[num_combustiveis] = veiculo[i].combustivel;
                        contagem_combustivel[num_combustiveis]++;
                        num_combustiveis++;
                    }
                }
                // Imprimir 
                cout << "Porcentagens de Veículos por Combustível:" << endl;
                for (int i = 0; i < num_combustiveis; i++) {
                    float porcentagem = contagem_combustivel[i] / total_veiculos * 100;
                    cout << combustivel_unico[i] << ": " << porcentagem << "%" << endl;
                }
                //veiculo mais barato 
                for (int i = 0; i < qtde; i++) {
                    if (veiculo[i].valido && veiculo[i].potencia_do_motor == 1.0) {
                        if (menor_valor == -1 || veiculo[i].valor < menor_valor) {
                            menor_valor = veiculo[i].valor;
                            indice_mais_barato = i;
                        }
                    }
                }
                // Encontrar o veículo 1.0 mais barato
                for (int i = 0; i < qtde; i++) {
                    if (veiculo[i].valido && veiculo[i].potencia_do_motor == 1.0) {
                        if (menor_valor == -1 || veiculo[i].valor < menor_valor) {
                            menor_valor = veiculo[i].valor;
                            indice_mais_barato = i;
                        }
                    }
                }
                //imprime
                if (indice_mais_barato != -1) {
                    cout << "Veículo 1.0 mais barato encontrado:" << endl;
                    cout << "Modelo: " << veiculo[indice_mais_barato].modelo << endl;
                    cout << "Marca: " << veiculo[indice_mais_barato].marca << endl;
                    cout << "Placa: " << veiculo[indice_mais_barato].placa << endl;
                    cout << "Valor: R$" << veiculo[indice_mais_barato].valor << endl;

                // Calcular financiamento em 60 meses
                float taxa_juros = 0.015; // Supondo uma taxa de juros mensal de 1.5%
                int num_meses = 60;
                float valor_financiado = veiculo[indice_mais_barato].valor;
                float parcela = (valor_financiado * taxa_juros) / (1 - pow(1 + taxa_juros, - num_meses));

                cout << "Valor da prestação em 60 meses: R$" << parcela << endl;
                } else {
                    cout << "Nenhum veículo 1.0 encontrado." << endl;
                }
                //direção hidráulica e câmbio automático, e ainda, valor do seguro estimado
                for (int i = 0; i < qtde; i++) {
                    if (veiculo[i].direcao == "hidráulica" && veiculo[i].cambio == "automático") {
                        if (veiculo[i].valor > valorMaximo) {
                            valorMaximo = veiculo[i].valor;
                            placaMaisCara = veiculo[i].placa;
                        }
                    }
                }
                //imprime
                cout << "Veículo mais caro com direção hidráulica e câmbio automático:" << endl;
                cout << "Placa: " << placaMaisCara << endl;
                cout << "Valor: R$" << valorMaximo << endl;
                //quantidade e média de quilometragem dos veículos com 5 anos ou mais (2019)
                for (int i = 0; i < qtde; i++) {
                    if (veiculo[i].ano <= 2019) { // Verifica se o veículo tem 5 anos ou mais
                        totalQuilometragem += veiculo[i].km;
                        quantidadeVeiculos++;
                    }
                }
                //imprime
                if (quantidadeVeiculos > 0) {
                    float mediaQuilometragem = (totalQuilometragem) / quantidadeVeiculos;
                    cout << "Quantidade de veículos com 5 anos ou mais: " << quantidadeVeiculos << endl;
                    cout << fixed << setprecision(2) << "Média de quilometragem: " << mediaQuilometragem << " km" << endl; //fixed para tirar do formato cientifico 
                } else {
                    cout << "Nenhum veículo com 5 anos ou mais encontrado." << endl;
                }break;
            } //fecha case 6
            case 7:
            { //salva e sai
                ofstream arquivo_saida("BD_veiculos.txt"); 
                if (arquivo_saida.is_open()) { //verifica se foi aberto 
                    for (int i = 0; i < qtde; ++i) {
                        if(veiculo[i].valido == true){ //salva todos que estiver como 1/true
                            arquivo_saida << veiculo[i].modelo << " "
                                    << veiculo[i].marca << " "
                                    << veiculo[i].tipo << " "
                                    << veiculo[i].ano << " "
                                    << veiculo[i].km << " "
                                    << veiculo[i].potencia_do_motor << " "
                                    << veiculo[i].combustivel << " "
                                    << veiculo[i].cambio << " "
                                    << veiculo[i].direcao << " "
                                    << veiculo[i].cor << " "
                                    << veiculo[i].portas << " "
                                    << veiculo[i].placa << " "
                                    << veiculo[i].valor << endl;
                        }
                    }
                    arquivo_saida << "fim"; //depois de salvar tudo escreve fim novamente no arquivo
                    arquivo_saida.close(); //fecha o arquivo
                    cout << "Alterações salvas com sucesso." << endl;
                } else { //caso n foi aberto
                    cout << "Erro ao abrir o arquivo para salvar as alterações." << endl;
                }
                // Finalizar o programa
                cout << "Saindo do Banco de Dados..." << endl;
                break;
            }
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 7);
    
    return 0;
}
