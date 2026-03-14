# C++ Containers: Reimplementing the STL (C++98)
## "Don't just use the library. Be the library."

This project is a deep dive into the internals of the C++ Standard Template Library. The challenge: Reimplementing core STL containers from scratch, adhering strictly to the C++98 standard, without using the std library for the underlying data structures.

## Why This Matters

For an Embedded Engineer, memory is a precious resource. This project demonstrates:

- Manual Memory Management: Implementing custom std::allocator logic.

- Data Structure Design: Building Red-Black Trees for map and dynamic arrays for vector.

- Template Metaprogramming: Using SFINAE (enable_if) and type traits to mimic STL behavior.

- Algorithm Efficiency: Ensuring O(logn) for tree operations and O(1) amortized for vector insertions.


| Container | Underlying Structure | Key Features |
| :--- | :--- | :--- |
| **`ft::vector`** | Dynamic Array | Amortized growth, iterator traits, and full `std::allocator` integration.  |
| **`ft::map`** | Red-Black Tree | Self-balancing tree architecture, bidirectional iterators, and key-value pair handling.  |
| **`ft::stack`** | Container Adaptor | Built on top of `ft::vector` to provide LIFO logic.  |

## Technical Highlights

### 1. The Red-Black Tree Implementation

The most complex part of the project was the map. I implemented a Red-Black Tree to ensure that search, insertion, and deletion always happen in logarithmic time. This involved handling complex rotations and re-coloring during node insertion/deletion to maintain tree balance.

### 2. Iterator Architecture

I built custom iterators from scratch, including:

- Random Access Iterators for Vector.

- Bidirectional Iterators for Map.

- Reverse Iterators using a template wrapper.

### 3. SFINAE & Type Traits

To ensure that my containers behave exactly like the STL, I implemented enable_if and is_integral to handle function overloading and prevent ambiguous template instantiations.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., clang++ or g++)

- make

### Installation

```
Bash
```
```  
git clone https://github.com/Sirelaw/Containers.git
cd Containers
make
```

### Running the Comparison Test

This project includes a test suite that compares the performance and output of ft:: containers against the standard std:: containers.

```
Bash
```
```
./container_test
```

References

[std::map](https://en.cppreference.com/w/cpp/container/map)

[std::set](https://en.cppreference.com/w/cpp/container/set)

[std::vector](https://en.cppreference.com/w/cpp/container/vector)

[std::stack](https://en.cppreference.com/w/cpp/container/stack)

[std::enable_if](https://en.cppreference.com/w/cpp/types/enable_if)

[C++ standard library as at Aug 2016](https://web.archive.org/web/20160811224408/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/)

Useful resources

[Red_Black Tree](https://www.youtube.com/watch?v=3RQtq7PDHog)

[Templates](https://youtube.com/playlist?list=PLAe2BCBg8rkIicrIjA6LyjiMn8GFaS6pJ)

