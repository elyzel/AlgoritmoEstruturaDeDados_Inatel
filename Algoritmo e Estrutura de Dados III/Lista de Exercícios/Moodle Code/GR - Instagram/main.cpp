/*
Você foi contratado pelo Instagram como engenheiro de software para gerenciar as relações entre os 
usuários. Para essa tarefa, você opta por utilizar um grafo direcionado, em que os nós representam os 
usuários, e as arestas as relações entre eles. Um usuário pode seguir outro, mas esse outro pode não o 
seguir de volta, assim como dois usuários podem se seguir mutuamente.

Entrada

A primeira linha contém um inteiro N indicando o número de usuários a serem cadastrados. 
Seguem N linhas com os nomes dos usuários. Após isso, seguem outras N linhas, dessa vez contendo 
o número dos usuários que determinada pessoa segue, sendo a entrada de cada um interrompida pelo número -1.
Por último temos um único inteiro, indicando o número do usuário o qual deseja-se verificar os seguidores.

Saída

A saída deve mostrar todos os seguidores da pessoa desejada.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 5<br>Amanda de Paiva<br>Gabriel Moreira<br>Cassia Reis<br>Helena Martins<br>Francisco Emanuel<br>1 2 3 -1<br>0 -1<br>1 3 4 -1<br>0 2 -1<br>1 -1<br>1 | Amanda de Paiva<br>Cassia Reis<br>Francisco Emanuel |

*/

#include<iostream>
#include<string>
#include<list>

using namespace std;

int main(){

    int N;

    cin >> N;
    cin.ignore();

    string nomes[N];

    //Recebe todos os nomes dos usuarios para cadastro
    for(int i = 0; i < N; i++)  {
        getline(cin, nomes[i]);
    }

    //Criacao da lista de adjascência
    list<int> adj[N];

    for(int u = 0; u < N; u++)  {
        int v;

        while(cin >> v && v != -1)  {
            adj[u].push_back(v);
        }
    }

    int desejado;
    cin >> desejado;

    for(int u = 0; u < N; u++)  {
        for(list<int>::iterator it = adj[u].begin(); it != adj[u.end(); it++])  {
            
            if(*it == desejado)  {
                cout << nomes[u] << endl;
                break;
            }
        }
    }

    return 0;
    
}

