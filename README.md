# Library Book Storage System Using Memory Allocation Methods

This project is an educational simulation designed to demonstrate how an Operating System manages secondary storage using different file allocation methods. By applying these concepts to a library "Book and Rack" system, the application provides a visual and interactive way to understand how files are physically mapped to disk blocks.

The repository includes three distinct versions:
1. **Linux GUI (GTK 3)**: A native C application providing a 10x10 grid visualizer for Linux environments.
2. **CLI Version**: A terminal-based implementation focusing on the core algorithmic logic and pointer manipulation.

---

## Technical Overview

### Allocation Methods Implemented
* **Contiguous Allocation**: Each book occupies a set of adjacent blocks. This version demonstrates high performance but highlights the issue of external fragmentation.
* **Linked Allocation**: Each book is stored as a linked list of blocks. This eliminates external fragmentation but shows how sequential access is required to find data.
* **Indexed Allocation**: A specific block is designated as an index block which contains the addresses of all data blocks. This demonstrates how modern file systems achieve direct access to file content.

---

## Literature Survey and Background Research

This project is grounded in established Operating System principles. The following sources were used to research the logic and architecture of the simulation:

### 1. Fundamental Concepts of Storage Management
As outlined by **Silberschatz, Galvin, and Gagne** in "Operating System Concepts," the primary goal of the OS is to provide efficient access to the disk and utilize disk space effectively. Their analysis of Contiguous, Linked, and Indexed allocation provides the theoretical framework for our implementation of block mapping.
* Source: [Operating System Concepts](https://www.os-book.com/)

### 2. Analysis of Disk Performance and Space Trade-offs
**William Stallings** in "Operating Systems: Internals and Design Principles" discusses the trade-off between the speed of Contiguous allocation and the flexibility of non-contiguous methods. His work emphasizes that while Contiguous allocation is efficient for sequential files, it requires periodic "compaction" to recover fragmented space. Our simulation visualizes this fragmentation in real-time.
* Source: [Operating Systems - William Stallings](https://williamstallings.com/OperatingSystems/)

### 3. Modern File Systems and Index Structures
**Andrew S. Tanenbaum** in "Modern Operating Systems" provides a deep dive into the use of i-nodes and index blocks, which is the basis for our Indexed Allocation module. His research explains how modern Unix-based systems (like the Kali Linux environment this app was built for) use multi-level indexing to handle large files.
* Source: [Modern Operating Systems - Pearson](https://www.pearson.com/)

### 4. Implementation Strategies for Linked Allocation
Research from **GeeksforGeeks** and **JavaTpoint** provided practical pseudocode for the "pointer" logic used in our Linked Allocation module. These resources illustrate how the OS avoids the need for a single continuous hole in memory, instead utilizing any available disk block.
* Source: [File Allocation Methods - GeeksforGeeks](https://www.geeksforgeeks.org/file-allocation-methods/)
* Source: [OS File Allocation Methods - JavaTpoint](https://www.javatpoint.com/os-file-allocation-methods)

### 5. Educational Impact of OS Visualizers
According to a survey of computer science education tools published on **Guru99**, visual simulations are essential for understanding abstract OS concepts like disk scheduling and block management. The visual grid in our GTK application is designed to bridge the gap between theoretical textbook descriptions and practical execution.
* Source: [Operating System Tutorial - Guru99](https://www.guru99.com/operating-system-tutorial.html)

---

## Installation and Setup (Linux GTK Version)

### Prerequisites
Ensure the GTK 3 development libraries are installed on your system:
```bash
sudo apt update
sudo apt install libgtk-3-dev pkg-config build-essential
```

### Compilation
Navigate to the source directory and compile using GCC:
```bash
gcc library_system_v2.c -o library_system_v2 `pkg-config --cflags --libs gtk+-3.0`
```

### Running the Application
```bash
./library_system_v2
```

---

## Authors
* Jerin Raj, Asher Selva Jason, Darren, Jelin

---
