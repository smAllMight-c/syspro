//Shortest Job First(Non-Preemptive) 

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct n
{
    char pname[20];
    int arrivalT, burstT, startT, endT, waitT, tat;
    struct n *next;
} node;

node *head, *last;
int totalwt = 0;
int totaltat = 0;

void create(char pn[20], int at, int bt) //Create nodes accordingly
{
    node *p;
    p = (node *)malloc(sizeof(node));
    strcpy(p->pname, pn);
    p->arrivalT = at;
    p->burstT = bt;
    p->next = NULL;
    if (head == NULL)
    {
        head = p;
    }

    else
    {
        last->next = p;
    }

    last = p;
}

void swap(node *p, node *q)
{ //Function for Swapping the values between 2 pointers
    char tem[20];
    int temp;
    strcpy(tem, p->pname);
    strcpy(p->pname, q->pname);
    strcpy(q->pname, tem);

    temp = p->arrivalT;
    p->arrivalT = q->arrivalT;
    q->arrivalT = temp;

    temp = p->burstT;
    p->burstT = q->burstT;
    q->burstT = temp;
}

void sort() //Sort the given the data according to Shortest job first (Non Preemptive)
{
    node *p, *q;
    int temp;
    int end = 0;
    char tem[20];
    for (p = head; p != NULL; p = p->next) //First sort the data according to Arrival Time using bubble sort
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->arrivalT > q->arrivalT)
            {
                swap(p, q);
            }
        }
    }

    for (p = head; p != NULL; p = p->next) //Now sort the arrival time sorted data according to the burst time
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p == head)
            {
                end = p->burstT; //Take a new variable end and store the value of exit times of all the process combined
            }
            else
            {
                if (q->arrivalT <= end && p->burstT > q->burstT) //You need to compare burst time of two process but only after checking that the arrival time of the second process is less than the combined end time so that a process doesnt get sorted even before it entered the system
                {
                    swap(p, q);
                }
            }
        }
        end = end + p->burstT; //Add the burst times of the process to keep track of exit times
    }
}

void calc() //Calculate Start time ,End Time, Turn around time, Wait time for each process(Common logic for all Scheduling Programs)
{
    node *p, *q;
    for (p = head; p != NULL; p = p->next)
    {
        if (p == head)
        {
            p->startT = p->arrivalT;        //Start time for each process would be its arrival time
            p->endT = p->burstT;            //End time for first process would be its burst time
            p->tat = p->endT - p->arrivalT; //Turn around time = Exit time - arrival time
            p->waitT = p->tat - p->burstT;  // Wait time = Turn around time - Burst time of the process
        }
        for (q = p->next; q != NULL; q = q->next)
        {

            if (q->arrivalT > p->endT)
            {
                q->startT = q->arrivalT;
            }
            else
                q->startT = p->endT;         //Start time of subsequent process would be the end time of previous process
            q->endT = q->startT + q->burstT; //End time would be the Start time + Burst time of the process
            q->tat = q->endT - q->arrivalT;
            q->waitT = q->tat - q->burstT;

            break;
        }
    }
}

void print() //Printing the data in a tabluar form (Common logic for all scheduling programs)
{
    node *p;
    printf("Pname\tArrival\tBurst\tStart\tend\ttat\twait\n");
    for (p = head; p != NULL; p = p->next)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p->pname, p->arrivalT, p->burstT, p->startT, p->endT, p->tat, p->waitT);
        totaltat += p->tat;
        totalwt += p->waitT;
    }
}

void printg() //Printing Gantt Chart(Common logic for all scheduling programs)
{

    node *current, *p = head, *q = head;

    for (current = head; current->next != NULL; current = current->next)
        ;

    printf("Exit Time -\t");
    printf("%d\t\t", p->startT);

    for (int i = 0; i <= current->endT; i++)
    {
        if (i == p->endT)
        {
            printf("%d\t\t", p->endT);
            p = p->next;
        }
    }
    printf("\n");
    printf("Pname\t\t");
    for (int i = 0; i <= current->endT; i++)
    {
        if (i == q->endT)
        {
            printf("\t%s\t", q->pname);
            q = q->next;
        }
    }

    printf("\n");
}

int main()
{
    int n, arrivalT, burstT;
    char pname[20];
    printf("How many process do you want to run ?");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter the process name, Arrival T, Burst T-:\n");
        scanf("%s%d%d", pname, &arrivalT, &burstT);
        create(pname, arrivalT, burstT);
    }

    sort();
    calc();
    print();
    printf("\nAverage Waiting time:%f", (float)totalwt / n);
    printf("\nAverage Turn Around Time:%f\n", (float)totaltat / n);
    printg();
}