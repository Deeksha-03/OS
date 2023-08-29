#include<stdio.h>
#include<conio.h>
#define max 25

void main()
{
    int frag[max], b[max], f[max], i, j, nb, nf, temp;
    static int bf[max], ff[max];

    printf("\n\tMemory Management Scheme - First Fit");
    printf("\nEnter the number of blocks:");
    scanf("%d", &nb);
    printf("\nEnter the number of Process:");
    scanf("%d", &nf);

    printf("\nEnter the size of all %d blocks: ",nb);
    for (i = 1; i <= nb; i++) {
        scanf("%d", &b[i]);
    }

    printf("\nEnter the size of all %d Processes:-\n",nf);
    for (i = 1; i <= nf; i++) {
        scanf("%d", &f[i]);
    }

    printf("\nProcess_no:\tProcess_size:\tBlock_no:\tBlock_size:");

    for (i = 1; i <= nf; i++)
    {
        int allocated = 0;
        for (j = 1; j <= nb; j++)
        {
            if (bf[j] != 1) // If bf[j] is not allocated
            {
                if (b[j] >= f[i]) {
                    ff[i] = j;
                    bf[j] = 1; // Allocate block j to file i
                    frag[i] = b[j] - f[i]; // Remaining space in the block
                    allocated = 1;
                    printf("\n%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]]);
                    break; // Stop searching for blocks
                }
            }
        }
        if (!allocated) {
            printf("\n%d\t\t%d\t\tNot Allocated\t\t-", i, f[i]);
        }
    }

    getch();
}

/*process 315 427 250 550
block 200 700 500 300 100 400*/
