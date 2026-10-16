# Dijkstra — Regiões Alagadas

> [!question] Problema
> O prefeito de Anatriacé precisa descobrir quais regiões estão a mais de **15 km** da bomba de drenagem.  
> O programa deve calcular a menor distância entre a bomba e todas as regiões e informar quais regiões continuam alagadas.

---

## 1. Ideia do problema

O problema pede a **menor distância da bomba até cada região**.

Como as conexões possuem **pesos (distâncias em km)**, utilizamos o algoritmo de **Dijkstra**.

### Por que Dijkstra?

- **BFS** → trabalha naturalmente com arestas sem pesos.
- **Prim** → constrói uma árvore geradora mínima.
- **Dijkstra** → encontra o menor caminho a partir de uma origem para os demais vértices.

Neste problema:

```text
Bomba
  ↓
Dijkstra
  ↓
Menor distância para cada região
  ↓
distância > 15 ?
  ↓
Região alagada
````

---

# 2. Código completo

```cpp
#define INF 99999

#include <iostream>
#include <list>
using namespace std;

struct Aresta {
    int origem, destino, peso;
};

void dijkstra_lista(list<Aresta> grafo[], int vertices, int origem) {

    bool visitado[vertices];
    int distancia[vertices];
    int atual;

    list<Aresta>::iterator it;

    // Inicialização
    for (int i = 0; i < vertices; i++) {
        visitado[i] = false;
        distancia[i] = INF;
    }

    // A distância da bomba até ela mesma é 0
    distancia[origem] = 0;

    atual = origem;

    // Dijkstra
    while (!visitado[atual]) {

        visitado[atual] = true;

        // Percorre as conexões da região atual
        for (it = grafo[atual].begin();
             it != grafo[atual].end();
             it++) {

            int d = it->destino;
            int p = it->peso;

            // Verifica se encontramos um caminho menor
            if (!visitado[d] &&
                distancia[atual] + p < distancia[d]) {

                distancia[d] = distancia[atual] + p;
            }
        }

        // Procura a próxima região com menor distância
        int menor_distancia = INF;

        for (int i = 0; i < vertices; i++) {

            if (!visitado[i] &&
                distancia[i] < menor_distancia) {

                menor_distancia = distancia[i];
                atual = i;
            }
        }
    }

    // Verifica quais regiões estão a mais de 15 km
    bool alagada = false;

    for (int i = 0; i < vertices; i++) {

        if (distancia[i] > 15) {
            cout << i << endl;
            alagada = true;
        }
    }

    if (!alagada) {
        cout << "Nenhuma regiao alagada" << endl;
    }
}

int main() {

    int vertices, arestas;
    int origem, destino, peso;
    int bomba;

    cin >> vertices;
    cin >> arestas;

    list<Aresta> grafo[vertices];

    // Leitura das conexões
    for (int i = 0; i < arestas; i++) {

        cin >> origem >> destino >> peso;

        grafo[origem].push_back({origem, destino, peso});
    }

    // Região onde está a bomba
    cin >> bomba;

    dijkstra_lista(grafo, vertices, bomba);

    return 0;
}
```

---

# 3. Anatomia do código

## 3.1 Constante `INF`

```
#define INF 99999
```

`INF` representa uma distância inicialmente muito grande.

Usamos isso porque, no início, ainda não sabemos a distância entre a origem e as outras regiões.

```
distância conhecida
       ↓
   0 para a bomba

outras regiões
       ↓
    INF
```

---

## 3.2 Bibliotecas

```
#include <iostream>
#include <list>
using namespace std;
```

### `iostream`

Permite utilizar:

```
cin
cout
```

### `list`

Permite utilizar a lista encadeada:

```
list<Aresta>
```

Ela será utilizada para representar a **lista de adjacência** do grafo.

---

# 4. Estrutura da aresta

```
struct Aresta {
    int origem, destino, peso;
};
```

Cada aresta possui três informações:

```
origem  → região de onde sai a conexão
destino → região para onde vai
peso    → distância da conexão
```

Por exemplo:

```
0 2 9
```

significa:

```
origem  = 0
destino = 2
peso    = 9 km
```

---

# 5. Função Dijkstra

```
void dijkstra_lista(list<Aresta> grafo[], int vertices, int origem)
```

A função recebe:

```
grafo    → lista de adjacência
vertices → quantidade de regiões
origem   → região onde está a bomba
```

A função é `void` porque não precisa retornar uma distância específica.

Ela calcula as distâncias e já verifica quais regiões estão alagadas.

---

# 6. Arrays utilizados

```
bool visitado[vertices];
int distancia[vertices];
int atual;
```

## `visitado`

Indica se uma região já foi processada pelo Dijkstra.

```
false → ainda não processada
true  → já processada
```

## `distancia`

Guarda a menor distância conhecida entre a bomba e cada região.

Exemplo:

```
Região:       0    1    2    3
Distância:    0    5    9   10
```

## `atual`

Guarda a região que estamos processando naquele momento.

---

# 7. Iterador

```
list<Aresta>::iterator it;
```

O iterador permite percorrer uma lista de arestas.

Ele será usado para acessar todas as conexões de uma determinada região.

---

# 8. Inicialização

```
for (int i = 0; i < vertices; i++) {
    visitado[i] = false;
    distancia[i] = INF;
}
```

Inicialmente:

```
Todas as regiões → não visitadas
Todas as distâncias → INF
```

Por exemplo, com 5 regiões:

```
Região       0    1    2    3    4
Visitado   false false false false false
Distância   INF  INF  INF  INF  INF
```

---

# 9. Definindo a origem

```
distancia[origem] = 0;
atual = origem;
```

A bomba é o ponto de partida.

A distância dela até ela mesma é:

```
0 km
```

Por isso:

```
distancia[origem] = 0;
```

E começamos o algoritmo nessa região:

```
atual = origem;
```

---

# 10. Laço principal do Dijkstra

```
while (!visitado[atual]) {
```

Enquanto a região atual ainda não tiver sido processada, executamos o algoritmo.

O `!` significa **negação**.

Portanto:

```
!visitado[atual]
```

significa:

> "A região atual ainda não foi visitada?"

---

# 11. Marcando a região

```
visitado[atual] = true;
```

Agora a região atual foi processada.

```
visitado[atual]
      ↓
    true
```

---

# 12. Percorrendo os vizinhos

```
for (it = grafo[atual].begin();
     it != grafo[atual].end();
     it++) {
```

Aqui percorremos todas as arestas que saem da região `atual`.

### `begin()`

Começa no primeiro elemento da lista.

### `end()`

Representa o final da lista.

### `it++`

Avança para a próxima aresta.

Visualmente:

```
grafo[atual]

[aresta 1] → [aresta 2] → [aresta 3] → fim
     ↑
    it
```

---

# 13. Obtendo destino e peso

```
int d = it->destino;
int p = it->peso;
```

Aqui simplificamos o acesso às informações da aresta.

```
d → destino
p → peso
```

Se tivermos:

```
2 → 6 com peso 2
```

então:

```
d = 6
p = 2
```

---

# 14. Relaxamento do Dijkstra

```
if (!visitado[d] &&
    distancia[atual] + p < distancia[d]) {

    distancia[d] = distancia[atual] + p;
}
```

Essa é a parte **mais importante do Dijkstra**.

A expressão:

```
distancia[atual] + p
```

calcula quanto custaria chegar ao destino passando pela região atual.

Depois comparamos:

```
distancia[atual] + p < distancia[d]
```

Pergunta:

> Encontramos um caminho menor para `d`?

Se sim:

```
distancia[d] = distancia[atual] + p;
```

A menor distância é atualizada.

---

# 15. Exemplo do relaxamento

Imagine:

```
0 ──9── 2 ──2── 6
```

Começando em `0`:

```
distância[0] = 0
```

Ao analisar a aresta:

```
0 → 2
peso = 9
```

calculamos:

```
distância[0] + 9
0 + 9
= 9
```

Então:

```
distância[2] = 9
```

Depois chegamos à região `2`.

A aresta:

```
2 → 6
peso = 2
```

produz:

```
distância[2] + 2
9 + 2
= 11
```

Então:

```
distância[6] = 11
```

---

# 16. Escolhendo a próxima região

Depois de analisar os vizinhos:

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

Agora o algoritmo procura:

> Qual região ainda não foi visitada e possui a menor distância conhecida?

Por exemplo:

```
Região       0    1    2    3    4
Distância    0    5    9   10   INF
Visitado    sim  não  não  não  não
```

A menor distância entre as regiões não visitadas é:

```
5
```

Então:

```
atual = 1
```

O Dijkstra passa a processar a região `1`.

---

# 17. Por que essa parte é importante?

O Dijkstra funciona repetidamente assim:

```
1. Escolhe a região atual
          ↓
2. Marca como visitada
          ↓
3. Analisa seus vizinhos
          ↓
4. Atualiza distâncias menores
          ↓
5. Escolhe a menor distância ainda não visitada
          ↓
6. Repete
```

---

# 18. Verificando as regiões alagadas

Depois que o Dijkstra termina:

```
bool alagada = false;

for (int i = 0; i < vertices; i++) {

    if (distancia[i] > 15) {
        cout << i << endl;
        alagada = true;
    }
}
```

Agora não estamos mais executando o Dijkstra.

Estamos apenas analisando o resultado.

A regra do problema é:

```
distância ≤ 15 km
        ↓
região atendida

distância > 15 km
        ↓
região alagada
```

Por isso:

```
if (distancia[i] > 15)
```

---

# 19. Caso nenhuma região esteja alagada

```
if (!alagada) {
    cout << "Nenhuma regiao alagada" << endl;
}
```

A variável começa como:

```
bool alagada = false;
```

Se encontrarmos alguma região com mais de 15 km:

```
alagada = true;
```

Se terminarmos o `for` e ela continuar `false`, nenhuma região ultrapassou os 15 km.

---

# 20. `main()`

```
int main() {

    int vertices, arestas;
    int origem, destino, peso;
    int bomba;
```

Criamos as variáveis para receber os dados do problema.

```
vertices → quantidade de regiões
arestas  → quantidade de conexões
origem   → região de origem
destino  → região de destino
peso     → distância do cano
bomba    → região onde está a bomba
```

---

# 21. Leitura dos vértices e arestas

```
cin >> vertices;
cin >> arestas;
```

Primeiro recebemos:

```
quantidade de regiões
quantidade de conexões
```

---

# 22. Criando a lista de adjacência

```
list<Aresta> grafo[vertices];
```

Criamos uma lista para cada região.

Exemplo:

```
grafo[0] → conexões da região 0
grafo[1] → conexões da região 1
grafo[2] → conexões da região 2
...
```

Isso representa o grafo usando **lista de adjacência**.

---

# 23. Lendo as conexões

```
for (int i = 0; i < arestas; i++) {

    cin >> origem >> destino >> peso;

    grafo[origem].push_back({origem, destino, peso});
}
```

Para cada conexão recebemos:

```
origem destino peso
```

E colocamos a aresta na lista correspondente à origem.

Por exemplo:

```
0 2 9
```

gera:

```
grafo[0]
   ↓
(0, 2, 9)
```

---

# 24. Região da bomba

```
cin >> bomba;
```

Depois das conexões, recebemos a região onde está a bomba.

Essa região será a origem do Dijkstra.

---

# 25. Chamando o Dijkstra

```
dijkstra_lista(grafo, vertices, bomba);
```

Passamos:

```
grafo   → estrutura do grafo
vertices → quantidade de regiões
bomba   → origem do Dijkstra
```

A partir daqui o algoritmo calcula as menores distâncias.

---

# 26. Diferença entre Prim e Dijkstra

Essa é uma diferença importante para não confundir os dois algoritmos.

## Prim

Pergunta:

> Qual é a menor aresta que posso usar para adicionar um novo vértice à árvore?

A atualização típica é:

```
distancia[d] = peso;
```

---

## Dijkstra

Pergunta:

> Qual é o menor caminho acumulado desde a origem até esse vértice?

A atualização é:

```
distancia[d] = distancia[atual] + peso;
```

### Resumindo

```
PRIM
↓
Árvore Geradora Mínima
↓
Menor aresta para expandir a árvore


DIJKSTRA
↓
Menores caminhos
↓
Menor distância acumulada desde a origem
```

---

# 27. Fluxo completo do programa

```
flowchart TD
    A[Início] --> B[Ler quantidade de regiões]
    B --> C[Ler quantidade de conexões]
    C --> D[Criar lista de adjacência]
    D --> E[Ler origem destino e peso]
    E --> F[Inserir aresta no grafo]
    F --> G[Ler região da bomba]
    G --> H[Inicializar Dijkstra]
    H --> I[Distância da bomba = 0]
    I --> J[Escolher região atual]
    J --> K[Marcar como visitada]
    K --> L[Percorrer seus vizinhos]
    L --> M[Calcular distância acumulada]
    M --> N{Encontrou distância menor?}
    N -->|Sim| O[Atualizar distância]
    N -->|Não| P[Continuar]
    O --> P
    P --> Q{Existem regiões não visitadas?}
    Q -->|Sim| J
    Q -->|Não| R[Verificar distâncias]
    R --> S{Distância > 15?}
    S -->|Sim| T[Imprimir região]
    S -->|Não| U[Ignorar região]
    T --> V{Existiu região alagada?}
    U --> V
    V -->|Não| W[Imprimir Nenhuma região alagada]
    V -->|Sim| X[Fim]
    W --> X
```

---

# 28. Resumo para memorizar

```
Dijkstra

1. Inicializa todas as distâncias com INF
2. Define a origem com distância 0
3. Escolhe a região atual
4. Marca como visitada
5. Percorre seus vizinhos
6. Calcula:

   distancia[atual] + peso

7. Se for menor, atualiza a distância
8. Escolhe a próxima menor distância
9. Repete
10. Verifica quais distâncias são maiores que 15
```

### Linha mais importante do algoritmo

```
if (!visitado[d] &&
    distancia[atual] + p < distancia[d]) {

    distancia[d] = distancia[atual] + p;
}
```

Ela representa o **relaxamento do Dijkstra**:

> "Se passar pela região atual produz um caminho menor até o destino, atualize a distância."

```

```