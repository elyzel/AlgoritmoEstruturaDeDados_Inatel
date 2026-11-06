/*
Faça um programa que leia inicialmente a quantidade de peixes P a serem inseridos no sistema.

Depois, o programa deve ler as características de cada peixe Pli] (0 <= i < P), que são números 
reais representando a viscosidade da pele (V), espessura da cauda (E) e diámetro do olho (O) do 
peixe. A toxidade T de cada peixe deve ser calcula de acordo com a formula: T=
int(V*E"N*E*N*O), onde V, E e O são as características do peixe e N é o número atômico do 
Nitrogénio (7). Insira os índices e as toxidades de cada peixe P[i] em uma árvore binária de busca.

Por fim, o usuário irá informar uma faixa de valores de toxidade e apenas os peixes com toxidade 
nessa faixa devem ser exibidos (incluindo os valores limites). Faça uma varredura em nivel, 
apresentando apenas os peixes cuja toxidade esteja na faixa desejada.

Não esqueça de liberar a memória no final do programa!

Entrada

A primeira linha da entrada é a quantidade de peixes P (0 < P < 1000).
Em seguida serão informadas P linhas com 3 números reais indicando:

viscosidade da pele (V) do peixe P[]:

- espessura da cauda (E) do peixe Pl]:

- e diametro do olho (O) do peixe PI]:

onde 0 <= i < P.

Por fim, serão informados dois valores inteiros Tmin e Tmax indicando respectivamente o valor 
mínimo e máximo da faixa de toxidade.

Saída
Na saída, o programa deve mostrar número i e a toxidade T de cada peixe (no formato i:T) fazendo 
uma varredura em nível na árvore binária de busca considerando o intervalo de toxidade desejado.


Exemplo de entrada	Exemplo de saída
4 
 1.5 2.3 0.8 
 2.1 1.1 0.3 
 1.9 2.2 0.7 
 1.8 1.8 0.8 
 300 400	0:311 
 2:315

*/

#include<iostream>
#include<list>

using namespace std;

//Estrutura Fundamental de Árvore Binária
struct node{
    int indice; //<-- Adiciona a variável indice
    int toxidade;   //<-- Adiciona a variável toxidade
    struct node * left;
    struct node * right;
};

//Função de Inserção - Árvore Binária
//<-- Criação de um novo nó, caso esteja vazio
void insert(node * & current, int indice, int toxidade){
    if(current = NULL){
        current = new node; //<-- Criação de um novo nó
        current->indice = indice;
        current->toxidade = toxidade;
        current->left = NULL;   //<-- Não movimenta
        current->right = NULL;  //<--
    }   else if(toxidade < current->toxidade){
            insert(current->left, indice, toxidade); //<-- Leva os valores do nó para a esquerda, logo que é menor
        }   else{
                insert(current->right, indice, toxidade);   //<-- Leva os valores do nó para a direita, logo que é maior
        }
}

//
void show_in_level(node * current, int Tmin, int Tmax){
    if(current == NULL){
        return;
    }

    list<node*> visit_list; //<-- Criação da lista ligada
    visit_list.push_back(current);  //Ordem por fila

    //Enquanto a lista não estiver vazia, continue executando...
    while(!visit_list.empty()){
        node * temp = visit_list.front();

        //Mais uma condição é criada para extrair o valor de cada peixe
        if(temp->toxidade >= Tmin && temp->toxidade <= Tmax){
            cout << temp->indice << ":" << temp->toxidade << endl;
        }

        if(temp->left != NULL){
            visit_list.push_back(temp->left);
        }

        if(temp->right != NULL){
            visit_list.push_back(temp->right);
        }

        visit_list.pop_front();
    }
}

//Limpa de memória
 void destruct(node * & current){
    if(current != NULL){
        destruct(current->left);
        destruct(current->right);

        delete current;
        current = NULL;
    }
}

int main(){

    node * root = NULL;

    int P;  //<-- Indice
    cin >> P;

    //Laço que recebe os dados de cada peixe
    for(int i = 0; i < P; i++){
        double V;   //<-- Viscosidade
        double E;   //<-- Espessura da Calda
        double O;   //<-- Diâmetro do olho

        cin >> V >> E >> O;

        int N = 7;  //<-- Número Atômico

        int T = (int)(V * E * N * E * N * O);

        insert(root, i, T);
    }

    int Tmin, Tmax;
    cin >> Tmin >> Tmax;

    show_in_level(root, Tmin, Tmax);

    destruct(root);

    return 0;
}