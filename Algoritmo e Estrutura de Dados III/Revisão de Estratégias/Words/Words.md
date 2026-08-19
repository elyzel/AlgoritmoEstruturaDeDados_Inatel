## 🔍 Explicação Detalhada de Cada Bloco e Linha

### Bloco 1: Inclusão de Bibliotecas e Declaração da `struct`

```C++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Estado {
    string sobra;
    int dono; 
};
```

- **`#include <iostream>`**: Fornece os fluxos de entrada (`cin`) e saída (`cout`).
    
- **`#include <vector>`**: Permite usar arrays dinâmicos para a fila de busca e para a lista de palavras.
    
- **`#include <string>`**: Permite a manipulação de cadeias de caracteres (métodos como `.length()` e `.substr()`).
    
- **`#include <algorithm>`**: Inclui funções utilitárias da biblioteca padrão.
    
- **`struct Estado { ... };`**: Define um tipo de dado personalizado para a busca.
    
    - `string sobra`: Guarda o sufixo de caracteres que está "sobrando" na frente da concatenação.
        
    - `int dono`: Identifica qual conjunto detém essa sobra ($1$ para o conjunto $A$, $2$ para o conjunto $B$).
        

### Bloco 2: Função de Controle de Repetição (`jaVisitado`)

```cpp
bool jaVisitado(const vector<Estado>& visitados, const string& sobra, int dono) {
    for (size_t i = 0; i < visitados.size(); i++) {
        if (visitados[i].dono == dono && visitados[i].sobra == sobra) {
            return true;
        }
    }
    return false;
}
```

- **`const vector<Estado>& visitados`**: Recebe a lista de estados já explorados por referência constante para economizar memória e evitar cópias.
    
- **`for (size_t i = 0; i < visitados.size(); i++)`**: Percorre todos os estados já cadastrados.
    
- **`if (visitados[i].dono == dono && visitados[i].sobra == sobra)`**: Compara se o mesmo conjunto já teve exatamente a mesma sobra de texto anteriormente.
    
- **`return true / return false`**: Retorna `true` se o estado for repetido (evitando ciclos infinitos na busca) e `false` caso seja um estado inédito.
    

### Bloco 3: Leitura das Entradas e Alocação dos Vetores

```C++
int main() {
    int N1, N2;

    while (cin >> N1 >> N2) {
        vector<string> A(N1);
        for (int i = 0; i < N1; i++) {
            cin >> A[i];
        }

        vector<string> B(N2);
        for (int i = 0; i < N2; i++) {
            cin >> B[i];
        }

        vector<Estado> fila;
        vector<Estado> visitados;

        bool possivel = false;
```

- **`while (cin >> N1 >> N2)`**: Lê a quantidade de palavras de $A$ e $B$ até atingir o fim da entrada (EOF).
    
- **`vector<string> A(N1)` e `vector<string> B(N2)`**: Criam listas com capacidades exatas para $N1$ e $N2$ palavras.
    
- **`vector<Estado> fila`**: Atua como a nossa fila de busca em largura (BFS).
    
- **`vector<Estado> visitados`**: Armazena o histórico de todos os estados já gerados para não processá-los mais de uma vez.
    
- **`bool possivel = false;`**: Flag que sinaliza se encontramos uma correspondência perfeita (`true`) ou não (`false`).
    

### Bloco 4: Inicialização da BFS (Combinações de Primeiro Nível)

```C++
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < N2; j++) {
                string u = A[i];
                string v = B[j];

                if (u == v) {
                    possivel = true;
                    break;
                }

                if (u.length() > v.length() && u.substr(0, v.length()) == v) {
                    string sobra = u.substr(v.length());
                    if (!jaVisitado(visitados, sobra, 1)) {
                        Estado est = {sobra, 1};
                        fila.push_back(est);
                        visitados.push_back(est);
                    }
                }
                else if (v.length() > u.length() && v.substr(0, u.length()) == u) {
                    string sobra = v.substr(u.length());
                    if (!jaVisitado(visitados, sobra, 2)) {
                        Estado est = {sobra, 2};
                        fila.push_back(est);
                        visitados.push_back(est);
                    }
                }
            }
            if (possivel) break;
        }
```

- **Dois laços `for` aninhados**: Testam todas as combinações possíveis de início colocando uma palavra de $A$ contra uma palavra de $B$.
    
- **`if (u == v)`**: Se uma palavra de $A$ for idêntica a uma de $B$, a solução é imediata com apenas $1$ palavra de cada conjunto.
    
- **`u.substr(0, v.length()) == v`**: Verifica se a palavra mais longa começa exatamente com a palavra menor.
    
- **`u.substr(v.length())`**: Corta o prefixo comum e extrai apenas a parte que sobra.
    
- **`fila.push_back(est)` e `visitados.push_back(est)`**: Insere o estado inicial na fila para ser explorado e o registra como visitado.
    

### Bloco 5: Laço Principal da BFS e Transições de Estado

```C++
        int inicioFila = 0;

        while (inicioFila < (int)fila.size() && !possivel) {
            Estado atual = fila[inicioFila];
            inicioFila++;

            string sobra = atual.sobra;
            int dono = atual.dono;
```

- **`int inicioFila = 0;`**: Ponteiro/índice que avança sobre o `vector`, simulando uma fila FIFO sem precisar de bibliotecas adicionais.
    
- **`while (inicioFila < (int)fila.size() && !possivel)`**: Executa enquanto houver novos estados a serem explorados e a resposta afirmativa ainda não tiver sido encontrada.
    

#### Ramo 1: A Sobra Pertence ao Conjunto $A$ (`dono == 1`)

```C++
            if (dono == 1) {
                for (int j = 0; j < N2; j++) {
                    string v = B[j];

                    if (sobra == v) {
                        possivel = true;
                        break;
                    }

                    if (sobra.length() > v.length() && sobra.substr(0, v.length()) == v) {
                        string nova_sobra = sobra.substr(v.length());
                        if (!jaVisitado(visitados, nova_sobra, 1)) {
                            Estado prox = {nova_sobra, 1};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                    else if (v.length() > sobra.length() && v.substr(0, sobra.length()) == sobra) {
                        string nova_sobra = v.substr(sobra.length());
                        if (!jaVisitado(visitados, nova_sobra, 2)) {
                            Estado prox = {nova_sobra, 2};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                }
            }
```

- Como $A$ está na frente, testamos anexar cada palavra $v$ do conjunto $B$ para tentar cobrir a sobra:
    
    1. **`sobra == v`**: A palavra de $B$ casa com a sobra com precisão cirúrgica. Ambos os lados terminaram alinhados $\rightarrow$ `possivel = true`.
        
    2. **`sobra.length() > v.length()`**: A sobra de $A$ era maior do que a peça de $B$. $A$ continua na frente, gerando uma sobra menor (`dono = 1`).
        
    3. **`v.length() > sobra.length()`**: A peça de $B$ cobriu a sobra de $A$ e ainda ultrapassou. Agora $B$ assume a liderança com a nova sobra (`dono = 2`).
        

#### Ramo 2: A Sobra Pertence ao Conjunto $B$ (`dono == 2`)

- Executa a mesma lógica descrita acima de maneira simétrica, testando agora as palavras $u$ pertencentes ao conjunto $A$.
    

### Bloco 6: Impressão da Resposta Final

```C++
        if (possivel) {
            cout << "S" << endl;
        } else {
            cout << "N" << endl;
        }
    }

    return 0;
}
```

- Imprime `'S'` se foi possível atingir alinhamento total ou `'N'` se toda a fila foi consumida sem sucesso.
    

## ⚡ Tabela de Análise de Complexidade

|**Métrica**|**Complexidade**|**Detalhes**|
|---|---|---|
|**Tempo**|$O(V \cdot (\vert{}A\vert{} + \vert{}B\vert{}))$|Cada sobra é sempre um sufixo de alguma palavra original. Como existem no máximo 40 sufixos por palavra e 20 palavras por conjunto, o número total de estados possíveis é $V \le 2 \times (20 \times 40) = 1600$.|
|**Espaço**|$O(V)$|Vetores `fila` e `visitados` armazenando no máximo $1600$ estruturas `Estado`.|