/*
Exercício 1 — Fácil: struct
Enunciado

Crie uma struct chamada Aluno contendo:

nome
idade
nota

Depois, crie um aluno, preencha seus dados e mostre-os na tela.
*/

#include<iostream>
#include<string>
using namespace std;

struct Aluno{
    string nome;
    int idade;
    float nota;
};

int main()  {
    
    Aluno aluno1;

    aluno1.nome = "Eliseu";
    aluno1.idade = 21;
    aluno1.nota = 9;

    cout << "Nome do Aluno " << aluno1.nome << endl;
    cout << "Idade do Aluno " << aluno1.idade << endl;
    cout << "Nota do Aluno " << aluno1.nota << endl;

    return 0;

}
