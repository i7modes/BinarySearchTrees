# Binary Search Tree in C

[![CI](https://github.com/i7modes/BinarySearchTrees/actions/workflows/ci.yml/badge.svg)](https://github.com/i7modes/BinarySearchTrees/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C Standard](https://img.shields.io/badge/C-C99-blue.svg)
![Memory Status](https://img.shields.io/badge/Valgrind-0%20Leaks-brightgreen.svg)

A clean, robust, and production-ready implementation of a **Binary Search Tree (BST)** in C99. Features full tree traversals (In-Order, Pre-Order, Post-Order), terminal 2D ASCII visualization, Lowest Common Ancestor (LCA) algorithms, comprehensive unit tests, and zero memory leaks.

---

## Architecture: Binary Search Tree

A Binary Search Tree is a hierarchical data structure where every node satisfies the invariant:
$$\text{Keys in Left Subtree} < \text{Node Key} < \text{Keys in Right Subtree}$$

```text
                    [50]
                   /    \
                 [30]   [70]
                /   \   /   \
              [20] [40][60] [80]
```

### 2D ASCII Terminal Visualization:
The library includes a horizontal ASCII renderer (`BST_Print2D`):
```text
              [80]
       [70]
              [60]
[50]
              [40]
       [30]
              [20]
```

---

## Features

- **Core Operations**: `BST_Insert`, `BST_Delete` (handling leaf, single-child, and two-children cases with in-order successor), `BST_Find`, `BST_FindMin`, `BST_FindMax`.
- **Tree Traversals**:
  - **In-Order**: Visited in ascending sorted order ($20 \rightarrow 30 \rightarrow 40 \dots$).
  - **Pre-Order** & **Post-Order**.
  - **Array Serialization (`BST_ToArrayInOrder`)**: Exports sorted elements into a flat array.
- **Tree Metrics & Algorithms**:
  - **Lowest Common Ancestor (`BST_LowestCommonAncestor`)**: Calculates the lowest shared ancestor of two keys in $\mathcal{O}(h)$ time.
  - **Tree Height (`BST_Height`)** & **Node Count (`BST_Size`)**.
  - **Validator (`BST_IsValid`)**: Confirms that every subtree strictly obeys the BST invariant.
- **Memory Safety**: `BST_Destroy(&root)` deallocates all nodes recursively and nullifies the caller's pointer (0 memory leaks verified by Valgrind).
- **Automated Testing & CI**: 38 unit test assertions tested across Ubuntu and Windows.

---

## Complexity Analysis

| Operation | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
| :--- | :---: | :---: | :---: |
| `BST_Insert` | $\mathcal{O}(\log n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |
| `BST_Delete` | $\mathcal{O}(\log n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |
| `BST_Find` / `FindMin` / `FindMax` | $\mathcal{O}(\log n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ iterative |
| `BST_InOrder` / `PreOrder` / `PostOrder` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |
| `BST_LowestCommonAncestor` | $\mathcal{O}(\log n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ iterative |
| `BST_Height` / `BST_Size` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |
| `BST_Destroy` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |

---

## Project Structure

```text
BinarySearchTrees/
├── include/
│   └── bst.h                    # Public API, types, and legacy compatibility
├── src/
│   └── bst.c                    # Core BST implementation & algorithms
├── examples/
│   └── demo.c                   # Terminal showcase with 2D tree visualizer
├── tests/
│   └── test_bst.c               # Automated unit test suite (38 assertions)
├── .github/
│   └── workflows/
│       └── ci.yml               # GitHub Actions CI matrix
├── Makefile                     # Cross-platform build script
├── LICENSE                      # MIT License
├── .gitignore                   # Ignore binaries and temporary files
└── README.md                    # Project documentation
```

---

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/i7modes/BinarySearchTrees.git
cd BinarySearchTrees
```

### 2. Build and Run Demo
```bash
make demo
make run-demo
```

### 3. Run Automated Unit Tests
```bash
make check
```

Expected output:
```text
========================================
  Binary Search Tree Automated Tests
========================================

--- Test: Empty Tree Safety ---
  [PASS] NULL tree is empty
  [PASS] NULL tree size is 0
  [PASS] NULL tree height is 0
...
========================================
  Results: 38/38 assertions passed
========================================
```

### 4. Run Memory Leak Check (Linux / WSL)
```bash
make test
valgrind --leak-check=full --show-leak-kinds=all ./bin/test_runner
```

---

## Code Example

```c
#include "bst.h"
#include <stdio.h>

int main(void) {
    // 1. Insert values
    BSTNode *root = NULL;
    root = BST_Insert(root, 50);
    root = BST_Insert(root, 30);
    root = BST_Insert(root, 70);
    root = BST_Insert(root, 20);
    root = BST_Insert(root, 40);

    // 2. Visual 2D ASCII Print
    BST_Print2D(root);

    // 3. In-Order Traversal (Sorted)
    printf("Sorted: ");
    BST_PrintInOrder(root); // [ 20 30 40 50 70 ]

    // 4. Lowest Common Ancestor
    const BSTNode *lca = BST_LowestCommonAncestor(root, 20, 40);
    printf("LCA(20, 40) = %d\n", lca->data); // Output: 30

    // 5. Clean up memory
    BST_Destroy(&root); // root is now NULL, 0 memory leaks!
    return 0;
}
```

---

## License

Distributed under the [MIT License](file:///c:/Users/i7mod/OneDrive/GitHub/BinarySearchTrees/LICENSE). Created by [i7modes](https://github.com/i7modes).
