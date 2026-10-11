
> [!QUESTION]
>
>Nestes dias se pensa muito em economia, mesmo em Anatricé. Para reduzir custos operacionais, o prefeito decidiu otimizar a iluminação das estradas. Até agora, todas as rotas eram iluminadas durante toda noite, o que custava um real por metro a cada dia. Para economizar, eles decidiram não iluminar mais todas as estradas e desligar a iluminação de algumas delas. Para ter certeza que os habitantes de Anatricé continuem a se sentirem seguros, eles querem otimizar o sistema de tal forma que após desligar a iluminação de algumas estradas à noite, sempre existirá algum caminho iluminado de qualquer junção para qualquer outra junção.
>
>Qual é a quantidade máxima de dinheiro que o governo pode economizar, sem fazer os seus habitantes sentirem-se inseguros?
>
>## Entrada
>
A entrada contém vários casos de teste. Cada caso de teste inicia com dois números **m** (1 ≤ **m** ≤ 200000) e **n** (**m**-1 ≤ **n** ≤ 200000), que são o número de junções da cidade e o número de estradas, respectivamente. Seguem n conjuntos de três valores inteiros, **x**, **y** e **z**, especificando qual será a estrada bidirecional entre **x** e **y** com **z** metros (0 ≤ **x**, **y** < **m** e **x** ≠ **y**).
>
>A entrada termina com **m**=**n**=0. O grafo especificado em cada caso de teste é conectado. O tamanho total de todas as estradas em cada caso de teste é menor do que 231.
>
>## Saída
>
>Para cada caso de teste imprima uma linha contendo a máxima quantidade diária de reais que o >governo pode economizar.


![[Pasted image 20261009185256.png]]

![[Pasted image 20261009185533.png]]

**RESPOSTA:**

```cpp
int main(){
	list<Aresta> grafo[2000];
	int m, n, x, y, z;
	
	cin >> m >> n;
	for(int i = 0; i<n; i++){
		cin >> x >> y >> z;
		grafo[x].push_back({x,y,z});
		grafo[y].push_back({y,x,z});
	}
	custo_otimizado = prim(grafo, m, 0);
	economia = custo_anterior - custo_otimizado;
	cout << economia << endl;
}
```