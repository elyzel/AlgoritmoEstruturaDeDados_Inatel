#include<iostream>
using namespace std;

int main()  {
    char gabarito[10]; //< -- Char do Gabarito irá armazenar fixo 10 caracteres
    char respostas[10]; //< -- Char das respostas irá armazenar fixo 10 caracteres

    char *p_gabarito = gabarito; //< -- Declaração dos ponteiros dentro do vetor 
    char *p_resposta = respostas;// < -- Declaração dos ponteiros dentro do vetor

    for(int i = 0; i < 10; i++) {
        cin >> *(p_gabarito + i); // Recebe o valor de cada letra do gabarito e armazena no vetor através do ponteiro
    }

    for(int i = 0; i < 10; i++) {
        cin >> *(p_resposta + i); //Recebbe o valor de cada letra como resposta
    }

    int acertos = 0;//< -- Declaração da variavel que irá armazenar a quantidade de acertos

    //< -- Comparação das respostas com o gabarito -->
    for(int i = 0; i < 10; i++) {
        if(*(p_gabarito + i) == *(p_resposta + i))  {
            acertos++;
        }
    }

    cout << "acertos " << acertos << endl;

    return 0;


}