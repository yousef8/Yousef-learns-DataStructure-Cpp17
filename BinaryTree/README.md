# Binary Tree (Full/Strict)

- Every node has 0 or 2 children.

## Terminology

- **Leaf Node**: A node that does not have any children.
- **Internal Node**: A node that has at least one child.
- **Root Node**: The topmost node in the tree.
- **Height of a Tree**: The number of edges on the longest path from root node to a leaf.
- **Depth of a Node**: The number of edges from the root to the node.
- **Level of a Node**: The number of nodes along the path from the root to the node (including the node itself).

## Formulas

- internal nodes = total nodes - leaf nodes
- leaf nodes = internal nodes + 1 (for a non-empty binary tree)
- minimum number of nodes = 2 * h + 1 (where h is the height of the tree)
- maximum number of nodes = 2^(h+1) - 1
- height = log2(n + 1) - 1 (where n is the number of nodes)
- minimum levels = ceil(log2(nodes + 1))
- minimum levels = ceil(log2(leaf nodes)) + 1

## Other types of Binary Trees

### Perfect Binary Tree

- All leaf nodes are at the same level.
- All internal nodes have exactly two children.

- num of nodes = 2^(h+1 = levels) - 1
- h = log2(n + 1) - 1

### Complete Binary Tree

- All levels are fully filled except possibly the last level, which is filled from left to right.

### Degenerate (Pathological) Tree

- Each parent node has only one child, resembling a linked list.
- Given N nodes, we can construct largest depth of N using a degenerate tree.
- Smallest depth of log(N) can be achieved using a balanced binary tree.

### Balanced Binary Tree

- In a balanced binary tree, the depth of the two subtrees of every node never differs by more than one.
- We try to keep the height of the tree as small as possible.
