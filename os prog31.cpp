#include <stdio.h>

#define MAX_FRAMES 3 // Maximum number of page frames
#define MAX_PAGES 10 // Maximum number of pages in the reference string

int pageFrames[MAX_FRAMES]; // Array to store page frames
int pageQueue[MAX_FRAMES]; // FIFO queue to manage page replacement
int pageQueueFront = 0; // Front of the FIFO queue
int pageQueueRear = -1; // Rear of the FIFO queue

int pageReferences[MAX_PAGES] = {0, 1, 2, 3, 2, 4, 5, 3, 4, 1}; // Page reference string

int pageFaults = 0; // Number of page faults

// Initialize the page frames and FIFO queue
void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1; // Empty frame indicated by -1
        pageQueue[i] = -1;
    }
}

// Display the current state of page frames
void displayPageFrames() {
    printf("Page Frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] != -1) {
            printf("%d ", pageFrames[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// Check if the page is already in memory
int isPageInMemory(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// Replace the oldest page using FIFO policy
void replacePage(int page) {
    int replacedPage = pageQueue[pageQueueFront];

    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == replacedPage) {
            pageFrames[i] = page;
            pageQueue[pageQueueFront] = page;
            pageQueueFront = (pageQueueFront + 1) % MAX_FRAMES;
            return;
        }
    }
}

int main() {
    initialize();

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pageReferences[i];

        if (!isPageInMemory(page)) {
            pageFaults++;
            int freeFrame = -1;

            // Find a free frame
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (pageFrames[j] == -1) {
                    freeFrame = j;
                    break;
                }
            }

            if (freeFrame != -1) {
                pageFrames[freeFrame] = page;
                pageQueueRear = (pageQueueRear + 1) % MAX_FRAMES;
                pageQueue[pageQueueRear] = page;
            } else {
                replacePage(page);
            }

            displayPageFrames();
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

