#include <stdio.h>

void implimentWorstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // This will store the block id of the allocated block to a process
    int allocation[processes];
    int occupied[blocks];

    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    for(int i = 0; i < blocks; i++)
        occupied[i] = 0;

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i=0; i < processes; i++)
    {
        int indexPlaced = -1;
        for(int j = 0; j < blocks; j++)
        {
           // if not occupied and block size is large enough
           if(blockSize[j] >= processSize[i] && !occupied[j])
            {
                // place it at the first block fit to accomodate process
                if (indexPlaced == -1)
                    indexPlaced = j;

                // if any future block is larger than the current block where
                // process is placed, change the block and thus indexPlaced
                else if (blockSize[indexPlaced] < blockSize[j])
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

            // Reduce available memory for the block
            blockSize[indexPlaced] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Driver code
int main()
{
    int i;
    int blocks;
    int processes;
    printf("Enter the number of processes and blocks: ");
    scanf("%d%d", &processes,&blocks);

    int processSize[processes];
    printf("\nEnter size of each process: ");
    for(i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    int blockSize[blocks];
    printf("\nEnter size of each block: ");
    for(i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    implimentWorstFit(blockSize, blocks, processSize, processes);

    return 0;
}

/*process 315 427 250 550
block 200 700 500 300 100 400*/


