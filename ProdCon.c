#include<stdio.h>
#include<stdlib.h>

int mutex=1,full=0,empty=3,x=0;
void producer();
void consumer();
int wait(int);
int signal(int);
int main()
{
	int n;
	printf("\n 1.Producer\n 2.Consumer\n");
	while(1)
	{
    	printf("\nEnter your choice");
    	scanf("%d",&n);
    	switch(n)
		{
    		case 1: if((mutex==1)&&(empty==0))
            			printf("Buffer is full");
            		else
                		producer();
            		break;
    		case 2: if((mutex==1)&&(full!=0))
            			consumer();
        			else
            			printf("Buffer is empty");
        			break;
    		case 3: exit(0);
            		break;
    	}
	}
	return 0;
}

int wait(int s)
{
	return(--s);
}

int signal(int s)
{
	return(++s);
}

void producer()
{
    mutex=wait(mutex);
    full=signal(full);
    empty=wait(empty);
    x++;
    printf("\nProducer produces the item %d",x);
    mutex=signal(mutex);
}

void consumer()
{
	mutex=wait(mutex);
	full=wait(full);
	empty=signal(empty);
	printf("\nConsumer consumes item %d",x);
	x--;
	mutex=signal(mutex);
}
