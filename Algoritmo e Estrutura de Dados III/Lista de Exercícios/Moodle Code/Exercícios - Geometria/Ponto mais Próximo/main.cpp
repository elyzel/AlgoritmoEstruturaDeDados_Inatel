/*
Contexto: Um jogo de realidade aumentada precisa identificar o ponto mais próximo de um usuário dentro 
de um conjunto de pontos de interesse.
Entradas: Primeiro um inteiro N (1 <= N <= 100), seguido por N pares de inteiros x, y (-1000 <= x, y <= 1000) 
representando os pontos de interesse, e um par ux, uy representando a posição do usuário.
Saídas: O par de inteiros mais próximo do usuário. Em caso de empate, apresente o ponto com menor x, 
e se ainda for necessário, desempate com o menor y.


| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 3<br>0 0<br>5 5<br>10 10<br>5 5 | 5 5 |
| 2<br>0 0<br>2 2<br>1 1 | 0 0 |
*/

#include <iostream>
using namespace std;

//Estrutura Básica da Geometria
struct ponto{
    int x, y;
};

int distancia(ponto a, ponto b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;

    return dx * dx + dy * dy;
}

int main(){
    int N;
    cin >> N;

    ponto pontos[N];    //<-- Criação da lista ligada

    //Recebimento dos pontos x e y em cada coordenada
    for(int i = 0; i < N; i++){
        cin >> pontos[i].x >> pontos[i].y;
    }

    ponto usuario;
    cin >> usuario.x >> usuario.y;

    ponto melhor_ponto = pontos[0];
    int menor_distancia = distancia(pontos[0], usuario);

    for(int i = 1; i < N; i++){
        int d = distancia(pontos[i], usuario);

        if(d < menor_distancia ||
           (d == menor_distancia &&
           (pontos[i].x < melhor_ponto.x ||
           (pontos[i].x == melhor_ponto.x &&
            pontos[i].y < melhor_ponto.y)))){

            menor_distancia = d;
            melhor_ponto = pontos[i];
        }
    }

    cout << melhor_ponto.x << " " << melhor_ponto.y << endl;

    return 0;
} 