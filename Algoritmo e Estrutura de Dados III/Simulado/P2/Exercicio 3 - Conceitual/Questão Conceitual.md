> [!QUESTION]
> 1)
> 
> ![[Pasted image 20261009174117.png]]

**RESPOSTA:**

### D (Distância) 

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
| INF | 2   | 0   | 2   | 4   | 2   |


### P (Pai)

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
| -1  | V6  | -1  | V3  | V2  | V4  |

### V (Vértices Visitados)

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
|     | V   | V   | V   | V   | V   |


> [!QUESTION]
> 2)
> 
> ![[Pasted image 20261009174326.png]]


**RESPOSTA:**

### D (Peso Mínimo)

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
| 0   | 7   | 1   | 3   | 11  | 5   |

### P (Ponto de Origem)

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
| -1  | V6  | V1  | V3  | V2  | V4  |
### V (Vértices Visitados)

| v1  | v2  | v3  | v4  | v5  | v6  |
| --- | --- | --- | --- | --- | --- |
| V   | V   | V   | V   | V   | V   |

> [!QUESTION]
> Seja o grafo direcionado cuja função aresta-vértice é mostrada abaixo:
>| aresta | vértices |
| ------ | -------- |
| a1     | {v1,v2}  |
| a2     | {v1,v4}  |
| a3     | {v3,v4}  |
| a4     | {v4,v5}  |
| a5     | {v4,v6}  |
| a6     | {v6,v5}  |
| a7     | {v4,v2}  |
| a8     | {v5,v2}  |
| a9     | {v1,v3}  |
>
> Determine a ordenação topológica oara este grafo, e mostre os valores do vetor f ao rodar o algoritmo abaixo.
>
>**IMPORTANTE**: 
>
>a) Crie a lista de adjacências com as arestas na ordem em que aparecem na tabela
>
>b) o padrão de resposta deve ser 
>f={2,1,3,4,7,6} ord=v1-v3-v5-v2-v4
>
>DFS(G)  
    for each vertex u in V[G]  
  >      color[u] ← WHITE  
        π[u]← NIL  
>    time ← 0  
>    for each vertex u ∈ V[G]  
>        if color[u] = WHITE  
>            DFS-VISIT(u)
>
>DFS-VISIT(u)  
>    color[u] ← GRAY   
>    time ← time+1  
>    d[u] ← time  
>    for each v in Adj[u]   
>        if color[v] = WHITE  
>            π[v] ← u  
>            DFS-VISIT(v)  
>    color[u] ← BLACK   
 >   f[u] ← time ← time+1
>
>ORDENACAO_TOPOLOGICA(G)  
>    chame DFS(G)  
>    mostre os vértices em ordem decrescente do valor de f[] correspondente
>

**RESPOSTA:**

