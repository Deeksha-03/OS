//First Fist -> fast , but may give out huge holes
//Best Fit -> Optimal space utilization , but may occupy less processes in same block
//         -> Time more ,so slow and least internal fragmentation - (good)
//Worst Fit -> Can occupy multiple processes in same block
//          -> Time more ,so slow and high internal fragmentation - (bad)

#include <stdio.h>
void print(int processSize[], int allocation[], int n)
{
    int i;
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++)
    {
        printf(" %i\t\t\t", i + 1);
        printf("%i\t", processSize[i]);
        if (allocation[i] != -1)
            printf("%i", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int i, j;
    // Stores block id of the
    // block allocated to a process
    int allocation[n];
    int blockalocated[m];
    // Initially no block is assigned to any process
    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
     for (i = 0; i < m; i++)
    {
        blockalocated[i]=0;
    }

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (i = 0; i < n; i++) // here, n -> number of processes
    {
        for (j = 0; j < m; j++) // here, m -> number of blocks
        {
            if (blockSize[j] >= processSize[i]&&blockalocated[j]==0)
            {
                // allocating block j to the ith process
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];
                blockalocated[j]=1;
                break; // go to the next process in the queue
            }
        }
    }

    print(processSize, allocation, n);
}
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    // Stores block id of the block allocated to a process
    int allocation[n];
    int i, j, bestIdx;
    // Initially no block is assigned to any process
    for (i = 0; i < n; i++)
        allocation[i] = -1;

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (i = 0; i < n; i++)
    {
        // Find the best fit block for current process
        bestIdx = -1;
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        // If we could find a block for current process
        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            // Reduce available memory in this block.
            blockSize[bestIdx] -= processSize[i];
        }
    }

    print(processSize, allocation, n);
}
// Function to allocate memory to blocks as per worst fit
// algorithm
void worstFit(int blockSize[], int m, int processSize[],
              int n)
{
    // Stores block id of the block allocated to a
    // process
    int allocation[n], i, j, wstIdx;

    // Initially no block is assigned to any process
    for (i = 0; i < n; i++)
        allocation[i] = -1;

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (i = 0; i < n; i++)
    {
        // Find the best fit block for current process
        wstIdx = -1;
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        // If we could find a block for current process
        if (wstIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = wstIdx;

            // Reduce available memory in this block.
            blockSize[wstIdx] -= processSize[i];
        }
    }

    print(processSize, allocation, n);
}
void main()
{
    int m,i; // number of blocks in the memory
    int n; // number of processes in the input queue
    int blockSize[20];
    int processSize[20];
    int choice;
    printf("Enter the number of blocks\n");
    scanf("%d",&m);
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter the size of each block\n");
    for(i=0;i<m;i++)
    {
        scanf("%d",&blockSize[i]);
    }
    printf("Enter the size of each process\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&processSize[i]);
    }
    printf("\n1.First-fit\n2.Best-fit\n3.Worst-fit\n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:firstFit(blockSize, m, processSize, n);
                break;
        case 2:bestFit(blockSize,m,processSize,n);
                break;
        case 3:worstFit(blockSize,m,processSize,n);
                break;
        default:printf("invalid choice\n");
    }
}

/*process 315 427 250 550
block 200 700 500 300 100 400*/
