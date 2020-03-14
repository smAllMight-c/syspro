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


void swap (node *p,node *q) {
    int temp;
    char tem[20];

    strcpy(tem,p->pname);
    strcpy(p->pname,q->pname);
    strcpy(q->pname,tem);

    temp= p->arrivalT;
    p->arrivalT=q->arrivalT;
    q->arrivalT=temp;

    temp=p->burstT;
    p->burstT=q->burstT;
    q->burstT=temp;

}

void sort () {
     node *p,*q;
     int end=0;
     for(p=head;p!=NULL;p=p->next) { //Sort according to arrival time
          for(q=p->next;q!=NULL;q=q->next) {
               if(p->arrivalT > q->arrivalT) {
               swap(p,q);
          
          }
    
}
end = end + p->burstT;
}
      for(p=head;p!=NULL;p=p->next) {
          for(q=p->next;q!=NULL;q=q->next) {
               if(p->burstT > q->burstT && p!=head){
               swap(p,q);
               }
               else {
                    for(int i=p->arrivalT ;i < p->burstT ; i++) { 
                         if(i == q->arrivalT && ((p->burstT)-i) > q->burstT) {
                              end= end-((p->burstT)-i);
                             create(p->pname,end,((p->burstT)-i));
                             p->burstT=i;
                              
                         } 
                    
                    }
                    }
                    }
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

                q->startT = p->endT;         //Start time of subsequent process would be the end time of previous process
            q->endT = q->startT + q->burstT; //End time would be the Start time + Burst time of the process
            q->tat = q->endT - q->arrivalT;
            q->waitT = q->tat - q->burstT;

            break;
        }
    }
}
          
void print() {
     node *p;
     for(p=head;p!=NULL;p=p->next) {
          printf("%s\t%d\t%d\t%d\t%d\n",p->pname,p->arrivalT,p->burstT,p->startT,p->endT);
          }
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
    //printf("\nAverage Waiting time:%f", (float)totalwt / n);
   // printf("\nAverage Turn Around Time:%f\n", (float)totaltat / n);
   // printg();
}
