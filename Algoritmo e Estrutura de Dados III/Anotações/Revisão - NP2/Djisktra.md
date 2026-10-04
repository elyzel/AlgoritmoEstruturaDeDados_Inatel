
# Dijkstra — Entendendo a função passo a passo

## 1. Antes de olhar o código: qual é o problema?

Imagine este grafo:

```
        4
   0 --------> 1
   |           |
  2|           |1
   |           |
   ↓           ↓
   2 --------> 3
        3
```

Queremos descobrir:

> **Qual é o menor caminho entre um vértice de origem e um vértice de destino?**

Por exemplo:

```
Origem = 0
Destino = 3
```

Existem alguns caminhos possíveis:

```
0 → 1 → 3

custo:
4 + 1 = 5
```

ou:

```
0 → 2 → 3

custo:
2 + 3 = 5
```

O Dijkstra vai explorar o grafo procurando os menores custos.

---

# 2. A ideia principal do Dijkstra

Podemos resumir o algoritmo assim:

```
Começa na origem
       ↓
Descobre os vizinhos
       ↓
Calcula os custos para chegar neles
       ↓
Escolhe o vértice ainda não visitado
com menor distância
       ↓
Explora esse vértice
       ↓
Atualiza distâncias
       ↓
Repete
       ↓
Chega ao destino
       ↓
Reconstrói o caminho
```

### Mapa conceitual

---

# 3. A função completa

Primeiro vamos olhar o código inteiro.

```cpp
int dijkstra_lista(
    list<Aresta> grafo[],
    int vertices,
    int origem,
    int destino
){
    bool visitado[vertices];
    int pai[vertices];
    int distancia[vertices];
    int atual;

    list<Aresta>::iterator it;

    // Inicialização
    for(int i = 0; i < vertices; i++){
        visitado[i] = false;
        pai[i] = -1;
        distancia[i] = INF;
    }

    // A origem começa com distância 0
    distancia[origem] = 0;

    // Começamos pela origem
    atual = origem;

    // Enquanto o vértice atual não tiver sido visitado
    while(!visitado[atual]){

        // Marca o atual como visitado
        visitado[atual] = true;

        // Percorre todos os vizinhos de atual
        for(it = grafo[atual].begin();
            it != grafo[atual].end();
            it++){

            int d = it->destino;
            int p = it->peso;

            // Relaxamento
            if(!visitado[d] &&
               distancia[atual] + p < distancia[d]){

                distancia[d] = distancia[atual] + p;
                pai[d] = atual;
            }
        }

        // Procurar o próximo vértice
        int menor_distancia = INF;

        for(int i = 0; i < vertices; i++){

            if(!visitado[i] &&
               distancia[i] < menor_distancia){

                menor_distancia = distancia[i];
                atual = i;
            }
        }
    }

    // Reconstrução do caminho
    atual = destino;

    while(atual != origem){

        cout << atual + 1 << " <- ";

        atual = pai[atual];
    }

    cout << atual + 1 << endl;

    return distancia[destino];
}
```

Agora vamos desmontar isso.

---

# 4. Primeiro bloco — parâmetros da função

```cpp
int dijkstra_lista(
    list<Aresta> grafo[],
    int vertices,
    int origem,
    int destino
)
```

A função recebe quatro informações:

|Parâmetro|Significado|
|---|---|
|`grafo[]`|Grafo representado por listas de adjacência|
|`vertices`|Quantidade de vértices|
|`origem`|De onde vamos começar|
|`destino`|Para onde queremos chegar|

E retorna:

```
int
```

porque no final queremos retornar a distância mínima.

---

# 5. Como o grafo está armazenado?

Provavelmente temos algo parecido com:

```cpp
struct Aresta {
    int destino;
    int peso;
};
```

Então podemos ter:

```
grafo[0]
 ├── destino = 1, peso = 4
 └── destino = 2, peso = 2

grafo[1]
 └── destino = 3, peso = 1

grafo[2]
 └── destino = 3, peso = 3
```

Visualmente:

O `grafo[0]`, por exemplo, representa:

> "Quais vértices podem ser alcançados a partir do vértice 0?"

---

# 6. Segundo bloco — criando as estruturas

```cpp
bool visitado[vertices];

int pai[vertices];

int distancia[vertices];

int atual;
```

Essas quatro variáveis são fundamentais.

---

## 6.1 `visitado[]`

```
bool visitado[vertices];
```

Guarda se um vértice já foi processado.

Exemplo:

```
visitado[0] = true
visitado[1] = false
visitado[2] = true
visitado[3] = false
```

Significa:

```
0 → já processado
1 → ainda não
2 → já processado
3 → ainda não
```

Podemos imaginar:

---

# 7. `distancia[]`

```
int distancia[vertices];
```

Esse vetor guarda:

> **Qual é a menor distância conhecida até cada vértice?**

Inicialmente não sabemos nada.

Por isso:

```
distancia[i] = INF;
```

`INF` significa "infinito".

Então inicialmente:

```
distancia:

0 → ∞
1 → ∞
2 → ∞
3 → ∞
```

Mas sabemos que estamos começando em `0`.

Então:

```
distancia[origem] = 0;
```

Resultado:

```
0 → 0
1 → ∞
2 → ∞
3 → ∞
```

Isso significa:

> Para chegar ao vértice 0 partindo do próprio 0, o custo é 0.

---

# 8. `pai[]`

Essa é uma das partes mais importantes.

```
int pai[vertices];
```

O vetor `pai` guarda:

> **De qual vértice eu vim para chegar aqui pelo melhor caminho conhecido?**

Imagine:

```
0 → 2 → 3
```

Então:

```
pai[2] = 0
pai[3] = 2
```

Podemos enxergar assim:

Isso será utilizado depois para reconstruir o caminho.

---

# 9. Inicialização completa

Agora temos:

```
for(int i = 0; i < vertices; i++){
    visitado[i] = false;
    pai[i] = -1;
    distancia[i] = INF;
}
```

Para cada vértice:

```
visitado = false
pai = -1
distancia = infinito
```

Por exemplo, com 4 vértices:

|Vértice|visitado|pai|distancia|
|---|---|---|---|
|0|false|-1|∞|
|1|false|-1|∞|
|2|false|-1|∞|
|3|false|-1|∞|

Depois:

```
distancia[origem] = 0;
```

Se a origem for `0`:

|Vértice|visitado|pai|distancia|
|---|---|---|---|
|0|false|-1|**0**|
|1|false|-1|∞|
|2|false|-1|∞|
|3|false|-1|∞|

---

# 10. Começando pela origem

```
atual = origem;
```

Se:

```
origem = 0;
```

então:

```
atual = 0
```

Ou seja:

> "Vamos começar analisando o vértice 0."

---

# 11. O grande `while`

Agora começa o coração do algoritmo:

```
while(!visitado[atual]){
```

Leia isso como:

> **Enquanto o vértice atual ainda não tiver sido visitado, processe-o.**

O fluxo é:

---

# 12. Marcando o vértice

Dentro do `while`:

```
visitado[atual] = true;
```

Se:

```
atual = 0
```

temos:

```
visitado[0] = true
```

Agora estamos dizendo:

> "Já processei o vértice 0."

---

# 13. Explorando os vizinhos

Agora vem:

```
for(it = grafo[atual].begin();
    it != grafo[atual].end();
    it++)
```

Essa parte percorre todos os elementos da lista de adjacência.

Se:

```
grafo[0]:

1, peso 4
2, peso 2
```

o `for` vai visitar:

```
primeiro:
1 → peso 4

depois:
2 → peso 2
```

Visualmente:

---

# 14. Pegando destino e peso

Dentro do `for`:

```
int d = it->destino;
int p = it->peso;
```

Se estamos analisando:

```
0 → 2
```

com peso:

```
2
```

teremos:

```
d = 2
p = 2
```

Então:

```
d = para onde vou
p = quanto custa ir
```

---

# 15. A parte mais importante: relaxamento

Agora chegamos nesta condição:

```
if(!visitado[d] &&
   distancia[atual] + p < distancia[d])
```

Essa é provavelmente a parte que mais causa confusão no início.

Vamos traduzir para português:

> "Se o destino ainda não foi visitado **e** o caminho passando pelo vértice atual é menor que a melhor distância que eu conheço..."

Então faça:

```
distancia[d] = distancia[atual] + p;
```

---

# 16. Vamos fazer isso com números

Imagine:

```
0 → 2
```

peso:

```
2
```

Sabemos:

```
distancia[0] = 0
```

Então calculamos:

```
distancia[0] + peso

0 + 2

= 2
```

Descobrimos:

```
distancia[2] = 2
```

E:

```
pai[2] = 0;
```

Então:

```
2 pode ser alcançado através de 0
```

---

# 17. Visualizando o relaxamento

---

# 18. Por que guardar o `pai`?

Imagine que encontramos:

```
distancia[2] = 2
pai[2] = 0
```

Mais tarde encontramos:

```
distancia[3] = 5
pai[3] = 2
```

Temos:

```
pai[3] = 2
pai[2] = 0
```

Portanto:

```
3 veio de 2
2 veio de 0
```

Então podemos reconstruir:

```
0 → 2 → 3
```

---

# 19. Terminamos de analisar os vizinhos

Depois que todos os vizinhos de `atual` foram analisados, precisamos decidir:

> **Quem será o próximo vértice?**

É aqui que entra:

```
int menor_distancia = INF;
```

Começamos dizendo:

```
menor distância encontrada = infinito
```

---

# 20. Procurando o próximo vértice

Depois:

```
for(int i = 0; i < vertices; i++){

    if(!visitado[i] &&
       distancia[i] < menor_distancia){

        menor_distancia = distancia[i];
        atual = i;
    }
}
```

Essa parte significa:

> Percorra todos os vértices e encontre o vértice **não visitado** que possui a **menor distância conhecida**.

---

# 21. Exemplo

Imagine:

|Vértice|visitado|distância|
|---|---|---|
|0|✅|0|
|1|❌|4|
|2|❌|2|
|3|❌|∞|

O algoritmo pergunta:

```
Quem ainda não foi visitado?
```

Temos:

```
1
2
3
```

Agora:

```
qual possui a menor distância?
```

Resposta:

```
2
```

Porque:

```
2 < 4 < ∞
```

Então:

```
atual = 2;
```

---

# 22. Essa é a "mágica" do Dijkstra

É importante entender isto:

```
Dijkstra não escolhe simplesmente o próximo vértice
que está conectado.

Ele escolhe o vértice NÃO VISITADO
com a MENOR DISTÂNCIA CONHECIDA.
```

Essa é uma das ideias centrais do algoritmo.

---

# 23. O algoritmo inteiro funcionando

Agora podemos juntar tudo:

---

# 24. Mas como o caminho é reconstruído?

Depois que o algoritmo terminou:

```
atual = destino;
```

Suponha:

```
origem = 0
destino = 3
```

Então:

```
atual = 3
```

Agora:

```
while(atual != origem)
```

Enquanto ainda não chegamos à origem, fazemos:

```
cout << atual + 1 << " <- ";
```

e depois:

```
atual = pai[atual];
```

---

# 25. Exemplo da reconstrução

Suponha:

```
pai[3] = 2
pai[2] = 0
```

Começamos:

```
atual = 3
```

### Primeira repetição

```
3 != 0
```

imprime:

```
3 <-
```

Depois:

```
atual = pai[3];
```

Logo:

```
atual = 2
```

---

### Segunda repetição

```
2 != 0
```

imprime:

```
2 <-
```

Depois:

```
atual = pai[2];
```

Logo:

```
atual = 0
```

---

### Terceira verificação

```
0 != 0
```

é falso.

Sai do `while`.

Depois:

```
cout << atual + 1 << endl;
```

Resultado conceitual:

```
3 <- 2 <- 0
```

Observe que ele imprime **do destino para a origem**.

O caminho original é:

```
0 → 2 → 3
```

---

# 26. Por que `pai[]` funciona?

Pense no `pai` como uma sequência de pistas:

```
Destino
   ↓
Quem me trouxe aqui?
   ↓
Meu pai
   ↓
Quem trouxe meu pai?
   ↓
Outro pai
   ↓
Origem
```

Por exemplo:

Portanto:

```
3 ← 2 ← 0
```

Invertendo:

```
0 → 2 → 3
```

---

# 27. Mapa mental de todas as variáveis

Esta é uma parte que recomendo muito deixar no seu Obsidian:

---

# 28. A lógica em uma frase

Se você tiver que lembrar apenas uma coisa, lembre disso:

> **Dijkstra mantém a menor distância conhecida para cada vértice, escolhe o vértice não visitado mais próximo, usa esse vértice para tentar melhorar as distâncias dos seus vizinhos e repete o processo.**

Podemos representar:

```
         ┌──────────────────┐
         │ Escolher vértice │
         │ mais próximo     │
         └────────┬─────────┘
                  ↓
         ┌──────────────────┐
         │ Explorar         │
         │ seus vizinhos    │
         └────────┬─────────┘
                  ↓
         ┌──────────────────┐
         │ Melhorar         │
         │ distâncias?      │
         └────────┬─────────┘
                  ↓
         ┌──────────────────┐
         │ Atualizar        │
         │ distancia/pai   │
         └────────┬─────────┘
                  ↓
              Repetir
```

---

# 29. Uma analogia para entender de verdade

Imagine que você está em uma cidade e quer chegar a várias outras cidades.

Você possui uma tabela:

|Cidade|Melhor distância conhecida|
|---|---|
|A|0|
|B|∞|
|C|∞|
|D|∞|

Você está em `A`.

Descobre:

```
A → B = 4
A → C = 2
```

Sua tabela fica:

|Cidade|Distância|
|---|---|
|A|0|
|B|4|
|C|2|
|D|∞|

Agora você pergunta:

> "Qual cidade ainda não visitei e está mais perto?"

Resposta:

```
C = 2
```

Então vai para C.

Descobre que:

```
C → D = 3
```

Logo:

```
A → C → D
```

tem custo:

```
2 + 3 = 5
```

Então:

```
distancia[D] = 5
pai[D] = C
```

É exatamente isso que o código está fazendo.