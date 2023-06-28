#include <stdio.h>
#include<stdlib.h>
struct matrix
{
    int n;
    int pid[10];
    int prio[10];
    int at[10];
    int bt[10];
    int tat[10];
    int wt[10];
    int ct[10];
    int btb[10];

}matrix;
void preemptivesrtf(struct matrix);
void prioritypreemptive(struct matrix);
void sjfnonpreemptive(struct matrix);
void prioritynonpreemptive(struct matrix);
int clk=0,min,cmin,cnt,k,exe,st=0,sw=0,i,j,ch;
float n1,avgt,avgw;
int main()
{
   struct matrix srtf;
    printf("Enter no of processes \n");
   scanf("%d",&srtf.n);
   printf("Enter in increasing order of AT \n");
   for(i=1;i<=srtf.n;i++){
    printf("\nEnter %d process no:",i);
    scanf("%d",&srtf.pid[i]);
    printf("\nEnter %d arrival time:",i);
    scanf("%d",&srtf.at[i]);
    printf("\nEnter %d burst time :",i);
    scanf("%d",&srtf.bt[i]);
    printf("\nEnter %d priority:",i);
    scanf("%d",&srtf.prio[i]);

}
for(i=1;i<=srtf.n;i++){
        srtf.btb[i]=srtf.bt[i];
    }
 printf("\n 1.S J F \n2. pre emptive sjf \n 3.priority premptive 4. \n priority non pre emtive \n");
 printf("Enter your choice:");
 scanf("%d",&ch);
 switch(ch)
 {
 case 1:
 		sjfnonpreemptive(srtf);
		 break;
 case 2:
 		preemptivesrtf(srtf);
		 break;
 case 3:
 		prioritypreemptive(srtf);
  		break;
 case 4:
    	prioritynonpreemptive(srtf);
		break;
case 5: exit(0); 
		break;
default:
printf("invalid choice");
 }
 return 0;
}

void preemptivesrtf(struct matrix m){

    while(1)
	{
        if(clk<m.at[m.n])
		{
        for(j=1;j<=m.n;j++)
		{
            if(m.at[j]<=clk)
			{
                continue;
            }
            else
			{
                k=j;
                break;
            }
        }
        }
        else{
            k=-1;
        }
        cmin=0;cnt=0;min=9999;
        for(i=1;i<=m.n;i++){
            if(m.at[i]<=clk && m.bt[i]>0){
            if(m.bt[i]<min){
                cmin=i;
                min=m.bt[i];
                cnt++;
            }
            }
        }

        if(cnt>0 && k!=-1)
		{
        if(m.bt[cmin]<=(m.at[k]-clk)){
           exe=m.bt[cmin];
           printf(" process %d starts %d for %d time units \n",m.pid[cmin],m.at[cmin],exe);
           clk=clk+m.bt[cmin];
           m.bt[cmin]=0;
           m.ct[cmin]=clk;
        }

        else{
          exe=m.at[k]-clk;
          clk=clk+exe;
          m.bt[cmin]-=exe;
          m.ct[cmin]=clk;
          printf("process %d starts %d for %d time units \n\n",m.pid[cmin],m.at[cmin],exe);
        }
        }

        else if(cnt>0 && k==-1){
            exe=m.bt[cmin];
        printf("process %d starts %d for %d time units \n\n",m.pid[cmin],m.at[cmin],exe);
           clk=clk+m.bt[cmin];
           m.bt[cmin]=0;
           m.ct[cmin]=clk;
        }

        else{
            break;
        }

    }

    for(i=1;i<=m.n;i++){
        m.tat[i]=m.ct[i]-m.at[i];
        m.wt[i]=m.tat[i]-m.btb[i];
    }
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for(i=1;i<=m.n;i++){
    st+=m.tat[i];
    sw+=m.wt[i];
    printf("%d\t%d\t\t%d\n", m.pid[i], m.tat[i], m.wt[i]);
    }

    n1=m.n;
    avgt=st/n1;
    avgw=sw/n1;
    printf("Avg TAT= %f \n",avgt);
    printf("Avg WT= %f \n ",avgw);

}

void prioritypreemptive(struct matrix m)
{
    while(1)
	{
       if(clk<m.at[m.n])
	   {
        for(j=1;j<=m.n;j++)
		{
            if(m.at[j]<=clk)
			{
                continue;
            }
            else
			{
                k=j;
                break;
            }
        }
    	}
        else
		{
            k=-1;
        }

        cmin=0;
		cnt=0;
		min=9999;
        for(i=1;i<=m.n;i++)
		{
            if(m.at[i]<=clk && m.bt[i]>0)
			{
            if(m.prio[i]<min)
			{
                cmin=i;
                min=m.prio[i];
                cnt++;
            }
            }
        }

        if(cnt>0 && k!=-1)
		{
        if(m.bt[cmin]<=(m.at[k]-clk))
		{
           exe=m.bt[cmin];
           printf("Executed process %d with AT %d for BT %d \n",m.pid[cmin],m.at[cmin],exe);
           clk=clk+m.bt[cmin];
           m.bt[cmin]=0;
           m.ct[cmin]=clk;
        }

        else
		{
          exe=m.at[k]-clk;
          clk=clk+exe;
          m.bt[cmin]-=exe;
          m.ct[cmin]=clk;
          printf("Executed process %d with AT %d for BT %d \n",m.pid[cmin],m.at[cmin],exe);
        }
        }

        else if(cnt>0 && k==-1)
		{
            exe=m.bt[cmin];
        	printf("Executed process %d with AT %d for BT %d \n",m.pid[cmin],m.at[cmin],exe);
            clk=clk+m.bt[cmin];
            m.bt[cmin]=0;
            m.ct[cmin]=clk;
        }

        else
		{
            break;
        }
    }
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for(i=1;i<=m.n;i++){
        m.tat[i]=m.ct[i]-m.at[i];
        m.wt[i]=m.tat[i]-m.btb[i];
        printf("%d\t%d\t\t%d\n", m.pid[i], m.tat[i], m.wt[i]);
    }
    for(i=1;i<=m.n;i++){
    st+=m.tat[i];
    sw+=m.wt[i];
    }
    n1=m.n;
    avgt=st/n1;
    avgw=sw/n1;
    printf("Avg TAT for Priority preemptive= %f \n",avgt);
    printf("Avg WT for Priority preemptive= %f \n ",avgw);

}

void sjfnonpreemptive(struct matrix m){
    while(1){
        cmin=0;cnt=0;min=9999;
        for(i=1;i<=m.n;i++)
		{
            if(m.at[i]<=clk && m.bt[i]>0)
			{
            if(m.bt[i]<min)
			{
                cmin=i;
                min=m.bt[i];
                cnt++;
            }
            }
        }

        if(cnt>0){ 
            exe=m.bt[cmin];
            clk=clk+m.bt[cmin];
            m.bt[cmin]=0;
            m.ct[cmin]=clk;
            printf("Executed process %d with AT %d for BT %d \n",m.pid[cmin],m.at[cmin],exe);
        }
        else{
            break;
        }

}
 printf("Process\tTurnaround Time\tWaiting Time\n");
 for(i=1;i<=m.n;i++){
        m.tat[i]=m.ct[i]-m.at[i];
        m.wt[i]=m.tat[i]-m.btb[i];
        printf("%d\t%d\t\t%d\n", m.pid[i], m.tat[i], m.wt[i]);
    }
    for(i=1;i<=m.n;i++){
    st+=m.tat[i];
    sw+=m.wt[i];
    }
    n1=m.n;
    avgt=st/n1;
    avgw=sw/n1;
    printf("Avg TAT for SJF non-preemptive= %f \n",avgt);
    printf("Avg WT for SJF non-preemptive= %f \n ",avgw);


}

void prioritynonpreemptive(struct matrix m){
    while(1){
    cmin=0;cnt=0;min=9999;
    for(i=1;i<=m.n;i++){
            if(m.at[i]<=clk && m.bt[i]>0){ 
            if(m.prio[i]<min){
                cmin=i;
                min=m.prio[i];
                cnt++;
            }
            }
        }

     if(cnt>0){ 
            exe=m.bt[cmin];
            clk=clk+m.bt[cmin];
            m.bt[cmin]=0;
            m.ct[cmin]=clk;
            printf("Executed process %d with AT %d for BT %d \n",m.pid[cmin],m.at[cmin],exe);
        }
        else{ 
            break;
        }
}
 printf("Process\tTurnaround Time\tWaiting Time\n");
for(i=1;i<=m.n;i++){
        m.tat[i]=m.ct[i]-m.at[i];
        m.wt[i]=m.tat[i]-m.btb[i];
        printf("%d\t%d\t\t%d\n", m.pid[i], m.tat[i], m.wt[i]);
    }
    for(i=1;i<=m.n;i++){
    st+=m.tat[i];
    sw+=m.wt[i];
    }
    n1=m.n;
    avgt=st/n1;
    avgw=sw/n1;
    printf("Avg TAT for Priority non-preemptive= %f \n",avgt);
    printf("Avg WT for Priority non-preemptive= %f \n ",avgw);

}
