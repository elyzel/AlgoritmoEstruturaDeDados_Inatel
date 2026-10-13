# Questão

##### Faça um programa que leia dos dados dos vértices e arestas de um grafo e os armazene em uma lista de adjacências. Depois mostre o grafo gerado.

Cada nó da lista de adjacências deve conter o vértice de destino e o peso da aresta.

Use a struct abaixo para implementar seu programa. 

```cpp
struct no  
{  
    int v; // vertice adjacente  
    int peso; // peso da aresta  
};
```

Faça uma função para criar as arestas. O cabeçalho desta função deve ser:

```cpp
void cria_aresta(list<no>adj[], int u, int v, int p, int orientado)
```

##### Entrada

A entrada consiste de várias linhas:

- a primeira linha contém dois inteiros: o primeiro corresponde ao número de vértices do grafo, e o segundo define se o grafo é orientado (1) ou não orientado (0).

- as demais linhas três inteiros, que correspondem ao vértice de origem, o vértice de destino e o peso de cada aresta, respectivamente. A entrada de dados termina quando ocorrer uma linha com três números iguais a -1 (esta não deve ser inserida no grafo).  

##### Saída

A saída deverá mostrar a lista de adjacências gerada, como no exemplo abaixo.

Exemplo 1

| Exemplo de entrada | Exemplo de saída |
| ------------------ | ---------------- |
| 5 1                | 0 2 4            |
| 4 1 3              | 0 1 2            |
| 0 2 4              | 1 3 2            |
| 1 3 2              | 2 4 7            |
| 3 1 3              | 3 1 3            |
| 0 1 2              | 3 4 2            |
| 2 4 7              | 4 1 3            |
| 3 4 2              | 4 0 1            |
| 4 0 1              |                  |
| -1 -1 -1           |                  |
|                    |                  |
| 5 0                | 0 2 4            |
| 4 1 3              | 0 1 2            |
| 0 2 4              | 0 4 1            |
| 1 3 2              | 1 4 3            |
| 3 1 3              | 1 3 2            |
| 0 1 2              | 1 3 3            |
| 2 4 7              | 1 0 2            |
| 3 4 2              | 2 0 4            |
| 4 0 1              | 2 4 7            |
| -1 -1 -1           | 3 1 2            |
|                    | 3 1 3            |
|                    | 3 4 2            |
|                    | 4 1 3            |
|                    | 4 2 7            |
|                    | 4 3 2            |
|                    | 4 0 1            |
|                    |                  |

## Código Completo

```cpp
#include <iostream>
#include <list>

using namespace std;

// Estrutura que representa uma aresta da lista de adjacência
struct no
{
    int v;      // vértice de destino
    int peso;   // peso da aresta
};

// Função responsável por criar uma aresta (Modo Tradicional)
void cria_aresta(list<no> adj[], int u, int v, int p, int orientado)
{
    // Criamos uma variável do tipo "no" e preenchemos os dados
    no novo_no;
    novo_no.v = v;
    novo_no.peso = p;
    
    // Adiciona a aresta u -> v
    adj[u].push_back(novo_no);

    // Se o grafo NÃO for orientado, adicionamos a volta (v -> u)
    if (orientado == 0)
    {
        no no_volta;
        no_volta.v = u;
        no_volta.peso = p;
        adj[v].push_back(no_volta);
    }
}

int main()
{
    int n;
    int orientado;

    // Lê o número de vértices e se o grafo é orientado
    cin >> n >> orientado;

    // Cria um vetor de listas de adjacência
    list<no> adj[n];

    int u, v, p;

    // Lê as arestas até encontrar -1 -1 -1
    while (cin >> u >> v >> p)
    {
        // Verifica se chegou ao fim da entrada
        if (u == -1 && v == -1 && p == -1)
        {
            break;
        }

        // Cria a aresta no grafo
        cria_aresta(adj, u, v, p, orientado);
    }

    // Mostra a lista de adjacências (Modo Tradicional com Iterador)
    for (int i = 0; i < n; i++)
    {
        // Declaramos um iterador para a nossa lista de "no"
        list<no>::iterator it;

        // O iterador começa no início da lista e vai até o final
        for (it = adj[i].begin(); it != adj[i].end(); it++)
        {
            // Usamos a setinha "->" para acessar os dados dentro do iterador
            cout << i << " " << it->v << " " << it->peso << endl;
        }
    }

    return 0;
}
```

## Lógica de Diagrama

```mermaid
flowchart TD
    A[Início] --> B[Ler n e orientado]
    B --> C[Criar lista de adjacências]
    C --> D[Ler u, v e peso]
    D --> E{u = -1, v = -1<br>e peso = -1?}
    E -->|Sim| F[Percorrer lista de adjacências]
    E -->|Não| G["cria_aresta()"]
    G --> H[Adicionar u → v]
    H --> I{Grafo não orientado?}
    I -->|Sim| J[Adicionar v → u]
    I -->|Não| D
    J --> D
    F --> K[Imprimir vértice,<br>destino e peso]
    K --> L[Fim]
```







