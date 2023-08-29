#include <stdio.h>
int main()
{
    int n, m, all[10][10], max[10][10], ava[10], need[10][10],work[10];
    int i, j, k, finish[10], prev[10], c, count = 0;

    printf("Enter number of processes and number of resources required \n");
    scanf("%d %d", &n, &m);

    printf("Enter the request matrix for %d processes\n", n);
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
                    for (j = 0; j < m; j++)
                    {
                        work[j] = work[j] + all[i][j];
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

    if (count == n)
        printf("\nNo Deadlock Detected! \n");

    else
        printf("\nDeadlock Detected! \n");

    return 0;
}
