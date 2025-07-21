 #  Repositório de Algoritmos e Estruturas de Dados II (AEDS II)

Este repositório contém implementações de estruturas de dados clássicas e projetos práticos desenvolvidos durante a disciplina 
de Algoritmos e Estruturas de Dados II (AEDS II).

## Estrutura do Repositório
```
.
├── Teorica/
│   ├── Árvores/
│   │   ├── arvore.c                (Árvore binária básica)
│   │   ├── arvoreAVL.c             (Árvore AVL balanceada)
│   │   └── saida_arvore.txt        (Exemplo de saída)
│   ├── TabelaHash/
│   │   ├── TabelaHash.c            (Implementação principal)
│   │   ├── hash.h                  (Definições)
│   │   └── funcoes_hashing.c       (Funções de dispersão)
│   ├── Ordenação/
│   │   ├── mergeSort.c             (Merge Sort)
│   │   ├── heapSort.c              (Heap Sort)
│   │   └── bubbleSorst.c           (Bubble Sort com typo)
│   └── Estruturas Lineares/
│       ├── pilha_encadeada.c       (Pilha dinâmica)
│       ├── lista_simpl_encadeada.c (Lista encadeada)
│       └── vetorDinamico.c         (Vetor redimensionável)
│
└── Pratica/
    ├── Labirinto/
    │   ├── labirinto.c             (Solução de labirintos)
    │   ├── Proj_labirinto.c        (Main do projeto)
    │   └── Labirintos/             (Mapas)
    │       ├── labirinto1.txt      (Exemplo)
    │       └── ...                 (labirinto2.txt, etc.)
    ├── Árvores/
    │   ├── funcoesBST.c            (Operações BST)
    │   ├── funcoesAVL.c            (Balanceamento AVL)
    │   └── instancias/             (Dados de teste)
    │       ├── 1                   (Caso 1)
    │       └── ...                 (2, 3, etc.)
    └── Ordenacao/
        ├── funcoesOrdenacao.c      (Algoritmos)
        ├── Projeto_Ordenacao.c     (Aplicação)
        └── jogadores.csv           (Dataset)
```
## 1. Códigos Teóricos (./Teorica/)
Implementações didáticas de estruturas de dados e algoritmos:
### Árvores
  - arvore.c → Árvore binária básica.
  - arvoreAVL.c → Árvore AVL (com balanceamento).
  - aida_arvore.txt → Exemplo de saída de um teste com árvores.
### Tabela Hash
  - TabelaHash/ → Implementação completa com:
  - Funções de hashing (funcoes_hashing.c).
  - Tabela dinâmica (TabelaHash.c).
### Ordenação
  - mergeSort.c → Algoritmo Merge Sort.
  - heapSort.c → Heap Sort com estrutura de heap.
  - bubbleSorst.c → Provavelmente Bubble Sort (typo no nome).
### Outras Estruturas
  - pilha_encadeada.c → Pilha com alocação dinâmica.
  - lista_simpl_encadeada.c → Lista simplesmente encadeada.
  - vetorDinamico.c → Vetor redimensionável.

## 2. Projetos Práticos (./Pratica/)

Trabalhos realizados na parte prática da disciplina
### Labirinto
  Resolução automática de labirintos (arquivos .txt representam mapas).
  - Arquivos principais:
    * labirinto.c → Lógica de navegação.
    * Proj_labirinto.c → Possível main do projeto.
        
### Árvores (BST/AVL)
  Manipulação de árvores binárias de busca (BST) e AVL.
  - Destaques:
    * funcoesBST.c → Operações em BST.
    * funcoesAVL.c → Rotações e balanceamento.
    * Pasta instancias/ → Casos de teste.

### Ordenação de Dados
  Implementação de algoritmos de ordenação sobre um dataset (jogadores.csv).
  - Arquivos:
    * funcoesOrdenacao.c → Algoritmos (MergeSort, QuickSort, etc.).
    * Projeto_Ordenacao.c → Aplicação principal.
        
## Como Utilizar
  ### Compilação:
  Em projetos com múlpliplos arquivos fontes, use os Makefiles disponíveis em cada pasta (ex.: Pratica/Arvore/makefile) com o comando:

    make
    
