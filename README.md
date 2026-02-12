# 🔴⚫ Red-Black Tree Implementation in C++

A robust and efficient implementation of a **Self-Balancing Binary Search Tree (Red-Black Tree)** in C++.
This project demonstrates core data structure concepts including tree rotations, recoloring rules, balancing invariants, and performance benchmarking.

---

## 🚀 Features

* **Full Implementation**: Support for insertion, deletion, and search.
* **Self-Balancing**: Guarantees ( O(\log n) ) time complexity for all primary operations.
* **Visualization**: Console-based tree printing with Red/Black color indicators.
* **Memory Safe**: Proper destructor handling prevents memory leaks.
* **Performance Benchmarking**: Built-in stress tests with CSV export for timing analysis.
* **Modular Design**: Clear separation between headers, implementation, and test utilities.

---

## 📂 Repository Structure

```
RED_BLACK_TREE/
│
├── CMakeLists.txt
├── include/
│   └── RedBlackTree.hpp
├── src/
│   ├── RedBlackTree.cpp
│   └── main.cpp
├── tests/
│   ├── test_basic.cpp
│   ├── test_stress.cpp
│   ├── test_performance.cpp
│   └── graph.py
└── build/   (generated after compilation)
```

### Key Components

* **RedBlackTree.hpp** — Public interface of the Red-Black Tree class
* **RedBlackTree.cpp** — Implementation (rotations, insert/delete, fixups)
* **main.cpp** — Demo executable (`rbt_tree`)
* **test_basic.cpp** — Functional correctness test
* **test_stress.cpp** — Stress and robustness test
* **test_performance.cpp** — Benchmark utility (generates CSV performance data)
* **graph.py** — Python script to visualize benchmark results

---

## 🛠 Requirements

### C++ Build Requirements

* CMake ≥ 3.10
* C++17-compatible compiler (GCC or Clang)

### Python Requirements (for plotting)

* Python 3
* numpy
* pandas
* matplotlib
* scipy

Install Python dependencies with:

```bash
python3 -m pip install numpy pandas matplotlib scipy
```

---

## 🛠 Installation & Compilation

### 1. Clone the repository

```bash
git clone https://github.com/scaioo/RED_BLACK_TREE.git
cd RED_BLACK_TREE
```

### 2. Build the project (recommended: out-of-source build)

```bash
mkdir -p build
cd build
cmake ..
make -j4
```

This generates the following executables inside `build/`:

* `rbt_tree`
* `test_basic`
* `test_stress`
* `test_performance`

---

## ▶️ Running the Project

### Run the demo program

```bash
./rbt_tree
```

### Run correctness tests

```bash
./test_basic
./test_stress
```

### Run performance benchmark

```bash
./test_performance
```

This will generate:

```
build/rbt_performance.csv
```

Note: Large input sizes (e.g., 100k–1M elements) may take noticeable time depending on your hardware.

---

## 📊 Plotting Performance Results

After running `test_performance`, use the plotting utility:

```bash
python3 tests/graph.py
```

The script:

* Automatically detects `build/rbt_performance.csv`
* Plots execution time vs. input size
* Fits a theoretical ( O(\log n) ) curve for comparison

---

## 🧠 Red-Black Tree Properties

This implementation enforces the five classical Red-Black Tree properties:

1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, both of its children are black.
5. Every path from a node to its descendant NIL nodes contains the same number of black nodes.

Balancing is maintained through:

* Left and right rotations
* Recoloring rules
* Insert fix-up procedure
* Delete fix-up procedure

All primary operations run in:

[
O(\log n)
]

---

## 🧪 Developer Notes

* `verifyProperties()` can be used to assert Red-Black invariants during testing.
* For realistic large-scale benchmarks, disable verbose output in performance tests.
* The project structure allows easy extension (e.g., templating the tree for generic types).

---

## 🚧 Possible Improvements

* Add GoogleTest or Catch2 unit testing framework
* Add GitHub Actions CI workflow
* Convert the implementation into a templated generic container
* Add Graphviz export for graphical visualization
* Improve automatic performance aggregation and plot export

---

## 📜 License

This project is open-source and available under the MIT License.

---

## 👨‍💻 Author

**Andrea Scaioli**
MSc Physics — University of Milan

Passionate about algorithms, computational science, and efficient data structures.
