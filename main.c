#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Heap
//Patient added, inserted based on priority to heap

//have a hash table with a limited number of beds, doctors, and resources
//Starting at root, assign resources from hash table (remove them from table temporarily)
//based on severity of root, then move to next node in the heap

//max resource the hospital can distribute
#define MAX_BEDS 1000
#define TOTAL_DOCTORS 100
#define TOTAL_CLANKERS 500

//Max Heap Size my n
#define MHS 2000


enum triagelevel{
    Epstein,
    Aids,
    Tyrese,
    Jew,
    Flopping
};

enum status{
    waiting,
    beingtreated
};

//might add temperature, heart rate, and other symptoms of being a league player
typedef struct patient{
    int id;
    enum triagelevel tl;
    enum status statusrn;
};

typedef struct{
    struct patient patients[MHS];
    int currentpatients
}daheap;



//insert patient into queue, 
void addtoqueue(void){
    //BETTER IDEA heap (priority queue)


}

void showmedasauce(void){
    //display the current queue
}

int main(void){
    for(int i = 0; i<5; i++){
        printf("gg\n");
    }

    printf("nhjgg\n");

    //lowkey forgot that this program should keep running until
    //user is done with (quit function)
    int quit = 0;
    while(quit == 0){

        // get the patient information from a seperate file
        // each one makes a node, and is added to the queue.

        //maybe when a user runs the code, they choose between 
        //entering a new user, or seeing the current queue
        
        int iChoice;
        do {
            printf("Entering a new user (1), viewing queue (2), or quitting program (3) ?.\nEnter 1 or 2 or 3\n");
            scanf("%d", &iChoice);
            if(iChoice == 1)
            {
                //entering a new user
                addtoqueue;

            }
            else if(iChoice == 2){
                //viewing queue
                showmedasauce;
            }
            else if(iChoice == 3){
                //quitting
                quit = 1;
                printf("Quitting... cya later ni!");
            }
            else{
            //error
                printf("Error, try again.\n");
            }
        }while (iChoice > -1 && iChoice < 4);
    }   
    return 0;
}