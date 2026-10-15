/*
Exercício 1 — Fácil: struct
Enunciado

Crie uma struct chamada Aluno contendo:

nome
idade
nota

Depois, crie um aluno, preencha seus dados e mostre-os na tela.

Utilizando a mesma struct Aluno, crie um ponteiro que aponte para um aluno.

Modifique a nota do aluno utilizando o ponteiro.
*/

#include<iostream>
#include<string>

using namespace std;

// Estrutura do Struct
struct Aluno{
    string nome;
    int idade;
    float nota;
};

//<--   Função  -- >
int main()  {

//< -- Chamando o struct... -- >
    Aluno aluno1;

    aluno1.nome = "Joao"; 
    aluno1.idade = 21; 
    aluno1.nota = 6.0;

//< -- Criação do ponteiro  -->
    Aluno *pAluno;

//< -- Direcionamento do ponteiro   -->
    pAluno = &aluno1;

    pAluno->idade = 22.2;

    cout << "Nome do aluno: " << aluno1.nome  << endl;
    cout << "Idade do aluno: " << aluno1.idade  << endl;
    cout << "Nota do aluno: " << aluno1.nota  << endl;

    return 0;

}