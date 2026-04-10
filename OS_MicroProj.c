#include <stdio.h>

#define memsize 50
int memory[memsize] = {0};

void disp() {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < memsize; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

//Cont
void conti(){
  int start, size;

    printf("Enter starting block and size: ");
    scanf("%d %d", &start, &size);
    
    for (int i = start; i < start + size; i++) {
        if (memory[i]==1 || start+size > memsize){
            printf("Allocation Failed (Blocks not free)\n");
            return;
        }
    }
    for (int i = start; i < start + size; i++) {
        memory[i] = 1;
    }
    printf("Contiguous Allocation Successful\n");
    disp();
}

//Link
void link(){
    int size;
    int links[memsize];

    printf("Enter number of blocks: ");
    scanf("%d", &size);

    printf("Enter block numbers: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &links[i]);
    }
    for (int i = 0; i < size; i++) {
        if (memory[links[i]]==1 || memory[links[i]] > memsize || size > memsize){
            printf("Allocation Failed (Blocks not free)\n");
            return;
       }
    }
    for (int i = 0; i < size; i++) {
        memory[links[i]] = 1;
    }
    disp();
}

void indexA() {
    int index, size;
    int blocks[memsize];

    printf("Enter index block: ");
    scanf("%d", &index);

    if (index < 1 || index > memsize) {
        printf("Invalid index block\n");
        return;
    }

    if (memory[index] == 1) {
        printf("Index block already allocated\n");
        return;
    }

    printf("Enter number of blocks: ");
    scanf("%d", &size);

    if (size <= 0 || size > memsize) {
        printf("Invalid size\n");
        return;
    }

    printf("Enter block numbers: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &blocks[i]);

        // Validate each block
        if (blocks[i] < 1 || blocks[i] > memsize) {
            printf("Invalid block number\n");
            return;
        }

        if (memory[blocks[i]] == 1) {
            printf("Allocation Failed (Block not free)\n");
            return;
        }
    }

    // Allocate index block
    memory[index] = 1;

    // Allocate data blocks
    for (int i = 0; i < size; i++) {
        memory[blocks[i] - 1] = 1;
    }

    printf("Indexed Allocation Successful\n");
    disp();
}

// Main function
int main() {
    int choice;
    while (1) {
        printf("\n--- Library Storage System ---\n");
        printf("1) Contiguous Allocation\n2) Linked Allocation\n3) Indexed Allocation\n4) Display Memory\n5) Exit\n");

        for (int i=0;i<1;i++) {
            printf("Enter choice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                conti();
            }
            else if (choice == 2) {
                link();
            }
            else if (choice == 3) {
                indexA();
            }
            else if (choice == 4) {
                disp();
            }
            else if (choice == 5) {
                return 0;
            }
            else {
                printf("Invalid Input\n");
                i=-1;
            }
        }
    }
}
