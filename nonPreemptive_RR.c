#include<stdio.h>
int at[20],cput[20];
void main(){

    int n,i,choice,tq;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter arrival time and cpu time for each process respectively\n");
    for(i =0;i<n;i++){
        scanf("%d %d",&at[i],&cput[i]);
    }

    printf("Menu\n\n1.Round Robin\n2.Priority(Non Preemptive)\n\n3.Exit\n");
    while(1){
        scanf("%d",&choice);
        switch(choice){
        case 1: printf("Enter the time quantum \n");
        scanf("%d",&tq);
            roundRobin(n,tq);
        break;
        case 2: NonprePriority(n);
        break;
        case 3: exit(0);
        default:printf("Wring choice\n");
    }
    }
}

void roundRobin(int n, int tq){
    int i,remaining_time[20],wt[20],tat[20],completed = 0,time=0;
    float awt=0,atat=0;
    for(i=0;i<n;i++){
        remaining_time[i]=cput[i];
    }
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && at[i] <= time) {
                if (remaining_time[i] <= tq) {
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    completed++;

                    tat[i] = time - at[i];
                    wt[i] = tat[i] - cput[i];
                } else {
                    time += tq;
                    remaining_time[i] -= tq;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        atat += tat[i];
        awt += wt[i];
    }
    atat /= n;
    awt /= n;

    printf("\nProcess\Cpu Time\tArrival Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i , cput[i], at[i], tat[i], wt[i]);
    }
    printf("Average Turnaround Time: %.2f\n", atat);
    printf("Average Waiting Time: %.2f\n", awt);
}

void NonprePriority(int n){
    int priority[20],wt[20],tat[20],hp=0,cmpt[20],cput1[20],sum=0,i,sum_burst_time=0;
    float awt=0,atat=0;
    printf("Enter the priorities of processes\n");
     for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        scanf("%d", &priority[i]);
    }
    printf("\t PROCESS \t TURNAROUND TIME\t WAITING TIME\n");
    for (i = 0; i < n; i++) {
            cput1[i]=cput[i];
    sum_burst_time += cput[i];
  }

  priority[9]=-1;
    while(sum < sum_burst_time)
   {
    hp = 9;
    for (i = 0; i < n; i++) {
      if (at[i] <= sum && cput1[i]>0 && priority[i] > priority[hp])
        hp = i;
    }
    printf("\t P[%d] \t\t %d \t\t %d\n", hp , sum + cput1[hp] - at[hp], sum - at[hp]);
    atat += sum + cput1[hp] - at[hp];
    awt += sum - at[hp];
    sum += cput1[hp];
    cput1[hp] = 0;
  }
  awt = awt/n;
    atat =atat/n;

        printf("\nAverage Waiting Time -- %f", awt);
        printf("\nAverage Turnaround Time -- %f\n", atat);
}

/*
5

0 5
1 3
2 1
3 2
4 3

3
2
1
4
3
priority
Awt -- 5.000000
Atat -- 7.800000

rr
Atat: 8.20
Awt: 5.40
*/
