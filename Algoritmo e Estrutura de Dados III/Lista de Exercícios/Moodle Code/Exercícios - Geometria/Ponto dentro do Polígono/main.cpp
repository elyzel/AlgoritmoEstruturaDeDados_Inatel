/*
**Contexto:** Um designer de jogos precisa saber se um objeto (representado por um ponto) está dentro de uma área segura (um polígono) no mapa do jogo.

**Entradas:**
Primeiro, um inteiro N ($3 \le N \le 100$) representando o número de vértices do polígono, seguido por N pares de inteiros x, y ($-100 \le x, y \le 100$) para os vértices. Em seguida, um par px, py para o ponto.

**Saídas:**
"DENTRO" se o ponto estiver dentro do polígono, "!(DENTRO)" se não.

**Casos de teste:**

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 4 0 0 0 4 4 4 4 0 2 2 | DENTRO |
| 4 0 0 0 4 4 4 4 0 5 5 | !(DENTRO) |
*/

#include <iostream>
using namespace std;

struct ponto{
    int x, y;
};

bool dentro(ponto poligono[], int N, ponto p){
    bool resultado = false;

    for(int i = 0, j = N-1; i < N; j = i++){
        ponto a = poligono[j];
        ponto b = poligono[i];

        // Verifica se o ponto está sobre a aresta
        int cross = (b.x - a.x) * (p.y - a.y) -
                    (b.y - a.y) * (p.x - a.x);

        if(cross == 0 &&
           p.x >= min(a.x, b.x) &&
           p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) &&
           p.y <= max(a.y, b.y)){
            return true;
        }

        // Verifica se o raio horizontal cruza a aresta
        if((a.y > p.y) != (b.y > p.y)){
            double x_intersecao = a.x +
                (double)(p.y - a.y) * (b.x - a.x) /
                (b.y - a.y);

            if(x_intersecao > p.x){
                resultado = !resultado;
            }
        }
    }

    return resultado;
}

int main(){
    int N;
    cin >> N;

    ponto poligono[100];

    for(int i = 0; i < N; i++){
        cin >> poligono[i].x >> poligono[i].y;
    }

    ponto p;
    cin >> p.x >> p.y;

    if(dentro(poligono, N, p))
        cout << "DENTRO" << endl;
    else
        cout << "!(DENTRO)" << endl;

    return 0;
}