/*
Sokoban é um jogo muito conhecido. O que pouca gente sabe é que o jogo foi inventado pelos berberes, povos árabes que habitavam o norte da África, na região onde hoje fica o Marrocos. Para esse povo, os gatos são considerados animais que trazem mau agouro, principalmente devido ao seu comportamento egoísta (como evidencia o ditado citado acima).

Nesta versão original do Sokoban, o personagem é um gato que empurra blocos de terra ao seu redor. O jogo ocorre em um tabuleiro composto por N linhas e M colunas. Você controla o gato, que pode se mover para qualquer uma das quatro casas adjacentes (desde que estejam livres) ou empurrar um bloco em qualquer uma dessas quatro direções.

Assim como na versão mais conhecida, seu objetivo é empurrar o bloco até uma posição final específica. Lembre-se de que você só pode empurrar o bloco; nunca pode puxá-lo.

A versão berbere do jogo possui uma particularidade: existem casas que funcionam como portas especiais. Quando o gato ocupa a posição de uma porta pela primeira vez, ela se abre. Um bloco não pode ser empurrado para a posição de uma porta enquanto ela estiver fechada; uma vez aberta, a porta passa a comportar-se como uma casa livre.

Você deve empurrar o bloco até a posição final abrindo o menor número possível de portas.

Considere qualquer posição fora do tabuleiro como uma parede.

Entrada
A entrada consiste em várias instâncias e termina com o fim do arquivo (EOF).

Cada instância começa com uma linha contendo dois números inteiros separados por um espaço: M e N (1 ≤ N, M ≤ 25).

Em seguida, há N linhas, sendo que cada caractere pertence ao conjunto {*, j, b, x, #, .}, onde:

'*' representa uma parede;
'.' representa uma posição vazia;
'j' representa a posição inicial do gato (cada instância contém exatamente um caractere 'j');
'b' representa a posição inicial do bloco (cada instância contém exatamente um caractere 'b');
'x' representa a posição final desejada para o bloco (cada instância contém exatamente um caractere 'x');
'#' representa uma porta (cada instância contém no máximo 5 caracteres '#');
Saída
Para cada instância, imprima uma única linha. Se for possível empurrar o bloco para sua posição final, esta linha deve conter dois números inteiros: o número mínimo de portas que precisam estar abertas para realizar essa ação e o número mínimo de movimentos necessários com essa quantidade de portas abertas. Imprima '-1' se não for possível empurrar o bloco para sua posição final.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Deslocamentos ortogonais: Cima, Baixo, Esquerda, Direita
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

struct Estado {
    int gx, gy;
    int bx, by;
    int mask;
};

// Matriz estática 5D de distâncias (48 MB) para evitar sobrecarga de alocação dinâmica
int dist_map[25][25][25][25][32];

// Conta a quantidade de bits '1' ativos (portas abertas)
int contarPortas(int mask) {
    int cont = 0;
    while (mask > 0) {
        if (mask & 1) cont++;
        mask >>= 1;
    }
    return cont;
}

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;

    // Inicializa a matriz inteira de distâncias com -1
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            for (int k = 0; k < 25; k++)
                for (int l = 0; l < 25; l++)
                    for (int m = 0; m < 32; m++)
                        dist_map[i][j][k][l][m] = -1;

    // Leitura dos casos de teste até o Fim de Arquivo (EOF)
    while (cin >> N >> M) {
        vector<string> grid(N);
        int gx = 0, gy = 0;
        int bx = 0, by = 0;
        int fx = 0, fy = 0;

        vector<pair<int, int>> portas;

        for (int i = 0; i < N; i++) {
            cin >> grid[i];
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == 'j') {
                    gx = i; gy = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'b') {
                    bx = i; by = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'x') {
                    fx = i; fy = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == '#') {
                    portas.push_back({i, j});
                }
            }
        }

        // Caso especial: o bloco já inicia na posição final
        if (bx == fx && by == fy) {
            cout << "0 0\n";
            continue;
        }

        int totalPortas = (int)portas.size();

        // Fila BFS implementada sobre std::vector
        vector<Estado> fila;
        fila.reserve(300000);

        Estado inicial = {gx, gy, bx, by, 0};
        fila.push_back(inicial);
        dist_map[gx][gy][bx][by][0] = 0;

        int melhorPortas = 999;
        int melhorPassos = 9999999;

        int inicioFila = 0;

        while (inicioFila < (int)fila.size()) {
            Estado atual = fila[inicioFila++];
            int d = dist_map[atual.gx][atual.gy][atual.bx][atual.by][atual.mask];
            int pAbertas = contarPortas(atual.mask);

            // Se o bloco alcançou o objetivo final
            if (atual.bx == fx && atual.by == fy) {
                if (pAbertas < melhorPortas) {
                    melhorPortas = pAbertas;
                    melhorPassos = d;
                } else if (pAbertas == melhorPortas && d < melhorPassos) {
                    melhorPassos = d;
                }
                continue;
            }

            // Poda: se já abriu mais portas que a melhor solução completa, descarta
            if (pAbertas > melhorPortas) continue;

            // Testa as 4 direções de movimento do gato
            for (int dir = 0; dir < 4; dir++) {
                int ngx = atual.gx + dx[dir];
                int ngy = atual.gy + dy[dir];

                // Fora dos limites da grade ou colisão com parede fixa
                if (ngx < 0 || ngx >= N || ngy < 0 || ngy >= M || grid[ngx][ngy] == '*') {
                    continue;
                }

                int nbx = atual.bx;
                int nby = atual.by;
                int nmask = atual.mask;

                // CASO 1: O gato tenta entrar na casa do bloco -> EMPURRÃO
                if (ngx == atual.bx && ngy == atual.by) {
                    nbx += dx[dir];
                    nby += dy[dir];

                    // O bloco não pode sair da grade nem colidir com parede fixa
                    if (nbx < 0 || nbx >= N || nby < 0 || nby >= M || grid[nbx][nby] == '*') {
                        continue;
                    }

                    // Se a posição destino do bloco for uma porta, ela PRECISA estar aberta
                    bool portaBloqueada = false;
                    for (int p = 0; p < totalPortas; p++) {
                        if (nbx == portas[p].first && nby == portas[p].second) {
                            if (!(nmask & (1 << p))) {
                                portaBloqueada = true; // Porta fechada bloqueia o bloco
                                break;
                            }
                        }
                    }
                    if (portaBloqueada) continue;
                }

                // CASO 2: Se o gato pisar em uma porta '#', ela se abre
                for (int p = 0; p < totalPortas; p++) {
                    if (ngx == portas[p].first && ngy == portas[p].second) {
                        nmask |= (1 << p);
                    }
                }

                // Se o estado ainda não foi visitado
                if (dist_map[ngx][ngy][nbx][nby][nmask] == -1) {
                    dist_map[ngx][ngy][nbx][nby][nmask] = d + 1;
                    fila.push_back({ngx, ngy, nbx, nby, nmask});
                }
            }
        }

        // Impressão do resultado
        if (melhorPortas == 999) {
            cout << -1 << "\n";
        } else {
            cout << melhorPortas << " " << melhorPassos << "\n";
        }

        // Limpeza dos estados visitados para o próximo caso de teste em O(visitados)
        for (size_t i = 0; i < fila.size(); i++) {
            dist_map[fila[i].gx][fila[i].gy][fila[i].bx][fila[i].by][fila[i].mask] = -1;
        }
    }

    return 0;
}