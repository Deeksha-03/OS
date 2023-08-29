#include <stdio.h>
#define MAX 10
void implimentBestFit(int blockSize[], int blocks, int processSize[], int proccesses,int m)
{
    // This will store the block id of the allocated block to a process
    int allocation[proccesses];
    int occupied[blocks];

    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < proccesses; i++){
        allocation[i] = -1;
    }

    for(int i = 0; i < blocks; i++){
        occupied[i] = 0;
    }

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < proccesses; i++)
    {

        int indexPlaced = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i] && !occupied[j])
            {
                // place it at the first block fit to accomodate process
                if (indexPlaced == -1)
                    indexPlaced = j;

                // if any future block is smalller than the current block where
                // process is placed, change the block and thus indexPlaced
		// this reduces the wastage thus best fit
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }

        // If we were successfully able to find block for the process
        if (indexPlaced != -1)
        {
            // allocate this block j to process p[i]
            allocation[i] = indexPlaced;

            // make the status of the block as occupied
            occupied[indexPlaced] = 1;
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n ");
    for (int i = 0; i < proccesses; i++)
    {
        printf("%d \t\t\t %d \t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Driver code
int main()
{
    int p,m,j;
    printf("Enter the number of processes and blocks: ");
    scanf("%d%d",&p,&m);
    int processSize[p],blockSize[m];
    printf("Enter the Process sizes: ");
    for(j=0;j<p;j++)
            scanf("%d",&processSize[j]);

    printf("Enter the Block sizes: ");
    for(j=0;j<m;j++)
            scanf("%d",&blockSize[j]);

    int blocks = sizeof(blockSize)/sizeof(blockSize[0]);
    int proccesses = sizeof(processSize)/sizeof(processSize[0]);

    implimentBestFit(blockSize, blocks, processSize, proccesses,m);

    return 0 ;
}

/*process 315 427 250 550
block 200 700 500 300 100 400*/
