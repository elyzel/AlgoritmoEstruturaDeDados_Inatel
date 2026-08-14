## Bloco 1: Importação de Bibliotecas e Escopo

C++

```
#include <iostream>
#include <vector>
#include <algorithm> // Para usar sort() e max()

using namespace std;
```

### Explicação Linha por Linha:

- **`#include <iostream>`**: Permite usar os comandos padrão de entrada e saída (`cin` para ler dados, `cout` para imprimir na tela e `endl` para quebrar linhas).
    
- **`#include <vector>`**: Habilita o uso do contêiner `vector`, que funciona como uma lista/array dinâmico onde podemos definir o tamanho exato dos números em tempo de execução.
    
- **`#include <algorithm>`**: Importa algoritmos utilitários essenciais da biblioteca padrão:
    
    - `sort()`: Para ordenar os números em ordem crescente de forma ultra-rápida ($O(N \log N)$).
        
    - `max()`: Para comparar dois valores e retornar o maior entre eles.
        
- **`using namespace std;`**: Permite escrever diretamente `cin`, `cout`, `vector` e `sort`, sem precisar adicionar o prefixo `std::` antes de cada um.
    

## 🔄 Bloco 2: Estrutura Principal e Controle dos Casos de Teste

C++

```
int main() {
    int T;
    if (cin >> T) {
        for (int caso = 1; caso <= T; caso++) {
```

### Explicação Linha por Linha:

- **`int main() {`**: Ponto de entrada obrigatório de qualquer programa em C++. Toda a execução começa aqui.
    
- **`int T;`**: Declara a variável inteira `T`, que armazenará o número total de casos de teste a serem processados.
    
- **`if (cin >> T) {`**: Tenta ler o valor de `T`. O `if` garante segurança na leitura antes de iniciar as repetições.
    
- **`for (int caso = 1; caso <= T; caso++) {`**: Laço que itera por cada caso de teste de $1$ até $T$. O índice `caso` é usado diretamente na impressão final exigida pelo formato (`Case 1:`, `Case 2:`, etc.).
    

## 📥 Bloco 3: Leitura e Alocação dos Números

C++

```
            int n;
            cin >> n;

            // 1. Lê os n números no vector
            vector<int> A(n);
            for (int i = 0; i < n; i++) {
                cin >> A[i];
            }
```

### Explicação Linha por Linha:

- **`int n;` e `cin >> n;`**: Declara e lê a quantidade $n$ de números inteiros que pertencem ao caso de teste atual.
    
- **`vector<int> A(n);`**: Cria um vetor de inteiros chamado `A` com capacidade inicial de $n$ posições (índices de `0` até `n - 1`).
    
- **`for (int i = 0; i < n; i++) { cin >> A[i]; }`**: Percorre os índices de `0` até `n - 1`, lendo cada número digitado na entrada e guardando-o na respectiva posição do vetor `A`.
    

## 🔀 Bloco 4: Ordenação e Inicialização

C++

```
            // 2. Ordena o vetor do menor para o maior
            sort(A.begin(), A.end());

            int soma = 0;
```

### Explicação Linha por Linha:

- **`sort(A.begin(), A.end());`**: Reorganiza todos os elementos do vetor `A` do menor para o maior. Isso é essencial, pois separa os números menores (que ficarão nos primeiros índices) dos números maiores (que ficarão nos últimos índices).
    
- **`int soma = 0;`**: Inicializa o acumulador que guardará o valor total da soma máxima permutada para o caso atual.
    

## ⚖️ Bloco 5: Tratamento para $N$ PAR (`n % 2 == 0`)

C++

```
            // 3. Caso N seja PAR
            if (n % 2 == 0) {
                int k = n / 2;

                for (int i = 0; i <= k - 2; i++) soma -= 2 * A[i];
                soma -= A[k - 1];
                soma += A[k];
                for (int i = k + 1; i < n; i++) soma += 2 * A[i];
            }
```

### Explicação Linha por Linha:

- **`if (n % 2 == 0)`**: Verifica se a quantidade de elementos é um número par.
    
- **`int k = n / 2;`**: Define a metade do vetor (por exemplo, se $n = 4$, então $k = 2$).
    
- **`for (int i = 0; i <= k - 2; i++) soma -= 2 * A[i];`**: Multiplica os menores elementos por $-2$, pois na disposição alternada eles ficam no meio da sequência e são subtraídos por dois vizinhos maiores.
    
- **`soma -= A[k - 1];`**: O maior entre os números da metade inferior fica em uma das pontas extremas da fila, participando de apenas uma subtração (peso $-1$).
    
- **`soma += A[k];`**: O menor entre os números da metade superior fica na outra ponta extrema, participando de apenas uma adição (peso $+1$).
    
- **`for (int i = k + 1; i < n; i++) soma += 2 * A[i];`**: Multiplica os maiores elementos por $+2$, pois eles ficam no meio da fila e somam duas vezes em relação aos seus vizinhos menores.
    

## 🔀 Bloco 6: Tratamento para $N$ ÍMPAR (`else`)

C++

```
            // 4. Caso N seja ÍMPAR
            else {
                int k = n / 2;

                // Opção 1: Dois elementos centrais com peso -1
                int soma1 = 0;
                for (int i = 0; i <= k - 2; i++) soma1 -= 2 * A[i];
                soma1 -= A[k - 1];
                soma1 -= A[k];
                for (int i = k + 1; i < n; i++) soma1 += 2 * A[i];

                // Opção 2: Dois elementos centrais com peso +1
                int soma2 = 0;
                for (int i = 0; i <= k - 1; i++) soma2 -= 2 * A[i];
                soma2 += A[k];
                soma2 += A[k + 1];
                for (int i = k + 2; i < n; i++) soma2 += 2 * A[i];

                soma = max(soma1, soma2);
            }
```

### Explicação Linha por Linha:

- **`else {`**: Executado quando $n$ for ímpar (ex: $n = 5$, logo $k = 2$).
    
- **`int soma1 = 0;`**: Calcula a configuração onde sobram mais números grandes no meio (os dois termos centrais $A[k-1]$ e $A[k]$ vão para as pontas e recebem peso $-1$).
    
- **`int soma2 = 0;`**: Calcula a configuração alternativa onde sobram mais números pequenos no meio (os dois termos centrais $A[k]$ e $A[k+1]$ vão para as pontas e recebem peso $+1$).
    
- **`soma = max(soma1, soma2);`**: Compara as duas opções e seleciona a que produziu o maior valor final.
    

## 📤 Bloco 7: Impressão da Resposta e Finalização

C++

```
            // Impressão no padrão do problema
            cout << "Case " << caso << ": " << soma << endl;
        }
    }

    return 0;
}
```

### Explicação Linha por Linha:

- **`cout << "Case " << caso << ": " << soma << endl;`**: Imprime a mensagem formatada exatamente no padrão exigido pelo problema (`Case 1: 10`), seguido pela quebra de linha.
    
- **`}` (fechamentos)**: Encerram os laços `for`, o bloco `if` e o bloco da função principal.
    
- **`return 0;`**: Informa ao sistema operacional que o programa executou e encerrou com sucesso sem erros de execução.
