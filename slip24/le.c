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

void insert(int num,char *line) {
     node *temp=head;               //new node
    node *new = malloc(sizeof(node));
    new->line = malloc(strlen(line)+1);
    strcpy(new->line,line);
    new->next=NULL;
    if(num==1) {                //if to be inserted at first position
            new->next=temp->next;
            head = new;
            return;
        }
    for(int i=1;i<num-1 && temp ;i++) { //else go to just before where to be placed
        
        if(temp->next==NULL) { //if pointer reaches last position then make the new node last
            temp->next=new;
            return;
        }
        temp=temp->next;

    }
    new->next=temp->next;
    temp->next=new;

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
        printf("p : Print all lines\ns : Save\ne : Exit\nd : Delete\ni : Insert\n$");
        scanf("%s", choice);
        switch (choice[0]) //Cases
        {
        
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
