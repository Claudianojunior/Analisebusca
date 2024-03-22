#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <limits>
#include <chrono>
#include <tuple>
#include <fstream>
#include "buscas.h"

using namespace std;

typedef int (*Funcao)(vector<int> sequencia,int chaves);

vector<int> gerar_valores(int size) ;
double verifica_tempo(Funcao funcao,vector<int> sequencia ,vector<int>  chaves);
void criar_csv(vector<vector<tuple<int,int,string,double>>> dados);


int main() {
    vector<int> n = {10000,100000,1000000,10000000};
    vector<int> q = {100, 1000, 10000,100000};
    vector<vector<tuple<int,int,string,double>>> tempos (3);
    for (auto &ni:n){
        vector<int> sequencia = gerar_valores(ni);
    cout << "Entrou no ni "<< ni<<endl;
        for (auto &qi:q){
            vector<int> chaves = gerar_valores(qi);
            cout << "Entrou no qi "<< qi<<endl;   
            tempos[0].push_back( make_tuple(ni,
                                            qi,
                                            "Busca Sequencial"
                                            ,verifica_tempo(busca_sequencial,sequencia,chaves)));
            cout << "\tPassou busca Sequencial"<<endl;
            heapSort(sequencia);
            tempos[1].push_back(make_tuple(ni,
                                            qi,
                                            "Busca Sequencial Otimizada",
                                            verifica_tempo(busca_sequencial_otimizada,sequencia,chaves)));
            cout << "\tPassou busca Sequencial otimizada"<<endl;
            tempos[2].push_back(make_tuple(ni,
                                            qi,
                                            "Busca Binaria",
                                            verifica_tempo(busca_binaria,sequencia,chaves)));
            cout << "\tPassou busca binaria"<<endl;
        }
        cout <<endl;
    }
    criar_csv(tempos);
    return 0;
}


vector<int> gerar_valores(int size) {
    int int_max = std::numeric_limits<int>::max();
    int int_min = std::numeric_limits<int>::min();
    unordered_set<int> sequencia;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis( int_min,int_max);
    
    while (sequencia.size() < size) {
        sequencia.insert(dis(gen));
    }
    
    return std::vector<int>(sequencia.begin(), sequencia.end());
}


double verifica_tempo(Funcao funcao,vector<int> sequencia ,vector<int>  chaves){
    
    chrono::steady_clock::time_point inicio = chrono::steady_clock::now();


    for (int i =0;i<chaves.size();i++){
        funcao(sequencia,chaves[i]);
    }


    chrono::steady_clock::time_point fim = chrono::steady_clock::now();
    chrono::duration<double> tempo_gasto = chrono::duration_cast<chrono::duration<double>>(fim - inicio);

    return tempo_gasto.count();
}


void criar_csv(vector<vector<tuple<int,int,string,double>>> dados){
    
    ofstream arquivo("dados.csv");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }
    arquivo << "n,q,tipo_busca,tempo"<<endl;
    for (const auto& linha : dados) {
        for (const auto& tupla : linha) {
            arquivo << get<0>(tupla) << ","; 
            arquivo << get<1>(tupla) << ","; 
            arquivo << get<2>(tupla) << ","; 
            arquivo << get<3>(tupla) << endl;
        }
    }

    // Fecha o arquivo
    arquivo.close();

    cout << "Arquivo CSV criado com sucesso." << endl;
}