# 📚 Algoritmos III - Banco de Exercícios e Simulado

---

## 📝 Questão 1 (Mochila 0/1 - Força Bruta)

### Enunciado
Para o problema da mochila, tenho uma mochila com capacidade $C = 5\text{ kg}$, e os seguintes objetos:

| Objeto | Peso | Valor |
| :---: | :---: | :---: |
| 1 | 2 | 30 |
| 2 | 2 | 60 |
| 3 | 1 | 30 |
| 4 | 1 | 20 |
| 5 | 2 | 40 |
| 6 | 3 | 80 |
| 7 | 1 | 40 |

> Usando a estratégia de **força bruta** vamos fazer no máximo `[ 128 / 2^7 ]` comparações no pior caso, sendo que a solução nesse caso são os itens `[ 2, 6 ]` (ou `{2, 7, 3, 4}` dependendo da combinação de valor máximo $150$: itens `2, 6` peso $5$, valor $140$; ou `2, 6`? Vamos checar: $2(2,60) + 6(3,80) \to$ peso $5$, valor $140$. Já $2(60) + 7(40) + 3(30) + 4(20) \to$ peso $2+1+1+1=5$, valor $150$!). Portanto, essa `[ é ]` a melhor solução possível.

---

### 💡 Solução Detalhada
1. **Número de combinações avaliadas por Força Bruta:**
   - Com $N = 7$ objetos e decisão binária (pegar ou não pegar), o número de subconjuntos possíveis é:
     $$2^N = 2^7 = 128$$
2. **Melhor Solução (Ótima Global):**
   - Combinação $\{2, 3, 4, 7\}$:
     - Peso total: $2 + 1 + 1 + 1 = 5\text{ kg} \le 5\text{ kg}$
     - Valor total: $60 + 30 + 20 + 40 = 150$
   - Outras combinações viáveis:
     - $\{2, 6\} \to \text{peso } 5, \text{valor } 140$
     - $\{6, 7, 3\} \to \text{peso } 3+1+1=5, \text{valor } 80+40+30 = 150$
   - A Força Bruta testa todas as combinações viáveis, logo a solução encontrada **é a melhor solução possível**.

---

## 📝 Questão 2 (Complexidade Conceitual - Mochila)

### Enunciado
Seja o problema da mochila com uma mochila de capacidade $C$ e $N$ objetos. Se $N = 8$ e $C = 10$, então quantas opções a solução por **força bruta** para este problema vai avaliar? E a solução por **programação dinâmica**?

Coloque a resposta no formato: `2 e 2` *(Atenção para os espaços e para o "e" minúsculo)*.

**Alternativas:**
- (a) 128 e 10
- (b) nda
- (c) 256 e 50
- (d) 128 e 80
- (e) **256 e 80**

---

### 💡 Solução Detalhada
1. **Força Bruta:**
   - Avalia todas as $2^N$ combinações possíveis do conjunto das partes (*power set*):
     $$2^8 = 256\text{ opções}$$
2. **Programação Dinâmica:**
   - Preenche uma tabela de dimensões $N \times C$ (ou $(N+1) \times (C+1)$ subproblemas):
     $$\text{Complexidade } \Theta(N \cdot C) = 8 \times 10 = 80\text{ estados/avaliações}$$
3. **Resposta Correta:** **(e) 256 e 80**

---

## 📝 Questão 3 (Multiplicação de Cadeia de Matrizes - Programação Dinâmica)

### Enunciado
Tenho que realizar a multiplicação de matrizes abaixo:
$$A_0 \times A_1 \times A_2 \times A_3$$

As dimensões das matrizes são dadas abaixo:
| Matriz | Dimensões |
| :---: | :---: |
| $A_0$ | $20 \times 35$ |
| $A_1$ | $35 \times 15$ |
| $A_2$ | $15 \times 10$ |
| $A_3$ | $10 \times 55$ |

O algoritmo padrão de multiplicação $C = A \times B$ executa a linha interna `C[i,j] = C[i,j] + A[i,k]*B[k,j]` exatamente $\text{rows}(A) \times \text{cols}(A) \times \text{cols}(B)$ vezes.

Usando a técnica de programação dinâmica, determine o **menor número possível** de vezes que a linha será executada.

---

### 💡 Solução Detalhada
Vetor de dimensões: $p = [20, 35, 15, 10, 55]$, com $n=4$ matrizes ($A_0, A_1, A_2, A_3$).

1. **Cadeias de tamanho 1:**
   - $m[0,0] = m[1,1] = m[2,2] = m[3,3] = 0$

2. **Cadeias de tamanho 2:**
   - $m[0,1] = 20 \times 35 \times 15 = 10.500$
   - $m[1,2] = 35 \times 15 \times 10 = 5.250$
   - $m[2,3] = 15 \times 10 \times 55 = 8.250$

3. **Cadeias de tamanho 3:**
   - Para $A_0 \dots A_2$:
     - $k=0: m[0,0] + m[1,2] + 20 \cdot 35 \cdot 10 = 0 + 5250 + 7000 = 12.250$
     - $k=1: m[0,1] + m[2,2] + 20 \cdot 15 \cdot 10 = 10500 + 0 + 3000 = 13.500$
     - $\implies m[0,2] = 12.250$ (com corte em $k=0$)
   - Para $A_1 \dots A_3$:
     - $k=1: m[1,1] + m[2,3] + 35 \cdot 15 \cdot 55 = 0 + 8250 + 28875 = 37.125$
     - $k=2: m[1,2] + m[3,3] + 35 \cdot 10 \cdot 55 = 5250 + 0 + 19250 = 24.500$
     - $\implies m[1,3] = 24.500$ (com corte em $k=2$)

4. **Cadeia completa de tamanho 4 ($A_0 \dots A_3$):**
   - $k=0: m[0,0] + m[1,3] + 20 \cdot 35 \cdot 55 = 0 + 24500 + 38500 = \mathbf{63.000}$
   - $k=1: m[0,1] + m[2,3] + 20 \cdot 15 \cdot 55 = 10500 + 8250 + 16500 = \mathbf{35.250}$
   - $k=2: m[0,2] + m[3,3] + 20 \cdot 10 \cdot 55 = 12250 + 0 + 11000 = \mathbf{23.250}$

O menor valor é para $k=2$: $((A_0 \times A_1) \times A_2) \times A_3 \implies \mathbf{23250}$.

- **Resposta numérica:** `23250`

---

## 📝 Questão 4 (Mochila - Abordagem Gulosa com Valores Iguais)

### Enunciado
Para o problema da mochila, tenho uma mochila com capacidade $C = 5\text{ kg}$, e os seguintes objetos:

| Objeto | Peso | Valor |
| :---: | :---: | :---: |
| 1 | 2 | 10 |
| 2 | 2 | 10 |
| 3 | 1 | 10 |
| 4 | 1 | 10 |
| 5 | 2 | 10 |
| 6 | 3 | 10 |
| 7 | 1 | 10 |

> Usando a estratégia gulosa vamos fazer no máximo `[ 7 ]` comparações no pior caso (ou $N \log N$ na ordenação), sendo que a solução nesse caso são os itens `[ 3, 4, 7, 1 ]` (ou qualquer combinação de menor peso). Portanto, essa `[ é ]` a melhor solução possível.

---

### 💡 Solução Detalhada
1. **Heurística Gulosa:**
   - Densidade de valor $\frac{V}{P}$:
     - Itens 3, 4, 7: $\frac{10}{1} = 10$
     - Itens 1, 2, 5: $\frac{10}{2} = 5$
     - Item 6: $\frac{10}{3} = 3.33$
2. **Seleção:**
   - Pega 3 (peso 1), 4 (peso 1), 7 (peso 1) $\to$ Peso acumulado: $3\text{ kg}$, Valor: $30$.
   - Restam $2\text{ kg}$: pega o item 1 (ou 2, ou 5) de peso 2 $\to$ Peso total: $5\text{ kg}$, Valor total: $40$.
3. **Otimalidade:**
   - Como todos os itens possuem o mesmo valor individual, maximizar o valor é equivalente a empacotar o maior número possível de itens (menores pesos primeiro). A estratégia gulosa **encontra a solução ótima global** neste caso específico.

---

## 📝 Questão 5 (Mochila 0/1 - Limitação da Abordagem Gulosa)

### Enunciado
Para o problema da mochila, tenho uma mochila com capacidade $C = 5\text{ kg}$, e os seguintes objetos:

| Objeto | Peso | Valor |
| :---: | :---: | :---: |
| 1 | 2 | 30 |
| 2 | 2 | 60 |
| 3 | 1 | 30 |
| 4 | 1 | 20 |
| 5 | 2 | 40 |
| 6 | 3 | 80 |
| 7 | 1 | 40 |

> Usando a estratégia gulosa vamos fazer no máximo `[ 7 ]` comparações no pior caso, sendo que a solução nesse caso são os itens `[ 7, 2, 3, 4 ]` (Valor: 150). Portanto, essa `[ não é / é ]` a melhor solução possível.

---

### 💡 Solução Detalhada
1. **Densidades $\frac{\text{Valor}}{\text{Peso}}$:**
   - Item 7: $\frac{40}{1} = 40$
   - Item 2: $\frac{60}{2} = 30$
   - Item 3: $\frac{30}{1} = 30$
   - Item 6: $\frac{80}{3} \approx 26.67$
   - Item 4: $\frac{20}{1} = 20$
   - Item 5: $\frac{40}{2} = 20$
   - Item 1: $\frac{30}{2} = 15$
2. **Seleção Gulosa (capacidade = 5):**
   - Pega Item 7 (peso 1, cap restante 4)
   - Pega Item 2 (peso 2, cap restante 2)
   - Pega Item 3 (peso 1, cap restante 1)
   - Pega Item 4 (peso 1, cap restante 0)
   - **Itens selecionados:** $\{7, 2, 3, 4\}$, Peso total $= 5$, Valor total $= 40 + 60 + 30 + 20 = 150$.
3. **Observação conceitual:** O algoritmo guloso para a mochila 0/1 nem sempre garante a solução ótima em todos os casos gerais, mas para esta instância específica obteve $150$ (o ótimo absoluto).

---

## 📝 Questão 6 (Armazenamento em Mídia / Algoritmo Guloso)

### Enunciado
Abaixo, tenho uma listagem de vários arquivos de música com o respectivo tamanho em MB:

| Arquivo | Tamanho (MB) |
| :---: | :---: |
| 1 | 3,0 |
| 2 | 4,3 |
| 3 | 2,1 |
| 4 | 2,5 |
| 5 | 4,7 |
| 6 | 5,9 |
| 7 | 2,2 |

Quero armazenar o **maior número de músicas possível** em um pendrive de capacidade $15\text{ MB}$. Se usar a estratégia gulosa, a ordem em que eu vou selecionar os arquivos será:

**Alternativas:**
- (a) 3, 7, 4, 1, 2, 5, 6
- (b) 3, 7, 4, 1
- (c) **3, 7, 4, 1, 2**

---

### 💡 Solução Detalhada
1. **Critério Guloso:** Para maximizar a **quantidade** de itens, ordenamos pelo **menor tamanho**:
   - 1º: Arquivo 3 ($2,1\text{ MB}$) $\to$ Acumulado: $2,1\text{ MB}$
   - 2º: Arquivo 7 ($2,2\text{ MB}$) $\to$ Acumulado: $4,3\text{ MB}$
   - 3º: Arquivo 4 ($2,5\text{ MB}$) $\to$ Acumulado: $6,8\text{ MB}$
   - 4º: Arquivo 1 ($3,0\text{ MB}$) $\to$ Acumulado: $9,8\text{ MB}$
   - 5º: Arquivo 2 ($4,3\text{ MB}$) $\to$ Acumulado: $14,1\text{ MB}$
   - 6º: Arquivo 5 ($4,7\text{ MB}$) $\to 14,1 + 4,7 = 18,8\text{ MB} > 15\text{ MB}$ (Não cabe!)
2. **Resposta Correta:** **(c) 3, 7, 4, 1, 2**

---

## 📝 Questão 7 (Subvetor de Soma Mínima / Saldo de Gols)

### Enunciado
Na tabela abaixo têm-se os resultados de 7 jogos realizados pelo meu time:

| Jogo | Gols marcados | Gols sofridos | Saldo ($M - S$) |
| :---: | :---: | :---: | :---: |
| 1 | 2 | 1 | $+1$ |
| 2 | 2 | 2 | $0$ |
| 3 | 3 | 1 | $+2$ |
| 4 | 1 | 5 | $-4$ |
| 5 | 3 | 3 | $0$ |
| 6 | 2 | 3 | $-1$ |
| 7 | 4 | 1 | $+3$ |

Determine o maior intervalo contínuo em que o saldo de gols do meu time foi **mínimo** (menor valor acumulado possível).

**Alternativas:**
- (a) nda
- (b) 2-5
- (c) 3-7
- (d) 1-3
- (e) **4-6**

---

### 💡 Solução Detalhada
1. Vetor de saldos: $S = [+1, 0, +2, -4, 0, -1, +3]$
2. Avaliando os intervalos negativos:
   - Jogo 4: $-4$
   - Jogos 4 a 5: $-4 + 0 = -4$
   - Jogos 4 a 6: $-4 + 0 + (-1) = \mathbf{-5}$ (mínimo absoluto)
   - Jogos 4 a 7: $-5 + 3 = -2$
3. **Resposta Correta:** **(e) 4-6**

---

## 📝 Questão 8 (Mochila 0/1 - Programação Dinâmica Iterativa)

### Enunciado
Para o mesmo conjunto de 7 objetos e capacidade $C = 5\text{ kg}$:
> Usando a estratégia de **PD iterativa** vamos fazer no máximo `[ 35 / N*C ]` comparações no pior caso, sendo que a solução nesse caso são os itens `[ 2, 3, 4, 7 ]`. Portanto, essa `[ é ]` a melhor solução possível.

---

### 💡 Solução Detalhada
1. A tabela de PD possui dimensões $N \times C = 7 \times 5 = 35$ células computadas (ou $(7+1) \times (5+1)$ com as bordas nulas).
2. A Programação Dinâmica garante encontrar o **ótimo global** para o problema da mochila inteira (0/1) em tempo pseudo-polinomial $\mathcal{O}(N \cdot C)$.