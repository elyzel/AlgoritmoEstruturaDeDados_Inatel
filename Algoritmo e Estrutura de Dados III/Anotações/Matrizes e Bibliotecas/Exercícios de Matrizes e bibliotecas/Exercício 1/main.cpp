#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()  {

    //Criação das matrizes 2 x 3
    vector<vector<int>>matriz = {
        {5, 12, 3},
        {8, 2, 19}
    };

    int maiorValor = matriz[0][0]; //Começa assumindo que a primeira posição a11 é o maior valor.

    cout << "=== Sua Matriz ===" << endl;

    //Percorre pela matriz utilizando 2 loops para verificar respectivamente as linhas e colunas da matriz.
    for(size_t i = 0; i< matriz.size(); i++)    {   //Percorre pelas linhas
        for(size_t j = 0; j < matriz.size(); j++)   {   //Percorre pelas colunas

            cout << matriz[i][j] << "\t"; //Imprime o elemento 

            //Uso da biblioteca max para alcançar o maior valor da matriz
            maiorValor = max(maiorValor, matriz[i][j]);
        }

        cout << endl;
    }

    cout << "\n0 maior valor encontrado foi: " << maiorValor << endl;

    return 0;
}