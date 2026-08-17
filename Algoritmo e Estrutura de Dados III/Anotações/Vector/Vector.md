## O que é cada um?

### `vector<int>` (Vetor Unidimensional / 1D)

É uma **lista simples e dinâmica** de números inteiros. Pense nele como uma **única linha de dados** ou uma fita métrica de caixas numéricas.

- **Sintaxe de Acesso:** `v[i]` (acessa o elemento na posição `i`).
    
- **Visualização:**
    
    Plaintext
    
    ```
    [ 10, 20, 30, 40, 50 ]
    ```
    

**Principais Métodos:**

- `.push_back(valor)`: Adiciona um elemento ao final.
    
- `.size()`: Retorna a quantidade de elementos.
    
- `.pop_back()`: Remove o último elemento.


### `vector<vector<int>>` (Vetor Bidimensional / 2D)

É um **vetor onde cada elemento dentro dele é outro vetor**. Ou seja, é uma **tabela (matriz) de números**, que possui **linhas e colunas**.

- **Sintaxe de Acesso:** `matriz[linha][coluna]` (acessa a linha primeiro e depois a coluna específica).
    
- **Visualização:**
    
    Plaintext
    
    ```
              Coluna 0   Coluna 1   Coluna 2
    Linha 0: [   10    ,    20    ,    30   ]
    Linha 1: [   40    ,    50    ,    60   ]
    Linha 2: [   70    ,    80    ,    90   ]
    ```


## 🎯 Exercício 1: Nível Introdutório (Vector Unidimensional)

> **Desafio:** Crie um `vector` simples de números inteiros. Adicione 4 notas usando `.push_back()`, calcule a média das notas e mostre a maior nota presente usando a biblioteca `<algorithm>`.

### Resposta

C++

```
#include <iostream>
#include <vector>
#include <algorithm> // Necessário para std::max

using namespace std;

int main() {
    // 1. Criando um vector unidimensional vazio
    vector<double> notas;

    // 2. Adicionando valores ao final do vetor (linha simples)
    notas.push_back(7.5);
    notas.push_back(8.0);
    notas.push_back(6.5);
    notas.push_back(10.0);

    double soma = 0;
    double maiorNota = notas[0];

    // 3. Percorrendo a linha simples
    for (size_t i = 0; i < notas.size(); i++) {
        soma += notas[i];
        maiorNota = max(maiorNota, notas[i]); // Compara a nota atual com a maior registrada
    }

    double media = soma / notas.size();

    cout << "=== Relatorio de Notas ===" << endl;
    cout << "Total de notas inseridas: " << notas.size() << endl;
    cout << "Media da turma: " << media << endl;
    cout << "Maior nota da turma: " << maiorNota << endl;

    return 0;
}
```

## 🎯 Exercício 2: Nível Elaborado (Vector Bidimensional + Lógica)

> **Desafio:** Crie uma matriz $3 \times 3$ usando `std::vector` preenchida com os números de $1$ a $9$. 1. Imprima a matriz em formato de tabela no terminal. 2. Calcule e imprima a soma dos elementos apenas da **Diagonal Principal** (onde a linha $i$ é igual à coluna $j$).

### Resposta

C++

```
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Inicializando uma matriz 3x3 diretamente
    vector<vector<int>> matriz = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int somaDiagonal = 0;

    cout << "=== Matriz 3x3 ===" << endl;

    // 2. Percorrendo a matriz (Linhas i x Colunas j)
    for (size_t i = 0; i < matriz.size(); i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            
            cout << matriz[i][j] << "\t"; // Imprime o valor e alinha com tabulação

            // Verifica se o elemento está na diagonal principal
            if (i == j) {
                somaDiagonal += matriz[i][j];
            }
        }
        cout << endl; // Quebra de linha a cada fim de linha da matriz
    }

    cout << "\nSoma dos elementos da Diagonal Principal: " << somaDiagonal << endl;

    return 0;
}
```