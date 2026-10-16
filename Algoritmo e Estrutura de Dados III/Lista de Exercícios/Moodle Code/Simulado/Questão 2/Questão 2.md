# Prim — Árvore Geradora Mínima de Habilidades

> [!question] Problema
> Poles está desenvolvendo uma árvore de habilidades para um jogo de RPG. Cada habilidade possui um nome e um poder, e os upgrades conectam habilidades com um custo de experiência.
>
> O objetivo é calcular o **custo mínimo para conectar todas as habilidades**, utilizando o algoritmo de Prim conforme o modelo estudado.

## 1. Ideia do problema

Cada habilidade representa um vértice do grafo, e cada upgrade representa uma aresta cujo peso é o custo de experiência.

| Elemento do problema | Representação |
|---|---|
| Habilidade | Vértice |
| Upgrade | Aresta |
| Custo de experiência | Peso |
| Habilidade Base | Vértice inicial `0` |
| Custo mínimo total | Soma dos pesos da AGM |

O algoritmo utilizado é o **Prim**, que constrói uma Árvore Geradora Mínima (AGM).

> [!important] Observação sobre o modelo
> O código abaixo representa cada upgrade nos dois sentidos, como em um grafo não direcionado. Isso corresponde à interpretação de AGM usada nesta solução. Se a direção dos upgrades precisar ser respeitada literalmente, o algoritmo deverá ser revisto.

## 2. Código completo

```cpp
#include <iostream>
#include <list>
#include <string>
#define INF 999999
using namespace std;

struct Aresta {
    int origem, destino, peso;
};

// Mesmo Prim do modelo: soma o custo das arestas da AGM
int prim_lista(list<Aresta> grafo[], int vertices, int origem) {
    bool visitado[vertices];
    int pai[vertices], distancia[vertices], atual;

    for (int i = 0; i < vertices; i++) {
        visitado[i] = false;
        pai[i] = -1;
        distancia[i] = INF;
    }

    atual = origem;
    distancia[atual] = 0;

    while (!visitado[atual]) {
        visitado[atual] = true;

        list<Aresta>::iterator it;

        for (it = grafo[atual].begin();
             it != grafo[atual].end(); it++) {

            int d = it->destino;
            int p = it->peso;

            if (!visitado[d] && p < distancia[d]) {
                distancia[d] = p;
                pai[d] = atual;
            }
        }

        int menor_distancia = INF;

        for (int i = 0; i < vertices; i++) {
            if (!visitado[i] &&
                distancia[i] < menor_distancia) {

                menor_distancia = distancia[i];
                atual = i;
            }
        }
    }

    int custo = 0;

    for (int i = 0; i < vertices; i++) {
        custo += distancia[i];
    }

    return custo;
}

int main() {
    int H, U, origem, destino, custo;
    string nome;
    double poder;

    cin >> H;

    list<Aresta> grafo[H];

    for (int i = 0; i < H; i++) {
        cin >> nome >> poder;
    }

    cin >> U;

    for (int i = 0; i < U; i++) {
        cin >> origem >> destino >> custo;

        grafo[origem].push_back({origem, destino, custo});
        grafo[destino].push_back({destino, origem, custo});
    }

    cout << prim_lista(grafo, H, 0) << endl;

    return 0;
}
````

## 3. Anatomia do código

### 3.1. Bibliotecas e constante

```
#include <iostream>
#include <list>
#include <string>
#define INF 999999
using namespace std;
```

- `iostream`: permite utilizar `cin` e `cout`.
    
- `list`: permite criar listas de adjacência.
    
- `string`: permite ler o nome das habilidades.
    
- `INF`: representa um valor inicial muito grande para as distâncias.
    

### 3.2. Estrutura da aresta

```
struct Aresta {
    int origem, destino, peso;
};
```

Cada aresta armazena três informações:

- `origem`: habilidade de onde parte o upgrade.
    
- `destino`: habilidade conectada.
    
- `peso`: custo de experiência necessário para o upgrade.
    

Por exemplo:

```
0 1 1
```

Representa uma conexão da habilidade `0` para a habilidade `1`, com custo `1`.

### 3.3. Função Prim

```
int prim_lista(list<Aresta> grafo[], int vertices, int origem)
```

A função recebe:

- `grafo`: lista de adjacência.
    
- `vertices`: quantidade de habilidades.
    
- `origem`: habilidade inicial, neste caso a Base (`0`).
    

Ela retorna um número inteiro com o custo total da árvore geradora mínima.

### 3.4. Arrays do algoritmo

```
bool visitado[vertices];
int pai[vertices], distancia[vertices], atual;
```

|Variável|Função|
|---|---|
|`visitado[i]`|Indica se a habilidade já entrou na árvore|
|`pai[i]`|Guarda a habilidade que conectou `i` à árvore|
|`distancia[i]`|Guarda o menor peso conhecido para conectar `i`|
|`atual`|Habilidade processada naquele momento|

**Atenção:** no Prim, `distancia[i]` não representa a distância acumulada desde a Base. Representa o peso da menor aresta conhecida que conecta a habilidade à árvore.

### 3.5. Inicialização

```
for (int i = 0; i < vertices; i++) {
    visitado[i] = false;
    pai[i] = -1;
    distancia[i] = INF;
}
```

Todas as habilidades começam fora da árvore, sem pai definido e com custo inicialmente infinito.

Depois:

```
atual = origem;
distancia[atual] = 0;
```

A habilidade inicial é a Base (`0`). Seu custo é zero porque ela não precisa de outro upgrade para entrar na árvore.

### 3.6. Laço principal

```
while (!visitado[atual]) {
    visitado[atual] = true;
```

Enquanto a habilidade atual não tiver sido visitada, ela é adicionada à árvore.

O operador `!` significa negação:

```
!visitado[atual]
```

Significa que a habilidade ainda não foi visitada.

### 3.7. Percorrendo os upgrades

```
list<Aresta>::iterator it;

for (it = grafo[atual].begin();
     it != grafo[atual].end(); it++) {

    int d = it->destino;
    int p = it->peso;

    if (!visitado[d] && p < distancia[d]) {
        distancia[d] = p;
        pai[d] = atual;
    }
}
```

O iterador `it` percorre as conexões da habilidade atual.

- `d` recebe o destino da aresta.
    
- `p` recebe o custo da aresta.
    
- A condição verifica se o destino ainda não está na árvore e se encontramos uma aresta mais barata.
    

Se a condição for verdadeira, atualizamos o custo de conexão:

```
distancia[d] = p;
pai[d] = atual;
```

Isso registra a melhor conexão conhecida para incluir essa habilidade na árvore.

### 3.8. Escolhendo a próxima habilidade

```
int menor_distancia = INF;

for (int i = 0; i < vertices; i++) {
    if (!visitado[i] &&
        distancia[i] < menor_distancia) {

        menor_distancia = distancia[i];
        atual = i;
    }
}
```

Depois de analisar os vizinhos, o Prim procura a habilidade ainda não visitada com o menor custo de conexão.

Esse processo se repete até que todas as habilidades alcançáveis tenham sido incluídas.

### 3.9. Somando o custo total

```
int custo = 0;

for (int i = 0; i < vertices; i++) {
    custo += distancia[i];
}

return custo;
```

A soma dos valores de `distancia` corresponde ao custo total da AGM, desde que o grafo seja conexo e todas as habilidades tenham sido incluídas.

A habilidade inicial contribui com zero.

## 4. Entendendo o `main()`

### 4.1. Leitura das habilidades

```
int H, U, origem, destino, custo;
string nome;
double poder;

cin >> H;

list<Aresta> grafo[H];

for (int i = 0; i < H; i++) {
    cin >> nome >> poder;
}
```

Primeiro, o programa lê a quantidade de habilidades.

Em seguida, cria o grafo e lê o nome e o poder de cada habilidade. Essas informações são consumidas da entrada, mas não são utilizadas no cálculo do custo mínimo.

### 4.2. Leitura dos upgrades

```
cin >> U;

for (int i = 0; i < U; i++) {
    cin >> origem >> destino >> custo;

    grafo[origem].push_back({origem, destino, custo});
    grafo[destino].push_back({destino, origem, custo});
}
```

O programa lê a quantidade de upgrades e, para cada um, recebe origem, destino e custo.

As duas inserções representam a conexão nos dois sentidos:

```
origem ↔ destino
```

Essa escolha é a adaptação ao modelo de grafo não direcionado utilizado pelo Prim.

### 4.3. Chamada da função

```
cout << prim_lista(grafo, H, 0) << endl;
```

A função é chamada com a habilidade `0` como origem. O valor retornado é impresso, sem mensagens adicionais, para respeitar o formato de saída.

## 5. Fluxo do algoritmo

```
flowchart TD
    A[Início] --> B[Ler habilidades]
    B --> C[Criar lista de adjacência]
    C --> D[Ler upgrades e custos]
    D --> E[Inicializar arrays do Prim]
    E --> F[Começar pela Base 0]
    F --> G[Marcar habilidade atual]
    G --> H[Analisar conexões]
    H --> I[Atualizar menores custos]
    I --> J[Escolher menor custo não visitado]
    J --> K{Todas incluídas?}
    K -->|Não| G
    K -->|Sim| L[Somar os custos]
    L --> M[Imprimir custo mínimo]
    M --> N[Fim]
```

## 6. Resumo para memorizar

```
1. Ler as habilidades e ignorar o poder no cálculo.
2. Criar a lista de adjacência.
3. Ler os upgrades e seus custos.
4. Inicializar as distâncias com INF.
5. Definir a Base (0) com custo zero.
6. Marcar a habilidade atual como visitada.
7. Atualizar os menores custos das conexões.
8. Escolher a próxima habilidade com menor custo.
9. Repetir até incluir todas as habilidades.
10. Somar os custos e imprimir o resultado.
```

**Linha fundamental do Prim:**

```
if (!visitado[d] && p < distancia[d]) {
    distancia[d] = p;
    pai[d] = atual;
}
```

Ela significa: se a habilidade ainda não estiver na árvore e encontramos uma conexão mais barata, atualizamos o custo para incluí-la.

```

```