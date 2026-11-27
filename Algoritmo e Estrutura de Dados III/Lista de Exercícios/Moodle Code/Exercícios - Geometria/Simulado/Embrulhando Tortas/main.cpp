/*
O sistema de visão computacional de Soebad fez tanto sucesso que ele resolveu usá-lo também na expedição. Os pedidos online agora são enviados em lotes: as tortas são
colocadas lado a lado sobre uma bandeja e, antes do envio, o lote inteiro é envolvido por uma tira de filme plástico bem esticada, que contorna as tortas pelo lado de fora.

Uma câmera posicionada acima da bandeja identifica o centro de cada torta, em coordenadas inteiras (x, y). Todas as tortas de um lote têm o mesmo diâmetro D.

Soebad precisa de duas informações para cada lote:

1. O comprimento do filme plástico necessário para envolver todas as tortas. O filme deve ter o menor comprimento possível, ficando bem esticado ao redor do lote.
2. Quais tortas ficam encostadas no filme. Essas tortas estão mais expostas a impactos durante o transporte e recebem uma camada extra de proteção. Uma torta está encostada no filme quando o seu centro está sobre o contorno do lote, seja em um dos cantos ou sobre um dos trechos retos entre dois cantos (Desconsidere das bordas as tortas que forem colineares).

Dica: imagine o contorno formado pelos centros das tortas. O filme acompanha esse contorno nos trechos retos e, ao passar por cada canto, faz uma curva ao redor da torta. Somando todas essas curvas, o filme dá exatamente uma volta completa em torno de uma torta.

Sua missão é ajudar Soebad a calcular essas informações!

Entrada

A primeira linha da entrada contém dois números inteiros: a quantidade de tortas N (1 <= N <= 1000) e o diâmetro D das tortas (1 <= D <= 100).
Em seguida serão informadas N linhas, cada uma com dois números inteiros x e y (0 <= x, y <= 1000), representando as coordenadas do centro da torta T[i], onde 0 <= i < N. Não há duas tortas com o mesmo centro.

Saída

Na primeira linha, o programa deve mostrar os índices i das tortas encostadas no filme, em ordem crescente e separados por um espaço. Na segunda linha, o programa deve mostrar o comprimento do filme plástico, com duas casas decimais. Utilize PI = acos(-1).


Exemplo de entrada	Exemplo de saída
6 10
0 0
40 0
40 40
0 40
20 20
20 0	

0 1 2 3 5
191.42


4 6
0 0
24 18
8 6
16 12	
0 1 2 3
78.85


*/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct ponto {
    int x, y;
    int indice;
};

// Funcao do professor
float area_triangulo(ponto a, ponto b, ponto c) {

    return (
        a.x * b.y - a.y * b.x +
        a.y * c.x - a.x * c.y +
        b.x * c.y - b.y * c.x
    ) / 2.0;
}

// Funcao do professor
int lado(ponto a, ponto b, ponto p) {

    float s = area_triangulo(a, b, p);

    if (s > 0) {
        return 1;
    }
    else if (s < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

// Calcula a distancia entre dois pontos
double distancia(ponto a, ponto b) {

    int dx = b.x - a.x;
    int dy = b.y - a.y;

    return sqrt(dx * dx + dy * dy);
}

// Ordena os pontos
bool comparar(ponto a, ponto b) {

    if (a.x == b.x) {
        return a.y < b.y;
    }

    return a.x < b.x;
}

// Verifica se um ponto pertence a um segmento
bool no_segmento(ponto a, ponto b, ponto p) {

    return lado(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) &&
           p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) &&
           p.y <= max(a.y, b.y);
}

int main() {

    int N, D;
    double PI = acos(-1);

    cin >> N >> D;

    vector<ponto> pontos(N);

    // Leitura das coordenadas
    for (int i = 0; i < N; i++) {

        cin >> pontos[i].x >> pontos[i].y;

        pontos[i].indice = i;
    }

    // Caso exista apenas uma torta
    if (N == 1) {

        cout << 0 << endl;

        cout << fixed << setprecision(2)
             << PI * D << endl;

        return 0;
    }

    // Ordenacao dos pontos
    sort(pontos.begin(), pontos.end(), comparar);

    vector<ponto> inferior;
    vector<ponto> superior;

    // Construindo o contorno inferior
    for (int i = 0; i < N; i++) {

        while (inferior.size() >= 2 &&
               lado(inferior[inferior.size() - 2],
                    inferior.back(),
                    pontos[i]) <= 0) {

            inferior.pop_back();
        }

        inferior.push_back(pontos[i]);
    }

    // Construindo o contorno superior
    for (int i = N - 1; i >= 0; i--) {

        while (superior.size() >= 2 &&
               lado(superior[superior.size() - 2],
                    superior.back(),
                    pontos[i]) <= 0) {

            superior.pop_back();
        }

        superior.push_back(pontos[i]);
    }

    // Removendo extremidades duplicadas
    inferior.pop_back();
    superior.pop_back();

    // Unindo os contornos
    vector<ponto> contorno = inferior;

    for (int i = 0; i < superior.size(); i++) {

        contorno.push_back(superior[i]);
    }

    // Calculando o perimetro
    double perimetro = 0;

    int tamanho = contorno.size();

    for (int i = 0; i < tamanho; i++) {

        int proximo = (i + 1) % tamanho;

        perimetro += distancia(
            contorno[i],
            contorno[proximo]
        );
    }

    // Identificando as tortas expostas
    vector<bool> expostas(N, false);

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < tamanho; j++) {

            int proximo = (j + 1) % tamanho;

            if (no_segmento(contorno[j],
                            contorno[proximo],
                            pontos[i])) {

                expostas[pontos[i].indice] = true;

                break;
            }
        }
    }

    // Exibindo os indices em ordem crescente
    bool primeiro = true;

    for (int i = 0; i < N; i++) {

        if (expostas[i]) {

            if (!primeiro) {
                cout << " ";
            }

            cout << i;

            primeiro = false;
        }
    }

    cout << endl;

    // Calculando o comprimento do filme
    double comprimento = perimetro + PI * D;

    cout << fixed << setprecision(2)
         << comprimento << endl;

    return 0;
}
