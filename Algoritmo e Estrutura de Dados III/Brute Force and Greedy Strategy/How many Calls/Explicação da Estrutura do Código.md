
# Estrutura do Código: How Many Calls? (UVa 10518)

> [!abstract] Visão Geral do Algoritmo
> 
> O programa calcula o número de chamadas recursivas necessárias para determinar o $n$-ésimo número de Fibonacci, exibindo o último dígito do resultado na base $b$. A relação matemática direta utilizada é:
> 
> $$\text{chamadas}(n) = (2 \cdot fib(n+1) - 1) \pmod b$$
> 
> Para suportar $n$ de até $2^{63}-1$, a exponenciação rápida de matrizes calcula $fib(n+1) \pmod b$ em tempo $O(\log n)$.

## 🛠️ Arquitetura e Componentes

O código é dividido em três blocos funcionais principais:

1. **Multiplicação Modular de Matrizes (`multiplicar`)**: Realiza o produto entre duas matrizes $2 \times 2$ aplicando o operador `% mod`.
    
2. **Exponenciação Binária de Matrizes (`potenciaMatriz`)**: Eleva a matriz base à potência $n$ reduzindo as multiplicações a $O(\log n)$.
    
3. **Fluxo Principal (`main`)**: Gerencia o laço de entrada de dados, formatação do caso de teste e exibição do resultado.
    

## 📌 Detalhamento da Estrutura

### 1. Inclusão de Bibliotecas e Namespaces

C++

```
#include <iostream>

using namespace std;
```

> [!note] Componentes
> 
> - `<iostream>`: Fornece `cin` e `cout` para entrada e saída de dados.
>     
> - `using namespace std;`: Elimina a necessidade do prefixo `std::`.
>     

### 2. Multiplicação de Matrizes $2 \times 2$

C++

```
void multiplicar(long long A[2][2], long long B[2][2], long long mod) {
    long long C[2][2];
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % mod;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % mod;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % mod;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % mod;

    A[0][0] = C[0][0]; A[0][1] = C[0][1];
    A[1][0] = C[1][0]; A[1][1] = C[1][1];
}
```

> [!info] Mecânica Operacional
> 
> - **Entrada:** Matrizes $A$ e $B$ de tamanho $2 \times 2$ e um escalar de módulo `mod`.
>     
> - **Matriz Auxiliar `C`:** Garante que os valores originais de $A$ não sejam sobrescritos no meio das multiplicações.
>     
> - **Aritmética Modular:** Aplica `% mod` em cada célula calculada para evitar estouro de memória (_overflow_).
>     
> - **Saída:** Copia o resultado contido em `C` de volta para a matriz `A`.
>     

### 3. Exponenciação Rápida de Matrizes

C++

```
void potenciaMatriz(long long M[2][2], unsigned long long n, long long mod) {
    long long resultado[2][2] = {{1, 0}, {0, 1}}; // Matriz Identidade
    long long base[2][2] = {{M[0][0], M[0][1]}, {M[1][0], M[1][1]}};

    while (n > 0) {
        if (n % 2 == 1) {
            multiplicar(resultado, base, mod);
        }
        multiplicar(base, base, mod);
        n /= 2;
    }

    M[0][0] = resultado[0][0]; M[0][1] = resultado[0][1];
    M[1][0] = resultado[1][0]; M[1][1] = resultado[1][1];
}
```

> [!math] Algoritmo de Divisão e Conquista
> 
> - **Matriz Identidade (`resultado`):** Funciona como o número $1$ na multiplicação escalar ($M \times I = M$).
>     
> - **Variável `base`:** Armazena as potências quadráticas da matriz ($M, M^2, M^4, M^8, \dots$).
>     
> - **Laço `while (n > 0)`:**
>     
>     - Se `n` for ímpar (`n % 2 == 1`), multiplica o acumulador `resultado` pela `base` atual.
>         
>     - Eleva a `base` ao quadrado: `base = base * base`.
>         
>     - Divide o expoente pela metade: `n /= 2`.
>         

### 4. Função Principal (`main`)

C++

```
int main() {
    unsigned long long n;
    long long b;
    int caso = 1;

    while (cin >> n >> b && !(n == 0 && b == 0)) {
        long long M[2][2] = {{1, 1}, {1, 0}};

        potenciaMatriz(M, n, b);

        long long fib_n_mais_1 = M[0][0];
        long long chamadas = (2 * fib_n_mais_1 - 1) % b;

        if (chamadas < 0) {
            chamadas += b;
        }

        cout << "Case " << caso++ << ": " << n << " " << b << " " << chamadas << "\n";
    }

    return 0;
}
```

> [!tip] Estrutura do Controle de Execução
> 
> - **Tipos de Dados:** `unsigned long long` para $n$ (capaz de armazenar números de 64 bits positivos até $1.8 \times 10^{19}$).
>     
> - **Condição de Parada:** `!(n == 0 && b == 0)` interrompe a execução ao ler `0 0`.
>     
> - **Propriedade da Matriz de Fibonacci:**
>     
>     $$\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^n = \begin{pmatrix} fib(n+1) & fib(n) \\ fib(n) & fib(n-1) \end{pmatrix}$$
>     
> - **Ajuste para Módulo Negativo:** O comando `if (chamadas < 0) chamadas += b;` trata eventuais resultados negativos gerados pela operação `- 1`.
>     

## 💻 Código Completo Compilável

C++

```
#include <iostream>

using namespace std;

// Função para multiplicar duas matrizes 2x2 com módulo
void multiplicar(long long A[2][2], long long B[2][2], long long mod) {
    long long C[2][2];
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % mod;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % mod;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % mod;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % mod;

    A[0][0] = C[0][0]; A[0][1] = C[0][1];
    A[1][0] = C[1][0]; A[1][1] = C[1][1];
}

// Eleva a matriz M à potência n em O(log n)
void potenciaMatriz(long long M[2][2], unsigned long long n, long long mod) {
    long long resultado[2][2] = {{1, 0}, {0, 1}};
    long long base[2][2] = {{M[0][0], M[0][1]}, {M[1][0], M[1][1]}};

    while (n > 0) {
        if (n % 2 == 1) {
            multiplicar(resultado, base, mod);
        }
        multiplicar(base, base, mod);
        n /= 2;
    }

    M[0][0] = resultado[0][0]; M[0][1] = resultado[0][1];
    M[1][0] = resultado[1][0]; M[1][1] = resultado[1][1];
}

int main() {
    unsigned long long n;
    long long b;
    int caso = 1;

    while (cin >> n >> b && !(n == 0 && b == 0)) {
        long long M[2][2] = {{1, 1}, {1, 0}};

        potenciaMatriz(M, n, b);

        long long fib_n_mais_1 = M[0][0];
        long long chamadas = (2 * fib_n_mais_1 - 1) % b;

        if (chamadas < 0) {
            chamadas += b;
        }

        cout << "Case " << caso++ << ": " << n << " " << b << " " << chamadas << "\n";
    }

    return 0;
}
```

## ⚡ Análise de Complexidade

| **Métrica**         | **Complexidade** | **Justificativa**                                                           |
| ------------------- | ---------------- | --------------------------------------------------------------------------- |
| **Tempo**           | $O(\log n)$      | A exponenciação binária reduz $n$ pela metade em cada iteração do `while`.  |
| **Espaço Auxiliar** | $O(1)$           | Utiliza matrizes fixas de tamanho $2 \times 2$ alocadas na pilha (_stack_). |