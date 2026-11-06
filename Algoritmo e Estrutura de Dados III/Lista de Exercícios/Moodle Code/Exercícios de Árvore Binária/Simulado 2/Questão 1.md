Faça um programa que leia inicialmente a quantidade de peixes P a serem inseridos no sistema. Depois, o programa deve ler as características de cada peixe Pli] (0 <= i < P), que são números reais representando a viscosidade da pele (V), espessura da cauda (E) e diámetro do olho (O) do peixe. A toxidade T de cada peixe deve ser calcula de acordo com a formula: T= int(V*E"N*E*N*O), onde V, E e O são as características do peixe e N é o número atômico do Nitrogénio (7). Insira os índices e as toxidades de cada peixe P[i] em uma árvore binária de busca.

Por fim, o usuário irá informar uma faixa de valores de toxidade e apenas os peixes com toxidade nessa faixa devem ser exibidos (incluindo os valores limites). Faça uma varredura em nivel, apresentando apenas os peixes cuja toxidade esteja na faixa desejada.

Não esqueça de liberar a memória no final do programa!

Entrada

A primeira linha da entrada é a quantidade de peixes P (0 < P < 1000).

Em seguida serão informadas P linhas com 3 números reais indicando:

viscosidade da pele (V) do peixe P[]:

- espessura da cauda (E) do peixe Pl]:
- e diametro do olho (O) do peixe PI]:

onde 0 <= i < P.

Por fim, serão informados dois valores inteiros Tmin e Tmax indicando respectivamente o valor mínimo e máximo da faixa de toxidade.

Saída

Na saída, o programa deve mostrar número i e a toxidade T de cada peixe (no formato i:T) fazendo uma varredura em nível na árvore binária de busca considerando o intervalo de toxidade desejado.

Exemplo de entrada  Exemplo de saída

4

 1.5 2.3 0.8

 2.1 1.1 0.3

 1.9 2.2 0.7

 1.8 1.8 0.8

 300 400    0:311

 2:315


