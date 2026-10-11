> [!QUESTION]
> Você foi contratado pelo Instagram como engenheiro de software para gerenciar as relações entre os
usuários. Para essa tarefa, você opta por utilizar um grafo direcionado, em que os nós representam os usuários, e as arestas as relações entre eles. Um usuário pode seguir outro, mas esse outro pode não o seguir de volta, assim como dois usuários podem se seguir mutuamente.
>
>Entrada
>
A primeira linha contém um inteiro N indicando o número de usuários a serem cadastrados.
>
Seguem N linhas com os nomes dos usuários. Após isso, seguem outras N linhas, dessa vez contendo o número dos usuários que determinada pessoa segue, sendo a entrada de cada um interrompida pelo número -1. Por último temos um único inteiro, indicando o número do usuário o qual deseja-se verificar os seguidores.
>
Saída
>
A saída deve mostrar todos os seguidores da pessoa desejada.

| Exemplo de entrada                                                                                                                                   | Exemplo de saída                                    |
| :--------------------------------------------------------------------------------------------------------------------------------------------------- | :-------------------------------------------------- |
| 5<br>Amanda de Paiva<br>Gabriel Moreira<br>Cassia Reis<br>Helena Martins<br>Francisco Emanuel<br>1 2 3 -1<br>0 -1<br>1 3 4 -1<br>0 2 -1<br>1 -1<br>1 | Amanda de Paiva<br>Cassia Reis<br>Francisco Emanuel |

# C++ — Grafo Direcionado e Lista de Seguidores

## 1. Objetivo do programa

O objetivo é representar uma rede social usando um **grafo direcionado**, em que:

- Cada vértice representa um usuário.
    
- Cada aresta representa uma relação de seguir.
    
- Uma aresta `u → v` significa que o usuário `u` segue o usuário `v`.
    
- O programa recebe um usuário e imprime os nomes de todos que o seguem.
    

**Exemplo:** se Amanda segue Gabriel, existe a aresta `0 → 1`. Isso não significa necessariamente que Gabriel segue Amanda.

## 2. Código completo

```cpp
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();

    // Guarda os nomes dos usuários
    string nomes[N];

    for (int i = 0; i < N; i++) {
        getline(cin, nomes[i]);
    }

    // Lista de adjacência: uma lista para cada usuário
    list<int> adj[N];

    // Lê quem cada usuário segue
    for (int u = 0; u < N; u++) {
        int v;

        while (cin >> v && v != -1) {
            adj[u].push_back(v);
        }
    }

    // Usuário do qual queremos encontrar os seguidores
    int desejado;
    cin >> desejado;

    // Procura quem segue o usuário desejado
    for (int u = 0; u < N; u++) {
        for (list<int>::iterator it = adj[u].begin();
             it != adj[u].end(); it++) {

            if (*it == desejado) {
                cout << nomes[u] << endl;
                break;
            }
        }
    }

    return 0;
}
```

> **Observação sobre o padrão C++:** `string nomes[N]` e `list<int> adj[N]` usam um tamanho de array definido durante a execução. Isso não é permitido pelo padrão C++ em todas as implementações. O código acima pode funcionar como extensão de alguns compiladores. Uma versão portável pode usar alocação dinâmica ou outra estrutura padrão, sem precisar usar `vector`.

## 3. Bibliotecas e estrutura inicial

```
#include <iostream>
#include <list>
#include <string>

using namespace std;
```

### Anatomia

|Código|Função|
|---|---|
|`#include <iostream>`|Permite usar `cin` e `cout`.|
|`#include <list>`|Disponibiliza a estrutura `list`.|
|`#include <string>`|Disponibiliza o tipo `string`.|
|`using namespace std;`|Permite escrever `list` em vez de `std::list`, por exemplo.|

A função principal começa com:

```
int main() {
    // Instruções do programa
    return 0;
}
```

O programa executa as instruções dentro de `main()`. O `return 0` indica que a execução terminou normalmente.

## 4. Leitura da quantidade de usuários

```
int N;
cin >> N;
cin.ignore();
```

- `int N;` declara uma variável inteira para guardar o número de usuários.
    
- `cin >> N;` lê esse número.
    
- `cin.ignore();` descarta o caractere de quebra de linha que fica no fluxo de entrada depois da leitura de `N`.
    

O `cin.ignore()` é importante porque, logo depois, usaremos `getline()` para ler nomes completos.

## 5. Armazenamento dos nomes

```
string nomes[N];

for (int i = 0; i < N; i++) {
    getline(cin, nomes[i]);
}
```

### Como funciona?

`nomes` armazena o nome associado a cada índice do grafo.

|Índice|Nome|
|---|---|
|`0`|Amanda de Paiva|
|`1`|Gabriel Moreira|
|`2`|Cassia Reis|
|`3`|Helena Martins|
|`4`|Francisco Emanuel|

O laço começa em `i = 0` e continua enquanto `i < N`.

A instrução:

```
getline(cin, nomes[i]);
```

lê uma linha inteira, incluindo espaços. Por isso, funciona com nomes como `Amanda de Paiva`.

## 6. Criação da lista de adjacência

```
list<int> adj[N];
```

Essa é a estrutura que representa o grafo.

- `list<int>` é uma lista encadeada de números inteiros.
    
- `adj` é um conjunto de listas.
    
- `adj[u]` contém os índices dos usuários que `u` segue.
    

### Representação visual

Suponha que o usuário `0` siga os usuários `1`, `2` e `3`.

```
adj[0] → [1] → [2] → [3]
adj[1] → [0]
adj[2] → [1] → [3] → [4]
adj[3] → [0] → [2]
adj[4] → [1]
```

Cada linha representa uma lista de adjacência. Os valores são índices de usuários, e não os nomes propriamente ditos.

**Importante:** `list<int>` armazena os destinos das arestas. A lista não armazena automaticamente o índice de origem; ele é identificado pela posição `adj[u]`.

## 7. Leitura das relações entre usuários

```
for (int u = 0; u < N; u++) {
    int v;

    while (cin >> v && v != -1) {
        adj[u].push_back(v);
    }
}
```

Esse trecho lê as relações de cada usuário.

### Laço externo

```
for (int u = 0; u < N; u++)
```

Percorre todos os usuários, de `0` até `N - 1`.

A variável `u` representa o usuário que está informando quem segue.

### Variável de destino

```
int v;
```

`v` guarda o índice de um usuário seguido por `u`.

### Laço interno

```
while (cin >> v && v != -1)
```

O laço lê números enquanto a leitura for válida e o número for diferente de `-1`.

O número `-1` indica que terminou a lista de pessoas seguidas pelo usuário atual.

### Inserção na lista

```
adj[u].push_back(v);
```

Adiciona `v` ao final da lista do usuário `u`.

Por exemplo, se `u = 0` e a entrada for `1 2 3 -1`, as inserções serão:

|Leitura|Instrução|Conteúdo de `adj[0]`|
|---|---|---|
|`1`|`adj[0].push_back(1)`|`[1]`|
|`2`|`adj[0].push_back(2)`|`[1, 2]`|
|`3`|`adj[0].push_back(3)`|`[1, 2, 3]`|
|`-1`|Encerra o `while`|`[1, 2, 3]`|

O `-1` não é adicionado à lista.

## 8. Leitura do usuário desejado

```
int desejado;
cin >> desejado;
```

A variável `desejado` guarda o índice do usuário cujos seguidores queremos encontrar.

Se:

```
1
```

for o valor informado, queremos descobrir quem segue o usuário de índice `1`.

Se `nomes[1]` for `Gabriel Moreira`, o objetivo será encontrar todos os usuários cujas listas contenham o número `1`.

## 9. Busca pelos seguidores

```
for (int u = 0; u < N; u++) {
    for (list<int>::iterator it = adj[u].begin();
         it != adj[u].end(); it++) {

        if (*it == desejado) {
            cout << nomes[u] << endl;
            break;
        }
    }
}
```

Esse é o trecho principal do algoritmo.

### 9.1. Laço externo

```
for (int u = 0; u < N; u++)
```

Seleciona cada usuário para verificar quem ele segue.

### 9.2. Criação do iterador

```
list<int>::iterator it = adj[u].begin();
```

Um iterador funciona como uma referência para percorrer os elementos da lista.

- `list<int>::iterator`: tipo do iterador.
    
- `it`: nome da variável iteradora.
    
- `adj[u].begin()`: posição do primeiro elemento da lista.
    

### 9.3. Condição de continuação

```
it != adj[u].end()
```

`end()` representa a posição depois do último elemento. O laço termina quando o iterador chega a essa posição.

### 9.4. Avanço do iterador

```
it++
```

Avança para o próximo elemento da lista.

### 9.5. Acesso ao valor

```
if (*it == desejado)
```

O operador `*` acessa o valor apontado pelo iterador.

Se `*it` for igual ao índice procurado, significa que o usuário `u` segue o usuário desejado.

### 9.6. Impressão do nome

```
cout << nomes[u] << endl;
```

Imprime o nome de quem segue o usuário procurado.

### 9.7. Por que existe `break`?

```
break;
```

Encerra o laço interno assim que o usuário `u` é encontrado como seguidor.

Isso evita imprimir o mesmo nome mais de uma vez caso a lista daquele usuário contenha o mesmo destino repetido. O laço externo continua procurando outros seguidores.

## 10. Exemplo completo

### Entrada

```
5
Amanda de Paiva
Gabriel Moreira
Cassia Reis
Helena Martins
Francisco Emanuel
1 2 3 -1
0 -1
1 3 4 -1
0 2 -1
1 -1
1
```

### Relações obtidas

|Usuário de origem|Usuários que segue|
|---|---|
|Amanda (`0`)|Gabriel (`1`), Cassia (`2`), Helena (`3`)|
|Gabriel (`1`)|Amanda (`0`)|
|Cassia (`2`)|Gabriel (`1`), Helena (`3`), Francisco (`4`)|
|Helena (`3`)|Amanda (`0`), Cassia (`2`)|
|Francisco (`4`)|Gabriel (`1`)|

O último `1` da entrada indica que queremos os seguidores de Gabriel.

O algoritmo verifica as listas:

1. Amanda tem `1` na sua lista: imprime Amanda.
    
2. Gabriel não tem `1` na sua lista: não imprime Gabriel.
    
3. Cassia tem `1` na sua lista: imprime Cassia.
    
4. Helena não tem `1` na sua lista: não imprime Helena.
    
5. Francisco tem `1` na sua lista: imprime Francisco.
    

### Saída

```
Amanda de Paiva
Cassia Reis
Francisco Emanuel
```

## 11. Diagrama de fluxo em Mermaid

O diagrama abaixo representa as principais etapas da execução.

```
flowchart TD
    A([Início]) --> B[Ler N]
    B --> C[Ler os nomes dos N usuários]
    C --> D[Criar as listas de adjacência]
    D --> E[Selecionar usuário u]
    E --> F[Ler os usuários que u segue]
    F --> G{Foi lido -1?}
    G -- Não --> H[Adicionar v em adj u]
    H --> F
    G -- Sim --> I{Existem outros usuários?}
    I -- Sim --> E
    I -- Não --> J[Ler o índice desejado]
    J --> K[Percorrer cada lista adj u]
    K --> L{O destino é o desejado?}
    L -- Sim --> M[Imprimir o nome de u]
    M --> N[Continuar a busca]
    L -- Não --> N
    N --> O{Restam elementos ou usuários?}
    O -- Sim --> K
    O -- Não --> P([Fim])
```

## 12. Resumo dos conceitos

|Conceito|Aplicação no programa|
|---|---|
|Grafo direcionado|Representa a relação de seguir.|
|Vértice|Um usuário da rede social.|
|Aresta|Uma relação `u → v`.|
|Lista de adjacência|Guarda os destinos alcançados por cada usuário.|
|`list<int>`|Armazena os índices dos usuários seguidos.|
|`push_back()`|Adiciona um destino ao final da lista.|
|Iterador|Percorre os elementos de uma lista.|
|`*it`|Acessa o valor apontado pelo iterador.|
|`-1`|Encerra a leitura das relações de um usuário.|

**Ideia central para memorizar:** para descobrir quem segue um usuário `desejado`, percorremos as listas de todos os usuários e procuramos o índice `desejado`. Quando ele aparece em `adj[u]`, significa que `u` segue a pessoa procurada; portanto, imprimimos `nomes[u]`.