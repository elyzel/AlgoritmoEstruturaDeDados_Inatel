/*
**Contexto:**
Um arquiteto precisa calcular a área de um triângulo para determinar o espaço disponível para a construção de um novo prédio.

**Entradas:**
Três pares de inteiros x1, y1, x2, y2, x3, y3 ($-100 \le x, y \le 100$).

**Saídas:**
Um número decimal representando a área do triângulo.

**Casos de teste:**

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 0 0 4 0 2 3 | 6.0 |
| 1 1 1 1 1 1 | 0.0 |

*/

#include <iostream>
using namespace std;

struct ponto{
    int x, y;
};

double area_triangulo(ponto a, ponto b, ponto c){
    double area = (
        a.x * b.y - a.y * b.x +
        a.y * c.x - a.x * c.y +
        b.x * c.y - b.y * c.x
    ) / 2.0;

    if(area < 0)
        area = -area;

    return area;
}

int main(){
    ponto a, b, c;

    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;

    cout << area_triangulo(a, b, c) << endl;

    return 0;
}