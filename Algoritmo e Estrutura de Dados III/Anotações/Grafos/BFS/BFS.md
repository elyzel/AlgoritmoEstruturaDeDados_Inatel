

# Algoritmo de Dijkstra

Considera um conjunto S de menores caminhos para todos os vértices existentes do grafo.

## Código do Dijkstra

[[Código do Algoritmo de Djisktra]]

### **Observações**

`p` = Peso das Arestas

>[!ABSTRATION]
>A distâncias sempre serão comparadas relacionadas ao **vértice original**.

A ordem de comparação é sequencial ao relação ao vértices pelo que está referenciado no bloco de código abaixo:

```cpp
int menor_distancia = INF;

	// < -- Aqui está a linha responsável -- >
    for(int i=0; i<vertices; i++){

      if(!visitado[i] && distancia[i] < menor_distancia){

        menor_distancia = distancia[i];

        atual = i;
```



# Algoritmo de Prim



