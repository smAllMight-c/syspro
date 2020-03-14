#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct n
{
     char pname[20];
     int arrivalT, burstT, priority,exitT;
     struct n *next;

} node;

node *head, *last;

void create(char pn[20], int at, int bt, int pt)
{
     node *p;
     p = (node *)malloc(sizeof(node));
     strcpy(p->pname, pn);
     p->arrivalT = at;
     p->burstT = bt;
     p->priority = pt;
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
void swap(node *s, node *r)
{

     char temp1[20];
     int temp;

     strcpy(temp1, s->pname);
     strcpy(s->pname, r->pname);
     strcpy(r->pname, temp1);

     temp = s->arrivalT;
     s->arrivalT = r->arrivalT;
     r->arrivalT = temp;

     temp = s->burstT;
     s->burstT = r->burstT;
     r->burstT = temp;

     temp = s->priority;
     s->priority = r->priority;
     r->priority = temp;
}

void sort()
{
     int endT = 0, maxAT = 0, end = 0;
     ;
     node *p, *q;

     for (p = head; p != NULL; p = p->next)
     {
          for (q = p->next; q != NULL; q = q->next)
          {
               if (p->arrivalT > q->arrivalT)
               {
                    swap(p, q);
               }
          }
          if (p->arrivalT >= maxAT)
          {
               maxAT = p->arrivalT;
          }
          
     }

     for(p=head ; p!=NULL;p=p->next) {
          for(q=p->next;q!=NULL;q=q->next) {
               if(end >= maxAT && p->priority < q->priority) {
                    swap(p,q);
               } 
               else {
                    for(int i =p->arrivalT;i<=(p->arrivalT + p->burstT) ; i++) {
                         if(i - (p->arrivalT + p->burstT) == 0) {
                              break;
                         }
                         else if(i == q->arrivalT && p->priority < q->priority)  {
                              create(p->pname,0,0,p->priority);
                              p->burstT=i - p->arrivalT;
                              swap(p->next,q);
                              break;
                         }
                    }
               }
          }
          end = end + p->burstT;
          p->exitT = end;
     }
}


void calc()
{
    int at[20], bt[20], et[20], wt[20], tat[20],pr[20], n = 0, breaker = 0;
    char pname[20][20];

    node *p, *q;

    for (p = head; p != NULL; p = p->next, breaker = 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(pname[i], p->pname) == 0)
            {
                breaker = 1;
            }
        }

        if (breaker == 0)
        {
            strcpy(pname[n], p->pname);
            at[n] = p->arrivalT;
            bt[n] = p->burstT;
            et[n] = p->exitT;
            pr[n]=p->priority;
            for (q = p->next; q != NULL; q = q->next)
            {
                if (strcmp(p->pname, q->pname) == 0)
                {
                    if (q->exitT > p->exitT)
                    {
                        et[n] = q->exitT;
                    }
                    bt[n] = bt[n] + q->burstT;
                }
            }
            tat[n] = et[n] - at[n];
            wt[n] = tat[n] - bt[n];
            printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", pname[n], at[n], bt[n],pr[n], et[n], tat[n], wt[n]);
            n++;
        }
    }
}




void print()
{

    node *current, *p = head, *q = head;

    for (current = head; current->next != NULL; current = current->next)
        ;

    printf("Exit Times -\t");
    printf("%d\t\t", p->arrivalT);

    for (int i = 0; i <= current->exitT; i++)
    {
        if (i == p->exitT)
        {

            printf("%d\t\t", p->exitT);
            p = p->next;
        }
    }
    printf("\n");
    printf("Pname\t\t");
    for (int i = 0; i <= current->exitT; i++)
    {
        if (i == q->exitT)
        {

            printf("\t%s\t", q->pname);
            q = q->next;
        }
    }

    printf("\n");
}

int main(void)
{

     int n, arrivalT, burstT, priority;
     char pname[20];

     printf("Enter the number of processes-:\n");
     scanf("%d", &n);

     for (int i = 0; i < n; i++)
     {
          printf("Enter the Process name ,Arrival Time, Burst Time, Priority(Highest is 1 and lowest is 5)\n");
          scanf("%s%d%d%d", pname, &arrivalT, &burstT, &priority);
          create(pname, arrivalT, burstT, priority);
     }

     sort();
     calc();
     print();
}
