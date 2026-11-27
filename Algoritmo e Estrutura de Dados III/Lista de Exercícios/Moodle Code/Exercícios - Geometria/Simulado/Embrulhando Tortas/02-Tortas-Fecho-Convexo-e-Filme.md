---
tags: [cpp, geometria-computacional, exercicios, fecho-convexo]
---
# Exercício 2 — Fecho convexo e filme plástico

## Objetivo
Ler N centros de tortas de diâmetro D, identificar os índices das tortas expostas e calcular o comprimento mínimo do filme.

## 1. Fundamento geométrico
O fecho convexo é o menor conjunto convexo que contém todos os centros. Imagine um elástico envolvendo os pontos mais externos. O filme acompanha as arestas desse contorno, deslocadas pelo raio das tortas; as curvas somadas equivalem a uma circunferência completa.

$$L=perimetro+\pi D$$

> [!important] Pontos colineares
> O enunciado é ambíguo ao pedir que sejam desconsiderados das bordas, mas os exemplos incluem seus índices na saída. Nesta solução, eles são removidos como vértices intermediários durante a construção do fecho e recuperados depois, caso pertençam a um segmento externo.

## 2. Bibliotecas e estrutura
```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct ponto {
    int x, y;
    int indice;
};
```
| Item | Função |
|---|---|
| `iostream` | Entrada e saída |
| `cmath` | `sqrt()` e `acos()` |
| `vector` | Vetores dinâmicos |
| `algorithm` | `sort()`, `min()` e `max()` |
| `iomanip` | `setprecision()` |
| `indice` | Preserva a posição original da torta mesmo após ordenar os pontos |

## 3. Área orientada e função lado
Estas duas funções são reaproveitadas do arquivo `geometrico.cpp` do professor.

```cpp
float area_triangulo(ponto a, ponto b, ponto c) {
    return (
        a.x * b.y - a.y * b.x +
        a.y * c.x - a.x * c.y +
        b.x * c.y - b.y * c.x
    ) / 2.0;
}

int lado(ponto a, ponto b, ponto p) {
    float s = area_triangulo(a, b, p);
    if (s > 0) return 1;
    else if (s < 0) return -1;
    else return 0;
}
```
A área orientada conserva o sinal, que identifica a posição de P em relação à reta dirigida de A para B.

| Retorno de `lado()` | Interpretação |
|---|---|
| 1 | P está à esquerda de AB |
| -1 | P está à direita de AB |
| 0 | P está alinhado com AB |

Exemplo: A=(0,0), B=(4,0), P=(2,3) gera área positiva 6; P=(2,-3) gera -6; P=(2,0) gera zero.

## 4. Distância entre dois pontos
```cpp
double distancia(ponto a, ponto b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}
```
`dx` e `dy` são deslocamentos horizontal e vertical. `sqrt()` calcula a raiz quadrada. `double` preserva a parte decimal.

$$d=\sqrt{(x_b-x_a)^2+(y_b-y_a)^2}$$

## 5. Comparador para ordenação
```cpp
bool comparar(ponto a, ponto b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
```
`bool` representa verdadeiro ou falso. A função indica se A deve vir antes de B: primeiro por x, depois por y em caso de empate. A ordenação facilita a construção dos dois contornos.

## 6. Verificação de um ponto no segmento
```cpp
bool no_segmento(ponto a, ponto b, ponto p) {
    return lado(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) &&
           p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) &&
           p.y <= max(a.y, b.y);
}
```
`&&` significa E lógico: todas as condições devem ser verdadeiras. `lado() == 0` verifica alinhamento, enquanto `min()` e `max()` limitam o ponto ao segmento. Um ponto na extensão da reta, mas fora da aresta, não será aceito.

## 7. Entrada e caso especial
```cpp
int N, D;
double PI = acos(-1);
cin >> N >> D;
vector<ponto> pontos(N);
for (int i = 0; i < N; i++) {
    cin >> pontos[i].x >> pontos[i].y;
    pontos[i].indice = i;
}
if (N == 1) {
    cout << 0 << endl;
    cout << fixed << setprecision(2) << PI * D << endl;
    return 0;
}
```
O `for` percorre os índices de 0 a N-1. `pontos[i]` acessa uma torta. `acos(-1)` retorna pi em radianos. Se existe apenas uma torta, não há trechos retos e o índice exposto é 0. `fixed` e `setprecision(2)` formatam duas casas decimais.

## 8. Construção do fecho convexo (Monotone Chain)
```cpp
sort(pontos.begin(), pontos.end(), comparar);
vector<ponto> inferior, superior;
for (int i = 0; i < N; i++) {
    while (inferior.size() >= 2 &&
           lado(inferior[inferior.size() - 2],
                inferior.back(), pontos[i]) <= 0) {
        inferior.pop_back();
    }
    inferior.push_back(pontos[i]);
}
```
`sort()` ordena todo o vetor. A construção do contorno inferior percorre os pontos em ordem crescente. A cada novo ponto, o `while` testa se os dois últimos pontos e o candidato fazem uma curva válida. Se a orientação for negativa ou zero, remove o último ponto e repete. Ao final, adiciona o candidato.

| Método | Significado |
|---|---|
| `size()` | Quantidade de elementos |
| `back()` | Último elemento |
| `pop_back()` | Remove o último elemento |
| `push_back()` | Adiciona um elemento ao final |
| `begin()` / `end()` | Delimitam o intervalo para ordenar |

A condição `size() >= 2` evita acessar elementos inexistentes. O `&&` só avalia a função `lado()` se essa primeira condição for verdadeira. `<= 0` remove também os pontos colineares intermediários.

### Contorno superior
```cpp
for (int i = N - 1; i >= 0; i--) {
    while (superior.size() >= 2 &&
           lado(superior[superior.size() - 2],
                superior.back(), pontos[i]) <= 0) {
        superior.pop_back();
    }
    superior.push_back(pontos[i]);
}
```
É o mesmo processo, mas em ordem inversa. `i--` diminui o índice em uma unidade.

### União
```cpp
inferior.pop_back();
superior.pop_back();
vector<ponto> contorno = inferior;
for (int i = 0; i < superior.size(); i++) {
    contorno.push_back(superior[i]);
}
```
Os dois caminhos compartilham as extremidades; removemos o último ponto de cada um antes de unir, para não duplicá-los.

## 9. Perímetro
```cpp
double perimetro = 0;
int tamanho = contorno.size();
for (int i = 0; i < tamanho; i++) {
    int proximo = (i + 1) % tamanho;
    perimetro += distancia(contorno[i], contorno[proximo]);
}
```
`+=` soma a distância ao total. `%` calcula o resto da divisão, permitindo voltar ao primeiro vértice quando chegamos ao último. Para quatro pontos, a sequência de próximos índices é 1, 2, 3, 0. Quando todos os pontos são colineares, o fecho tem dois extremos; a distância é somada duas vezes, corretamente.

## 10. Identificação das tortas expostas
```cpp
vector<bool> expostas(N, false);
for (int i = 0; i < N; i++) {
    for (int j = 0; j < tamanho; j++) {
        int proximo = (j + 1) % tamanho;
        if (no_segmento(contorno[j], contorno[proximo], pontos[i])) {
            expostas[pontos[i].indice] = true;
            break;
        }
    }
}
```
O vetor começa com todos os valores falsos. O primeiro `for` percorre as tortas; o segundo testa cada aresta do fecho. Se uma torta está sobre uma aresta, seu índice original é marcado como verdadeiro. `break` encerra o laço interno porque não precisamos testar outras arestas.

## 11. Saída
```cpp
bool primeiro = true;
for (int i = 0; i < N; i++) {
    if (expostas[i]) {
        if (!primeiro) cout << " ";
        cout << i;
        primeiro = false;
    }
}
cout << endl;
double comprimento = perimetro + PI * D;
cout << fixed << setprecision(2) << comprimento << endl;
```
Percorrer os índices originais em ordem crescente garante a ordem solicitada. `!` é a negação lógica. A variável `primeiro` evita espaços extras antes ou depois dos índices.

## 12. Código completo
```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct ponto { int x, y, indice; };

float area_triangulo(ponto a, ponto b, ponto c) {
    return (a.x * b.y - a.y * b.x +
            a.y * c.x - a.x * c.y +
            b.x * c.y - b.y * c.x) / 2.0;
}
int lado(ponto a, ponto b, ponto p) {
    float s = area_triangulo(a, b, p);
    if (s > 0) return 1;
    else if (s < 0) return -1;
    else return 0;
}
double distancia(ponto a, ponto b) {
    int dx = b.x - a.x, dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}
bool comparar(ponto a, ponto b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
bool no_segmento(ponto a, ponto b, ponto p) {
    return lado(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}
int main() {
    int N, D;
    double PI = acos(-1);
    cin >> N >> D;
    vector<ponto> pontos(N);
    for (int i = 0; i < N; i++) {
        cin >> pontos[i].x >> pontos[i].y;
        pontos[i].indice = i;
    }
    if (N == 1) {
        cout << 0 << endl;
        cout << fixed << setprecision(2) << PI * D << endl;
        return 0;
    }
    sort(pontos.begin(), pontos.end(), comparar);
    vector<ponto> inferior, superior;
    for (int i = 0; i < N; i++) {
        while (inferior.size() >= 2 &&
               lado(inferior[inferior.size()-2], inferior.back(), pontos[i]) <= 0) {
            inferior.pop_back();
        }
        inferior.push_back(pontos[i]);
    }
    for (int i = N-1; i >= 0; i--) {
        while (superior.size() >= 2 &&
               lado(superior[superior.size()-2], superior.back(), pontos[i]) <= 0) {
            superior.pop_back();
        }
        superior.push_back(pontos[i]);
    }
    inferior.pop_back();
    superior.pop_back();
    vector<ponto> contorno = inferior;
    for (int i = 0; i < superior.size(); i++) {
        contorno.push_back(superior[i]);
    }
    double perimetro = 0;
    int tamanho = contorno.size();
    for (int i = 0; i < tamanho; i++) {
        int proximo = (i+1) % tamanho;
        perimetro += distancia(contorno[i], contorno[proximo]);
    }
    vector<bool> expostas(N, false);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < tamanho; j++) {
            int proximo = (j+1) % tamanho;
            if (no_segmento(contorno[j], contorno[proximo], pontos[i])) {
                expostas[pontos[i].indice] = true;
                break;
            }
        }
    }
    bool primeiro = true;
    for (int i = 0; i < N; i++) {
        if (expostas[i]) {
            if (!primeiro) cout << " ";
            cout << i;
            primeiro = false;
        }
    }
    cout << endl;
    double comprimento = perimetro + PI * D;
    cout << fixed << setprecision(2) << comprimento << endl;
    return 0;
}
```

## 13. Testes de mesa
### Exemplo 1
Entrada:
```text
6 10
0 0
40 0
40 40
0 40
20 20
20 0
```
O fecho possui quatro vértices, com perímetro 160. A torta 5 está na borda inferior e a torta 4 está no interior.
```text
0 1 2 3 5
191.42
```
### Exemplo 2
Entrada:
```text
4 6
0 0
24 18
8 6
16 12
```
Todos os centros estão alinhados. A distância entre extremos é 30, o perímetro é 60 e todas as tortas são expostas.
```text
0 1 2 3
78.85
```

## 14. Complexidade
Para N pontos e H vértices no fecho, a ordenação custa O(N log N), a construção do fecho custa O(N) após ordenar e a identificação das tortas expostas custa O(NH). No pior caso, o programa custa O(N²), com memória O(N). Para N até 1000, a busca pelas arestas tem até um milhão de testes.

## Revisão ativa
- Por que preservar o índice original?
- Qual a diferença entre reta e segmento?
- Por que remover os colineares e depois recuperá-los?
- Como o operador `%` fecha o contorno?
- Por que somar pi vezes o diâmetro?

Exercício anterior: [[01-Tortas-Preco-e-Posicao]]
