#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//max resource the hospital can distribute
#define MAX_SOMETHINGS 1000;

enum triagelevel{
    Epstein,
    Aids,
    Tyrese,
    Jew,
    Flopping
};

typedef struct patient{
    int id;
    enum triagelevel tl;
};


void addtoqueue(void){
    //adding a user to the queue

    //IDEA we keep track of the rear for each section,
    //maybe then we could use a circular queue (if we have it 
    //at a set size due to set amount of "resources" in the big H)

    //ANOTHER IDEA we could have mutliple circular queues, one for each
    //triage level. This way would make inserting easier and keep track
    //of number of patients in each triage. prob takes more storage,
    //and deleting and/or displaying queue might get a little weird tho


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