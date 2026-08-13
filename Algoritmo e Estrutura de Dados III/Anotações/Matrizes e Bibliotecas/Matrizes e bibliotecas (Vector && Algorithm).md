
__Matrizes___ são compostas por uma tabela que detém linhas e colunas, como um tabuleiro de xadrez.

- __Linha vertical($i$)__: Posição vertical
- __Coluna($j$)__: Posição horizontal
- Para acessar um elemento, você diz a linha e a coluna `matriz[i][j]`.

## Vector

Em C++, os arrays tradicionais têm tamanho fixo. O `vector` é um __array dinâmico__ que cresce e diminui conforme a necessidade e gerencia a memória de forma segura.

Para criar uma matriz de inteiros $3 \times 4$ (3 linhas e 4 colunas) preenchidos com zeros usando `vector`.

```cpp
vector<vvector<int>> matriz(3, vector<int>(4, 0));
```

## Algorithm

Ele traz funções prontas como `std::sort` para __ordenar__, `std::max` para __para pegar o maior valor__, `std::min`, entre outras. Em programação dinâmica, você usará `std::max` o tempo todo para escolher o melhor caminho.

> [!NOTE]
> Exercício 1: Crie uma matriz $2 \times 3$, preencha-a com valores definidos por você, imprima-a no formato de tabela na tela e mostre qual é o **maior valor** presente nela usando a função `max` do `<algorithm>`

> [!NOTE]
> Exercício 2: **O Problema (Clássico de DP):** Imagine uma grelha $3 \times 3$. Você começa no canto superior esquerdo `(0,0)` e quer chegar no canto inferior direito `(2,2)`. Você só pode se mover **para a direita** ou **para baixo**. Cada célula tem um valor (moedas). Qual é a quantidade máxima de moedas que você pode coletar?
> 
> Pense assim: Para chegar em qualquer célula `(i, j)`, você obrigatoriamente veio da **esquerda** `(i, j-1)` ou de **cima** `(i-1, j)`. Então, o melhor valor para `(i, j)` é o valor atual da célula mais o **máximo** entre o que veio de cima e o que veio da esquerda!
> 
> $$dp[i][j] = grid[i][j] + \max(dp[i-1][j], dp[i][j-1])$$




