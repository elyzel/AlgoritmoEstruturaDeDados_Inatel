# 🧠 Verificar se um grafo é conexo usando BFS com `void`

> [!question] Enunciado original
> Como vimos, é possível saber se um grafo é conexo usando um percurso em largura: se todos os vértices forem visitados, então o grafo é conexo.
>
> Faça um programa que faça uso do algoritmo de busca em largura e verifique se um dado grafo é ou não conexo.
>
> **Entrada**
>
> A entrada consiste de várias linhas:
>
> A primeira linha contém 2 inteiros:
>
> - O primeiro corresponde ao número de vértices do grafo. Você pode considerar que a rede não tem mais que 10 vértices.
> - O segundo identifica o vértice inicial (`start`).
>
> As demais linhas têm dois números inteiros, que correspondem aos vértices de origem e destino de uma aresta.
>
> A entrada de dados termina quando ocorrer uma linha com dois números iguais a `-1` (que não deve ser considerada).
>
> **Saída**
>
> Na saída, o programa deve dizer se o grafo é ou não conexo.
>
> **Observação:** para este problema, considere que o grafo é não direcionado, e que cada aresta tem peso 1.
>
> **Exemplo de entrada**
>
> ```text
> 9 0
> 0 1
> 0 7
> 1 2
> 1 7
> 2 3
> 2 5
> 2 8
> 3 4
> 3 5
> 4 5
> 5 6
> 6 7
> 6 8
> 7 8
> -1 -1
> ```
>
> **Saída esperada**
>
> ```text
> Conexo
> ```

---

## 🎯 Objetivo

Verificar se todos os vértices de um grafo não direcionado podem ser alcançados a partir de um vértice inicial, utilizando a busca em largura (BFS).

- Se todos os vértices forem visitados, o grafo é conexo.
- Se pelo menos um vértice não for visitado, o grafo não é conexo.

Neste exercício, a função `bfs` utiliza `void`, portanto não retorna diretamente `true` ou `false`. O resultado é comunicado por meio da variável global `conexo`.

---

## 💻 Código completo em C++

~~~cpp
#include <iostream>
#include <list>

using namespace std;

struct Aresta {
    int origem, destino, peso;
};

bool visitado[10];
bool conexo = true;

void bfs(list<Aresta> grafo[], int nVertices, int s) {

    list<int> fila_visitacao;
    list<Aresta>::iterator it;

    for (int i = 0; i < nVertices; i++) {
        visitado[i] = false;
    }

    fila_visitacao.push_back(s);
    visitado[s] = true;

    while (!fila_visitacao.empty()) {
        int atual = fila_visitacao.front();
        fila_visitacao.pop_front();

        for (it = grafo[atual].begin();
             it != grafo[atual].end(); it++) {

            int vizinho = it->destino;

            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila_visitacao.push_back(vizinho);
            }
        }
    }

    for (int i = 0; i < nVertices; i++) {
        if (!visitado[i]) {
            conexo = false;
            break;
        }
    }
}

int main() {
    int vertices, s;
    int origem, destino;

    cin >> vertices >> s;

    list<Aresta> grafo[vertices];

    while (cin >> origem >> destino) {
        if (origem == -1 && destino == -1) {
            break;
        }

        grafo[origem].push_back({origem, destino, 1});
        grafo[destino].push_back({destino, origem, 1});
    }

    bfs(grafo, vertices, s);

    if (conexo) {
        cout << "Conexo" << endl;
    } else {
        cout << "Nao conexo" << endl;
    }

    return 0;
}
~~~

---

## 1. Estrutura da aresta

~~~cpp
struct Aresta {
    int origem, destino, peso;
};
~~~

Define a estrutura de uma aresta, com três informações:

| Campo | Significado |
|---|---|
| `origem` | Vértice de onde parte a aresta |
| `destino` | Vértice ao qual a aresta chega |
| `peso` | Peso da aresta |

Embora o enunciado informe que o peso é `1`, mantemos esse campo para seguir o padrão utilizado nos exercícios anteriores.

## 2. Variáveis globais

~~~cpp
bool visitado[10];
bool conexo = true;
~~~

### `visitado[10]`

Armazena se cada vértice já foi visitado.

- `false`: o vértice ainda não foi visitado.
- `true`: o vértice já foi visitado.

O limite de 10 posições corresponde à restrição do enunciado.

### `conexo`

Começa com `true`, assumindo inicialmente que o grafo é conexo.

Se, depois da BFS, existir algum vértice não visitado, a variável passa a ser `false`.

Como ela é global, pode ser acessada tanto pela função `bfs` quanto pela função `main`.

## 3. Por que a função usa `void`?

~~~cpp
void bfs(list<Aresta> grafo[], int nVertices, int s)
~~~

- `void`: significa que a função não retorna um valor diretamente.
- `grafo[]`: recebe a lista de adjacência do grafo.
- `nVertices`: quantidade de vértices.
- `s`: vértice inicial da busca.

A função executa a BFS e atualiza a variável global `conexo` para informar o resultado.

**Comparação:**

| Tipo de função | Como comunica o resultado |
|---|---|
| `bool bfs(...)` | Retorna `true` ou `false` com `return` |
| `void bfs(...)` | Pode atualizar uma variável global ou uma variável passada por referência |

## 4. Criando a fila e o iterador

~~~cpp
list<int> fila_visitacao;
list<Aresta>::iterator it;
~~~

A fila controla a ordem em que os vértices serão visitados.

| Operação | Função |
|---|---|
| `push_back(x)` | Insere `x` no final da fila |
| `front()` | Consulta o primeiro elemento |
| `pop_front()` | Remove o primeiro elemento |
| `empty()` | Retorna `true` se a fila estiver vazia |

O iterador `it` permite percorrer as arestas armazenadas na lista de adjacência de cada vértice.

## 5. Inicializando os vértices

~~~cpp
for (int i = 0; i < nVertices; i++) {
    visitado[i] = false;
}
~~~

Antes de começar a busca, todos os vértices são marcados como não visitados.

Por exemplo, se o grafo tiver 5 vértices:

| Vértice | `visitado[i]` inicial |
|---:|:---:|
| 0 | `false` |
| 1 | `false` |
| 2 | `false` |
| 3 | `false` |
| 4 | `false` |

## 6. Começando a BFS

~~~cpp
fila_visitacao.push_back(s);
visitado[s] = true;
~~~

Duas operações acontecem:

1. O vértice inicial `s` é inserido na fila.
2. Ele é marcado como visitado.

Marcamos o vértice antes de inseri-lo na fila para evitar que ele seja adicionado novamente por outra aresta.

## 7. Enquanto a fila não estiver vazia

~~~cpp
while (!fila_visitacao.empty()) {
    int atual = fila_visitacao.front();
    fila_visitacao.pop_front();
~~~

### Entendendo `empty()`

O método `empty()` verifica se a fila está vazia.

- `fila_visitacao.empty()` resulta em `true` quando não há elementos.
- `!fila_visitacao.empty()` significa que a fila **não está vazia**.

Portanto, o `while` continua executando enquanto houver vértices aguardando processamento.

### Exemplo

| Estado da fila | `empty()` | `!empty()` | Continua? |
|---|:---:|:---:|:---:|
| `[0, 1, 4]` | `false` | `true` | Sim |
| `[1, 4]` | `false` | `true` | Sim |
| `[4]` | `false` | `true` | Sim |
| `[]` | `true` | `false` | Não |

A cada repetição, `front()` consulta o primeiro vértice e `pop_front()` o remove para processamento.

## 8. Percorrendo os vizinhos

~~~cpp
for (it = grafo[atual].begin();
     it != grafo[atual].end(); it++) {

    int vizinho = it->destino;
~~~

O `for` percorre todas as arestas que saem do vértice `atual` na lista de adjacência.

- `grafo[atual].begin()`: início da lista.
- `grafo[atual].end()`: posição após o último elemento.
- `it++`: avança para a próxima aresta.
- `it->destino`: obtém o vértice vizinho.

## 9. Visitando cada vizinho apenas uma vez

~~~cpp
if (!visitado[vizinho]) {
    visitado[vizinho] = true;
    fila_visitacao.push_back(vizinho);
}
~~~

Essa é uma das partes mais importantes do algoritmo.

1. `!visitado[vizinho]`: verifica se o vizinho ainda não foi visitado.
2. `visitado[vizinho] = true`: marca o vizinho como visitado.
3. `fila_visitacao.push_back(vizinho)`: adiciona o vizinho à fila para processamento posterior.

A marcação ocorre antes da inserção na fila. Assim, se o mesmo vértice for encontrado por outra aresta, ele não será colocado novamente na fila.

## 10. Verificando se o grafo é conexo

~~~cpp
for (int i = 0; i < nVertices; i++) {
    if (!visitado[i]) {
        conexo = false;
        break;
    }
}
~~~

Depois que a fila fica vazia, a BFS terminou. Agora verificamos todos os vértices.

- Se algum vértice não foi visitado, `conexo` recebe `false`.
- `break` encerra o `for` imediatamente, pois já sabemos que o grafo não é conexo.
- Se todos foram visitados, `conexo` continua `true`.

## 11. Por que não usamos `return` na BFS?

A função é `void`, então não pode retornar um valor como `true` ou `false`.

Em vez disso, o resultado fica armazenado na variável global `conexo`.

~~~cpp
if (conexo) {
    cout << "Conexo" << endl;
} else {
    cout << "Nao conexo" << endl;
}
~~~

No `main`, depois de executar a BFS, o programa consulta essa variável e imprime o resultado.

## 12. Construindo o grafo não direcionado

~~~cpp
grafo[origem].push_back({origem, destino, 1});
grafo[destino].push_back({destino, origem, 1});
~~~

Como o grafo é não direcionado, cada aresta precisa ser armazenada nos dois sentidos.

Se a entrada tiver:

~~~text
0 1
~~~

O programa armazena:

- Uma aresta de `0` para `1`.
- Uma aresta de `1` para `0`.

Isso permite que a BFS percorra o grafo em qualquer direção.

## 13. Encerramento da entrada

~~~cpp
if (origem == -1 && destino == -1) {
    break;
}
~~~

Quando o programa lê `-1 -1`, ele interrompe a leitura.

Essa linha é apenas um marcador de fim da entrada e não deve ser adicionada ao grafo.

---

## 🔎 Exemplo de execução

No exemplo do enunciado, o vértice inicial é `0`.

A BFS começa em `0`, descobre seus vizinhos e continua explorando os vértices alcançáveis.

| Etapa | Vértices processados | Resultado |
|---|---|---|
| 1 | `0` | Descobre `1` e `7` |
| 2 | `1` | Descobre `2` |
| 3 | `7` | Descobre `6` e `8` |
| 4 | `2` | Descobre `3` e `5` |
| 5 | `6` | Não encontra novos vértices |
| 6 | `8` | Não encontra novos vértices |
| 7 | `3` | Descobre `4` |
| 8 | `5` | Não encontra novos vértices |
| 9 | `4` | Não encontra novos vértices |

Ao final, os vértices `0` até `8` estão marcados como visitados.

Por isso, a saída é:

~~~text
Conexo
~~~

## 🔀 Fluxograma da solução

~~~mermaid
flowchart TD
    A[Início] --> B[Ler vértices e origem]
    B --> C[Construir lista de adjacência]
    C --> D[Inicializar visitado como false]
    D --> E[Inserir origem na fila]
    E --> F[Executar BFS]
    F --> G{Fila vazia?}
    G -- Não --> H[Remover primeiro vértice]
    H --> I[Examinar vizinhos]
    I --> J[Marcar e inserir vizinhos não visitados]
    J --> G
    G -- Sim --> K[Verificar todos os vértices]
    K --> L{Todos visitados?}
    L -- Sim --> M[Imprimir Conexo]
    L -- Não --> N[Imprimir Nao conexo]
    M --> O[Fim]
    N --> O
~~~

---

## 📌 Resumo dos conceitos

| Conceito | Para que serve |
|---|---|
| BFS | Percorrer o grafo a partir de um vértice inicial |
| Lista de adjacência | Armazenar as arestas de cada vértice |
| Fila | Controlar a ordem de processamento |
| `visitado[]` | Evitar visitar um vértice repetidamente |
| `empty()` | Verificar se a fila está vazia |
| `void` | Indicar que a função não retorna um valor |
| Variável global `conexo` | Comunicar o resultado da BFS ao `main` |
| `break` | Interromper o laço quando um vértice não visitado é encontrado |

## ⏱️ Complexidade

Usando lista de adjacência:

- **Tempo:** `O(V + E)`, em que `V` é o número de vértices e `E` o número de arestas.
- **Espaço:** `O(V + E)` para armazenar o grafo; a fila e o vetor de visitados ocupam `O(V)`.

**Ideia central para a prova:** um grafo não direcionado é conexo se, a partir de qualquer vértice inicial, a BFS conseguir visitar todos os vértices.