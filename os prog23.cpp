#include <stdio.h>

#define MAX_MEMORY_BLOCKS 100

int memory[MAX_MEMORY_BLOCKS]; // Represents the memory pool
int allocated[MAX_MEMORY_BLOCKS]; // 1 if block is allocated, 0 if it's free

int firstFit(int blockSize, int n) {
    for (int i = 0; i < n; i++) {
        if (allocated[i] == 0 && memory[i] >= blockSize) {
            return i;
        }
    }
    return -1; // No suitable block found
}

void allocateMemory(int blockSize, int n) {
    int blockIndex = firstFit(blockSize, n);

    if (blockIndex == -1) {
        printf("Memory allocation failed for block size %d\n", blockSize);
    } else {
        allocated[blockIndex] = 1;
        printf("Allocated memory block %d for block size %d\n", blockIndex, blockSize);
    }
}

void deallocateMemory(int blockIndex) {
    if (allocated[blockIndex] == 1) {
        allocated[blockIndex] = 0;
        printf("Deallocated memory block %d\n", blockIndex);
    } else {
        printf("Memory block %d is already free\n", blockIndex);
    }
}

int main() {
    int n, blockSize, choice;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the size of memory block %d: ", i);
        scanf("%d", &memory[i]);
        allocated[i] = 0;
    }

    while (1) {
        printf("\nMemory Management Menu:\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the block size to allocate: ");
                scanf("%d", &blockSize);
                allocateMemory(blockSize, n);
                break;
            case 2:
                printf("Enter the memory block index to deallocate: ");
                scanf("%d", &blockSize);
                deallocateMemory(blockSize);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

