#include "buscas.h"

void heapify(vector<int>& lista, int i, int size) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < size && lista[i] < lista[l])
        largest = l;
    if (r < size && lista[largest] < lista[r])
        largest = r;
    if (largest != i) {
        swap(lista[i], lista[largest]);
        heapify(lista, largest, size);
    }
}

void heapSort(vector<int>& lista) {
    int n = lista.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(lista, i, n);

    for (int i = n - 1; i > 0; i--) {
        swap(lista[0], lista[i]);
        heapify(lista, 0, i);
    }
}
// Funcao retorna a posicao do elemento procurado, ou retorna -1

int busca_sequencial(vector<int> sequencia, int chave) {
    for (int i = 0; i < sequencia.size(); i++) {
        if (sequencia[i] == chave) 
            return i;
    }
    return -1;
}

// Funcao Ordena, e retorna a posicao do elemento procurado, ou retorna -1
int busca_sequencial_otimizada(vector<int> sequencia, int chave) {
    for (int i = 0; i < sequencia.size(); i++) {
        if (chave < sequencia[i]) 
            return -1; 
        else if (chave == sequencia[i]) 
            return i;
    }
    return -1;
}

// Funcao Ordena, e retorna a posicao do elemento por uma busca binária, ou retorna -1
int busca_binaria(vector<int> sequencia, int chave) {

    int left = 0;
    int right = sequencia.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sequencia[mid] == chave) {
            return mid;
        } else if (sequencia[mid] < chave) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
