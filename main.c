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
#define DOC_TBL_SIZE 23

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

typedef struct {
    int patient_id;
    int bed_num;
} bed;

typedef struct {
    int doctor_id;
    int patient_id;
    struct doctor* next; // for hash table chaining
} doctor;

typedef struct {
    doctor* arr[TOTAL_DOCTORS];
    int front;
    int rear;
} doc_queue;

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

doc_queue* init_doc_queue() {
    doc_queue* q = (doc_queue*)malloc(sizeof(doc_queue));
    if (q == NULL) {
        return NULL;
    }
    q->front = 0;
    q->rear = -1;
    for (int i = 0; i < TOTAL_DOCTORS; i++) {
        q->arr[i] = NULL;
    }
    return q;
}

bool q_enqueue(doc_queue* q, doctor* new_doc) {
    if (q->rear == TOTAL_DOCTORS - 1) {
        return false; // Queue is full
    }
    q->arr[++q->rear] = new_doc;
    return true;
}

// Dequeues a doctor from queue and stores in the double pointer doc.
// Returns true if successful, else false.
bool q_dequeue(doc_queue* q, doctor** doc) {
    if (q->front > q->rear) {
        return false; // Queue is empty
    }
    *doc = q->arr[q->front++];
    return true;
}

bool q_is_empty(doc_queue* q) {
    return q->front > q->rear || q->front == -1;
}

int hash (int id, int table_size){
    return id % table_size;
}

bool doc_table_insert(doctor* doc_table, int size, doctor* new_doc) {
    if (doc_table == NULL || new_doc == NULL) {
        return false; // Invalid input
    }
    int index = hash(new_doc->doctor_id, size);
    // Chain the new doctor to the head of the list at the hashed index
    doctor* head = &doc_table[index];

    if (head->doctor_id == -1) {
        *head = *new_doc;
        head->next = NULL;
    } else {
        new_doc->next = head->next; 
        head->next = new_doc; 
    }
    return true;
}

doctor* doc_table_search(doctor* doc_table, int size, int doctor_id) {
    if (doc_table == NULL) {
        return NULL; 
    }
    
    int index = hash(doctor_id, size);
    doctor* current = &doc_table[index];
    while (current != NULL) {
        if (current->doctor_id == doctor_id) {
            return current; 
        }
        current = current->next; 
    }

    // If no doctor found
    return NULL; 
}

doctor *doc_table_pop(doctor* doc_table, int size, int doctor_id) {
    int index = hash(doctor_id, size);
    doctor* current = &doc_table[index];
    doctor* prev = NULL;
    while (current != NULL && current->doctor_id != doctor_id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return NULL;
    if (prev == NULL) {
        // If prev == NULL, we are at the head of chain.
        if (current->next == NULL) {
            // current is the only node in the chain
            current->doctor_id = -1; // Mark as empty
            current->patient_id = -1;
        } else {
            // Move node after current up
            doctor* temp = current->next; // TODO: idk if this is correct
            doc_table[index].doctor_id = temp->doctor_id;
            doc_table[index].patient_id = temp->patient_id;
            doc_table[index].next = temp->next;
        }
    } else {
        prev->next = current->next;
    }
    return current;
}

doctor* init_doc_table (int size) {
    doctor* doc_table = (doctor*)malloc(size * sizeof(doctor));
    for (int i = 0; i < size; i++) {
        doc_table[i].doctor_id = -1;
        doc_table[i].patient_id = -1;
        doc_table[i].next = NULL;
    }
    return doc_table;
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
        
        int iChoice = 5;
        do {
            printf("Entering a new user (1), viewing queue (2), or quitting program (3) ?.\nEnter '1' or '2' or '3'\n");
            if (scanf("%d", &iChoice) != 1) {
                // If scanf didn't return 1, the input was invalid.
                printf("Invalid input! Please enter a number.\n");

                //NOTE to TA: I had to google how to clear the bad input from the buffer
                // Clear the bad input from the buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
                
                iChoice = -1; // Force the loop to restart safely
            }
            else{
                if(iChoice == 1){
                //entering a new user

                //IDEA from EthpSTEIN and Jdiddy
                //prompt user if they want to make a singular entry (1patient), or a file with multiple patients 
                patient newpatient;
                printf("Enter ID: ");
                //if invalid ID is entered
                if(scanf("%d", &newpatient.id) != 1){
                    newpatient.id = -1;
                    // Clear the bad input from the buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                }
                printf("\nStatus right now, waiting (0) or being treated (1): ");
                //if invalid status is entered
                if(scanf("%d", &newpatient.statusrn) != 1){
                    newpatient.statusrn = -1;
                    // Clear the bad input from the buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                }
                printf("\nEnter Triage level: ");
                //if invalid triage level is entered
                if(scanf("%d", &newpatient.tl) != 1){
                    newpatient.tl = -1;
                    // Clear the bad input from the buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                }
                //if any of the inputs were invalid, don't add it the the heap
                if(newpatient.id == -1 || newpatient.statusrn == -1 || newpatient.tl == -1){
                    printf("Error in input, patient not added to queue.");
                }
                else{
                    addtoqueue(&heap, newpatient);
                    //now check if the patient at the end of the queue is healthy
                    if(heap.patients[heap.currentpatients - 1].tl == 0){
                        getOUT(&heap);
                        printf("patient was healthy, loading the slingshot...\nComplete, ejecting!\n");
                    }
                }
                
                }
                else if(iChoice == 2){
                    //viewing queue
                    showmedasauce(&heap);
                }
                else if(iChoice == 3){
                    //quitting
                    quit = 1;
                    //so can leave the input loop
                    iChoice = -1;
                    printf("Quitting... cya later ni!");
                }
                else{
                //error
                    printf("Error, try again.\n");
                }
            }
        }while (iChoice > 0 && iChoice < 4);
    }   
    return 0;
}