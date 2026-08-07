/*===================================================================================
			Exercício 6 - Lowest Number and Position
===================================================================================

Escreva um programa que leia um número N. Esse N representa o tamanho de um array X[N]. Em seguida, leia cada um dos números de X, encontre o menor elemento desse array e sua posição, imprimindo essas informações.

Entrada
A primeira linha da entrada contém um número inteiro N (1 < N < 1000), indicando a quantidade de elementos a serem lidos para um array X[N] de números inteiros. A segunda linha contém os N valores, separados por um espaço. Lembre-se de que não haverá números repetidos na entrada.

Saída
A primeira linha exibe a mensagem “Menor valor:” seguida de um espaço e do menor número lido na entrada. A segunda linha exibe a mensagem “Posicao:” seguida de um espaço e da posição do array onde se encontra o menor número, lembrando que o array começa na posição zero.
*/

#include<iostream>

using namespace std;

int main() {

	int N;
	cin >> N;

	int X[N]; 

	cin >> X[0]; 
	int menor = X[0]; 
	int posicao = 0;

	for(int i = 1; i < N; i++){
		cin >> X[i];
		
		if(X[i] < menor) {
			menor = X[i];
			posicao = i;
		}

	}
	cout << "Menor valor: " << menor << endl;
	cout << "Posicao: " << posicao << endl;

	return 0;
	}