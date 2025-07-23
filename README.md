# Data Structures and Algorithms Projects

This repository is organized into two main sections:

- `Teorica/`: Contains theoretical implementations of data structures and algorithms.
- `Pratica/`: Contains applied exercises and projects using the concepts learned.

---

## Directory Structure
```
.
├── Teorica/
│   ├── Trees/
│   │   ├── arvore.c                (Basic binary tree)
│   │   ├── arvoreAVL.c             (Balanced AVL tree)
│   │   ├── heap.c                  (Min-heap tree)
│   │   ├── partilha.c              (Patricia trie)
│   │   └── saida_arvore.txt        (Example output)
│   ├── LinearStructures/
│   │   ├── fila.c                  (Array-based queue)
│   │   ├── fila_enc.c              (Linked queue)
│   │   ├── pilha_encadeada.c       (Linked stack)
│   │   ├── lista_simpl_encadeada.c (Singly linked list)
│   │   └── vetorDinamico.c         (Dynamic array)
│   ├── Sorting/
│   │   ├── mergeSort.c             (Merge Sort)
│   │   ├── heapSort.c              (Heap Sort)
│   │   └── bubbleSorst.c           (Bubble Sort with typo in name)
│   └── HashTable/
│       ├── TabelaHash.c            (Main implementation)
│       ├── hash.h                  (Definitions)
│       └── funcoes_hashing.c       (Hashing functions)
│
└── Pratica/
    ├── Maze/
    │   ├── labirinto.c             (Maze solving logic)
    │   ├── Proj_labirinto.c        (Project main file)
    │   └── Mazes/
    │       ├── labirinto1.txt      (Example maze)
    │       └── ...                 (Additional mazes)
    ├── Trees/
    │   ├── funcoesBST.c            (Binary Search Tree operations)
    │   ├── funcoesAVL.c            (AVL balancing operations)
    │   └── instances/
    │       ├── 1                   (Test case 1)
    │       └── ...                 (Additional cases)
    └── Sorting/
        ├── funcoesOrdenacao.c      (Sorting algorithms)
        ├── Projeto_Ordenacao.c     (Sorting application)
        └── jogadores.csv           (Sample dataset)
```

## About the Repository

This repository is meant to consolidate implementations and applications of data structures and algorithms. It is split into two main parts:

`Teorica/`

Focuses on fundamental structures and sorting algorithms, with standalone C implementations:
  - Trees: Binary Trees, AVL Trees, Heaps, and Tries.    
  - Linear Structures: Queues, stacks, and lists implemented in both array and linked forms.    
  - Sorting: Classic algorithms like Merge Sort, Heap Sort, and Bubble Sort.    
  - Hash Tables: Basic hash table implementation with separate hashing functions.

`Pratica/`

Contains small projects and problem-solving using the concepts:

  - Maze Solver: A project for solving maze problem using backtracking.
  - Tree Algorithms: Applied usage of AVL and BST trees with test cases.
  - Sorting Project: Real-world inspired sorting application using CSV data.
## Requirements
   - C compiler (e.g. gcc)
   - A Unix-like environment is recommended for file handling

## Notes
  - The code is in portuguese
  - Some filenames might contain typos (e.g., bubbleSorst.c).
  - Comments within the code (in Portuguese) explain implementation details.
## License
  This project is for educational purposes and does not currently include a specific license.
