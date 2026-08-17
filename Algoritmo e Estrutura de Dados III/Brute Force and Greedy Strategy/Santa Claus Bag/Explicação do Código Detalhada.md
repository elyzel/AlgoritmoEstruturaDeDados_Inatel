# 🎅 Resolução Didática: O Saco do Papai Noel (Mochila 0/1)

> [!abstract] **O Desafio**
> 
> O Papai Noel tem um limite estrito de **50 kg** para colocar no saco de presentes. Cada pacote de presentes tem uma **quantidade de brinquedos** e um **peso em kg**.
> 
> O objetivo é **maximizar o número total de brinquedos** sem estourar os 50 kg, além de informar o peso final usado e quantos pacotes sobraram.

## 💡 1. Entendendo os Conceitos Principais (Sem Complicação)

Antes de olhar o código, precisamos entender as 3 peças fundamentais que usamos:

### A. O que é o `std::vector`?

Imagine que um array comum (`int arr[100]`) é uma **caixa de papelão com tamanho fixo**. Você precisa adivinhar o tamanho antes de usar.

O `std::vector` é uma **caixa mágica flexível**: você pode definir o tamanho exato que precisa enquanto o programa está rodando (`vector<int> qt(Pac + 1)`).

> [!tip] **Por que usamos `vector<vector<int>>`?**
> 
> É simplesmente uma **tabela (matriz)** dinâmica de duas dimensões, com linhas e colunas organizadas!

### B. O que faz a biblioteca `<algorithm>`?

Ela nos dá a função `max(Opção_A, Opção_B)`. Ela funciona como um juiz: compara dois valores e devolve o maior. É ela quem toma a decisão de qual escolha nos dá mais brinquedos.

### C. A Lógica da Programação Dinâmica (A "Tabela Gabarito")

Em vez de adivinhar todas as combinações do zero, nós montamos uma **tabela de decisões** onde:

- **Linhas (`i`):** Representam os pacotes disponíveis até aquele momento ($1, 2, 3 \dots$).
    
- **Colunas (`w`):** Representam limites de peso temporários ($0\text{ kg}, 1\text{ kg}, 2\text{ kg} \dots 50\text{ kg}$).
    

Cada célula `dp[i][w]` guarda a resposta para a pergunta:

> _"Se eu só tivesse os pacotes de $1$ a $i$, e um saco que aguenta no máximo $w$ kg, qual é o número máximo de brinquedos que conseguiria levar?"_

## ⚙️ 2. O Processo de Decisão (Como o Código "Pensa")

Para cada pacote $i$ com peso `peso[i]` e brinquedos `qt[i]`:

Plaintext

```
                     ┌─ O pacote CABE no limite w? ─┐
                     │                              │
                    SIM                             NÃO
                     │                              │
         ┌───────────┴───────────┐         Copiar o resultado de cima:
         │  Escolher o MAIOR entre:  │         dp[i][w] = dp[i-1][w]
         │                       │
   OPÇÃO 1: NÃO LEVAR       OPÇÃO 2: LEVAR
   Manter o valor de cima   Somar os brinquedos dele +
   dp[i-1][w]               o melhor das sobras de peso
                            dp[i-1][w - peso[i]] + qt[i]
```

## 📝 3. O Código Completo e Comentado

C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N; // Quantidade de viagens (casos de teste)
    
    if (cin >> N) {
        while (N--) {
            int Pac; // Quantidade de pacotes disponíveis nesta viagem
            cin >> Pac;

            // Aloca os vetores de brinquedos e peso com tamanho (Pac + 1)
            vector<int> qt(Pac + 1);
            vector<int> peso(Pac + 1);

            // Leitura dos dados de cada pacote
            for (int i = 1; i <= Pac; i++) {
                cin >> qt[i] >> peso[i];
            }

            int CAPACIDADE = 50; // Limite de peso estipulado
            
            // Tabela DP com (Pac + 1) linhas e (CAPACIDADE + 1) colunas, preenchida com 0
            vector<vector<int>> dp(Pac + 1, vector<int>(CAPACIDADE + 1, 0));

            // ====================================================
            // PASSO 1: Preenchimento da Tabela de Decisões
            // ====================================================
            for (int i = 1; i <= Pac; i++) {
                for (int w = 0; w <= CAPACIDADE; w++) {
                    if (peso[i] <= w) {
                        // O pacote cabe! Testamos as duas opções e pegamos a melhor:
                        dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - peso[i]] + qt[i]);
                    } else {
                        // O pacote é pesado demais para o limite 'w'. Não podemos levar.
                        dp[i][w] = dp[i - 1][w];
                    }
                }
            }

            // O resultado ótimo final fica na última célula da matriz
            int brinquedos = dp[Pac][CAPACIDADE];

            // ====================================================
            // PASSO 2: Rastreamento para Trás (Descobrir quais pacotes usamos)
            // ====================================================
            int w = CAPACIDADE;
            int peso_total = 0;
            int pacotes_levados = 0;

            for (int i = Pac; i > 0; i--) {
                // Se o valor mudou em relação à linha de cima, o pacote 'i' FOI SELECIONADO!
                if (dp[i][w] != dp[i - 1][w]) {
                    peso_total += peso[i];   // Soma o peso do pacote
                    pacotes_levados++;       // Incrementa a contagem de pacotes usados
                    w -= peso[i];            // Subtrai o peso para continuar rastreando o resto
                }
            }

            int pacotes_sobrando = Pac - pacotes_levados;

            // ====================================================
            // PASSO 3: Impressão dos Resultados
            // ====================================================
            cout << brinquedos << " brinquedos" << endl;
            cout << "Peso: " << peso_total << " kg" << endl;
            cout << "Sobra(m): " << pacotes_sobrando << " pacote(s)" << endl;
            cout << endl; // Linha em branco exigida pelo Beecrowd
        }
    }

    return 0;
}
```

## 🔍 4. Detalhando o Trabalhado do "Detetive" (Backtracking)

Depois de preencher toda a matriz, sabemos que o número máximo de brinquedos está em `dp[Pac][50]`. Mas **como descobrir o peso total e quantos pacotes sobraram?**

> [!example] **A Lógica do Rastreamento**
> 
> Olhamos para a última célula e comparamos com a célula **imediatamente acima dela**:
> 
> - **`dp[i][w] == dp[i - 1][w]`** $\rightarrow$ O número de brinquedos **não mudou** ao analisar o pacote $i$. Isso significa que o pacote $i$ **foi ignorado**.
>     
> - **`dp[i][w] != dp[i - 1][w]`** $\rightarrow$ O número de brinquedos **aumentou**! Isso significa que o pacote $i$ **foi colocado no saco**.
>     
>     - Então, somamos o peso dele (`peso_total += peso[i]`) e descontamos da nossa capacidade de busca (`w -= peso[i]`).
>         

## 📊 5. Análise de Desempenho

|**Métrica**|**Complexidade**|**O que significa na prática?**|
|---|---|---|
|**Tempo**|$O(\text{Pac} \times 50)$|Como a capacidade máxima é fixa ($50$), o programa executa no máximo $100 \times 50 = 5000$ operações simples por viagem. **Roda instantaneamente.**|
|**Espaço**|$O(\text{Pac} \times 50)$|Cria uma matriz de no máximo $101 \times 51$ inteiros, gastando menos de $25 \text{ KB}$ de memória.|