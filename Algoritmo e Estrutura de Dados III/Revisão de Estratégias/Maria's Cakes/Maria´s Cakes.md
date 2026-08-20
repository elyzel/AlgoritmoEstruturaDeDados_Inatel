# 🎂 Bolos de Maria (Otimização de Custos)

> [!abstract] **Visão Geral do Problema**
> 
> Maria tem um orçamento $D$ para comprar ingredientes e deve escolher **um único tipo de bolo** dentre $B$ opções disponíveis para assar o maior número de unidades possíveis.
> 
> Cada bolo possui uma lista de ingredientes e suas respectivas quantidades, e cada ingrediente possui um custo unitário fixo.

## 🧠 Modelagem Matemática

Para cada receita $b \in \{1, 2, \dots, B\}$:

$$\text{Custo}(b) = \sum_{k=1}^{Q_b} \text{preco}[\text{indice}_k] \times \text{quantidade}_k$$

$$\text{QtdBolos}(b) = \left\lfloor \frac{D}{\text{Custo}(b)} \right\rfloor$$

$$\text{Resposta} = \max_{1 \le b \le B} \text{QtdBolos}(b)$$

## 🔍 Explicação Detalhada de Cada Bloco e Linha do Código

### Bloco 1: Importação de Bibliotecas e Otimização de E/S

C++

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
```

- **`#include <iostream>`**: Permite usar os fluxos padrão de leitura (`cin`) e escrita (`cout`).
    
- **`#include <vector>`**: Fornece o contêiner dinâmico `std::vector` para armazenar a lista de preços dos ingredientes.
    
- **`#include <algorithm>`**: Fornece a função `max(a, b)` para calcular o valor máximo entre duas variáveis.
    
- **`using namespace std;`**: Permite o uso direto das funções e tipos da biblioteca padrão sem o prefixo `std::`.
    

### Bloco 2: Estrutura Principal e Controle dos Casos de Teste

C++

```
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            long long D;
            int I, B;
            cin >> D >> I >> B;
```

- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Desacopla o fluxo do C++ dos fluxos padrão de C, acelerando a velocidade de entrada e saída.
    
- **`int T;`**: Variável que guarda a quantidade total de casos de teste a serem executados.
    
- **`while (T--)`**: Laço que decrementa $T$ a cada iteração até processar todos os casos de teste.
    
- **`long long D; int I, B;`**:
    
    - `D`: Dinheiro disponível de Maria ($1 \le D \le 10^9$). Declarado como `long long` para suportar valores de até $10^9$ com segurança.
        
    - `I`: Quantidade de ingredientes existentes no catálogo ($1 \le I \le 100$).
        
    - `B`: Quantidade de tipos de bolos disponíveis ($1 \le B \le 100$).
        

### Bloco 3: Leitura e Armazenamento dos Preços dos Ingredientes

C++

```
            vector<long long> preco(I);
            for (int i = 0; i < I; i++) {
                cin >> preco[i];
            }

            long long max_bolos = 0;
```

- **`vector<long long> preco(I);`**: Aloca um vetor de tamanho $I$, onde a posição `i` armazena o preço de $1$ unidade do ingrediente com identificador `i`.
    
- **`for (int i = 0; i < I; i++) { cin >> preco[i]; }`**: Preenche o vetor `preco` com os valores informados na entrada.
    
- **`long long max_bolos = 0;`**: Variável acumuladora que armazenará a maior quantidade de bolos possíveis encontrada entre todas as receitas avaliadas.
    

### Bloco 4: Cálculo do Custo de Cada Receita e Divisão de Orçamento

C++

```
            for (int b = 0; b < B; b++) {
                int Q;
                cin >> Q;

                long long custo_bolo = 0;

                for (int k = 0; k < Q; k++) {
                    int indice;
                    long long quantidade;
                    cin >> indice >> quantidade;

                    custo_bolo += preco[indice] * quantidade;
                }

                if (custo_bolo > 0) {
                    long long bolos_possiveis = D / custo_bolo;
                    max_bolos = max(max_bolos, bolos_possiveis);
                }
            }
```

- **`for (int b = 0; b < B; b++)`**: Itera por cada uma das $B$ receitas de bolo.
    
- **`int Q; cin >> Q;`**: Lê a quantidade de ingredientes diferentes exigidos pela receita atual.
    
- **`long long custo_bolo = 0;`**: Inicializa o custo total para produzir $1$ unidade desse bolo.
    
- **`for (int k = 0; k < Q; k++)`**: Percorre os $Q$ ingredientes da receita:
    
    - `cin >> indice >> quantidade;`: Lê o código do ingrediente (`0` a `I-1`) e a quantidade necessária.
        
    - `custo_bolo += preco[indice] * quantidade;`: Multiplica o preço unitário pela quantidade requerida e acumula no custo do bolo.
        
- **`long long bolos_possiveis = D / custo_bolo;`**: A divisão inteira em C++ trunca as casas decimais automaticamente, calculando o número exato de bolos inteiros que cabem no orçamento $D$.
    
- **`max_bolos = max(max_bolos, bolos_possiveis);`**: Atualiza o recorde se essa receita permitir produzir mais bolos que as anteriores.
    

### Bloco 5: Impressão do Resultado

C++

```
            cout << max_bolos << "\n";
        }
    }

    return 0;
}
```

- **`cout << max_bolos << "\n";`**: Imprime o valor máximo de bolos obtido para o caso de teste atual.
    
- **`return 0;`**: Finaliza o programa indicando encerramento com sucesso.
    

## ⚡ Tabela de Análise de Complexidade

| **Métrica** | **Complexidade**   | **Detalhes**                                                                                                                                                                                          |
| ----------- | ------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Tempo**   | $O(I + B \cdot Q)$ | Leitura de $I$ preços mais $B$ receitas com até $Q$ ingredientes. Para $B, Q, I \le 100$, realiza no máximo $\approx 10.000$ operações simples por caso de teste (execução praticamente instantânea). |
| **Espaço**  | $O(I)$             | Alocação apenas do vetor `preco` de tamanho $I \le 100$.                                                                                                                                              |