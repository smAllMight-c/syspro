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
        printf("a : Append\np : Print all lines\ns : Save\ne : Exit\n$");
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
        
            break;
        default:
            break;
        }
    } while (strcmp(choice, "e") != 0);
}
