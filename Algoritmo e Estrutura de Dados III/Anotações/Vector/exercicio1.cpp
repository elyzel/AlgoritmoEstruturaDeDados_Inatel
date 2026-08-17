/*
Desafio: Crie um `vector` simples de números inteiros. Adicione 4 notas usando `.push_back()`, calcule a média das notas e mostre 
a maior nota presente usando a biblioteca `<algorithm>`.
*/

#include<iostream>
#include<vector> //Biblioteca responsável por fornecer o vetor dinâmico
#include<algorithm> //Biblioteca responsável por max e sort

using namespace std;

int main()  {

    vector<double> notas;   //Vector simples

    //Adicionando valores ao final do vetor
    notas.push_back(7.5);
    notas.push_back(8.0);
    notas.push_back(6.5);
    notas.push_back(10.0);

    double soma = 0;
    double maiorNota = notas[0];

    //Percorrendo a linha simples
    for(size_t i = 0; i < notas.size(); i++){
        soma += notas[i];
        maiorNota = max(maiorNota, notas[i]); //função max compara a nota atual com a maior registrada no vetor
    }

    double media = soma / notas.size();

    cout << "=== Relatorio de notas ===" << endl;
    cout << "Total de notas inseridas: " << notas.size() << endl;
    cout << "Media da notas inseridas: " << media << endl;
    cout << "Maior nota da turma: " << maiorNota << endl;

return 0;

}