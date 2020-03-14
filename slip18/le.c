#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{ //Structure
    char *line;
    struct node *next;
} node;
node *current = NULL, *head = NULL;

void create(char *line)
{ //Create individual nodes
    node *temp = malloc(sizeof(node));
    temp->line = malloc(strlen(line) + 1);
    strcpy(temp->line, line);
    temp->next = NULL;
    if (head == NULL)
        current = head = temp; //First node

    else
        current = current->next = temp; //all others
}

void write(char *fname)
{ //Basically a save function rewrites the whole file regardless of where changes were made
    FILE *fp;
    node *temp;
    fp = fopen(fname, "w"); // has to be opened in "w"mode only doesnt work in "rw"mode
    temp = head;
    while (temp != NULL)
    {
        fputs(temp->line, fp);
        temp = temp->next;
    }
    fclose(fp);
}

void print()
{ // have to create a new pointer otherwise error would occur on multiple runs of the program
    node *display;
    int i=1;
    for (display = head; display!=NULL; display = display->next,i++)
        printf("Line %d is %s\n",i, display->line);
}

void delete (int position) {
    if (head == NULL) 
      return; 
  
  node *temp=head; 
  
    if (position == 1) 
    { 
        head = temp->next;   // Change head 
        free(temp);               
        return; 
    } 
    for(int i=1; temp!=NULL && i<position-1; i++) 
         temp = temp->next; 
  
      if (temp == NULL || temp->next == NULL) // If position is more than number of ndoes
         return; 
  
    node *next = temp->next->next; 
    free(temp->next);  // Free memory 
    temp->next=next; 
}
void move(int move1,int move2) {
    node *temp=head,*temp1=head;  //2 pointer both starting at head

    for(int i=1;i< move1 && temp;i++)  //move pointer 1 to the node to be moved
        temp=temp->next;

    node *new = malloc(sizeof(node));  //create a new node
    new->line = malloc(strlen(temp->line)+1);
    strcpy(new->line,temp->line);
    new->next=NULL;
    if(move2==1) {   //if the node is to be moved to the first place
        new->next=temp1;  //link the new node to head
        head = new;        // make the new nde head
        return;
    }
    for(int i=1;i< move2 -1 && temp1;i++) { //else move the pointer just before the place to be moved
        temp1=temp1->next;
        if(temp1->next==NULL) {  //if the pointer reaches last position
            temp1->next=new;    //simply make the new node last
            return;
        }
    }
    new->next=temp1->next;  // if inbetween then the next of new pointer is the next of 2nd pointer
    temp1->next=new;  //point the next of 2nd pointer towards new
}

int main(int argc, char *argv[])
{
    char fileName[10];
    char choice[3];
    int m1,m2;
    if (argc < 2)
    { // Check if command line argument is provided else accept the file name
        printf("%d", argc);
        printf("Enter the file name\n");
        scanf("%s", fileName);
    }
    else
        strcpy(fileName, argv[1]);
    char line[300];
    FILE *fp;
    fp = fopen(fileName, "rw");

    while (fgets(line, sizeof(line), fp))
    {
        create(line);
    }
    fclose(fp);

    do
    { //For Choices
        printf("a : Append\np : Print all lines\ns : Save\ne : Exit\n\nm : Move\n$");
        scanf("%s", choice);
        switch (choice[0]) //Cases
        {
        case 'a':
            fp = fopen(fileName, "a");
            printf("Enter the data (Type ; to end)\n");
            getchar(); //rectifying scanf bug as a newline character is still in the input buffer
            scanf("%[^;]s", line); // Scan until ; occurs
            create(line);          //Send to create
            fclose(fp);
            break;
        case 'p':
            print();
            break;
         case 's':
            write(fileName);
            break;
        case 'd':
            printf("Enter the line to deleted");
            int n;
            scanf("%d", &n);
            delete (n);
            break;
        case 'm':   
            printf("Enter which line to move and where?\n");
            scanf("%d%d",&m1,&m2);
            move(m1,m2);
            if(m2<m1) 
            delete(m1+1);
            else
            delete(m1);
            break;
        case 'c' : 
            printf("Enter which line to copy and where?\n");
            scanf("%d%d",&m1,&m2);
            move(m1,m2); //Copy is nothing but move function without deleteing
            break;
        case 'i' : 
            printf("Where to insert?");
            scanf(" %d",&m1);
            printf("Enter the data (Type ; to end)\n");
            getchar();
            scanf("%[^;]s", line);
            insert(m1,line);
            break;
        default:
            break;
        }
    } while (strcmp(choice, "e") != 0);
}
