#include <stdio.h>

#define memsize 50

int memory[memsize] = {0};

// Display memory
void disp() {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < memsize; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

// Check if book already exists
int exists(int id) {
    for (int i = 0; i < memsize; i++) {
        if (memory[i] == id)
            return 1;
    }
    return 0;
}

// Contiguous Allocation
void conti() {
    int start, size, id;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    if (exists(id)) {
        printf("Book ID already exists\n");
        return;
    }

    printf("Enter starting index and size: ");
    scanf("%d %d", &start, &size);

    if (start < 0 || start + size > memsize) {
        printf("Invalid range\n");
        return;
    }

    for (int i = start; i < start + size; i++) {
        if (memory[i] != 0) {
            printf("Allocation Failed\n");
            return;
        }
    }

    for (int i = start; i < start + size; i++) {
        memory[i] = id;
    }

    printf("Contiguous Allocation Successful for Book ID: %d\n", id);
    disp();
}

// Linked Allocation
void link() {
    int size, id, links[memsize];

    printf("Enter Book ID: ");
    scanf("%d", &id);

    if (exists(id)) {
        printf("Book ID already exists\n");
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
        scanf("%d", &links[i]);

        if (links[i] < 0 || links[i] >= memsize) {
            printf("Invalid index\n");
            return;
        }

        if (memory[links[i]] != 0) {
            printf("Allocation Failed\n");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[links[i]] = id;
    }

    printf("Linked Allocation Successful for Book ID: %d\n", id);
    disp();
}

// Indexed Allocation
void indexA() {
    int index, size, id, blocks[memsize];

    printf("Enter Book ID: ");
    scanf("%d", &id);

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

    printf("Enter number of data blocks: ");
    scanf("%d", &size);

    if (size <= 0 || size > memsize) {
        printf("Invalid size\n");
        return;
    }

    printf("Enter data block indices: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &blocks[i]);

        if (blocks[i] < 0 || blocks[i] >= memsize) {
            printf("Invalid block index\n");
            return;
        }

        if (memory[blocks[i]] != 0) {
            printf("Allocation Failed (Block already used)\n");
            return;
        }
    }

    // Allocate index block
    memory[index] = id;

    // Allocate data blocks
    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = id;
    }

    printf("\nIndexed Allocation Successful\n");
    printf("Book ID: %d\n", id);
    printf("Index Block: %d\n", index);
    printf("Data Blocks: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", blocks[i]);
    }

    printf("\n");

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