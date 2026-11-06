---
assunto: Estrutura de Dados
date: 2026-10-23
---
- Processos particulares para **armazenamento**, **organização** e **manipulação** de dados.
- São dinâmicas e tornam o código mais organizado.
- Podem ser classificas em:
	1. lineares ou não lineares; (Vetor • Listas Ligadas | Grafo)
	2. homogêneas ou heterogêneas; 
	3. estáticas ou dinâmicas; 

---
## **Busca Sequencial**

Nessa estratégia, cada elemento da estrutura de dados é visitado de maneira sequencial (de acordo com a ordem de inserção, por exemplo:

![[Pasted image 20261023183104.png|630]]

![[Pasted image 20261023183519.png|631]]


## Complexidade O(n)

```tikz
\begin{document}

\begin{tikzpicture}

% Eixos
\draw[->] (0,0) -- (7,0) node[right] {$n$};
\draw[->] (0,0) -- (0,5) node[above] {Operações};

% Linha da complexidade O(n)
\draw[thick] (0,0) -- (6,4.2);

% Pontos
\fill (1,0.7) circle (2pt);
\fill (2,1.4) circle (2pt);
\fill (3,2.1) circle (2pt);
\fill (4,2.8) circle (2pt);
\fill (5,3.5) circle (2pt);
\fill (6,4.2) circle (2pt);

% Identificação da curva
\node[above right] at (4,2.8) {$O(n)$};

% Valores do eixo x
\node[below] at (1,0) {$1$};
\node[below] at (2,0) {$2$};
\node[below] at (3,0) {$3$};
\node[below] at (4,0) {$4$};
\node[below] at (5,0) {$5$};
\node[below] at (6,0) {$n$};

\end{tikzpicture}

\end{document}
```


---
## **Busca Binária**

Nessa estratégia, os elementos devem estar previamente ordenados.
A busca começa por um elemento central.

Caso o elemento buscado seja maior que o elemento central, a busca começa novamente considerando apenas a metade superior da estrutura, ou a metade inferior, caso o elemento seja menor.

![[Pasted image 20261023184705.png]]

![[Pasted image 20261023185223.png]]


### **Complexidade**

```tikz
\begin{document}

\begin{tikzpicture}[scale=0.9]

% Eixos
\draw[->] (0,0) -- (7,0) node[right] {$n$};
\draw[->] (0,0) -- (0,5) node[above] {Operações};

% Curva O(log_2 n)
\draw[thick, domain=0.1:6, samples=100]
    plot (\x, {2*ln(\x)/ln(2) + 1});

% Identificação da curva
\node[above right] at (4,4) {$O(\log_2 n)$};

% Valores do eixo x
\node[below] at (1,0) {$1$};
\node[below] at (2,0) {$2$};
\node[below] at (3,0) {$3$};
\node[below] at (4,0) {$4$};
\node[below] at (5,0) {$5$};
\node[below] at (6,0) {$n$};

\end{tikzpicture}

\end{document}
```


---

