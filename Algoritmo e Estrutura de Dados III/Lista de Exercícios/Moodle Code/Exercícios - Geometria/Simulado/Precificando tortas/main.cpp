/*
Soebad desenvolveu um sistema de visão computacional que identifica algumas características das tortas de jaca e peixe que ele produz. Ele quer usar esses dados para tomar decisões mais assertivas na hora fazer as vendas.

Inicialmente, dada as imagens de cada torta, ele consegue identificar alguns pontos: As extremidades esquerda e direita da borda da torta e as extremidades esquerda e direita da circunferência da base da torta. A figura abaixo mostra essas características:

Por fim, ele também consegue pesar a torta automaticamente. Com base nessas informações ele desenvolveu uma fórmula para precificar cada torta, com base na espessura da massa (EM), peso (P), diâmetro (D) e altura (A) da torta. O preço final PF da torta é calculado de acordo com a formula: PF = (EM*P*A+D+A). 

Além disso, ele quer usar o sistema para entender a posição da torta na esteira da linha de produção. Devido ao grande número de tortas produzidas, algumas tortas podem ficar na posição correta ou viradas com o fundo para cima. 

Sua missão é, dado o peso da torta e as coordenadas dos pontos .A, .B, .C e .D, indicar a posição da torta e calcular o seu preço final.

Obs: Considere que o diâmetro da circunferência da base é o mesmo do topo e a altura da torta é calculada a partir da base até o topo da torta.

Entrada
A primeira linha da entrada é composta por nove números inteiros representando o peso da torta, seguida das coordenadas x e y de cada um dos pontos .A, .B, .C e .D, respectivamente.

Saída
Na saída, o programa deve mostrar a posição da torta (Correta ou Virada) e o preço final da torta. 


Exemplo de entrada	Exemplo de saída
5 1 10 2 10 1 2 22 2	Correta
69
4 1 10 3 10 1 3 20 3	Correta
82
6 1 2 2 2 1 15 15 15	Virada
105

*/

#include <iostream>
#include <cstdlib>

using namespace std;

struct ponto {
    int x, y;
};

int main() {

    int peso;

    ponto a, b, c, d;

    cin >> peso;

    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cin >> d.x >> d.y;

    int EM = abs(b.x - a.x);

    int diametro = abs(d.x - c.x);

    int altura = abs(a.y - c.y);

    int preco = EM * peso * altura + diametro + altura;

    if (a.y > c.y) {
        cout << "Correta" << endl;
    }
    else {
        cout << "Virada" << endl;
    }

    cout << preco << endl;

    return 0;
}