## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta / Simulação Passo a Passo ($O(N^2)$):**
>     
>     Simular cada jogada fisicamente (como um _Bubble Sort_) executaria até $\frac{N(N-1)}{2} \approx 5 \times 10^9$ trocas no pior caso para $N = 10^5$, resultando em **Time Limit Exceeded (TLE)** imediato.
>     
> - ⚠️ **Estratégia Gulosa (Greedy):**
>     
>     Não se aplica para tentar "escolher a melhor jogada", pois qualquer escolha válida de inversão adjacente reduz o total de inversões em **exatamente 1**. O número total de turnos até o fim do jogo é um invariante fixo igual à quantidade total de inversões da permutação.
>     
> - ✅ **Paradigma Ideal: Divisão e Conquista (Merge Sort / $O(N \log N)$):**
>     
>     Como o vencedor depende unicamente da **paridade do número total de inversões** (ímpar $\rightarrow$ Marcelo, par $\rightarrow$ Carlos), adaptamos o algoritmo do _Merge Sort_ para contar as inversões durante a intercalação em tempo $O(N \log N)$.
>     

## 🧠 Modelagem Teórica do Jogo

Uma **inversão** ocorre para qualquer par de índices $(i, j)$ tal que $i < j$ e $A[i] > A[j]$.

1. Cada troca válida de elementos vizinhos desordenados elimina **exatamente uma inversão**.
    
2. O jogo termina quando não restam inversões ($0$ inversões restantes $\rightarrow$ vetor ordenado).
    
3. O total de jogadas possíveis é exatamente igual ao número de inversões $I$:
    
    - Se $I$ for **Ímpar**: Marcelo faz as jogadas $1, 3, 5, \dots, I$. Carlos não tem jogada restante $\implies$ **Marcelo vence**.
        
    - Se $I$ for **Par**: Carlos faz as jogadas $2, 4, 6, \dots, I$. Marcelo não tem jogada restante $\implies$ **Carlos vence**.

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Inclusão de Bibliotecas e Variável Acumuladora

```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long totalInversoes = 0;
```

- **`#include <iostream>`**: Responsável pela leitura e escrita de dados (`cin`, `cout`).
    
- **`#include <vector>`**: Utilizado para criar e gerenciar os vetores `arr` e `temp`.
    
- **`#include <algorithm>`**: Incluído para compatibilidade com o padrão da biblioteca de algoritmos.
    
- **`long long totalInversoes`**: O número de inversões em $10^5$ elementos pode chegar a $\approx 5 \times 10^9$, ultrapassando o limite do `int` de 32 bits ($2 \times 10^9$). Por isso, o tipo `long long` é mandatório.
    

### Bloco 2: A Função `intercalar` e a Lógica de Contagem

```C++
void intercalar(vector<int>& arr, vector<int>& temp, int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            totalInversoes += (meio - i + 1);
        }
    }
```

- **`int i = inicio, j = meio + 1, k = inicio;`**: Inicializa os índices de controle para a metade esquerda, metade direita e vetor auxiliar.
    
- **`if (arr[i] <= arr[j])`**: Quando o elemento da esquerda é menor ou igual, nenhuma inversão é gerada e ele vai para a posição ordenada.
    
- **`totalInversoes += (meio - i + 1);`**: Como ambas as metades já estão ordenadas internamente, se $arr[j] < arr[i]$, então $arr[j]$ é estritamente menor do que **todos** os elementos restantes da metade esquerda (do índice $i$ até $meio$). Somamos esse bloco inteiro de inversões em $O(1)$.
    

### Bloco 3: Finalização da Cópia da Intercalação

```C++
    while (i <= meio) temp[k++] = arr[i++];
    while (j <= fim) temp[k++] = arr[j++];

    for (i = inicio; i <= fim; i++) {
        arr[i] = temp[i];
    }
}
```

- **`while (i <= meio) ...` / `while (j <= fim) ...`**: Esvazia qualquer sobra de elementos de uma das duas metades.
    
- **`for (i = inicio; i <= fim; i++) arr[i] = temp[i];`**: Transfere o segmento ordenado de volta para o vetor principal `arr`.
    

### Bloco 4: A Função Recursiva `mergeSort`


```C++
void mergeSort(vector<int>& arr, vector<int>& temp, int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    mergeSort(arr, temp, inicio, meio);
    mergeSort(arr, temp, meio + 1, fim);
    intercalar(arr, temp, inicio, meio, fim);
}
```

- **`if (inicio >= fim) return;`**: Caso base da recursão (subvetores de tamanho $1$ ou $0$).
    
- **`int meio = inicio + (fim - inicio) / 2;`**: Calcula o ponto central evitando estouro de inteiros.
    
- **`mergeSort(...)`**: Divide o problema recursivamente em duas metades e chama `intercalar` para unir e contar inversões.
    

### Bloco 5: Laço Principal e Decisão do Vencedor

```C++
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    while (cin >> N && N != 0) {
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        vector<int> temp(N);
        totalInversoes = 0;

        mergeSort(arr, temp, 0, N - 1);

        if (totalInversoes % 2 != 0) {
            cout << "Marcelo\n";
        } else {
            cout << "Carlos\n";
        }
    }

    return 0;
}
```

- **`while (cin >> N && N != 0)`**: Itera por todos os casos de teste até o valor sentinela $0$.
    
- **`if (totalInversoes % 2 != 0)`**: Como Marcelo é o primeiro jogador, número ímpar de jogadas garante que ele fará a última jogada possível, consagrando-se campeão. Caso contrário, Carlos vence.
    

## ⚡ Tabela de Análise de Complexidade

|**Métrica**|**Complexidade**|**Justificativa**|
|---|---|---|
|**Tempo**|$O(N \log N)$|O vetor é dividido em $\log_2 N$ níveis de recursão, e cada nível realiza um trabalho linear de intercalação $O(N)$. Para $N = 10^5$, são executadas cerca de $1.7 \times 10^6$ operações.|
|**Espaço**|$O(N)$|Vetor auxiliar `temp` alocado com tamanho $N$ para a etapa de intercalação.|