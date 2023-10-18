#include <stdio.h>

#define MAX_FRAMES 3 // Maximum number of page frames
#define MAX_PAGES 10 // Maximum number of pages in the reference string

int pageFrames[MAX_FRAMES]; // Array to store page frames
int pageTimestamp[MAX_FRAMES]; // Timestamps for pages in frames

int pageReferences[MAX_PAGES] = {0, 1, 2, 3, 2, 4, 5, 3, 4, 1}; // Page reference string

int pageFaults = 0; // Number of page faults

// Initialize the page frames and timestamps
void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1; // Empty frame indicated by -1
        pageTimestamp[i] = 0;
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

// Replace the least recently used page using LRU policy
void replacePage(int page) {
    int minTimestamp = pageTimestamp[0];
    int replaceIndex = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (pageTimestamp[i] < minTimestamp) {
            minTimestamp = pageTimestamp[i];
            replaceIndex = i;
        }
    }

    pageFrames[replaceIndex] = page;
    pageTimestamp[replaceIndex] = 0;
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
            } else {
                replacePage(page);
            }

            displayPageFrames();
        }

        // Update page timestamps
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageFrames[j] != -1) {
                pageTimestamp[j]++;
            }
        }
        pageTimestamp[page] = 0;
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

