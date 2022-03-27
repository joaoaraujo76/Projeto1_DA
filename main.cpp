#include <iostream>
#include <fstream>
#include <vector>
#include "Encomenda.h"
#include "Carrinha.h"

using namespace std;

int main() {
    // abrir os ficheiros e verificar se existem;

    ifstream inFile_carrinhas, inFile_encomendas;

    inFile_carrinhas.open("carrinhas.txt");
    inFile_encomendas.open("encomendas.txt");

    if (!inFile_carrinhas.is_open()) {
        cerr << "Unable to open carrinhas.txt";
        exit(1);
    }

    if (!inFile_encomendas.is_open()) {
        cerr << "Unable to open encomendas.txt";
        exit(1);
    }

    //-------------------------------------------------------------------------------

    // sacar informação carrinhas;

    string info_carrinha;
    int volMax, pesoMax, custo;
    vector<Carrinha> carrinhas;


    getline(inFile_carrinhas, info_carrinha); // ignorar primeira linha;
    while (inFile_carrinhas >> volMax >> pesoMax >> custo){
        Carrinha c(volMax,pesoMax,custo);
        carrinhas.push_back(c);
    }

    //-----------------------------------------------------------------------------

    // sacar informação encomendas;

    string info_encomenda;
    int volume, peso, recompensa, duracao;
    getline(inFile_carrinhas, info_encomenda);
    vector<Encomenda> encomendas;

    getline(inFile_encomendas, info_encomenda); // ignorar primeira linha;
    while (inFile_encomendas >> volume >> peso >> recompensa >> duracao){
        Encomenda e(volume,peso,recompensa,duracao);
        encomendas.push_back(e);
    }

    return 0;
}
