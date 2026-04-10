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
                // conti();
            }
            else if (choice == 2) {
                // link();
            }
            else if (choice == 3) {
                // index();
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
