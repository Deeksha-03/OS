#include <stdio.h>

#define MAX_FRAMES 3 // Number of memory frames

int frames[MAX_FRAMES]; // Array to hold memory frames
int framePointer = 0;   // Pointer to the current frame being replaced
int pageFaultCount = 0; // Counter for page faults

// Function to check if a page is already in memory
int isPageInMemory(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// Function to display the contents of memory frames
void displayFrames() {
    //printf("Memory frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// Function to simulate page replacement using FIFO algorithm
void fifo(int pages[], int pageCount) {
    for (int i = 0; i < pageCount; i++) {
        printf("For page %d: ", pages[i]);

        if (!isPageInMemory(pages[i]))
        {
            frames[framePointer] = pages[i];
            framePointer = (framePointer + 1) % MAX_FRAMES;
            pageFaultCount++;
            //printf("Page fault occurred. ");
        }
        else {
            printf("No page fault. ");
        }

        displayFrames();
    }

    printf("\nTotal Page Faults: %d\n", pageFaultCount);
}

int main() {
    int pageCount;
    printf("Enter the number of pages: ");
    scanf("%d",&pageCount);
    int pages[pageCount];
    printf("Enter the pages: ");
    for(int i=0;i<pageCount;i++){
        scanf("%d",&pages[i]);
    }

    // Initialize frames array with -1 to indicate empty frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    fifo(pages, pageCount);

    return 0;
}
/*7 0 1 2 0 3 0 4 2 3
page fault = 9*/
