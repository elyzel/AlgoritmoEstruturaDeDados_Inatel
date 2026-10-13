# Busca em Largura (BFS) com Lista de Adjacência

## 1. Enunciado do exercício

> [!question] Enunciado original
> Faça um programa que leia os dados dos vértices e arestas de um grafo não orientado, e os armazene em uma lista de adjacências. Depois, o programa deve mostrar o percurso em largura do grafo gerado.
>
> Faça uma função para implementar o percurso em largura. O cabeçalho desta função deve ser:
>
> `void bfs(list<no> adj[], int nVertices, int s)`
>
> O algoritmo de busca em largura é mostrado abaixo:
>
> ```text
> BFS(adj[], nVertices, s)
>     for u = 0 até nVertices-1
>         if u != s
>             state[u] = 'u'  // undiscovered
>             pai[u] = -1     // sem pais
>
>     state[s] = 'd'          // discovered
>     pai[s] = -1
>     Q.push_back(s)
>
>     while (!Q.empty())
>         u = *Q.begin()
>         Q.pop_front()
>         print u
>
>         for (p = adj[u].begin(); p != adj[u].end(); p++)
>             v = p->v
>             print (u, v)
>
>             if state[v] == 'u'
>                 state[v] = 'd'
>                 pai[v] = u
>                 Q.push_back(v)
>
>         state[u] = 'p'  // processed
> ```
>
> **Entrada**
>
> A entrada consiste de várias linhas:
>
> - A primeira linha contém dois inteiros: o primeiro corresponde ao número de vértices do grafo e o segundo ao vértice inicial.
> - As demais linhas contêm três inteiros, que correspondem ao vértice de origem, ao vértice de destino e ao peso de cada aresta, respectivamente.
> - A entrada termina quando ocorrer uma linha com três números iguais a `-1`. Essa linha não deve ser inserida no grafo.
>
> **Saída**
>
> A saída deverá mostrar os vértices e as arestas visitados, como no exemplo abaixo.
>
> **Exemplo de entrada**
>
> ```text
> 5 0
> 0 1 0
> 0 4 0
> 1 2 0
> 1 3 0
> 1 4 0
> 2 3 0
> 3 4 0
> -1 -1 -1
> ```
>
> **Exemplo de saída**
>
> ```text
> 0
> 0 1
> 0 4
> 1
> 1 0
> 1 2
> 1 3
> 1 4
> 4
> 4 0
> 4 1
> 4 3
> 2
> 2 1
> 2 3
> 3
> 3 1
> 3 2
> 3 4
> ```

---

## 2. Objetivo do programa

O objetivo é construir um grafo não orientado usando uma lista de adjacência e realizar uma busca em largura, também conhecida como BFS (*Breadth-First Search*).

A BFS começa em um vértice inicial e percorre o grafo utilizando uma fila.

Durante o percurso, o programa deve:

1. Imprimir o vértice que está sendo processado.
2. Percorrer e imprimir cada aresta da lista de adjacência desse vértice.
3. Descobrir os vizinhos que ainda não foram visitados.
4. Registrar o pai de cada novo vértice descoberto.
5. Adicionar os novos vértices à fila.
6. Terminar quando a fila estiver vazia.

### Estruturas utilizadas

| Estrutura | Finalidade |
|---|---|
| `struct Aresta` | Armazena origem, destino e peso de uma aresta. |
| `list<Aresta> grafo[]` | Representa a lista de adjacência do grafo. |
| `bool visitado[]` | Indica se cada vértice já foi descoberto. |
| `int pai[]` | Registra qual vértice descobriu cada vértice. |
| `list<int> fila_visitacao` | Guarda os vértices que aguardam processamento. |
| `list<Aresta>::iterator it` | Percorre as arestas de uma lista de adjacência. |

---

## 3. Código completo

~~~cpp
#include <iostream>
#include <list>

using namespace std;

struct Aresta {
    int origem, destino, peso;
};

void bfs(list<Aresta> adj[], int nVertices, int s) {

    bool visitado[nVertices];
    int pai[nVertices];

    list<int> fila_visitacao;
    list<Aresta>::iterator it;

    // Inicializa os vértices
    for (int i = 0; i < nVertices; i++) {
        visitado[i] = false;
        pai[i] = -1;
    }

    // Insere o vértice inicial na fila
    fila_visitacao.push_back(s);
    visitado[s] = true;

    while (!fila_visitacao.empty()) {

        // Consulta o primeiro vértice da fila
        int atual = fila_visitacao.front();

        // Remove o vértice da fila
        fila_visitacao.pop_front();

        // Imprime o vértice visitado
        cout << atual << endl;

        // Percorre as arestas do vértice atual
        for (it = adj[atual].begin();
             it != adj[atual].end(); it++) {

            int vizinho = it->destino;

            // Imprime a aresta examinada
            cout << atual << " " << vizinho << endl;

            // Se o vizinho ainda não foi descoberto
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                pai[vizinho] = atual;
                fila_visitacao.push_back(vizinho);
            }
        }
    }
}

int main() {

    int vertices, s;
    int origem, destino, peso;

    // Lê o número de vértices e o vértice inicial
    cin >> vertices >> s;

    list<Aresta> grafo[vertices];

    // Lê as arestas até encontrar o sentinela
    while (cin >> origem >> destino >> peso) {

        if (origem == -1 && destino == -1 && peso == -1) {
            break;
        }

        // Grafo não orientado: insere nos dois sentidos
        grafo[origem].push_back({origem, destino, peso});
        grafo[destino].push_back({destino, origem, peso});
    }

    // Executa a busca em largura
    bfs(grafo, vertices, s);

    return 0;
}
~~~

---

## 4. Explicação do código por blocos

### 4.1. Bibliotecas

~~~cpp
#include <iostream>
#include <list>

using namespace std;
~~~

- `iostream`: permite utilizar `cin` para leitura e `cout` para impressão.
- `list`: disponibiliza a estrutura de lista duplamente encadeada da biblioteca padrão C++.
- `using namespace std`: permite escrever `list`, `cin` e `cout` sem o prefixo `std::`.

A fila do programa será implementada usando uma `list<int>`, com inserção no final e remoção no início.

### 4.2. Estrutura `Aresta`

~~~cpp
struct Aresta {
    int origem, destino, peso;
};
~~~

A estrutura `Aresta` agrupa três informações referentes a uma aresta.

| Campo | Significado |
|---|---|
| `origem` | Vértice de onde a aresta parte. |
| `destino` | Vértice para o qual a aresta aponta. |
| `peso` | Peso associado à aresta. |

Por exemplo:

~~~cpp
{0, 1, 0}
~~~

Representa uma aresta de origem `0`, destino `1` e peso `0`.

Como o grafo é não orientado, cada aresta será armazenada nas listas dos dois vértices envolvidos.

### 4.3. Cabeçalho da função `void bfs()`

~~~cpp
void bfs(list<Aresta> adj[], int nVertices, int s)
~~~

Essa função recebe o grafo e executa o percurso em largura.

| Parte | Significado |
|---|---|
| `void` | Indica que a função não retorna um valor. |
| `bfs` | Nome da função. |
| `list<Aresta> adj[]` | Grafo representado por listas de adjacência. |
| `int nVertices` | Quantidade de vértices do grafo. |
| `int s` | Vértice inicial da busca. |

**Por que usar `void`?**

Uma função que retorna um valor poderia usar `int`, `bool` ou outro tipo. Neste exercício, a BFS imprime o percurso diretamente usando `cout`, sem precisar devolver um resultado.

Por isso, usamos `void`.

Isso não significa que a função não executa operações. Ela inicializa arrays, percorre listas, controla a fila e imprime a saída. Significa apenas que não devolve um valor ao terminar.

### 4.4. Arrays e fila de visitação

~~~cpp
bool visitado[nVertices];
int pai[nVertices];

list<int> fila_visitacao;
list<Aresta>::iterator it;
~~~

**`visitado[]`**

Guarda um valor booleano para cada vértice:

- `false`: o vértice ainda não foi descoberto.
- `true`: o vértice já foi descoberto.

**`pai[]`**

Armazena o vértice que descobriu cada vértice. O valor `-1` indica que não há pai registrado.

**`fila_visitacao`**

Guarda os vértices descobertos que ainda precisam ter suas listas de adjacência examinadas.

**`it`**

É um iterador que percorre uma lista de arestas. Como a lista armazena elementos do tipo `Aresta`, seu tipo é `list<Aresta>::iterator`.

### 4.5. Inicialização dos arrays

~~~cpp
for (int i = 0; i < nVertices; i++) {
    visitado[i] = false;
    pai[i] = -1;
}
~~~

O laço percorre todos os vértices, de `0` até `nVertices - 1`.

A cada repetição:

- `visitado[i] = false` marca o vértice como ainda não descoberto.
- `pai[i] = -1` informa que ainda não há pai registrado.

Para um grafo com cinco vértices:

| `i` | `visitado[i]` | `pai[i]` |
|---:|---|---:|
| 0 | `false` | -1 |
| 1 | `false` | -1 |
| 2 | `false` | -1 |
| 3 | `false` | -1 |
| 4 | `false` | -1 |

### 4.6. Inserção do vértice inicial

~~~cpp
fila_visitacao.push_back(s);
visitado[s] = true;
~~~

Supondo que `s = 0`:

1. `push_back(s)` insere o vértice `0` no final da fila.
2. `visitado[s] = true` marca o vértice inicial como descoberto.

A fila passa a ser:

~~~text
[0]
~~~

O vértice inicial já é marcado como descoberto para impedir que uma aresta de retorno o coloque novamente na fila.

### 4.7. A condição `while (!fila_visitacao.empty())`

~~~cpp
while (!fila_visitacao.empty()) {
~~~

Esse laço mantém a BFS funcionando enquanto houver vértices aguardando processamento.

Vamos separar a expressão:

**`fila_visitacao.empty()`**

O método `empty()` verifica se a fila está vazia.

| Fila | Resultado de `empty()` |
|---|---|
| `[0, 1, 4]` | `false` |
| `[1, 4]` | `false` |
| `[4]` | `false` |
| `[]` | `true` |

**O operador `!`**

O símbolo `!` é a negação lógica. Ele inverte um valor booleano.

| Expressão | Resultado |
|---|---|
| `!true` | `false` |
| `!false` | `true` |

Portanto, `!fila_visitacao.empty()` significa que a fila não está vazia.

| Situação | `empty()` | `!empty()` | Ação do `while` |
|---|---|---|---|
| Há elementos na fila | `false` | `true` | Continua |
| A fila está vazia | `true` | `false` | Termina |

O `while` é necessário porque cada vértice descoberto pode revelar novos vizinhos. O algoritmo continua até não existir mais nenhum vértice aguardando processamento.

### 4.8. Consulta e remoção do primeiro vértice

~~~cpp
int atual = fila_visitacao.front();
fila_visitacao.pop_front();
~~~

A primeira linha consulta o primeiro elemento da fila e guarda seu valor em `atual`.

A segunda linha remove esse elemento da fila.

Exemplo:

| Operação | Fila | `atual` |
|---|---|---:|
| Estado inicial | `[0, 1, 4]` | — |
| `front()` | `[0, 1, 4]` | 0 |
| `pop_front()` | `[1, 4]` | 0 |

`front()` não remove o elemento; `pop_front()` remove.

Essa ordem garante que o programa guarde o vértice antes de removê-lo da fila.

### 4.9. Impressão do vértice

~~~cpp
cout << atual << endl;
~~~

Imprime o vértice que está sendo processado.

Se `atual = 0`, a saída será:

~~~text
0
~~~

Essa linha não representa uma aresta. Ela indica qual vértice foi retirado da fila para ter seus vizinhos examinados.

### 4.10. Percorrendo as arestas com o iterador

~~~cpp
for (it = adj[atual].begin();
     it != adj[atual].end(); it++) {

    int vizinho = it->destino;

    cout << atual << " " << vizinho << endl;
~~~

Esse `for` percorre todas as arestas armazenadas na lista de adjacência do vértice atual.

| Expressão | Função |
|---|---|
| `adj[atual]` | Seleciona a lista de adjacência do vértice atual. |
| `.begin()` | Obtém um iterador para o primeiro elemento. |
| `it != adj[atual].end()` | Verifica se o iterador ainda não chegou ao final. |
| `it++` | Avança para a próxima aresta. |
| `it->destino` | Acessa o destino da aresta atual. |

A expressão `it->destino` é uma forma de acessar o campo `destino` do objeto apontado pelo iterador. Ela equivale a `(*it).destino`.

Se a lista de adjacência de `0` contiver os destinos `1` e `4`, o programa imprimirá:

~~~text
0 1
0 4
~~~

A ordem depende da ordem em que as arestas foram inseridas na lista.

### 4.11. Descobrindo os vizinhos: o bloco do `if`

~~~cpp
if (!visitado[vizinho]) {
    visitado[vizinho] = true;
    pai[vizinho] = atual;
    fila_visitacao.push_back(vizinho);
}
~~~

Esse bloco decide se o vizinho precisa ser adicionado à fila.

**Primeira linha: verificar se ainda não foi descoberto**

~~~cpp
if (!visitado[vizinho]) {
~~~

A condição só é verdadeira quando `visitado[vizinho]` é `false`.

Por exemplo:

| `visitado[vizinho]` | `!visitado[vizinho]` | Resultado |
|---|---|---|
| `false` | `true` | Entra no `if`. |
| `true` | `false` | Ignora o bloco. |

**Segunda linha: marcar como descoberto**

~~~cpp
visitado[vizinho] = true;
~~~

Marca o vizinho imediatamente, antes de colocá-lo na fila. Assim, se outra aresta encontrar o mesmo vértice, ele não será adicionado novamente.

**Terceira linha: registrar o pai**

~~~cpp
pai[vizinho] = atual;
~~~

Registra qual vértice descobriu o vizinho pela primeira vez.

Se o vértice atual for `0` e o vizinho for `1`, teremos `pai[1] = 0`.

**Quarta linha: adicionar à fila**

~~~cpp
fila_visitacao.push_back(vizinho);
~~~

Insere o vizinho no final da fila, para que ele seja processado posteriormente.

#### Exemplo passo a passo

Suponha que o vértice atual seja `0`, com vizinhos `1` e `4`.

Inicialmente, ambos ainda não foram descobertos.

| Operação | Vizinho 1 | Vizinho 4 | Fila |
|---|---|---|---|
| Estado inicial | `false` | `false` | `[]` |
| Descobre 1 | `true` | `false` | `[1]` |
| Descobre 4 | `true` | `true` | `[1, 4]` |

O array `pai` também passa a conter:

| Vértice | Pai |
|---:|---:|
| 0 | -1 |
| 1 | 0 |
| 4 | 0 |

**Por que marcar antes de inserir na fila?**

Imagine que o vértice `1` possui uma aresta de volta para `0`. Como `0` já foi marcado como descoberto, essa aresta não o adicionará novamente à fila.

Essa regra impede descobertas repetidas e é essencial para que a BFS funcione corretamente em grafos com ciclos.

### 4.12. Fim do percurso

Quando a fila fica vazia, a condição `!fila_visitacao.empty()` torna-se falsa e o `while` termina.

A função `bfs()` chega ao fim. Como seu tipo de retorno é `void`, não precisa de uma instrução `return` com valor.

---

## 5. Como o `main()` funciona

### 5.1. Leitura dos dados iniciais

~~~cpp
int vertices, s;
int origem, destino, peso;

cin >> vertices >> s;
~~~

A primeira linha da entrada contém:

- `vertices`: quantidade de vértices.
- `s`: vértice inicial da BFS.

No exemplo, `vertices = 5` e `s = 0`.

### 5.2. Criação da lista de adjacência

~~~cpp
list<Aresta> grafo[vertices];
~~~

Cria uma lista de adjacência para cada vértice. Cada lista armazena objetos do tipo `Aresta`.

### 5.3. Leitura das arestas

~~~cpp
while (cin >> origem >> destino >> peso) {

    if (origem == -1 && destino == -1 && peso == -1) {
        break;
    }

    grafo[origem].push_back({origem, destino, peso});
    grafo[destino].push_back({destino, origem, peso});
}
~~~

O `while` lê três valores por linha até encontrar o sentinela `-1 -1 -1`.

O `break` encerra a leitura sem inserir o sentinela no grafo.

Como o grafo é não orientado, cada aresta é inserida nos dois sentidos. Por exemplo, a entrada `0 1 0` gera:

- Uma aresta na lista de `0`, com destino `1`.
- Uma aresta na lista de `1`, com destino `0`.

O peso é armazenado, mas não interfere no algoritmo BFS deste exercício.

### 5.4. Chamada da função

~~~cpp
bfs(grafo, vertices, s);
~~~

Essa instrução chama a função, passando o grafo, a quantidade de vértices e o vértice inicial.

A execução passa para `bfs()` e, quando a função termina, o programa chega a `return 0;`, encerrando normalmente o `main()`.

---

## 6. Rastreamento da execução

Para a entrada do exemplo, a lista de adjacência fica assim:

| Vértice | Vizinhos na ordem de inserção |
|---:|---|
| 0 | 1, 4 |
| 1 | 0, 2, 3, 4 |
| 2 | 1, 3 |
| 3 | 1, 2, 4 |
| 4 | 0, 1, 3 |

A BFS começa no vértice `0`.

| Vértice processado | Vizinhos examinados | Novas descobertas | Fila após o processamento |
|---:|---|---|---|
| 0 | 1, 4 | 1, 4 | `[1, 4]` |
| 1 | 0, 2, 3, 4 | 2, 3 | `[4, 2, 3]` |
| 4 | 0, 1, 3 | Nenhuma | `[2, 3]` |
| 2 | 1, 3 | Nenhuma | `[3]` |
| 3 | 1, 2, 4 | Nenhuma | `[]` |

Observe que os vértices `0`, `1`, `2`, `3` e `4` são processados uma única vez.

As arestas de retorno também são impressas, pois o programa imprime cada aresta examinada antes de verificar se o destino já foi descoberto.

---

## 7. Fluxograma do programa

~~~mermaid
flowchart TD
    A([Início]) --> B[Ler quantidade de vértices e origem]
    B --> C[Criar lista de adjacência]
    C --> D[Ler origem, destino e peso]
    D --> E{Entrada é -1 -1 -1?}
    E -- Não --> F[Inserir aresta nos dois sentidos]
    F --> D
    E -- Sim --> G[Chamar bfs]
    G --> H[Inicializar visitado e pai]
    H --> I[Inserir origem na fila]
    I --> J{Fila vazia?}
    J -- Não --> K[Consultar e remover primeiro vértice]
    K --> L[Imprimir vértice]
    L --> M[Percorrer arestas adjacentes]
    M --> N[Imprimir aresta]
    N --> O{Vizinho não descoberto?}
    O -- Sim --> P[Marcar, registrar pai e inserir na fila]
    O -- Não --> Q{Há outra aresta?}
    P --> Q
    Q -- Sim --> N
    Q -- Não --> J
    J -- Sim --> R([Fim])
~~~

---

## 8. Resumo dos conceitos

- **`void`:** define uma função que não retorna um valor.
- **Lista de adjacência:** representa os vizinhos de cada vértice.
- **`visitado[]`:** impede que um vértice seja descoberto repetidamente.
- **`pai[]`:** registra de qual vértice cada vértice foi descoberto.
- **Fila:** garante que os vértices sejam processados na ordem em que foram descobertos.
- **`empty()`:** verifica se a fila está vazia.
- **`!`:** nega o resultado de uma expressão booleana.
- **`front()`:** consulta o primeiro elemento da fila.
- **`pop_front()`:** remove o primeiro elemento.
- **`push_back()`:** insere um elemento no final.
- **Iterador:** percorre os elementos de uma lista.
- **`it->destino`:** acessa o destino da aresta atual.
- **`pai[vizinho] = atual`:** registra quem descobriu o vizinho.
- **Grafo não orientado:** cada aresta é armazenada nos dois sentidos.

### Complexidade

Considerando `V` vértices e `E` arestas:

- **Tempo:** `O(V + E)`, pois cada vértice é processado uma vez e cada lista de adjacência é percorrida.
- **Espaço auxiliar:** `O(V)` para os arrays e a fila.
- **Espaço total do grafo:** `O(V + E)`.

A ideia central da BFS é: **retirar um vértice da fila, examinar seus vizinhos, descobrir os que ainda não foram visitados e adicioná-los ao final da fila. O processo termina quando a fila fica vazia.**