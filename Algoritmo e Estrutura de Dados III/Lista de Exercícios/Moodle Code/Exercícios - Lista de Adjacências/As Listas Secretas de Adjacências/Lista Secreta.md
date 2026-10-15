# Lista de Adjacência — Graphlandia

> [!question] Enunciado do problema  
> **Contexto**
> 
> Em Graphlandia, os mensageiros usam rotas secretas para entregar mensagens entre as cidades. CodeMaster descobre sobre essas rotas e decide mapeá-las usando listas de adjacência para cada cidade, identificando todas as cidades conectadas diretamente a ela.
> 
> **Entrada**
> 
> A primeira linha contém dois inteiros `N` e `M`, representando o número de cidades e o número de caminhos, respectivamente.
> 
> As próximas `M` linhas contêm dois inteiros `A` e `B` (`1 ≤ A, B ≤ N`), indicando um caminho bidirecional entre as cidades `A` e `B`.
> 
> **Saída**
> 
> Para cada cidade `i` (`1 ≤ i ≤ N`), imprima uma linha começando com a quantidade de cidades diretamente conectadas a `i`, seguida pelos índices dessas cidades em ordem crescente.
> 
> **Exemplo de entrada**
> 
> ```
> 4 4
> 1 2
> 2 3
> 3 4
> 4 1
> ```
> 
> **Exemplo de saída**
> 
> ```
> 2 2 4
> 2 1 3
> 2 2 4
> 2 1 3
> ```

## 1. Objetivo do programa

Construir uma **lista de adjacência** para representar um grafo não direcionado e imprimir, para cada cidade:

1. Quantas cidades estão conectadas diretamente a ela.
    
2. Quais são essas cidades, em ordem crescente.
    

Como os caminhos são bidirecionais, se existe uma conexão entre `A` e `B`, então `B` também aparece na lista de adjacência de `A`.

## 2. Código completo

```cpp
#include <iostream>
#include <list>

using namespace std;

int main() {
    int N; // Número de cidades
    int M; // Número de caminhos

    cin >> N >> M;

    // Criação das listas de adjacência
    list<int> adj[N + 1];

    // Leitura dos caminhos
    for (int i = 0; i < M; i++) {
        int A, B;

        cin >> A >> B;

        // Caminho bidirecional
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    // Impressão das listas de cada cidade
    for (int i = 1; i <= N; i++) {
        // Ordena as cidades em ordem crescente
        adj[i].sort();

        // Imprime a quantidade de cidades conectadas
        cout << adj[i].size();

        // Percorre a lista de adjacência
        for (list<int>::iterator it = adj[i].begin();
             it != adj[i].end();
             it++) {
            cout << " " << *it;
        }

        // Quebra de linha após cada cidade
        cout << "\n";
    }

    return 0;
}
```

## 3. Explicação por blocos

### Bloco 1 — Bibliotecas

```
#include <iostream>
#include <list>

using namespace std;
```

- `iostream`: permite ler dados com `cin` e imprimir com `cout`.
    
- `list`: disponibiliza a estrutura `list`, uma lista encadeada da biblioteca padrão do C++.
    
- `using namespace std`: permite escrever `list`, `cin` e `cout` sem o prefixo `std::`.
    

### Bloco 2 — Leitura dos dados

```
int N;
int M;

cin >> N >> M;
```

- `N`: quantidade de cidades, ou vértices do grafo.
    
- `M`: quantidade de caminhos, ou arestas do grafo.
    
- `cin >> N >> M`: lê os dois valores da primeira linha.
    

No exemplo:

|Variável|Valor|Significado|
|---|---|---|
|`N`|4|Quatro cidades|
|`M`|4|Quatro caminhos|

### Bloco 3 — Criação da lista de adjacência

```
list<int> adj[N + 1];
```

Cria um conjunto de listas, uma para cada índice de cidade.

- `list<int>`: lista encadeada que armazena números inteiros.
    
- `adj`: nome do vetor de listas.
    
- `N + 1`: permite utilizar diretamente os índices de `1` até `N`, deixando o índice `0` sem uso.
    

Representação inicial:

|Cidade|Lista de adjacência|
|---|---|
|`adj[1]`|Vazia|
|`adj[2]`|Vazia|
|`adj[3]`|Vazia|
|`adj[4]`|Vazia|

**Importante:** cada posição de `adj` contém uma lista própria. Portanto, `adj[1]` é diferente de `adj[2]`.

### Bloco 4 — Leitura e inserção dos caminhos

```
for (int i = 0; i < M; i++) {
    int A, B;

    cin >> A >> B;

    adj[A].push_back(B);
    adj[B].push_back(A);
}
```

O laço é executado `M` vezes, uma vez para cada caminho informado.

- `i`: contador de caminhos.
    
- `A` e `B`: cidades conectadas.
    
- `push_back()`: adiciona um elemento ao final da lista.
    

As duas inserções representam a bidirecionalidade:

```
adj[A].push_back(B);
adj[B].push_back(A);
```

A primeira registra `B` na lista de `A`. A segunda registra `A` na lista de `B`.

#### Rastreamento das inserções

Entrada:

```
4 4
1 2
2 3
3 4
4 1
```

|Iteração|Caminho lido|Lista de `A` atualizada|Lista de `B` atualizada|
|---|---|---|---|
|1|`1 2`|`adj[1] = [2]`|`adj[2] = [1]`|
|2|`2 3`|`adj[2] = [1, 3]`|`adj[3] = [2]`|
|3|`3 4`|`adj[3] = [2, 4]`|`adj[4] = [3]`|
|4|`4 1`|`adj[4] = [3, 1]`|`adj[1] = [2, 4]`|

Depois da leitura, as listas são:

|Cidade|Lista de adjacência antes da ordenação|
|---|---|
|`1`|`[2, 4]`|
|`2`|`[1, 3]`|
|`3`|`[2, 4]`|
|`4`|`[3, 1]`|

Observe que a lista da cidade `4` ficou `[3, 1]`, porque as conexões foram inseridas nessa ordem.

### Bloco 5 — Percorrendo cada cidade

```
for (int i = 1; i <= N; i++) {
    adj[i].sort();

    cout << adj[i].size();

    // ...
}
```

Esse laço percorre as cidades de `1` até `N`.

#### Ordenação

```
adj[i].sort();
```

Ordena os elementos da lista atual em ordem crescente.

Exemplo:

```
Antes:  [3, 1]
Depois: [1, 3]
```

#### Quantidade de conexões

```
cout << adj[i].size();
```

O método `size()` retorna a quantidade de elementos da lista.

Por exemplo, se `adj[1] = [2, 4]`, então `adj[1].size()` retorna `2`.

### Bloco 6 — Iteradores

```
for (list<int>::iterator it = adj[i].begin();
     it != adj[i].end();
     it++) {
    cout << " " << *it;
}
```

Esse laço percorre todos os elementos da lista de adjacência da cidade atual.

|Expressão|Função|
|---|---|
|`list<int>::iterator`|Tipo de iterador usado para percorrer a lista|
|`it`|Variável que indica a posição atual|
|`adj[i].begin()`|Posição do primeiro elemento|
|`adj[i].end()`|Posição posterior ao último elemento|
|`it != adj[i].end()`|Continua enquanto não chegar ao final|
|`it++`|Avança para o próximo elemento|
|`*it`|Acessa o valor do elemento atual|

**Por que usar** `***it**`**?**

O iterador representa uma posição na lista. O operador `*` acessa o valor armazenado nessa posição.

Exemplo: se `adj[1] = [2, 4]`, a iteração funciona assim:

|Passo|`it` aponta para|`*it`|Saída adicionada|
|---|---|---|---|
|1|Primeiro elemento|2|`2`|
|2|Segundo elemento|4|`4`|
|3|`end()`|—|O laço termina|

O espaço em `" "` é colocado antes de cada cidade para separar os números.

### Bloco 7 — Quebra de linha

```
cout << "\n";
```

Essa instrução precisa estar **dentro do laço externo**, depois de imprimir todas as conexões da cidade atual.

Assim, cada cidade ocupa uma linha diferente.

Exemplo:

```
2 2 4
2 1 3
2 2 4
2 1 3
```

Se a quebra de linha ficar fora do laço externo, todas as cidades serão impressas na mesma linha, causando uma saída incorreta para o formato solicitado.

## 4. Rastreamento da saída completa

Depois da leitura e da ordenação, o grafo fica assim:

|Cidade (`i`)|Lista ordenada (`adj[i]`)|`size()`|Linha impressa|
|---|---|---|---|
|1|`[2, 4]`|2|`2 2 4`|
|2|`[1, 3]`|2|`2 1 3`|
|3|`[2, 4]`|2|`2 2 4`|
|4|`[1, 3]`|2|`2 1 3`|

A saída final é:

```
2 2 4
2 1 3
2 2 4
2 1 3
```

O primeiro número de cada linha representa a quantidade de cidades vizinhas. Os números seguintes são os índices dessas cidades.

## 5. Diagrama do fluxo do programa

```
flowchart TD
    A([Início]) --> B[Ler N e M]
    B --> C[Criar listas de adjacência]
    C --> D[Ler um caminho A-B]
    D --> E[Adicionar B em adj A]
    E --> F[Adicionar A em adj B]
    F --> G{Todos os M caminhos foram lidos?}
    G -- Não --> D
    G -- Sim --> H[Selecionar cidade i]
    H --> I[Ordenar adj i]
    I --> J[Imprimir adj i size]
    J --> K[Percorrer a lista com iterador]
    K --> L[Imprimir cada vizinha]
    L --> M[Imprimir quebra de linha]
    M --> N{Todas as N cidades foram impressas?}
    N -- Não --> H
    N -- Sim --> O([Fim])
```

## 6. Resumo dos conceitos

|Conceito|Para que serve neste programa|
|---|---|
|Grafo não direcionado|Representa caminhos que podem ser percorridos nos dois sentidos|
|Vértice|Representa uma cidade|
|Aresta|Representa um caminho entre duas cidades|
|Lista de adjacência|Armazena as cidades conectadas diretamente a cada cidade|
|`list<int>`|Armazena os vizinhos em uma lista encadeada|
|`push_back()`|Insere um vizinho no final da lista|
|`sort()`|Ordena os vizinhos em ordem crescente|
|`size()`|Retorna a quantidade de vizinhos|
|Iterador|Percorre os elementos da lista|
|`*it`|Acessa o elemento apontado pelo iterador|
|`"\n"`|Inicia uma nova linha na saída|

### Complexidade

- **Construção do grafo:** (O(N + M)), considerando a inicialização das listas e a leitura das arestas.
    
- **Ordenação:** para cada cidade, a lista é ordenada separadamente. O custo total depende dos graus dos vértices e pode ser expresso como (O(\sum_{i=1}^{N} d_i \log d_i)), considerando listas não vazias, em que (d_i) é o número de vizinhos da cidade `i`.
    
- **Impressão:** (O(N + M)), contando as cidades e as ocorrências de vizinhos na representação fornecida, para um grafo sem arestas duplicadas.
    
- **Espaço:** (O(N + M)) para armazenar as listas de adjacência.
    

> [!tip] Para memorizar  
> Em um grafo não direcionado, cada aresta `A-B` é armazenada nas duas listas: `adj[A]` recebe `B`, e `adj[B]` recebe `A`. Depois, ordenamos cada lista, contamos os elementos com `size()` e percorremos os vizinhos usando um iterador.