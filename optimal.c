#include <stdio.h>

void displayFrames(int fr[], int fn) {
    //printf("Memory frames: ");
    for (int i = 0; i < fn; i++) {
        if (fr[i] != -1) {
            printf("%d ", fr[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

void optimalPage(int pg[], int pn, int fn) {
    // Create an array for given number of frames and initialize it as empty.
    int fr[fn];
    for (int i = 0; i < fn; i++) {
        fr[i] = -1;
    }

    // Traverse through page reference array and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++) {
        // Page found in a frame: HIT
        int found = 0;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == pg[i]) {
                hit++;
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Page %d: Hit   :", pg[i]);
        } else {
            // Page not found in a frame: MISS

            // If there is space available in frames.
            int emptyFrame = -1;
            for (int j = 0; j < fn; j++) {
                if (fr[j] == -1) {
                    fr[j] = pg[i];
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1) {
                printf("Page %d: Miss  :", pg[i]);
            } else {
                // Find the page to be replaced.
                int farthest = -1, replaceIndex = -1;
                for (int j = 0; j < fn; j++) {
                    int k;
                    for (k = i + 1; k < pn; k++) {
                        if (fr[j] == pg[k]) {
                            if (k > farthest) {
                                farthest = k;
                                replaceIndex = j;
                            }
                            break;
                        }
                    }
                    if (k == pn) {
                        replaceIndex = j;
                        break;
                    }
                }
                fr[replaceIndex] = pg[i];
                printf("Page %d: Miss  :", pg[i], fr[replaceIndex]);
            }
        }

        // Display the contents of memory frames after each iteration.
        displayFrames(fr, fn);
    }

    printf("\nNo. of hits = %d\n", hit);
    printf("No. of misses = %d\n", pn - hit);
}

int main() {
    int pn;
    printf("Enter the number of pages: ");
    scanf("%d",&pn);
    int pg[pn];
    printf("Enter the pages: ");
    for(int i=0;i<pn;i++){
        scanf("%d",&pg[i]);
    }
    int fn = 3;
    optimalPage(pg, pn, fn);
    return 0;
}

/*7 0 1 2 0 3 0 4 2 3*/
