#include <stdio.h>
int main()
{
    int n, m, all[10][10], max[10][10], ava[10], need[10][10],work[10];
    int i, j, k, finish[10], prev[10], c, count = 0,array[10],z=0;
    printf("Enter number of processes and number of resources required \n");
    scanf("%d %d", &n, &m);
    printf("Enter maximum number of required resources for each of the %d processes(matrix)\n", n);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the allocated matrix for %d processes\n", n);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &all[i][j]);

    printf("Enter number of available resources \n");
    for (i = 0; i < m; i++)
        scanf("%d", &ava[i]);

    for (i = 0; i < m; i++)
        work[i]=ava[i];

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - all[i][j];

    for (i = 0; i < n; i++)
        finish[i] = 0;

    k = 1;
    while (k)
    {
        k = 0; // Reset the value of k for each iteration of the loop
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                c = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] <= work[j])
                        c++;
                }

                if (c == m)//if all resources available for execution
                {
                    array[z++]=i; //to keep track of index of process executed
                    printf("Resources can be allocated to Process:%d and available resources are: ", (i+ 1));

                    for (j = 0; j < m; j++)
                        printf("%d ", work[j]);

                    printf("\n");

                    for (j = 0; j < m; j++)
                    {
                        work[j] += all[i][j];
                        all[i][j] = 0;
                    }
                    finish[i] = 1;
                    count++;
                }
            }
        }
        // Check if the current state is different from the previous state
        for (i = 0; i < n; i++)
        {
            if (finish[i] != prev[i])
            {
                k = 1;
                break;
            }
        }
        for (i = 0; i < n; i++)
            prev[i] = finish[i];

    }
    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) //printing need matrix
    {
        for (j = 0; j < m; j++)
            printf("%d ",need[i][j]);
        printf("\n");
    }

    if (count == n)
    {
        printf("\nSystem is in safe mode \n<");
        for(i=0;i<n;i++)
        printf("P%d ",(array[i]+1));
        printf(">\n");
    }
    else
        printf("\nSystem is not in safe mode. Deadlock occurred! \n");

    return 0;
}

/*alloc

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

max

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

3 3 2
op:
2 4 5 1 3*/
