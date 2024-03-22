#ifndef BUSCA_H
#define BUSCA_H
#include <vector>

using namespace std;

void heapify(vector<int>& lista, int i, int size);
void heapSort(vector<int>& lista);
int busca_sequencial(vector<int> sequencia, int chave);
int busca_sequencial_otimizada(vector<int> sequencia, int chave) ;
int busca_binaria(vector<int> sequencia, int chave);
#endif