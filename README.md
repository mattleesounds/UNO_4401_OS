# Operating Systems - CSCI 4401/5401

A comprehensive collection of operating systems programming assignments demonstrating core OS concepts including process management, concurrency, deadlock detection, memory management, and resource scheduling.

## Technical Skills Demonstrated

- **Systems Programming**: Low-level C and Java implementation of OS algorithms
- **Concurrency & Synchronization**: Multi-threaded programming with proper synchronization primitives
- **Algorithm Implementation**: Complex graph algorithms, scheduling algorithms, and memory management techniques
- **Data Structures**: Custom graph implementations, resource allocation graphs, page tables
- **Problem Solving**: Translation of theoretical OS concepts into working code

## Projects Overview

### Assignment 2: Process Management & Fork Trees
**Technologies**: C, Python
**Location**: `Assignment2/`

Implementation of process creation and management using fork() system calls:

- **Part A**: Process tree generation with parent-child relationships
- **Part B**: Fork tree visualization (generates process hierarchy diagrams)
- **Part C**: Complex multi-level process trees
- **Part D**: Advanced process control and inter-process relationships

**Key Concepts**:
- System calls (fork, exec, wait)
- Process tree construction
- JSON output generation from process structures
- Data visualization with Python

### Assignment 3: Thread Synchronization
**Technologies**: Java
**Location**: `os-assign3/`

Multi-threaded applications demonstrating synchronization mechanisms:

- **Part A1 & A2**: Basic thread creation and synchronization
- **Part B3 & B4**: Complex synchronization scenarios with shared resources
- **Part C**: Producer-consumer problem implementation

**Key Concepts**:
- Java threading (`Thread`, `Runnable`)
- Synchronization primitives (locks, semaphores)
- Race condition prevention
- Thread-safe data structures

### Assignment 4: Deadlock Detection
**Technologies**: Java
**Location**: `Deadlock.java`

Resource Allocation Graph (RAG) implementation with cycle detection for deadlock identification:

**Features**:
- Graph-based representation of processes and resources
- Dynamic edge management (request/allocation)
- Cycle detection algorithm using DFS
- Real-time deadlock detection and reporting
- Resource manager with FIFO waiting queues

**Key Concepts**:
- Resource Allocation Graphs
- Deadlock detection algorithms
- Graph cycle detection (DFS with recursion stack)
- Process-resource state management

**Implementation Highlights**:
```java
// Core components
- RAG: Resource Allocation Graph management
- Graph: Custom graph implementation with cycle detection
- ResourceManager: Handles resource allocation and waiting queues
- Node: Represents processes and resources in the graph
```

### Assignment 5: Memory & Disk Management
**Technologies**: Java
**Location**: `assign5/HW5.java`

Comprehensive implementation of memory management and disk scheduling algorithms:

#### Part I: Main Memory
- **Contiguous Allocation**: First-Fit, Best-Fit, Worst-Fit algorithms
- **Paging**: Page number and offset calculation for 4KB pages
- **Address Mapping**: Logical to physical address translation using page tables

#### Part II: Virtual Memory
- **FIFO Page Replacement**: First-In-First-Out algorithm with fault counting
- **LRU Page Replacement**: Least Recently Used algorithm implementation

#### Part III: File Systems
- **I-Node Calculations**: File size limits with direct and indirect pointers
- **Multi-level Indexing**: Single and double indirect pointer calculations

#### Part IV: Disk Scheduling
- **FCFS**: First-Come-First-Serve scheduling
- **SCAN**: Elevator algorithm implementation
- **LOOK**: SCAN variant without end-to-end traversal
- **SSTF**: Shortest-Seek-Time-First greedy algorithm

**Key Concepts**:
- Memory allocation strategies and fragmentation
- Virtual memory and page replacement
- File system architecture and i-node structures
- Disk arm scheduling and seek time optimization

## Technical Highlights

### Algorithm Complexity
- Implemented O(n) memory allocation algorithms
- O(V+E) graph traversal for deadlock detection
- Efficient page replacement with optimal data structures

### Code Quality
- Clean, well-structured object-oriented design
- Proper separation of concerns (Graph, RAG, ResourceManager)
- Comprehensive error handling
- Clear variable naming and code organization

### System-Level Understanding
- Deep knowledge of OS internal mechanisms
- Translation of theoretical concepts to practical implementations
- Understanding of performance trade-offs in different algorithms

## Skills Demonstrated

### Programming Languages
- **C**: Low-level systems programming, pointer manipulation, process management
- **Java**: Object-oriented design, collections framework, threading
- **Python**: Data visualization and analysis

### Operating Systems Concepts
- Process lifecycle and management
- Thread synchronization and concurrency control
- Deadlock prevention and detection
- Memory management (paging, virtual memory)
- File system design
- Disk scheduling optimization

### Software Engineering
- Version control with Git
- Modular code design
- Algorithm implementation from specification
- Testing and debugging system-level code

## Building & Running

### Assignment 2 (Process Management)
```bash
cd Assignment2/MattLee_CS5401_Assignment2/partA
gcc partA.c -o partA
./partA
```

### Assignment 3 (Thread Synchronization)
```bash
cd os-assign3
javac PartA1.java
java PartA1
```

### Assignment 4 (Deadlock Detection)
```bash
javac Deadlock.java
java Deadlock <input_file>
```

Input file format: `ProcessID Action ResourceID` (where Action is W for Wait/Request or R for Release)

### Assignment 5 (Memory & Disk Management)
```bash
cd assign5
javac HW5.java
java HW5
```

## Course Information

**Course**: CSCI 4401/5401 - Operating Systems
**Semester**: Fall 2023
**Institution**: University of Nebraska Omaha (UNO)

## License

This repository contains academic coursework and is intended for portfolio demonstration purposes.
