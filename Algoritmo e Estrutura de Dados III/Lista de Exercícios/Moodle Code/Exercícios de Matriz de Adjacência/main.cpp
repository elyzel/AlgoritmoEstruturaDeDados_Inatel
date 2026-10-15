/*
Contexto:

As cidades de Graphlandia estão ameaçadas por um grande vilão, Disconnecto, que planeja destruir 
algumas pontes (arestas) para isolar as cidades. CodeMaster precisa identificar quais cidades se 
tornarão inacessíveis se uma determinada ponte for destruída, usando uma matriz de adjacência.

Entrada:

A primeira linha contém dois inteiros N e M, onde N é o número de cidades (nós) (1 ≤ N ≤ 100) e M é o 
número de caminhos (arestas) (1 ≤ M ≤ N*(N-1)/2). As próximas M linhas descrevem os caminhos, cada uma 
contendo dois inteiros A e B (1 ≤ A, B ≤ N), indicando um caminho bidirecional entre as cidades A e B. 
Seguido por um par de inteiros X e Y (1 ≤ X, Y ≤ N), indicando a ponte em questão.

Saída:

Imprima uma lista de todas as cidades que se tornarão inacessíveis de X, se a ponte entre X e Y for 
destruída.
*/