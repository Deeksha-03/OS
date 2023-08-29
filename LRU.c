#include <stdio.h>

// Function to display the current state of memory frames
void displayFrames(int fr[], int fn) {
    for (int i = 0; i < fn; i++) {
        if (fr[i] != -1) {
            printf("%d ", fr[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}
int isPageInMemory(int page,int fn,int frames[fn])
{
    for (int i = 0; i < fn; i++) {
        if (frames[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}
// Function to implement the LRU page replacement algorithm
void lruPage(int pg[], int pn, int fn)
{
    int fr[fn];
    for (int i = 0; i < fn; i++)
        fr[i] = -1;

    int hit = 0;

    for (int i = 0; i < pn; i++)
    {

        if (isPageInMemory(pg[i],fn,fr))
        {
            hit++;
            printf("Page %d: Hit   :", pg[i]);
        }
        else
        {
              // If there is space available in frames.
            int emptyFrame = -1;
            for (int j = 0; j < fn; j++)
            {
                if (fr[j] == -1) {
                    fr[j] = pg[i];
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1)
                printf("Page %d: Miss  :", pg[i]);
            else {
                int minCounter = pn + 1, replaceIndex = -1;
                for (int j = 0; j < fn; j++)
                {
                    int k;
                    for (k = i - 1; k >= 0; k--) {
                        if (fr[j] == pg[k]) {
                            if (k < minCounter) {
                                minCounter = k;
                                replaceIndex = j;
                            }
                            break;
                        }
                    }
                    if (k == -1) {
                        replaceIndex = j;
                        break;
                    }
                }
                fr[replaceIndex] = pg[i];
                printf("Page %d: Miss  :", pg[i]);
            }
        }

        displayFrames(fr, fn);
    }

    printf("\nNo. of hits = %d\n", hit);
    printf("No. of misses = %d\n", pn - hit);
}

int main() {
    int pn;
    printf("Enter the number of pages: ");
    scanf("%d", &pn);
    int pg[pn];
    printf("Enter the pages: ");
    for (int i = 0; i < pn; i++) {
        scanf("%d", &pg[i]);
    }
    int fn = 3;
    lruPage(pg, pn, fn);
    return 0;
}

/*
7 0 1 2 0 3 0 4 2 3
*/
