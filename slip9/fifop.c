#include<stdio.h>

int hits = 0, miss = 0, p = 0;     //Globally declared so make it easier



void print(int frame_size, int frame[]) {      //Print Function for the frame
  for (int i = 0; i < frame_size; i++) {
    if (frame[i] == -1) {
      printf(" -");                            //If the frame is empty just print "-"
    } else
      printf(" %d", frame[i]);                   //else just print the frame value
  }
  printf("\n");
}



void add(int frame_size, int frame[], int reference) {  //add the user input
  int allocated = 0;
  for (int i = 0; i < frame_size; i++) {
    if (frame[i] == reference) {                       //If the input is the same as something in the frame increment hit counter and print the message
      hits++;
      printf(" Hit for %d ", reference);
      allocated = 1;
      break;
    } else
    if (frame[i] == -1) {                       //If the frame is empty increment fault counter and add the input to frame
      miss++;
      printf("Fault for %d ", reference);
      frame[i] = reference;
      allocated = 1;
      break;
    }
  }
  if (allocated == 0) {                                //If the frame is not empty and the input doesnt match anything in the frame incremment fault counter and insert it into the frame
    frame[p] = reference;
    p = (p + 1) % frame_size;                     //Increment p's value and mod it with frame size to know which frame to insert the value in
    miss++;
    printf("Fault for %d ", reference);

  }
  print(frame_size, frame);                  //Print the current frame

}

int main() {
  int frame_size, r;
  printf("Enter the frame size\n");          
  scanf("%d", & frame_size);
  int frame[frame_size];
  int referenceNumber;
  printf("Enter the number of references\n");
  scanf("%d", & referenceNumber);
  int references[referenceNumber];
  for (int i = 0; i < frame_size; i++) {          //Make all the frame values to default -1 just to indicate that it is empty
    frame[i] = -1;
  }
  print(frame_size, frame);
  for (int i = 0; i < referenceNumber; i++) {          //Scan an input from the user and add it to the frame
    scanf("%d", & r);
    add(frame_size, frame, r);

  }
  printf("The number of hits are %d and the number of faults are %d\n", hits, miss);

}