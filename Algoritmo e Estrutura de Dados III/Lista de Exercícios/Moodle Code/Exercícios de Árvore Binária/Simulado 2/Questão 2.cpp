/*
Vamos evoluir o sistema.
Agora, o sistema deve permitir a inserção, listagem e remoção de peixes.
Caso o usuário deseje inserir um novo peixe, o programa deve ler as características do peixe. Primeiro ele deve ler um número inteiro que corresponde a identificação do peixe. Em seguida serão informados três números reais que representam a viscosidade da pele (V), espessura da
cauda (E) e diâmetro do olho (O) do peixe. A toxidade T de cada peixe deve ser calcula de acordo com a formula: T = int(V*E*N*E*N*O), onde V, E e O são as características do peixe e N é o número atômico do Nitrogênio (7). Insira o índice e a toxidade de cada peixe em uma árvore
binária de busca.
O usuário pode informar um nível de toxidade máximo a ser buscado e todos os peixes que estiverem abaixo desse nível de toxidade devem ser apresentados em ordem decrescente de toxidade.
Por fim, para remover um peixe, o usuário deve informar um nivel mínimo de toxidade. Todos os peixes com toxidade maior ou igual a esse valor devem ser removidos da arvore binária de busca, mantendo a estrutura dos dados.
O usuário pode fazer quantas operações ele desejar. O programa termina quando o usuário escolher a opção de sair.
Não esqueça de liberar a memória no final do programa!
Entrada
Cada linha da entrada começa com um inteiro indicando a opção escolhida: 1-Inserir um novo peixe; 2-Listar peixes; 3-Remover um peixe; 4-Sair.
Caso a opção escolhida seja 1, serão informadas as características de um peixe, na seguinte ordem:
· o código i;
· a viscosidade da pele (V);
· a espessura da cauda (E);
· e o diâmetro do olho (O).
Caso a opção escolhida seja 2, será informado um valor real Tmax (o valor máximo de toxidade) para indicar quais peixes devem ser listados.
Caso a opção escolhida seja 3, será informado um valor real Tmin (o valor mínimo de toxidade) para indicar quais peixes devem ser removidos.
Por fim, se a opção escolhida for 4, o programa é encerrado.
Saída
Na saída, sempre que a opção 2 for escolhida, o programa deve mostrar número i e a toxidade T de cada peixe (no formato i:T) fazendo uma varredura em ordem decrescente na árvore binária de busca, considerando apenas os peixes com toxidade abaixo de Tmax.
*/