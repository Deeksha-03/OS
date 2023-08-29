#include<stdio.h>
int at[20],cput[20];
void main(){

    int n,i,choice;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter arrival time and cpu time for each process respectively\n");
    for(i =0;i<n;i++){
        scanf("%d %d",&at[i],&cput[i]);
    }

    printf("Menu\n\n1.FCFS\n2.SJF(Non Preemptive)\n3.SRTF(Preemptive)\n4.Exit\n");
    while(1){
        scanf("%d",&choice);
        switch(choice){
        case 1: fcfs(n);
        break;
        case 2: sjf(n);
        break;
        case 3: srtf(n);
        break;
        case 4: exit(0);
        default:printf("Wring choice\n");
    }
    }
}

void srtf(int n) {
    int remaining_time[20], tat[20], wt[20], completion_time[20], smallest, time, i, count = 0;
    float awt=0,atat=0;

    for (i = 0; i < n; i++)
        remaining_time[i] = cput[i];

    time = 0;

    while (count != n) {
        smallest = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && remaining_time[i] > 0) {
                if (smallest == -1 || remaining_time[i] < remaining_time[smallest])
                    smallest = i;
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        remaining_time[smallest]--;

        if (remaining_time[smallest] == 0) {
            count++;
            completion_time[smallest] = time + 1;
            wt[smallest] = completion_time[smallest] - at[smallest] - cput[smallest];
            tat[smallest] = completion_time[smallest] - at[smallest];
        }

        time++;
    }
    for(i=0;i<n;i++){
        awt+=wt[i];
        atat += tat[i];

    }
    awt = awt/n;
    atat =atat/n;

    printf("\nProcess\tArrival Time\tCPU Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i, at[i], cput[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time -- %f", awt);
    printf("\nAverage Turnaround Time -- %f\n", atat);

}

void sjf(int n){
    int cmpt[20],tat[20],wt[20],cput1[20];
    float awt=0, atat=0,sum_burst_time=0;
    int sum=0,i,j, smallest;
        printf("\t PROCESS \t TURNAROUND TIME\t WAITING TIME\n");

    for (i = 0; i < n; i++) {
            cput1[i]=cput[i];
    sum_burst_time += cput[i];
  }
    cput1[9]=9999;
    while(sum < sum_burst_time)
   {
    smallest = 9;
    for (i = 0; i < n; i++) {
      if (at[i] <= sum && cput1[i] > 0 && cput1[i] < cput1[smallest])
        smallest = i;
    }
    printf("\t P[%d] \t\t %d \t\t %d\n", smallest , sum + cput1[smallest] - at[smallest], sum - at[smallest]);
    atat += sum + cput1[smallest] - at[smallest];
    awt += sum - at[smallest];
    sum += cput1[smallest];
    cput1[smallest] = 0;
  }
    awt = awt/n;
    atat =atat/n;

        printf("\nAverage Waiting Time -- %f", awt);
        printf("\nAverage Turnaround Time -- %f\n", atat);
}

void fcfs(int n){
    int cmpt[20],tat[20],wt[20],pname[20],temp;
    float awt=0, atat=0;
    int sum=0,i;
    for(i=0;i<n;i++){
      pname[i]=i;
    }
    for(i=0;i<n;i++){
      if(at[i]==at[i+1] && cput[i]>cput[i+1]){
        temp = cput[i];
        cput[i]=cput[i+1];
        cput[i+1]=temp;
        temp = pname[i];
        pname[i]=pname[i+1];
        pname[i+1]=temp;
      }
    }
    for(i=0;i<n;i++){
      sum += cput[i];
      cmpt[i]=sum;
      tat[i]=cmpt[i]-at[i];
      wt[i]=tat[i]-cput[i];
    }

    for(i=0;i<n;i++){
        awt+=wt[i];
        atat += tat[i];
    }
    awt = awt/n;
    atat =atat/n;
    printf("\t PROCESS \tARRIVAL TIME \tCPU TIME \t WAITING TIME\t TURNAROUND TIME\n");
    for(i=0;i<n;i++){
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d \t\t %d", pname[i],at[i], cput[i], wt[i], tat[i]);
        }
        printf("\nAverage Waiting Time -- %f", awt);
        printf("\nAverage Turnaround Time -- %f\n", atat);
getch();

}
/*SJF
0 10
0 1
3 2
5 1
10 5
awt=4
atat=7.8

4
0 3
1 6
4 4
6 2

fcfs
tat7.25
wt 3.5

srtf
6.25
2.5
*/
