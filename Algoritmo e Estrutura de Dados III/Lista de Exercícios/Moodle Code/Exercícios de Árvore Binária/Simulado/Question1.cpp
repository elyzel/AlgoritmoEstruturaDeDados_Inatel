/*
Soebad Saliv é um cozinheiro renomado e excêntrico. Ele costuma usar espécies exóticas de peixes, 
pescados na represa de Anatricé em seus preparos. 

Atualmente, o prato que tem feito muito sucesso e garantiu vários prêmios para Soebad é sua 
torta de jaca e peixe. Com isso, inúmeros turistas passam em seu restaurante e fazem pedidos 
online das suas tortas. 

Ele desenvolveu um sistema de precificação para facilitar a venda das tortas.

Sua missão é ajudá-lo a completar esse sistema!

Faça um programa que leia inicialmente a quantidade de tortas T a serem cadastradas no sistema.

Depois, o programa deve ler as características de cada torta T[i] (0 <= i < T), que são números 
reais representando a espessura da massa (EM), o peso (P), o diâmetro (D) e a altura (A) da torta. 
O preço final PF da torta é calculado de acordo com a formula: PF = (EM*P*A+D+A). 
Insira o código i e o preço final PF de cada torta T[i] em uma árvore binária de busca e 
faça uma listagem em ordem crescente do preço.

Não esqueça de liberar a memória no final do programa!

Entrada

A primeira linha da entrada é a quantidade de tortas T.
Em seguida serão informadas T linhas com 4 números reais indicando:

- espessura da massa (EM) da torta T[i];

- peso (P) da torta T[i];

- altura (A) da torta T[i];

- e diâmetro (D) da torta T[i];

onde 0 <= i < T.

Saída
Na saída, o programa deve mostrar número i e o preço PF de cada torta (no formato i:PF) em ordem 
crescente de preço.


converta isso em markdown
Aqui está a tabela da imagem convertida para o formato Markdown:

Exemplo de entrada	Exemplo de saída
4
5.1 2.8 8.1 29.8
4.85 3.1 7.9 31.1
4.98 2.89 8 30.9
3.8 2.1 7.95 26.5	3:97
0:153
2:154
1:157
3
5 3.2 4 28
9 3.4 3 25
6 3.3 5 21	0:96
1:119
2:125
*/


#include <iostream>
using namespace std;

struct node {
    int codigo; //Inserção do código de cada torta
    double preco;   //Inserção do preço de cada torta
    struct node * left;
    struct node * right;
};

// Insere uma torta na arvore
void insert(node * & current, int codigo, double preco) {

    if(current == NULL) {
        current = new node;
        current->codigo = codigo;   //Armazenamento do código
        current->preco = preco;     //Armazenamento do preco
        current->left = NULL;
        current->right = NULL;
    }
    //<-- Se o preço for menor, move-se para a esquerda
    else if(preco < current->preco) {
        insert(current->left, codigo, preco);
    }
    //<-- Se o preco for maior, move-se para a direita
    else {
        insert(current->right, codigo, preco);
    }
}

// Percorre a arvore em ordem crescente
void show_in_order(node * current) {

    if(current != NULL) {

        show_in_order(current->left);

        //Percorre e mostra o valor de todos os codigos na ordem
        cout << current->codigo << ":"
             << (int)(current->preco) << endl;

        show_in_order(current->right);
    }
}

// Libera a memoria da arvore
void destruct(node * & current) {

    if(current != NULL) {

        destruct(current->left);
        destruct(current->right);

        delete current;
        current = NULL;
    }
}

int main() {

    node * root = NULL; //Reinicializa o ponteiro para vazio

    int T;
    double EM, P, A, D, PF;

    cin >> T;

    for(int i = 0; i < T; i++) {

        cin >> EM >> P >> A >> D;

        PF = (EM * P * A) + D + A;

        insert(root, i, PF); //Ponteiro, contador, PF
    }

    show_in_order(root);    //Mostrar em ordem o ponteiro

    destruct(root); //Limpar os valor do ponteiro

    return 0;
}
