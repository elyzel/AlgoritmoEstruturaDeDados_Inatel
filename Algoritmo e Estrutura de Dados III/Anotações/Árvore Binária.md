
# 🌳 Árvore Binária — Representações Visuais

> [!abstract] Ideia principal
> Uma árvore binária é uma árvore em que cada nó pode possuir no máximo dois filhos:
> **filho da esquerda** e **filho da direita**.

---

# 1. Representação de um nó

O nó possui três informações:

```cpp
struct treenode {
    int info;
    struct treenode *left;
    struct treenode *right;
};
````

Visualmente, podemos imaginar cada nó assim:

```
             ┌───────────────┐
       p ──► │     info      │
             ├───────────────┤
             │     left ─────┼──► filho esquerdo
             │    right ─────┼──► filho direito
             └───────────────┘
```

### O que cada parte representa?

```
info
 ↓
valor armazenado no nó

left
 ↓
ponteiro para o filho da esquerda

right
 ↓
ponteiro para o filho da direita
```

Se não existir filho:

```
left  → NULL
right → NULL
```

---

# 2. Inserção — a história acontecendo

Código:

```
void tInsert(treenodeptr &p, int x){ 
    if (p == NULL) { 
        p = new treenode; 
        p->info = x; 
        p->left = NULL; 
        p->right = NULL; 
    } else if (x < p->info) 
        tInsert(p->left, x); 
    else 
        tInsert(p->right, x); 
}
```

---

## 🎬 História 1 — árvore vazia

Queremos inserir:

```
5
```

Estado inicial:

```
p
│
▼
NULL
```

O código verifica:

```
if (p == NULL)
```

Resultado:

```
p == NULL
   ↓
SIM
   ↓
criar novo nó
```

Depois:

```
p = new treenode;
p->info = x;
p->left = NULL;
p->right = NULL;
```

A árvore passa a ser:

```
      5
     / \
   NULL NULL
```

### 🌳 Estado atual

```
graph TD
    A["5"]
    A --> B["NULL"]
    A --> C["NULL"]
```

---

# 3. Inserindo um segundo valor

Agora queremos inserir:

```
3
```

A árvore já possui:

```
      5
     / \
   NULL NULL
```

O código chega em:

```
else if (x < p->info)
```

Temos:

```
x = 3
p->info = 5
```

Então:

```
3 < 5
 ↓
SIM
 ↓
esquerda
```

O código executa:

```
tInsert(p->left, x);
```

Agora estamos olhando para:

```
      5
     /
    ↓
   NULL
```

Como `p->left` é `NULL`, um novo nó é criado.

### 🌳 Resultado

```
graph TD
    A["5"]
    A --> B["3"]
    A --> C["NULL"]
```

A árvore agora é:

```
    5
   /
  3
```

---

# 4. Inserindo um terceiro valor

Agora:

```
x = 10
```

Árvore atual:

```
    5
   /
  3
```

Começamos comparando com `5`:

```
10 < 5
   ↓
NÃO
```

Então o código vai para:

```
else
    tInsert(p->right, x);
```

Ou seja:

```
10 > 5
 ↓
direita
```

Como a direita de `5` está vazia:

```
      5
     / \
    3  NULL
```

criamos o nó `10`.

### 🌳 Resultado

```
graph TD
    A["5"]
    A --> B["3"]
    A --> C["10"]
```

Agora:

```
      5
     / \
    3   10
```

---

# 5. Inserindo um quarto valor

Agora queremos inserir:

```
1
```

### Primeira comparação

```
      5
     / \
    3   10
```

Temos:

```
1 < 5
 ↓
esquerda
```

Vamos para o nó `3`.

### Segunda comparação

```
    3
```

Temos:

```
1 < 3
 ↓
esquerda
```

A esquerda de `3` está vazia.

Então:

```
NULL
 ↓
novo nó
 ↓
1
```

### 🌳 Resultado final

```
graph TD
    A["5"]
    A --> B["3"]
    A --> C["10"]
    B --> D["1"]
```

A história completa foi:

```
Inserir 1

        5
        │
        │ 1 < 5
        ↓
        3
        │
        │ 1 < 3
        ↓
       NULL
        │
        │ cria nó
        ↓
        1
```

Resultado:

```
      5
     / \
    3   10
   /
  1
```

---

# 6. 🧠 Regra visual da inserção

Podemos resumir a história da inserção assim:

```
                 INSERIR x
                     │
                     ▼
               p == NULL?
                /       \
              SIM       NÃO
               │          │
               ▼          ▼
          cria o nó    compara x
                         com p->info
                       /           \
                x < p->info      x >= p->info
                     │                │
                     ▼                ▼
                 esquerda           direita
                     │                │
                     └──────┬─────────┘
                            ▼
                       repete a busca
```

### Regra para memorizar

```
x < p->info
    ↓
ESQUERDA

x >= p->info
    ↓
DIREITA
```

---

# 7. 🔎 Busca — a história acontecendo

Código:

```
treenodeptr tSearch(treenodeptr p, int x) { 
    if (p == NULL) 
        return NULL; 
    else if (x == p->info) 
        return p; 
    else if (x < p->info) 
        return tSearch(p->left,x); 
    else
        return tSearch(p->right,x); 
}
```

Vamos usar:

```
      5
     / \
    3   10
   / \
  1   4
```

Queremos procurar:

```
x = 4
```

---

## 🎬 Passo 1 — começa no 5

```
x = 4
p->info = 5
```

Comparamos:

```
4 == 5 ?  NÃO
4 <  5 ?  SIM
```

Então:

```
tSearch(p->left, x);
```

Visualmente:

```
graph TD
    A["5"]:::ativo
    A --> B["3"]
    A --> C["10"]
    B --> D["1"]
    B --> E["4"]

    classDef ativo stroke-width:4px
```

Caminho:

```
5
↓
esquerda
↓
3
```

---

# 8. Busca — segunda comparação

Agora estamos no `3`.

```
x = 4
p->info = 3
```

Comparação:

```
4 == 3 ?  NÃO
4 <  3 ?  NÃO
```

Então:

```
tSearch(p->right, x);
```

Vamos para a direita:

```
      5
     / \
    3   10
   / \
  1   4
       ↑
```

---

# 9. Busca — encontrou

Agora:

```
x = 4
p->info = 4
```

Temos:

```
4 == 4
 ↓
SIM
 ↓
return p
```

### Resultado

```
5 → 3 → 4
          ★
       encontrado
```

### História completa

```
        5
        │
        │ 4 < 5
        ↓
        3
        │
        │ 4 > 3
        ↓
        4
        │
        │ 4 == 4
        ↓
    ENCONTRADO
```

---

# 10. Busca — quando não encontra

Se procurarmos:

```
x = 7
```

A história seria:

```
        5
        │
        │ 7 > 5
        ↓
       10
        │
        │ 7 < 10
        ↓
       NULL
        │
        ↓
     return NULL
```

### Regra visual

```
p == NULL
    ↓
não encontrou

x == p->info
    ↓
encontrou

x < p->info
    ↓
procura à esquerda

x > p->info
    ↓
procura à direita
```

---

# 11. 🔽 Busca pelo menor

Código:

```
treenodeptr tPointSmaller(treenodeptr &p) { 
    treenodeptr t = p; 
    if (p->left == NULL){ 
        p = p->right; 
        return t; 
    } 
    else 
        return tPointSmaller(p->left); 
}
```

A ideia principal é:

> Para encontrar o menor valor, seguimos sempre para a esquerda.

Exemplo:

```
        8
       / \
      3   10
     / \
    1   5
```

Começamos em `8`:

```
p->left != NULL
        ↓
vai para esquerda
```

Chegamos em `3`:

```
p->left != NULL
        ↓
vai para esquerda
```

Chegamos em `1`:

```
p->left == NULL
        ↓
ENCONTRAMOS O MENOR
```

### 🌳 Caminho

```
8 → 3 → 1
        ★
      menor
```

Visualmente:

```
graph TD
    A["8"]
    A --> B["3"]
    A --> C["10"]
    B --> D["1"]:::menor
    B --> E["5"]

    classDef menor stroke-width:5px
```

### Regra para memorizar

```
MENOR
  ↓
vai sempre para a ESQUERDA
  ↓
até encontrar
p->left == NULL
```

---

# 12. 🗑️ Remoção — a grande história

Código:

```
bool tRemove(treenodeptr &p, int x) { 
    treenodeptr t; 

    if (p == NULL) 
        return false; 

    if (x == p->info){ 
        t = p; 

        if(p->left == NULL) 
            p = p->right; 

        else if(p->right == NULL) 
            p = p->left; 

        else { 
            t = tPointSmaller(p->right); 
            p->info = t->info; 
        } 

        delete t; 
        return true; 
    } 

    else if (x < p->info) 
        return tRemove(p->left,x);
}
```

A remoção possui **três situações principais**.

---

# 13. 🗑️ Caso 1 — nó sem filho

Árvore:

```
      5
     / \
    3   10
```

Queremos remover:

```
10
```

O código encontra:

```
x == p->info
```

Depois verifica:

```
p->left == NULL
```

Como `10` não possui filho esquerdo:

```
p = p->right
```

Como `p->right` também é `NULL`:

```
10
 ↓
NULL
```

Depois:

```
delete t;
```

### 🌳 Resultado

```
graph TD
    A["5"]
    A --> B["3"]
    A --> C["NULL"]
```

Antes:

```
      5
     / \
    3   10
```

Depois:

```
      5
     /
    3
```

---

# 14. 🗑️ Caso 2 — nó com um filho

Imagine:

```
      5
     /
    3
   /
  1
```

Queremos remover `3`.

O nó `3` possui:

```
left  → 1
right → NULL
```

O código encontra:

```
else if(p->right == NULL)
```

Então:

```
p = p->left;
```

Ou seja:

```
3
│
└── left → 1
```

O nó `3` é substituído pelo seu filho `1`.

### 🌳 Antes

```
      5
     /
    3
   /
  1
```

### 🌳 Depois

```
      5
     /
    1
```

Visualmente:

```
graph TD
    A["5"]
    A --> B["1"]
```

---

# 15. 🗑️ Caso 3 — nó com dois filhos

Esse é o caso mais importante.

Imagine:

```
        8
       / \
      3   10
     / \
    1   5
```

Queremos remover:

```
3
```

Mas `3` possui:

```
left  → 1
right → 5
```

Então não podemos simplesmente colocar `NULL`.

O código entra no:

```
else {
    t = tPointSmaller(p->right);
    p->info = t->info;
}
```

---

## 🎬 História

Estamos em:

```
        8
       / \
      3   10
     / \
    1   5
```

O nó `3` tem dois filhos.

Então:

```
vai para a subárvore direita de 3
```

Ou seja:

```
5
```

Agora usamos:

```
tPointSmaller(p->right)
```

Como `5` não possui filho esquerdo:

```
p->left == NULL
```

Encontramos o menor.

```
      3
     / \
    1   5
        ★
      menor
```

Depois:

```
p->info = t->info;
```

O `3` passa a receber o valor `5`.

### Nesse momento:

```
        8
       / \
      5   10
     / \
    1   5
```

Depois o código executa:

```
delete t;
```

Removendo o nó que continha o `5` original.

### Resultado:

```
        8
       / \
      5   10
     /
    1
```

### História visual completa

```
ANTES

        8
       / \
      3   10
     / \
    1   5

        ↓
        
3 possui DOIS FILHOS

        ↓

procura o menor da subárvore direita

        ↓

        5
        ★

        ↓

copia 5 para o nó que tinha 3

        ↓

        8
       / \
      5   10
     / \
    1   5

        ↓

delete t

        ↓

DEPOIS

        8
       / \
      5   10
     /
    1
```

---

# 16. 🧠 Resumo visual da remoção

```
                    ENCONTRO x
                        │
                        ▼
                   p == NULL?
                   /       \
                 SIM       NÃO
                  │          │
                  ▼          ▼
               false      x == p->info?
                              │
                         ┌────┴────┐
                        SIM       NÃO
                         │          │
                         ▼          ▼
                    quantos      procura
                     filhos?     esquerda/
                                 direita
                         │
             ┌───────────┼───────────┐
             │           │           │
             ▼           ▼           ▼
           nenhum      1 filho    2 filhos
             │           │           │
             ▼           ▼           ▼
          substitui   substitui    menor da
          por NULL    pelo filho   subárvore
                                    direita
                                        │
                                        ▼
                                   copia valor
                                        │
                                        ▼
                                    delete
```

---

# 17. 🎯 Mapa visual da Árvore Binária

```
                         ÁRVORE BINÁRIA
                               │
               ┌───────────────┴───────────────┐
               │                               │
           ESTRUTURA                        OPERAÇÕES
               │                               │
               ▼                   ┌───────────┼───────────┐
       ┌───────────────┐           │           │           │
       │     info      │        Inserção      Busca      Remoção
       │     left      │           │           │           │
       │     right     │           ▼           ▼           ▼
       └───────────────┘       esquerda/    esquerda/    0, 1 ou 2
                              direita       direita      filhos
```

---

# ⭐ Como estudar a árvore visualmente

Sempre tente acompanhar nesta ordem:

```
1. QUAL É A ÁRVORE ATUAL?
            ↓
2. QUAL VALOR ESTOU INSERINDO/PROCURANDO/REMOVENDO?
            ↓
3. QUAL COMPARAÇÃO O CÓDIGO FAZ?
            ↓
4. ESQUERDA OU DIREITA?
            ↓
5. O QUE MUDOU NA ÁRVORE?
```

### Para inserção

```
valor
 ↓
comparação
 ↓
esquerda/direita
 ↓
NULL?
 ↓
cria nó
```

### Para busca

```
valor
 ↓
comparação
 ↓
esquerda/direita
 ↓
encontrou ou NULL?
```

### Para menor

```
nó atual
 ↓
tem esquerda?
 ↓
SIM → continua esquerda
NÃO → é o menor
```

### Para remoção

```
encontra o nó
 ↓
quantos filhos?
 ↓
0 → remove
1 → substitui pelo filho
2 → procura menor da direita
```

> **Ideia central:** nas suas notas, a árvore não deve ser apenas uma imagem parada. Ela deve **mudar conforme o código executa**. Assim você consegue ligar diretamente cada `if`, cada chamada recursiva e cada ponteiro à mudança visual na árvore.

```

```