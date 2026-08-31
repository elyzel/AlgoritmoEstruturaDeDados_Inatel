# 🏋️ Exercícios Inéditos para Fixação

### Exercício 1 (Mochila 0/1 e Análise de Complexidade)
Um drone de entregas suporta carga máxima de $W = 6\text{ kg}$. Temos 5 pacotes disponíveis:
- $P_1$: $(2\text{ kg}, \text{R\$} 40)$
- $P_2$: $(3\text{ kg}, \text{R\$} 50)$
- $P_3$: $(1\text{ kg}, \text{R\$} 25)$
- $P_4$: $(4\text{ kg}, \text{R\$} 70)$
- $P_5$: $(2\text{ kg}, \text{R\$} 35)$

1. Quantos subconjuntos a força bruta analisaria?
2. Quantos estados a tabela de Programação Dinâmica possui?
3. Qual é a combinação ótima e o valor máximo?

<details>
<summary><b>Ver Resposta</b></summary>

1. **Força Bruta:** $2^5 = 32$ combinações.
2. **PD:** $N \times W = 5 \times 6 = 30$ estados úteis.
3. **Solução Ótima:**
   - Pacotes $\{P_1, P_3, P_5\} \to \text{peso } 2+1+2=5\text{ kg}, \text{valor } 100$
   - Pacotes $\{P_3, P_4\} \to \text{peso } 1+4=5\text{ kg}, \text{valor } 95$
   - Pacotes $\{P_1, P_2, P_3\} \to \text{peso } 2+3+1=6\text{ kg}, \text{valor } 40+50+25 = \mathbf{115}$ (ÓTIMO)
</details>

---

### Exercício 2 (Multiplicação de Cadeia de Matrizes)
Dadas três matrizes com as seguintes dimensões:
- $M_1: 10 \times 100$
- $M_2: 100 \times 5$
- $M_3: 5 \times 50$

Calcule o número mínimo de multiplicações escalares para calcular $M_1 \times M_2 \times M_3$.

<details>
<summary><b>Ver Resposta</b></summary>

- **Ordem 1: $(M_1 \times M_2) \times M_3$**
  - $M_1 \times M_2$: $10 \times 100 \times 5 = 5.000$ (gera matriz $10 \times 5$)
  - Multiplicação final: $10 \times 5 \times 50 = 2.500$
  - **Total:** $5.000 + 2.500 = \mathbf{7.500}$

- **Ordem 2: $M_1 \times (M_2 \times M_3)$**
  - $M_2 \times M_3$: $100 \times 5 \times 50 = 25.000$ (gera matriz $100 \times 50$)
  - Multiplicação final: $10 \times 100 \times 50 = 50.000$
  - **Total:** $25.000 + 50.000 = \mathbf{75.000}$

**Menor número possível:** $\mathbf{7.500}$ multiplicações com parênteses em $(M_1 \times M_2) \times M_3$.
</details>

---

### Exercício 3 (Subvetor de Soma Máxima / Algoritmo de Kadane)
Dado o histórico diário de lucros/prejuízos de um ativo:
`[-2, 1, -3, 4, -1, 2, 1, -5, 4]`

Qual é o intervalo contínuo de dias que gera o **maior lucro acumulado** e qual é esse valor?

<details>
<summary><b>Ver Resposta</b></summary>

- Aplicando Kadane:
  - Subvetor $[4, -1, 2, 1]$
  - Soma máxima: $4 + (-1) + 2 + 1 = \mathbf{6}$
</details>