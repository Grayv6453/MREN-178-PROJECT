#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(void){
    for(int i = 0; i<5; i++){
        printf("gg\n");
    }

    printf("nhjgg\n");

    // get the patient information from a seperate file
    // each one makes a node, and is added to the queue.

    //maybe when a user runs the code, they choose between 
    //entering a new user, or seeing the current queu

    printf("Entering a new user (1), or view queue (2).\nEnter 1 or 2\n");
    int iChoice;
    scanf("%d", &iChoice);
    if(iChoice == 1)
    {
        //entering a new user
    }
    else if(iChoice == 2){
        //viewing queue
    }
    else{
        //error
    }

    return 0;
}