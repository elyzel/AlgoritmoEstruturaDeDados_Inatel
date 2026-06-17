#include<iostream>

using namespace std;

int main()  {
    int *vetor = NULL; //< -- Ponteiro 1
    int *p = NULL; //< -- Ponteiro 2
    int N; //< -- Tamanho do vetor
    double soma = 0;
    double media;

    cin >> N;
    vetor = new int[N]; 

    p = vetor; //Ponteiro 2 está apontando para o indice 0 do ponteiro vetor

    //< -- Recebimento dos valores do ponteiro
    for(int i = 0; i < N; i++)  {
        cin >> *p;
        p++;
    }

    p = vetor;

    //< -- Soma dos valores de indice do ponteiro
    for(int i = 0; i < N; i++)  {
        soma += *p;
        p++;
    }

    //Calcula a media dos valores inseridos
    media = soma/N;

    cout << "A media dos valores inseridos e igual a " << media << endl;

    delete[] vetor;

    return 0;

}