#include<iostream>

using namespace std;

int main(){
    //Variáveis
    int n, m;

    cin >> n >> m;

    //Construção da Matriz
    int matriz [100][100] = {0}; 
    //< -- '{0}' significa preencher a matriz toda com 0

    for(int i = 0; i < m; i++)  {
        int a, b;

        cin >> a >> b;

        matriz[a - 1][b - 1] = 1;
        matriz[b - 1][a - 1] = 1;
    }

    // Varre toda matriz, expondo todos valores de todas as posições.
    // o "if(j < n - 1)" é apenas para evitar um espaço no final da linha
    for(int i = 0; i < n; i++)  {
        for(int j = 0; j < m; j++)  {
            cout << matriz[i][j];
            if(j < n - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}