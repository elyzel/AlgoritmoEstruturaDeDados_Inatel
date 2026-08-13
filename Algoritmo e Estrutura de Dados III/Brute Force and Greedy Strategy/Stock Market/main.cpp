/*
Um investidor iniciante quer aprender a investir no mercado de ações. Como não tem experiência, ele escolheu uma empresa e acompanhou diariamente o valor da ação durante N dias. Ao final, ele quis saber quanto dinheiro teria ganho se tivesse investido durante o período em que acompanhou o valor da ação. Para ser sincero, o investidor é multimilionário e possui muito dinheiro, o suficiente para comprar qualquer quantidade de ações da empresa. No entanto, como é muito cauteloso com seus investimentos, decidiu que nunca manteria mais de uma ação da empresa de cada vez.

Para cobrir os custos, a corretora cobra uma taxa fixa de C dólares por cada compra de ação.

Você deve calcular o lucro máximo que o investidor poderia ter obtido investindo durante os N dias, tendo também a opção de não investir dinheiro algum.

Entrada
A entrada consiste em vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros, N e C (1 ≤ N ≤ 2 × 10⁵, 0 ≤ C ≤ 30). A segunda linha contém os N preços P1, P2, …, PN referentes aos dias 1, 2, …, N, respectivamente. Cada preço Pi satisfaz a condição 1 ≤ Pi ≤ 1000.
Saída
Para cada caso de teste na entrada, seu programa deve produzir exatamente uma linha contendo exatamente um número inteiro: o lucro máximo
do investidor, em dólares.

Anotações:
N = número de dias que observou a ação
C = número fixo de custo pela compra de cada ação

*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()  {
    int N; //Número de dias acompanhando as ações
    int C; //Taxa fixa do corretor
    int P; //Preco da ação

    while(cin >> N >> C)    {

        vector<int> P(N);
    }
}
