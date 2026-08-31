
# Algoritmo

Sequência de passos para alcançar uma objetivo com um contexto.

# Problema

Dor que move um individuo a alcançar um objetivo.

# Tipos de problemas

- Ordenação
- Processamento de Strings
- Grafos
- Combinatórios
- Geométricos
- Numéricos

# Estratégias de Projetos de Algoritmos

- Força Bruta(Brute Force)
- Dividir e Conquistar(Divide and Conquer)
- Diminuir e Conquistar (Decrease and Conquer)
- Transformar e Conquistar(Transform and Conquistar)

# Força Bruta

Conhecida como busca exaustiva.

Resolve o problema avaliando todas as possibilidades.
Realize uma varredura completa do espaço de busca

Uma das estratégias mais fáceis de aplicar.

Pode ser usada em uma ampla de variedades de problemas.

# Algoritmo Geral de Força Bruta

Listar todas as soluções potenciais ao problema de uma maneira sistemática.
Quando a busca terminar, retornar a solução encontrada.

## Busca Sequencial

Dada uma lista com vários elementos, retornar quantos elementos similares a um determinado elemento existem uma lista:

```cpp
int conta_ocorrencias(int n, int *vet, int elem) {
quantidade = 0;
int i; for (i=0; i<n; i++){
if (elem == vet[i]) quantidade++;
	}
return quantidade;
}
```

| __Vantagens__                                                | __Desvantagens__                       |
| ------------------------------------------------------------ | -------------------------------------- |
| Ampla aplicabilidade                                         | Raramente fornece algoritmos complexos |
| Simplicidade                                                 |                                        |
| Fornece algoritmos razoáveis para alguns problemas           |                                        |
| Em alguns casos, busca exaustiva é a única solução conhecida |                                        |

# Estratégia Gulosa

Escolhe, em cada iteração, o objeto mais "apetitoso" que vê pela frente.

Toma decisões com base nas informações disponíveis na iteração corrente, sem olhar as consequências que essas decisões terão no futuro.

Problemas que admitem solução gulosa são raros


# Divisão e conquista

É criada uma solução para uma pequena instância de um problema, dividindo-se em instâncias menores. Cada instância e resolvida usando o algoritmo definido.

As solução das instâncias menores são combinadas com a instância original.

## Quick Sort

```c++
PENDRIVE (t, n, c) D t1 ≤ ... ≤ tn
	i := 1
	enquanto i ≤ n e ti ≤c
		c := c - ti
		i := i+1
	devolva {1, ... ,i-1}
```

## Programação Dinâmica

Considera sistematicamente todas as decisões possíveis e __sempre__ seleciona aquele que prova ser a melhor. Armazenado as consequências de todas as possíveis decisões até o momento e usando esta informação de forma sistemática, __a quantidade total de trabalho é minimizada__.

- Usada para otimização

