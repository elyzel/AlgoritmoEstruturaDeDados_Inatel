# Lista de Adjacência com Peso — Grafo Orientado e Não Orientado

> [!question] Enunciado
> Harry, Rony e Hermione fizeram o favor de perder o Mapa do Maroto. E como solução para os seus problemas eles resolveram propor um desafio para um bruxo da Escola de Magia e Telecomunicações de Santa Rita. Eles pensaram que seria melhor criar, de forma temporária, um programa para ler apenas alguns pontos específicos de Hogwarts e suas distâncias e armazenar essas informações em um Grafo. As salas são os vértices e as distâncias são os pesos das arestas.
>
> Faça um programa que leia os dados dos vértices e arestas e os armazene em uma Lista de Adjacências.
>
> ## Entrada
>
> A primeira linha contém dois inteiros correspondendo ao número de vértices do grafo e o segundo define se o grafo é orientado (`1`) ou não orientado (`0`).
>
> As demais linhas contêm três inteiros correspondentes ao vértice de origem, o vértice de destino e o peso de cada aresta, respectivamente.
>
> A entrada termina quando ocorrer uma linha com três números iguais a `-1` (esta não deve ser registrada).
>
> ## Saída
>
> A saída deverá mostrar a lista de adjacências gerada.
>
> ## Exemplo de entrada
>
> ```text
> 5 1
> 4 1 3
> 0 2 4
> 1 3 2
> 3 1 3
> 0 1 2
> 2 4 7
> 3 4 2
> 4 0 1
> -1 -1 -1
> ```
>
> ## Exemplo de saída
>
> ```text
> 0 2 4
> 0 1 2
> 1 3 2
> 2 4 7
> 3 1 3
> 3 4 2
> 4 1 3
> 4 0 1
> ```

---

## 1. Objetivo do programa

O objetivo é representar um **grafo com pesos** utilizando uma **lista de adjacência**.

Cada aresta possui três informações:

```text
origem → destino → peso
```

Por exemplo:

```
4 1 3
```

significa:

```
4 ──3──> 1
```

- `4` → vértice de origem
- `1` → vértice de destino
- `3` → peso da aresta

O programa também precisa funcionar para:

- **Grafo orientado** → `M = 1`
- **Grafo não orientado** → `M = 0`

---

# 2. Estrutura usada para representar uma aresta

Uma aresta possui duas informações que precisamos guardar dentro da lista:

```
destino
peso
```

Por isso criamos uma `struct`:

```
struct no {
    int v;
    int p;
};
```

Onde:

|Campo|Significado|
|---|---|
|`v`|vértice de destino|
|`p`|peso da aresta|

Por exemplo:

```
no x;

x.v = 1;
x.p = 3;
```

representa:

```
destino = 1
peso = 3
```

---

# 3. Lista de adjacência

A estrutura principal é:

```
list<no> adj[N];
```

Isso significa que temos uma lista para cada vértice.

Podemos visualizar:

```
adj[0] → lista de arestas que saem de 0

adj[1] → lista de arestas que saem de 1

adj[2] → lista de arestas que saem de 2

adj[3] → lista de arestas que saem de 3

adj[4] → lista de arestas que saem de 4
```

Cada elemento da lista é um `no`.

Por exemplo:

```
adj[4]

┌─────────┐
│ v = 1   │
│ p = 3   │
└─────────┘
     ↓
┌─────────┐
│ v = 0   │
│ p = 1   │
└─────────┘
```

Isso representa:

```
4 ──3──> 1
4 ──1──> 0
```

---

# 4. Código completo

```cpp
#include <iostream>
#include <list>

using namespace std;

struct no {
    int v; // Vértice de destino
    int p; // Peso da aresta
};

int main() {

    int N; // Número de vértices
    int M; // 1 = orientado / 0 = não orientado

    cin >> N >> M;

    // Lista de adjacência
    list<no> adj[N];

    int v; // Vértice de origem
    int u; // Vértice de destino
    int p; // Peso

    // Leitura das arestas
    while (cin >> v >> u >> p) {

        // Final da entrada
        if (v == -1 && u == -1 && p == -1) {
            break;
        }

        // Grafo orientado
        if (M == 1) {
            adj[v].push_back({u, p});
        }

        // Grafo não orientado
        else {
            adj[v].push_back({u, p});
            adj[u].push_back({v, p});
        }
    }

    // Percorre todos os vértices
    for (int i = 0; i < N; i++) {

        // Percorre a lista de adjacência do vértice i
        for (list<no>::iterator it = adj[i].begin();
             it != adj[i].end();
             it++) {

            cout << i << " "
                 << it->v << " "
                 << it->p << endl;
        }
    }

    return 0;
}
```

---

# 5. Leitura de `N` e `M`

```
int N;
int M;

cin >> N >> M;
```

A primeira linha da entrada contém:

```
N M
```

No exemplo:

```
5 1
```

Então:

```
N = 5
M = 1
```

Isso significa:

- existem `5` vértices: `0, 1, 2, 3, 4`
- o grafo é orientado porque `M = 1`

---

# 6. Por que `list<no>` e não `list<int>`?

Essa é uma das partes mais importantes do exercício.

Se fizéssemos:

```
list<int> adj[N];
```

cada posição conseguiria guardar apenas um número:

```
[ 1 ][ 3 ][ 7 ]
```

Mas uma aresta precisa guardar:

```
destino + peso
```

Por exemplo:

```
4 1 3
```

Precisamos guardar:

```
destino = 1
peso = 3
```

Por isso usamos:

```
struct no {
    int v;
    int p;
};
```

e:

```
list<no> adj[N];
```

Agora cada posição pode guardar:

```
{1, 3}
{4, 7}
{0, 1}
```

---

# 7. Leitura das arestas

O programa usa:

```
while (cin >> v >> u >> p) {
```

A cada repetição são lidos:

```
origem destino peso
```

Por exemplo:

```
4 1 3
```

resulta em:

```
v = 4
u = 1
p = 3
```

Neste programa usamos:

```
v = origem
u = destino
p = peso
```

---

# 8. Condição de parada

O enunciado determina que a entrada termina com:

```
-1 -1 -1
```

Por isso usamos:

```
if (v == -1 && u == -1 && p == -1) {
    break;
}
```

O `break` encerra o `while`.

### Atenção

Uma condição como:

```
if (v != -1 && u != -1 && p != -1)
```

estaria errada.

Ela significaria:

> "pare quando os três valores forem diferentes de -1".

O correto é:

```
v == -1
u == -1
p == -1
```

porque queremos identificar exatamente:

```
-1 -1 -1
```

---

# 9. Grafo orientado

Quando:

```
M = 1
```

o grafo é orientado.

Por exemplo:

```
4 1 3
```

significa:

```
4 ──3──> 1
```

Apenas uma direção é registrada:

```
adj[v].push_back({u, p});
```

Substituindo:

```
adj[4].push_back({1, 3});
```

Visualmente:

```
adj[4]
   ↓
┌─────────┐
│ v = 1   │
│ p = 3   │
└─────────┘
```

Não fazemos:

```
adj[1].push_back({4, 3});
```

porque isso criaria uma segunda direção.

---

# 10. Grafo não orientado

Quando:

```
M = 0
```

o grafo é não orientado.

Por exemplo:

```
4 1 3
```

significa:

```
4 ──3── 1
```

Podemos ir de `4` para `1` e de `1` para `4`.

Por isso registramos duas vezes:

```
adj[v].push_back({u, p});
adj[u].push_back({v, p});
```

Com:

```
v = 4
u = 1
p = 3
```

temos:

```
adj[4].push_back({1, 3});
adj[1].push_back({4, 3});
```

Representação:

```
adj[4] → {1,3}

adj[1] → {4,3}
```

---

# 11. `push_back()`

A função:

```
push_back()
```

adiciona um elemento ao final da lista.

Quando fazemos:

```
adj[v].push_back({u, p});
```

estamos dizendo:

> Adicione na lista do vértice `v` uma estrutura contendo o destino `u` e o peso `p`.

Por exemplo:

```
adj[4].push_back({1, 3});
```

significa:

```
lista de 4
    ↓
{ destino = 1, peso = 3 }
```

---

# 12. Percorrendo os vértices

Depois de construir o grafo:

```
for (int i = 0; i < N; i++) {
```

percorremos todos os vértices.

Para:

```
N = 5
```

teremos:

```
i = 0
i = 1
i = 2
i = 3
i = 4
```

Cada `i` representa uma lista:

```
i = 0 → adj[0]

i = 1 → adj[1]

i = 2 → adj[2]

i = 3 → adj[3]

i = 4 → adj[4]
```

---

# 13. Percorrendo uma lista com iterador

Para percorrer a lista usamos:

```
for (list<no>::iterator it = adj[i].begin();
     it != adj[i].end();
     it++) {
```

Podemos dividir em três partes:

```
list<no>::iterator it = adj[i].begin();
```

Começa no primeiro elemento.

```
it != adj[i].end();
```

Continua enquanto não chegar ao final.

```
it++;
```

Avança para o próximo elemento.

---

# 14. Por que o iterador é `list<no>::iterator`?

Nossa lista é:

```
list<no>
```

Então o iterador precisa saber que está percorrendo objetos do tipo `no`.

Por isso:

```
list<no>::iterator
```

e não:

```
list<int>::iterator
```

---

# 15. Acessando os dados com `it->`

Cada elemento apontado pelo iterador possui:

```
struct no {
    int v;
    int p;
};
```

Então:

```
it->v
```

significa:

> acesse o campo `v` do elemento atual.

E:

```
it->p
```

significa:

> acesse o campo `p` do elemento atual.

Por exemplo:

```
it
 ↓
┌─────────┐
│ v = 1   │
│ p = 3   │
└─────────┘
```

Então:

```
it->v
```

retorna:

```
1
```

e:

```
it->p
```

retorna:

```
3
```

---

# 16. Impressão

A saída é:

```
cout << i << " "
     << it->v << " "
     << it->p << endl;
```

Temos:

```
i     → origem
it->v → destino
it->p → peso
```

Portanto:

```
origem destino peso
```

Exemplo:

```
4 1 3
```

---

# 17. Rastreamento completo do exemplo

Entrada:

```
5 1
4 1 3
0 2 4
1 3 2
3 1 3
0 1 2
2 4 7
3 4 2
4 0 1
-1 -1 -1
```

Como:

```
M = 1
```

o grafo é orientado.

### Depois de ler as arestas

```
adj[0] → {2,4} → {1,2}

adj[1] → {3,2}

adj[2] → {4,7}

adj[3] → {1,3} → {4,2}

adj[4] → {1,3} → {0,1}
```

Visualmente:

```
0 ──4──> 2
│
└─2──> 1

1 ──2──> 3

2 ──7──> 4

3 ──3──> 1
│
└─2──> 4

4 ──3──> 1
│
└─1──> 0
```

---

# 18. Rastreamento da impressão

|`i`|Lista|Saída|
|---|---|---|
|`0`|`{2,4}`, `{1,2}`|`0 2 4` / `0 1 2`|
|`1`|`{3,2}`|`1 3 2`|
|`2`|`{4,7}`|`2 4 7`|
|`3`|`{1,3}`, `{4,2}`|`3 1 3` / `3 4 2`|
|`4`|`{1,3}`, `{0,1}`|`4 1 3` / `4 0 1`|

Resultado:

```
0 2 4
0 1 2
1 3 2
2 4 7
3 1 3
3 4 2
4 1 3
4 0 1
```

---

# 19. Fluxo do programa

#chatgpt-mermaid-_r_23p_{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;font-size:14px;fill:rgb(255, 255, 255);}@keyframes edge-animation-frame{from{stroke-dashoffset:0;}}@keyframes dash{to{stroke-dashoffset:0;}}#chatgpt-mermaid-_r_23p_ .edge-animation-slow{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 50s linear infinite;stroke-linecap:round;}#chatgpt-mermaid-_r_23p_ .edge-animation-fast{stroke-dasharray:9,5!important;stroke-dashoffset:900;animation:dash 20s linear infinite;stroke-linecap:round;}#chatgpt-mermaid-_r_23p_ .error-icon{fill:rgba(255, 255, 255, 0.03);}#chatgpt-mermaid-_r_23p_ .error-text{fill:rgb(255, 255, 255);stroke:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .edge-thickness-normal{stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .edge-thickness-thick{stroke-width:3.5px;}#chatgpt-mermaid-_r_23p_ .edge-pattern-solid{stroke-dasharray:0;}#chatgpt-mermaid-_r_23p_ .edge-thickness-invisible{stroke-width:0;fill:none;}#chatgpt-mermaid-_r_23p_ .edge-pattern-dashed{stroke-dasharray:3;}#chatgpt-mermaid-_r_23p_ .edge-pattern-dotted{stroke-dasharray:2;}#chatgpt-mermaid-_r_23p_ .marker{fill:rgba(255, 255, 255, 0.498);stroke:rgba(255, 255, 255, 0.498);}#chatgpt-mermaid-_r_23p_ .marker.cross{stroke:rgba(255, 255, 255, 0.498);}#chatgpt-mermaid-_r_23p_ svg{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;font-size:14px;}#chatgpt-mermaid-_r_23p_ p{margin:0;}#chatgpt-mermaid-_r_23p_ .label{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;color:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .cluster-label text{fill:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .cluster-label span{color:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .cluster-label span p{background-color:transparent;}#chatgpt-mermaid-_r_23p_ .label text,#chatgpt-mermaid-_r_23p_ span{fill:rgb(255, 255, 255);color:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .node rect,#chatgpt-mermaid-_r_23p_ .node circle,#chatgpt-mermaid-_r_23p_ .node ellipse,#chatgpt-mermaid-_r_23p_ .node polygon,#chatgpt-mermaid-_r_23p_ .node path{fill:rgb(26, 40, 61);stroke:rgb(31, 78, 148);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .rough-node .label text,#chatgpt-mermaid-_r_23p_ .node .label text,#chatgpt-mermaid-_r_23p_ .image-shape .label,#chatgpt-mermaid-_r_23p_ .icon-shape .label{text-anchor:middle;}#chatgpt-mermaid-_r_23p_ .node .katex path{fill:#000;stroke:#000;stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .rough-node .label,#chatgpt-mermaid-_r_23p_ .node .label,#chatgpt-mermaid-_r_23p_ .image-shape .label,#chatgpt-mermaid-_r_23p_ .icon-shape .label{text-align:center;}#chatgpt-mermaid-_r_23p_ .node.clickable{cursor:pointer;}#chatgpt-mermaid-_r_23p_ .root .anchor path{fill:rgba(255, 255, 255, 0.498)!important;stroke-width:0;stroke:rgba(255, 255, 255, 0.498);}#chatgpt-mermaid-_r_23p_ .arrowheadPath{fill:rgba(255, 255, 255, 0.498);}#chatgpt-mermaid-_r_23p_ .edgePath .path{stroke:rgba(255, 255, 255, 0.498);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .flowchart-link{stroke:rgba(255, 255, 255, 0.498);fill:none;}#chatgpt-mermaid-_r_23p_ .edgeLabel{background-color:rgb(24, 24, 24);text-align:center;}#chatgpt-mermaid-_r_23p_ .edgeLabel p{background-color:rgb(24, 24, 24);}#chatgpt-mermaid-_r_23p_ .edgeLabel rect{opacity:0.5;background-color:rgb(24, 24, 24);fill:rgb(24, 24, 24);}#chatgpt-mermaid-_r_23p_ .labelBkg{background-color:rgba(24, 24, 24, 0.5);}#chatgpt-mermaid-_r_23p_ .cluster rect{fill:rgba(255, 255, 255, 0.03);stroke:rgba(255, 255, 255, 0.082);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .cluster text{fill:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ .cluster span{color:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;font-size:12px;background:rgba(255, 255, 255, 0.03);border:1px solid rgba(255, 255, 255, 0.082);border-radius:2px;pointer-events:none;z-index:100;}#chatgpt-mermaid-_r_23p_ .flowchartTitleText{text-anchor:middle;font-size:18px;fill:rgb(255, 255, 255);}#chatgpt-mermaid-_r_23p_ rect.text{fill:none;stroke-width:0;}#chatgpt-mermaid-_r_23p_ .icon-shape,#chatgpt-mermaid-_r_23p_ .image-shape{background-color:rgb(24, 24, 24);text-align:center;}#chatgpt-mermaid-_r_23p_ .icon-shape p,#chatgpt-mermaid-_r_23p_ .image-shape p{background-color:rgb(24, 24, 24);padding:2px;}#chatgpt-mermaid-_r_23p_ .icon-shape .label rect,#chatgpt-mermaid-_r_23p_ .image-shape .label rect{opacity:0.5;background-color:rgb(24, 24, 24);fill:rgb(24, 24, 24);}#chatgpt-mermaid-_r_23p_ .label-icon{display:inline-block;height:1em;overflow:visible;vertical-align:-0.125em;}#chatgpt-mermaid-_r_23p_ .node .label-icon path{fill:currentColor;stroke:revert;stroke-width:revert;}#chatgpt-mermaid-_r_23p_ .node .neo-node{stroke:rgb(31, 78, 148);}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node rect,#chatgpt-mermaid-_r_23p_ [data-look="neo"].cluster rect,#chatgpt-mermaid-_r_23p_ [data-look="neo"].node polygon{stroke:url(#chatgpt-mermaid-_r_23p_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-_r_23p_ [data-look="neo"].swimlane.cluster rect{filter:none;}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node path{stroke:url(#chatgpt-mermaid-_r_23p_-gradient);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node .outer-path{filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node .neo-line path{stroke:rgb(31, 78, 148);filter:none;}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node circle{stroke:url(#chatgpt-mermaid-_r_23p_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-_r_23p_ [data-look="neo"].node circle .state-start{fill:#000000;}#chatgpt-mermaid-_r_23p_ [data-look="neo"].icon-shape .icon{fill:url(#chatgpt-mermaid-_r_23p_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-_r_23p_ [data-look="neo"].icon-shape .icon-neo path{stroke:url(#chatgpt-mermaid-_r_23p_-gradient);filter:drop-shadow( 1px 2px 2px rgba(185,185,185,1));}#chatgpt-mermaid-_r_23p_ .node text{font-size:14px;font-weight:600;letter-spacing:normal;fill:rgb(153, 206, 255);}#chatgpt-mermaid-_r_23p_ .edgeLabels text{font-size:13px;font-weight:600;letter-spacing:-0.08px;fill:rgb(153, 206, 255);}#chatgpt-mermaid-_r_23p_ .node tspan[font-weight="normal"],#chatgpt-mermaid-_r_23p_ .edgeLabels tspan[font-weight="normal"]{font-weight:600;}#chatgpt-mermaid-_r_23p_ .edgeLabel .label rect{opacity:1;rx:13px;ry:13px;fill:rgb(0, 14, 26);stroke:rgb(26, 62, 95);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .node rect,#chatgpt-mermaid-_r_23p_ .node circle,#chatgpt-mermaid-_r_23p_ .node ellipse,#chatgpt-mermaid-_r_23p_ .node polygon,#chatgpt-mermaid-_r_23p_ .node path{fill:rgb(0, 40, 77);stroke:rgba(255, 255, 255, 0.1);stroke-width:1px;}#chatgpt-mermaid-_r_23p_ .node rect{rx:16px;ry:16px;}#chatgpt-mermaid-_r_23p_ .node.mermaid-decision .label-container{fill:rgb(0, 14, 26);stroke:rgb(26, 62, 95);stroke-dasharray:2,2;}#chatgpt-mermaid-_r_23p_ .edgePaths .flowchart-link{stroke:rgba(255, 255, 255, 0.498);stroke-width:1px;stroke-linecap:round;stroke-linejoin:round;}#chatgpt-mermaid-_r_23p_ .marker{fill:rgba(255, 255, 255, 0.498);stroke:rgba(255, 255, 255, 0.498);}#chatgpt-mermaid-_r_23p_ :root{--mermaid-font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;}InícioLer N e MCriar list no adj NLer origem destino pesoÉ -1 -1 -1?Percorrer vérticesM == 1?Adicionar destino e peso emadj origemAdicionar origem em destino edestino em origemPercorrer lista com iteratorImprimir origem destino pesoExistem mais elementos?Existem mais vértices?FimSimNãoSimNãoSimNãoSimNão

---

# 20. Erros importantes que foram corrigidos

## Erro 1 — `list<int>`

Errado:

```
list<int> adj[N];
```

Porque uma aresta precisa armazenar:

```
destino + peso
```

Correto:

```
list<no> adj[N];
```

---

## Erro 2 — Condição de parada

Errado:

```
if (v != -1 && u != -1 && p != -1)
```

Correto:

```
if (v == -1 && u == -1 && p == -1)
```

---

## Erro 3 — Origem e destino invertidos

Se:

```
4 1 3
```

temos:

```
origem = 4
destino = 1
peso = 3
```

Portanto:

```
adj[v].push_back({u, p});
```

e não:

```
adj[u].push_back({v, p});
```

para o caso orientado.

---

## Erro 4 — `i` não existia

Não podemos fazer:

```
adj[i]
```

sem antes declarar e percorrer `i`.

Por isso:

```
for (int i = 0; i < N; i++) {
```

---

## Erro 5 — Tipo do iterador

Se temos:

```
list<no> adj[N];
```

o iterador precisa ser:

```
list<no>::iterator
```

---

# 21. Resumo para memorizar

A ideia principal deste exercício é:

```
Grafo
  ↓
Lista de adjacência
  ↓
Cada posição representa um vértice
  ↓
Cada elemento da lista representa uma aresta
  ↓
Cada aresta possui:
    ├── destino
    └── peso
```

A estrutura:

```
struct no {
    int v;
    int p;
};
```

representa uma aresta.

A estrutura:

```
list<no> adj[N];
```

representa o grafo.

Para adicionar uma aresta orientada:

```
adj[origem].push_back({destino, peso});
```

Para adicionar uma aresta não orientada:

```
adj[origem].push_back({destino, peso});
adj[destino].push_back({origem, peso});
```

Para percorrer:

```
for (list<no>::iterator it = adj[i].begin();
     it != adj[i].end();
     it++) {
```

E para acessar:

```
it->v  // destino
it->p  // peso
```

> [!tip] Regra mental  
> **`adj[i]` = todas as arestas que saem do vértice `i`.**
> 
> Dentro dessa lista, cada `no` guarda **para onde vai (`v`) e quanto custa (`p`)**.
