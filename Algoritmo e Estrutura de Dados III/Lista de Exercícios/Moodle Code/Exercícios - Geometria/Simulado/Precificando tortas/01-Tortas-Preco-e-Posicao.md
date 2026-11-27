---
tags: [cpp, geometria-computacional, exercicios]
---
# Exercício 1 — Preço e posição da torta

## Objetivo
Ler o peso e quatro pontos, calcular espessura, diâmetro e altura, identificar a posição e calcular o preço.

## 1. Bibliotecas e estrutura
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

struct ponto {
    int x, y;
};
```
- `iostream`: disponibiliza `cin` e `cout`.
- `cstdlib`: disponibiliza `abs()` para inteiros.
- `using namespace std`: permite usar os nomes da biblioteca padrão sem `std::`.
- `struct ponto`: agrupa duas coordenadas inteiras. É a mesma estrutura do material `geometrico.cpp` do professor.

## 2. Entrada de dados
```cpp
int peso;
ponto a, b, c, d;
cin >> peso;
cin >> a.x >> a.y;
cin >> b.x >> b.y;
cin >> c.x >> c.y;
cin >> d.x >> d.y;
```
`peso` guarda o primeiro número. Cada variável do tipo `ponto` guarda duas coordenadas. O operador `.` acessa um membro da estrutura; `>>` lê os valores na ordem da entrada. Espaços e quebras de linha funcionam como separadores.

## 3. Cálculo das dimensões
```cpp
int EM = abs(b.x - a.x);
int diametro = abs(d.x - c.x);
int altura = abs(a.y - c.y);
```
| Variável | Significado | Cálculo |
|---|---|---|
| EM | Espessura da massa | Diferença horizontal entre A e B |
| diametro | Diâmetro | Diferença horizontal entre C e D |
| altura | Altura | Diferença vertical entre A e C |

`abs()` retorna o valor absoluto, evitando medidas negativas. Por exemplo, `abs(2 - 15)` retorna 13.

> [!note] Hipótese geométrica
> A figura original não foi disponibilizada na conversa. A interpretação das coordenadas foi deduzida dos três exemplos: AB e CD são horizontais; AB mede a espessura, CD mede o diâmetro. Se houver pontos inclinados em testes não apresentados, a solução poderá precisar de adaptação.

## 4. Preço final
```cpp
int preco = EM * peso * altura + diametro + altura;
```
A multiplicação tem prioridade sobre a soma. A expressão corresponde à fórmula do enunciado:

$$PF=EM\cdot P\cdot A+D+A$$

## 5. Condicional e saída
```cpp
if (a.y > c.y) {
    cout << "Correta" << endl;
} else {
    cout << "Virada" << endl;
}
cout << preco << endl;
```
`if` testa se a borda tem coordenada vertical superior à base, conforme os exemplos. `else` executa quando a condição é falsa. `endl` encerra a linha. O caso de altura zero não foi especificado; o código o classificaria como Virada.

## 6. Código completo
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

struct ponto {
    int x, y;
};

int main() {
    int peso;
    ponto a, b, c, d;
    cin >> peso;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cin >> d.x >> d.y;

    int EM = abs(b.x - a.x);
    int diametro = abs(d.x - c.x);
    int altura = abs(a.y - c.y);
    int preco = EM * peso * altura + diametro + altura;

    if (a.y > c.y) {
        cout << "Correta" << endl;
    } else {
        cout << "Virada" << endl;
    }
    cout << preco << endl;
    return 0;
}
```
`main()` é o ponto inicial do programa. `return 0` indica encerramento normal.

## 7. Conferência manual
| Entrada | EM | D | Altura | Preço | Posição |
|---|---:|---:|---:|---:|---|
| `5 1 10 2 10 1 2 22 2` | 1 | 21 | 8 | 69 | Correta |
| `4 1 10 3 10 1 3 20 3` | 2 | 19 | 7 | 82 | Correta |
| `6 1 2 2 2 1 15 15 15` | 1 | 14 | 13 | 105 | Virada |

No primeiro caso: `1 * 5 * 8 + 21 + 8 = 69`.

## Revisão ativa
- Por que usar `abs()` nas dimensões, mas não na comparação da posição?
- Qual a diferença entre `a.x` e `a.y`?
- O que muda se a torta for virada?

Próximo exercício: [[02-Tortas-Fecho-Convexo-e-Filme]]
