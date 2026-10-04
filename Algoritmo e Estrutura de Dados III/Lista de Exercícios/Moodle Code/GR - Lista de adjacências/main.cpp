#include<iostream> 
#include<list>

using namespace std;

//Estrutura que representa uma aresta da lista de adjacência
struct no   {
    int v;  // vértice de destino
    int peso;   //peso de aresta
};
    
void cria_aresta(list<no> adj[], int u, int v, int p, int orientado)    {   // < -- Função responsável por criar uma aresta

    adj[u].push_back({v, p}); //< -- Adiciona a aresta entre o v e o p, ou seja, v -> p

    if(orientado == 0)  {
        adj[v].push_back({u, p});
    }
}

int main()  {
    int n;
    int orientado;

    //Recebe os valores de vértices e se é orientado ou não.
    cin >> n >> orientado;

    // Alocação dinâmica de um array de listas
    list<no> *adj = new list<no>[n];    

    int u, v, p;

    // Lê as arestas até encontrar -1 -1 -1
    while (cin >> u >> v >> p)
    {
        if (u == -1 && v == -1 && p == -1)
        {
            break;
        }

        // Cria a aresta no grafo
        cria_aresta(adj, u, v, p, orientado);
    }

    // Mostra a lista de adjacências
    for (int i = 0; i < n; i++)
    {
        for (const auto &x : adj[i])
        {
            cout << i << " " << x.v << " " << x.peso << endl;
        }
    }

    // Libera a memória alocada dinamicamente
    delete[] adj;

    return 0;
}






