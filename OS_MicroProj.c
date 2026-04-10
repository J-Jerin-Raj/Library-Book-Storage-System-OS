#include <stdio.h>

#define memsize 50

int memory[memsize] = {0};   // stores book IDs (0 = free)
int bookID = 1;              // auto-increment book ID

// Display memory
void disp() {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < memsize; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

// Contiguous Allocation
void conti() {
    int start, size;

    printf("Enter starting index and size: ");
    scanf("%d %d", &start, &size);

    if (start < 0 || start + size > memsize) {
        printf("Invalid range\n");
        return;
    }

    for (int i = start; i < start + size; i++) {
        if (memory[i] != 0) {
            printf("Allocation Failed (Blocks not free)\n");
            return;
        }
    }

    for (int i = start; i < start + size; i++) {
        memory[i] = bookID;
    }

    printf("Contiguous Allocation Successful for Book ID: %d\n", bookID++);
    disp();
}

// Linked Allocation
void link() {
    int size, links[memsize];

    printf("Enter number of blocks: ");
    scanf("%d", &size);

    if (size <= 0 || size > memsize) {
        printf("Invalid size\n");
        return;
    }

    printf("Enter block indices: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &links[i]);

        if (links[i] < 0 || links[i] >= memsize) {
            printf("Invalid index\n");
            return;
        }

        if (memory[links[i]] != 0) {
            printf("Allocation Failed (Block not free)\n");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[links[i]] = bookID;
    }

    printf("Linked Allocation Successful for Book ID: %d\n", bookID++);
    disp();
}

// Indexed Allocation
void indexA() {
    int index, size, blocks[memsize];

    printf("Enter index block: ");
    scanf("%d", &index);

    if (index < 0 || index >= memsize) {
        printf("Invalid index block\n");
        return;
    }

    if (memory[index] != 0) {
        printf("Index block already allocated\n");
        return;
    }

    printf("Enter number of blocks: ");
    scanf("%d", &size);

    if (size <= 0 || size > memsize) {
        printf("Invalid size\n");
        return;
    }

    printf("Enter block indices: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &blocks[i]);

        if (blocks[i] < 0 || blocks[i] >= memsize) {
            printf("Invalid index\n");
            return;
        }

        if (memory[blocks[i]] != 0) {
            printf("Allocation Failed (Block not free)\n");
            return;
        }
    }

    // allocate index block
    memory[index] = bookID;

    // allocate data blocks
    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = bookID;
    }

    printf("Indexed Allocation Successful for Book ID: %d\n", bookID++);
    disp();
}

// Deallocation
void deallocate() {
    int id;
    printf("Enter Book ID to remove: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < memsize; i++) {
        if (memory[i] == id) {
            memory[i] = 0;
            found = 1;
        }
    }

    if (found)
        printf("Book ID %d removed successfully\n", id);
    else
        printf("Book ID not found\n");

    disp();
}

// Main
int main() {
    int choice;

    while (1) {
        printf("\n--- Library Book Storage System ---\n");
        printf("1) Contiguous Allocation\n");
        printf("2) Linked Allocation\n");
        printf("3) Indexed Allocation\n");
        printf("4) Display Memory\n");
        printf("5) Deallocate Book\n");
        printf("6) Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: conti(); break;
            case 2: link(); break;
            case 3: indexA(); break;
            case 4: disp(); break;
            case 5: deallocate(); break;
            case 6: return 0;
            default: printf("Invalid Input\n");
        }
    }
}