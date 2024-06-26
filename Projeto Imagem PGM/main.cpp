//Este programa realiza processamento de imagens no formato PGM, 
//permitindo diversas operações como ajuste de brilho, 
//criação de imagem negativa, binarização, redução de resolução, adição de ruído, e aplicação de filtro médio, 
//além de salvar as modificações.

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Estrutura para guardar uma imagem em formato PGM
typedef struct {
    string formato;        // Tipo de imagem (P2 ou P5)
    int largura;           // Número de colunas
    int altura;            // Número de linhas
    int valorMaximo;       // Valor máximo de um pixel
    int** matrizPixels;    // Matriz de pixels da imagem
    int** matrizOriginal;  // Matriz para armazenar a imagem original (para aplicar filtro posteriormente)
} ImagemPGM;

// Função para ler a imagem original que vem em PGM
void carregarImagem(ImagemPGM &img, ifstream &arquivoEntrada) {
    arquivoEntrada >> img.formato;
    arquivoEntrada >> img.largura;
    arquivoEntrada >> img.altura;
    arquivoEntrada >> img.valorMaximo;

    // Alocando memória conforme as dimensões da imagem
    img.matrizPixels = new int*[img.altura];
    img.matrizOriginal = new int*[img.altura]; 
    for (int i = 0; i < img.altura; i++) {
        img.matrizPixels[i] = new int[img.largura];
        img.matrizOriginal[i] = new int[img.largura]; 
        for (int j = 0; j < img.largura; j++) {
            arquivoEntrada >> img.matrizPixels[i][j];
            img.matrizOriginal[i][j] = img.matrizPixels[i][j];
        }
    }
}

// Função para ajustar o brilho da imagem 
void ajustarBrilho(ImagemPGM &img, int opcaoBrilho, int valorBrilho) {
    // Clarear a imagem
    if (opcaoBrilho == 1) { 
        for (int i = 0; i < img.altura; i++) {
            for (int j = 0; j < img.largura; j++) {
                int novoPixel = img.matrizPixels[i][j] + valorBrilho;
                img.matrizPixels[i][j] = min(img.valorMaximo, novoPixel); // Garante que o valor não ultrapasse o máximo
            }
        }
        cout << endl << "Brilho aumentado!" << endl << endl;
    } else if (opcaoBrilho == 2) { // Escurecer a imagem
        for (int i = 0; i < img.altura; i++) {
            for (int j = 0; j < img.largura; j++) {
                int novoPixel = img.matrizPixels[i][j] - valorBrilho;
                img.matrizPixels[i][j] = max(0, novoPixel); // Garante que o valor não seja menor que 0
            }
        }
        cout << endl << "Brilho reduzido!" << endl << endl;
    }
}

// Função para aplicar a imagem negativa
void aplicarNegativo(ImagemPGM &img) {
    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            img.matrizPixels[i][j] = img.valorMaximo - img.matrizPixels[i][j];
        }
    }
}

// Função que converte a imagem em um formato binário
void binarizarImagem(ImagemPGM &img, int limiar) {
    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            if (img.matrizPixels[i][j] > limiar) {
                img.matrizPixels[i][j] = img.valorMaximo;
            } else {
                img.matrizPixels[i][j] = 0;
            }
        }
    }
}

// Função para reduzir a imagem para 64x64 pixels
void reduzirImagem(ImagemPGM &img, int tamanhoBloco) {
    int novaLargura = 64;
    int novaAltura = 64;
    
    // Faz o cálculo do tamanho do bloco em comparação com original 
    int blocoLargura = img.largura / novaLargura;
    int blocoAltura = img.altura / novaAltura;

    // Nova imagem formada
    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            int soma = 0;
            int contador = 0;

            // Calcula a média dentro do bloco
            for (int x = i * blocoAltura; x < (i + 1) * blocoAltura; x++) {
                for (int y = j * blocoLargura; y < (j + 1) * blocoLargura; y++) {
                    soma += img.matrizPixels[x][y];
                    contador++;
                }
            }

            // Calcula a média geral 
            int media = soma / contador;

            // Aplica a média no bloco
            for (int x = i * blocoAltura; x < (i + 1) * blocoAltura; x++) {
                for (int y = j * blocoLargura; y < (j + 1) * blocoLargura; y++) {
                    img.matrizPixels[x][y] = media;
                }
            }
        }
    }

    // Ajusta as dimensões para 64x64 pixels
    img.altura = novaAltura;
    img.largura = novaLargura;
}

// Função que gera os ruídos na imagem
void adicionarRuido(ImagemPGM &img, int nivelRuido) {
    srand(time(NULL));

    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            int ruido = rand() % (nivelRuido + 1) - nivelRuido / 2;
            img.matrizPixels[i][j] = min(img.valorMaximo, max(0, img.matrizPixels[i][j] + ruido));
        }
    }

    cout << endl << "Ruído adicionado à imagem com sucesso!" << endl << endl;
}

// Função para aplicar filtro médio na imagem toda
void aplicarFiltroMedio(ImagemPGM &img, int tamanhoFiltro) {
    // Matriz temporária que guarda os pixels que foram alterados
    int** tempPixels = new int*[img.altura];
    for (int i = 0; i < img.altura; i++) {
        tempPixels[i] = new int[img.largura];
    }

    // Aplica o filtro de média
    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            int soma = 0;
            int contador = 0;

            // Calculando a média dos pixels em volta
            for (int x = max(0, i - tamanhoFiltro); x <= min(img.altura - 1, i + tamanhoFiltro); x++) {
                for (int y = max(0, j - tamanhoFiltro); y <= min(img.largura - 1, j + tamanhoFiltro); y++) {
                    soma += img.matrizOriginal[x][y]; // Utiliza a matriz original
                    contador++;
                }
            }

            // Calculando a média geral 
            int media = soma / contador;
            tempPixels[i][j] = media;
        }
    }

    // Copiando os pixels escolhidos para a matriz principal novamente
    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            img.matrizPixels[i][j] = tempPixels[i][j];
        }
    }

    // Liberando a memória da matriz criada temporariamente
    for (int i = 0; i < img.altura; i++) {
        delete[] tempPixels[i];
    }
    delete[] tempPixels;

    cout << endl << "Filtro aplicado com sucesso!" << endl << endl;
}

// Função para salvar a imagem nova em arquivo PGM 
void salvarImagem(ImagemPGM &img, ofstream &arquivoSaida) {
    arquivoSaida << img.formato << endl;
    arquivoSaida << img.largura << " ";
    arquivoSaida << img.altura << endl;
    arquivoSaida << img.valorMaximo << endl;

    for (int i = 0; i < img.altura; i++) {
        for (int j = 0; j < img.largura; j++) {
            arquivoSaida << img.matrizPixels[i][j] << " ";
        }
        arquivoSaida << endl;
    }
}

int main() {
    ImagemPGM imagem;

    ifstream arquivoEntrada("stanford.pgm");
    if (!arquivoEntrada.is_open()) {
        cout << endl << "O arquivo selecionado não existe!";
        return 1;
    }

    carregarImagem(imagem, arquivoEntrada);
    arquivoEntrada.close();

    int opcaoDesejada = 0;
    int opcaoBrilho, valorBrilho;
    int limiar;
    int tamanhoBloco = 8; // Tamanho único 

    do {
        cout << "--------------------------------------------------------" << endl;
        cout << endl << "1 - Alterar o Brilho da Imagem" << endl 
             << "2 - Encontrar a Imagem Negativa" << endl  
             << "3 - Binarizar a Imagem" << endl   
             << "4 - Reduzir a Imagem";
        cout << endl << "5 - Criar Ruídos na Imagem" << endl   
             <<  "6 - Aplicar Filtro Médio" << endl 
             << "7 - Sair" << endl;
        cout << "--------------------------------------------------------" << endl;     

        cout << endl << "Escolha a opção desejada: ";//pede a opção para o usuário
        cin >> opcaoDesejada;//Lê a opção do usuário

        //caso de escoher uma opção não disponível aleátoria 
        while (opcaoDesejada < 1 || opcaoDesejada > 7) {
            cout << endl << "Opção Inválida! Insira uma opção válida: ";
            cin >> opcaoDesejada;
        }

        //Menu de opções  
        switch (opcaoDesejada) {
            case 1:
                cout << endl << "Deseja clarear ou escurecer a imagem?" << endl << endl << "1 - Clarear" << endl << "2 - Escurecer" << endl;
                cout << endl << "Digite a Opção: ";
                cin >> opcaoBrilho;
                while (opcaoBrilho < 1 || opcaoBrilho > 2) {
                    cout << endl << "Opção Inválida, Digite uma opção válida! ";
                    cin >> opcaoBrilho;
                }
                if (opcaoBrilho == 1) {
                    cout << endl << "Digite a porcentagem de brilho que você deseja adicionar a imagem(0-100%): ";
                    cin >> valorBrilho;
                    while (valorBrilho <= 0 || valorBrilho > 100) {
                        cout << endl << "Você escolheu uma porcentagem inválida, digite novamente: ";
                        cin >> valorBrilho;
                    }
                    valorBrilho = valorBrilho * 255 / 100;
                    ajustarBrilho(imagem, opcaoBrilho, valorBrilho); 
                } else if (opcaoBrilho == 2) {
                    cout << endl << "Digite a porcentagem de brilho que você deseja retirar da imagem: ";
                    cin >> valorBrilho;
                    while (valorBrilho <= 0 || valorBrilho > 100) {
                        cout << endl << "Você escolheu uma porcentagem inválida, digite novamente: ";
                        cin >> valorBrilho;
                    }
                    valorBrilho = valorBrilho * 255 / 100;
                    ajustarBrilho(imagem, opcaoBrilho, valorBrilho);
                }
                break;
            case 2:
                aplicarNegativo(imagem);
                cout << endl << "Aplicando Negativo..." << endl << endl;
                cout << endl << "Aplicado com sucesso!" << endl << endl;
                break;
            case 3:
                cout << endl << "Digite o valor do limiar que deseja para binarizar a imagem: ";
                cin >> limiar;
                binarizarImagem(imagem, limiar);
                cout << endl << "Imagem binarizada com sucesso!" << endl << endl;
                break;
            case 4:
                reduzirImagem(imagem, tamanhoBloco);
                cout << endl << "Redução aplicada!" << endl << endl;
                break;
            case 5:
                int nivelRuido;
                cout <<  endl << "Digite o nível de ruído: ";
                cin >> nivelRuido;
                adicionarRuido(imagem, nivelRuido);
                break;
            case 6:
                int tamanhoFiltro;
                cout << endl << "Digite as dimensões para aplicar na imagem: ";
                cin >> tamanhoFiltro;
                aplicarFiltroMedio(imagem, tamanhoFiltro);
                break;
        }
    } while (opcaoDesejada != 7);

    cout << endl << "Finalizando o programa..." << endl;

    ofstream arquivoSaida("novaIMG.pgm");
    if (!arquivoSaida.is_open()) {
        cout << endl << "O arquivo selecionado não existe!";
        return 1;
    }

    salvarImagem(imagem, arquivoSaida);
    arquivoSaida.close();

    // Liberação da memória alocada para a matriz de pixels
    for (int i = 0; i < imagem.altura; i++) {
        delete[] imagem.matrizPixels[i];
        delete[] imagem.matrizOriginal[i];
    }
    delete[] imagem.matrizPixels;
    delete[] imagem.matrizOriginal;

    return 0;
}
