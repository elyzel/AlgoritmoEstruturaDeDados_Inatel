# 🏆 Apagar e Ganhar (Beecrowd 1084)

> [!abstract] **Visão Geral do Problema**
> 
> Dado um número de $N$ dígitos, devemos apagar exatamente $D$ dígitos de modo que o número resultante de $N - D$ dígitos seja o **maior valor numérico possível**, mantendo a ordem relativa dos dígitos que não foram apagados.

## 🧠 Modelagem com Pilha Monótona (_Monotonic Stack_)

Para maximizar um número, devemos priorizar colocar **dígitos maiores nas posições mais à esquerda** (ordem de grandeza).

Plaintext

```
Entrada: N = 4, D = 2, Número = "4172"

Passo 1: Lê '4' ──► Pilha: [4]
Passo 2: Lê '1' ──► Pilha: [4, 1]
Passo 3: Lê '7' ──► '7' > '1' ──► Remove '1' (apagados = 1) ──► Pilha: [4]
                    '7' > '4' ──► Remove '4' (apagados = 2) ──► Pilha: []
                    Insere '7' ──► Pilha: [7]
Passo 4: Lê '2' ──► Apagados atingiu D=2 (não apaga mais)  ──► Pilha: [7, 2]

Resultado Final: "72"
```

## 🔍 Explicação Detalhada de Cada Bloco e Linha do Código

### Bloco 1: Importação de Bibliotecas e Otimização de E/S

C++

```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
```

- **`#include <iostream>`**: Permite usar `cin` e `cout`.
    
- **`#include <vector>`**: Fornece o contêiner de vetores dinâmicos.
    
- **`#include <string>`**: Permite manipular a cadeia de caracteres do número e utilizar métodos de pilha como `.push_back()`, `.pop_back()` e `.back()`.
    
- **`#include <algorithm>`**: Funções e algoritmos utilitários da biblioteca padrão.
    
- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Acelera drasticamente a leitura dos casos de teste para $N \le 10^5$.
    

### Bloco 2: Controle do Laço Principal

C++

```
int main() {
    int N, D;

    while (cin >> N >> D && !(N == 0 && D == 0)) {
        string numero;
        cin >> numero;
```

- **`int N, D;`**: $N$ é o total de dígitos inicial e $D$ é a quantidade exata de dígitos a apagar.
    
- **`while (cin >> N >> D && !(N == 0 && D == 0))`**: Processa os casos repetidamente até que a linha contenha `0 0`.
    
- **`string numero; cin >> numero;`**: Lê o número como texto, já que $N$ pode ter até $100.000$ dígitos (muito além da capacidade de qualquer tipo inteiro primitivo como `long long`).
    

### Bloco 3: Processamento com a Pilha Gulosa

C++

```
        string resultado = "";
        int apagados = 0;

        for (int i = 0; i < N; i++) {
            char digitoAtual = numero[i];

            while (!resultado.empty() && apagados < D && resultado.back() < digitoAtual) {
                resultado.pop_back();
                apagados++;
            }

            resultado.push_back(digitoAtual);
        }
```

- **`string resultado = "";`**: Usamos a própria string como uma **pilha (LIFO)**.
    
- **`int apagados = 0;`**: Contador de quantos dígitos já foram eliminados até o momento.
    
- **`for (int i = 0; i < N; i++)`**: Itera por cada dígito da esquerda para a direita.
    
- **`while (!resultado.empty() && apagados < D && resultado.back() < digitoAtual)`**:
    
    - `!resultado.empty()`: Verifica se a pilha contém dígitos.
        
    - `apagados < D`: Garante que não apagaremos mais dígitos do que o limite $D$.
        
    - `resultado.back() < digitoAtual`: Se o último dígito inserido for menor que o dígito que acabou de chegar, ele é uma "escolha ruim" para a grandeza do número.
        
- **`resultado.pop_back(); apagados++;`**: Remove o dígito menor anterior e computa $+1$ na cota de apagamentos.
    
- **`resultado.push_back(digitoAtual);`**: Insere o dígito atual no topo da pilha.
    

### Bloco 4: Ajuste do Tamanho Final e Saída

C++

```
        int tamanhoFinal = N - D;
        resultado = resultado.substr(0, tamanhoFinal);

        cout << resultado << "\n";
    }

    return 0;
}
```

- **`int tamanhoFinal = N - D;`**: O enunciado exige que o número final tenha exatamente $N - D$ dígitos.
    
- **`resultado = resultado.substr(0, tamanhoFinal);`**: Se a string de entrada estiver em ordem decrescente (ex: `98765` com $D = 2$), o laço `while` interno nunca removerá nada. Essa linha descarta os $D$ dígitos excedentes do final da string.
    
- **`cout << resultado << "\n";`**: Imprime a resposta final do caso de teste.
    

## ⚡ Análise de Complexidade

|**Métrica**|**Complexidade**|**Detalhes**|
|---|---|---|
|**Tempo**|$O(N)$|Cada caractere entra na pilha (`push_back`) exatamente 1 vez e sai dela (`pop_back`) no máximo 1 vez. O tempo total é linear por caso de teste.|
|**Espaço**|$O(N)$|Memória utilizada apenas para armazenar a string de entrada `numero` e a string `resultado`.|