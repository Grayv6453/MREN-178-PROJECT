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

//might add temperature, heart rate, and other symptoms of being a league player
typedef struct {
    int id;
    int tl;
    int statusrn;
}patient;

typedef struct{
    patient patients[MHS];
    int currentpatients;
}daheap;

//initialize the heap
void heapbirth(daheap* heap){
    heap->currentpatients = 0;
}

void swapenis(patient* uno, patient* dos){
    patient temp = *uno;
    *uno = *dos;
    *dos = temp;
}

//insert patient into queue, 
void addtoqueue(daheap* heap, patient CurrPat){
    //BETTER IDEA heap (priority queue)
    //if the heap is full
    if(heap->currentpatients >= MHS){
        printf("step aside bub, too many neighbours in here\n");
        return;
    }

    //add the new patient to the heap
    int currentpeen = heap->currentpatients;
    heap->patients[currentpeen] = CurrPat;
    heap->currentpatients++;

    //do the sorting(saiyan) walk (compare with parent, swap if necessary)
    int daddynumber = (currentpeen - 1)/2;

    while (currentpeen > 0 && (heap->patients[currentpeen]).tl > (heap->patients[daddynumber]).tl){
        swapenis(&heap->patients[currentpeen], &heap->patients[daddynumber]);

        //Move up da tree
        currentpeen = daddynumber;
        daddynumber = (currentpeen - 1)/2;
    }
}

//removing from heap, deletes from the end since that is where a healthy person would end up.
//return id of the patient booted
int getOUT(daheap* heap){
    if(heap->currentpatients <= 0){
        printf("no patients to boot...\n");
        return -1;
    }
    //id of the patient about to get deleted, the one at the very end
    int bootedid = heap->patients[(heap->currentpatients)-1].id;

    //just decrement the size of the array to make that last column unavailable.
    heap->currentpatients--;
    return bootedid;
}


void showmedasauce(daheap* heap){
    //display the current queue
    for(int i = 0; i< heap->currentpatients; i++){
        printf("\nID: %d\ntriage level: %d\ntreatment status: %d\n", heap->patients[i].id, heap->patients[i].tl, heap->patients[i].statusrn);
    }

    //maybe display the waiting times for different triage ranges/levels as well?
}

int main(void){
    for(int i = 0; i<5; i++){
        printf("gg\n");
    }

    printf("nhjgg\n");

    //create the heap and shit
    daheap heap;
    heapbirth(&heap);

    //lowkey forgot that this program should keep running until
    //user is done with (quit function)
    int quit = 0;
    while(quit == 0){

        // get the patient information from a seperate file
        // each one makes a node, and is added to the queue.

        //maybe when a user runs the code, they choose between 
        //entering a new user, or seeing the current queue
        
        int iChoice = 0;
        do {
            printf("Entering a new user (1), viewing queue (2), or quitting program (3) ?.\nEnter '1' or '2' or '3'\n");
            scanf("%d", &iChoice);
            if(iChoice == 1)
            {
                //entering a new user
                patient newpatient;
                printf("Enter ID: ");
                scanf("%d", &newpatient.id);
                printf("\nStatus right now, waiting (0) or being treated (1): ");
                scanf("%d", &newpatient.statusrn);
                printf("\nEnter Triage level: ");
                scanf("%d", &newpatient.tl);
                addtoqueue(&heap, newpatient);
            }
            else if(iChoice == 2){
                //viewing queue
                showmedasauce(&heap);
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