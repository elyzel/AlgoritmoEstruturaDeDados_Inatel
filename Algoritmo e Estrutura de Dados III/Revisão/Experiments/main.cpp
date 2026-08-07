/*========================================================================
			Exercício 4 - Experiments
========================================================================


Maria acaba de iniciar a pós-graduação em uma faculdade de medicina e precisa da sua ajuda para organizar um experimento de laboratório pelo qual é responsável. Ela quer saber, ao final do ano, quantos animais foram utilizados no laboratório e qual a porcentagem de cada tipo de animal utilizado.

O laboratório utiliza, especificamente, três tipos de animais: sapos, ratos e coelhos. Para obter essas informações, ela dispõe do número exato de experimentos realizados, bem como do tipo e da quantidade de cada animal utilizado em cada experimento.

Entrada
A primeira linha da entrada contém um número inteiro N, indicando a quantidade de casos de teste a seguir. Cada caso de teste contém um número inteiro Quantidade (1 ≤ Quantidade ≤ 15), que representa o número de animais utilizados, e um caractere Tipo ('C', 'R' ou 'S'), indicando o tipo de animal:
- C: Coelho
- R: Rato
- S: Sapo

Saída
Imprima o total de animais utilizados, o total de cada tipo de animal e a porcentagem de cada um em relação ao total de animais utilizados. A porcentagem deve ser exibida com duas casas decimais.
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int N;
    cin >> N;

    int total = 0, c = 0, r = 0, s = 0;

    for (int i = 0; i < N; i++) {
        int Q;
        char tipo;
        
        cin >> Q >> tipo;

        total += Q;

        if (tipo == 'C') {
            c += Q;
        } else if (tipo == 'R') {
            r += Q;
        } else if (tipo == 'S') {
            s += Q;
        }
    } 

    double perc_c = (c * 100.0) / total;
    double perc_r = (r * 100.0) / total;
    double perc_s = (s * 100.0) / total;

    cout << fixed << setprecision(2);
    cout << "Total: " << total << " cobaias" << endl;
    cout << "Total de coelhos: " << c << endl;
    cout << "Total de ratos: " << r << endl;
    cout << "Total de sapos: " << s << endl;
    cout << "Percentual de coelhos: " << perc_c << " %" << endl;
    cout << "Percentual de ratos: " << perc_r << " %" << endl;
    cout << "Percentual de sapos: " << perc_s << " %" << endl;

    return 0;
}