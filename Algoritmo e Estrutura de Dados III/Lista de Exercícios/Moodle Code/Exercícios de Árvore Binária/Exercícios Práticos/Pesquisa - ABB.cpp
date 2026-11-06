#include<iostream>

using namespace std;

struct node{
    int data;   //<-- Armazena o valor inteiro
    struct node * left; //<-- Ponteiro para o filho da esquerda
    struct node * right;    //<-- Ponteiro para o filho da direita
};

void insert(node * & current, int data){
    //<-- Verifica se a posição está vazio -->
    if(current = NULL){
        //<-- Criação de um novo nó
        current = new node;
        //<-- Armazena-se o valor
        current->data = data;
        //<-- Inicialização dos 2 ponteiros left e right
        current->left = NULL;
        current->right = NULL;

        //<-- Se o valor novo for menor que o valor atual, move para a esquerda
        //<-- Se o valor novo for maior que o valor atual, move para a direita

    }   else if(data < current-> data){
        insert(current->left, data);
    }   else{
        insert(current->right, data);
    }
}

//<-- A função recebe os parâmetros do ponteiro(current) e o valor(data)
node * search(node * current, int data){
    //<-- Verificação para saber se o valor foi encontrado
    if(current == NULL){ 
        return NULL;    //<-- Se não foi encontrado, resultará em vazio
    
    //<-- Verificação caso o valor tenha sido encontrado
    } else if(data == current->data){
        return current; //<-- Retorna o valor encontrado

    //<-- Senão, deverá continuar procurando a esquerda ou direita
    } else {
        if(data < current->data){
            return search(current->left, data);
        } else {
            return search(current->right, data);
        }
    }
}

//Limpeza dos valores armazenados
void destruct(node * & current) {

    //<-- Se os valores não estiverem vazios, deverá excluir os dados armazenados
    if(current != NULL) {
        destruct(current->left);
        destruct(current->right);

        delete current;
        current = NULL;
    }
}

int main(){

    node * root = NULL; //<-- root representa o ponteiro na raíz da árvore

    int N, valor, X;

    cin >> N;

    for(int i  = 0; i < N; i++){
        cin >> valor;
        insert(root, valor);
    }

    cin >> X;

    node * result = search(root, X);

    if(result == NULL)  {
        cout << "Nao encontrado" << endl;
    }   else{
        cout << "Encontrado" << endl;
    }

    destruct(root);

    return 0;
}

