#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Heap
//Patient added, inserted based on priority to heap

//Starting at root, remove patient from heap and assign doctor in hash table

//max resource the hospital can distribute
#define MAX_BEDS 1000
#define TOTAL_DOCTORS 100
#define TOTAL_CLANKERS 500
#define DOC_TBL_SIZE 23

//Max Heap Size (only so many people can be waiting in line)
#define MHS 2000

//might add temperature, heart rate, and other symptoms of being a league player
typedef struct {
    int id;
    int tl;
}patient;

typedef struct{
    patient patients[MHS];
    int currentpatients;
}daheap;

typedef struct {
    int patient_id;
    int bed_num;
} bed;

typedef struct doctor{
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

void swapih(patient* uno, patient* dos){
    patient temp = *uno;
    *uno = *dos;
    *dos = temp;
}



// The bubble-down process
void heapify(daheap* heap, int index, int *finalposi) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Check if the left child exists and is greater than the current node
    if (leftChild < heap->currentpatients && heap->patients[leftChild].tl > heap->patients[largest].tl){
        largest = leftChild;
    }

    // Check if the right child exists and is greater than the largest so far
    if (rightChild < heap->currentpatients && heap->patients[rightChild].tl > heap->patients[largest].tl) {
        largest = rightChild;
    }
    // If the largest is not the current node, swap and continue heapifying
    if (largest != index) {
        swapih(&heap->patients[index], &heap->patients[largest]);
        heapify(heap, largest, finalposi);
    }
    else{
        *finalposi = largest;
    }
}

// bubble up process used in the update function "updih"
//takes heap and position of the item being updated
void shutthebubbleup(daheap* heap, int index, int *finalposi) {
    int daddynumber = (index - 1) / 2;

    // While not at root, and current node is greater than its parent
    while (index > 0 && heap->patients[index].tl > heap->patients[daddynumber].tl) {
        swapih(&heap->patients[index], &heap->patients[daddynumber]);
        
        // Move up
        index = daddynumber;
        daddynumber = (index - 1) / 2;
    }

    *finalposi = index;
}

//add patient to heap 
void addtoqueue(daheap* heap, patient CurrPat, int *finalposi){
    //if the heap is full (limit to how many people can be added to the waiting list)
    //only so many people can be in the waiting line
    if(heap->currentpatients >= MHS){
        printf("step aside bub, too many bums in here\n");
        return;
    }

    //add the new patient to the heap
    int fellas = heap->currentpatients;
    heap->patients[fellas] = CurrPat;
    heap->currentpatients++;

    shutthebubbleup(heap, fellas, finalposi);
}

//removing from heap, deletes from root
// returns 1 if it deletes, -1 if fails
//updates the patient booty to be the patient removed from the heap
int getOUT(daheap* heap, patient* booty){
    if(heap->currentpatients <= 0){
        printf("no patients to boot...\n");
        return -1;
    }
    //id of the patient about to get deleted, the one at the very end
    *booty = heap->patients[0];
    heap->currentpatients--;

    //bubble down from root
    int filler = 0;
    heapify(heap, 0, &filler);
    return 1;
}

// Searches for a patient by ID. Returns their index if found, or -1 if not found.
int findoldhead(daheap* heap, int updatedIDih){
    for (int i = 0; i < heap->currentpatients; i++) {
        if (heap->patients[i].id == updatedIDih) {
            //found that matafaka
            return i;
        }
    }
    return -1; // Not in the system
}

//resort the heap function(heapify but if the item is in the middle of the heap)
void updih(daheap* heap, int index, int newaidslevel, int *finalposi) {
    int oldaidslevel = heap->patients[index].tl;
    
    // Update the values
    heap->patients[index].tl = newaidslevel;

    // If their priority went up (they dying harder), bubble up
    if (newaidslevel > oldaidslevel) {
        shutthebubbleup(heap, index, finalposi);
    } 
    // If their priority went down (they're somehow doing better?), bubble down
    else if (newaidslevel < oldaidslevel) {
        
        heapify(heap, index, finalposi);
    }
    //if priority didn't change (shouldn't be possible to reach this funciton then, but jsut in case)
    else{
        *finalposi = index;
    }
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
        return false; 
    }
    q->arr[++q->rear] = new_doc;
    return true;
}

// Dequeues doctor from q and stores in double-pointer doc
// Returns true if successful, else false
bool q_dequeue(doc_queue* q, doctor** doc) {
    // If queue is full, return false
    if (q->front > q->rear) {
        return false;
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
            current->doctor_id = -1; // mark doctor a1s empty
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
    if (doc_table == NULL) {
        return NULL; 
    }
    for (int i = 0; i < size; i++) {
        doc_table[i].doctor_id = -1;
        doc_table[i].patient_id = -1;
        doc_table[i].next = NULL;
    }
    return doc_table;
}

int main(void){
    //create the heap type stuff
    daheap heap;
    heapbirth(&heap);

    //lowkey forgot that this program should keep running until
    //user is done with it 
    int quit = 0;
    while(quit == 0){

        // get the patient information from a seperate file
        // each one makes a node, and is added to the queue.

        //when a user runs the code, they choose between 
        //entering a new user, discharging, viewing list, or quitting
        
        int iChoice = -1;
        do {
            printf("Entering a new user (1), discharging patient (2), view waiting list (3), or quitting program (4) ?.\nEnter '1', '2', '3', or '4'\n");
            if (scanf("%d", &iChoice) != 1) {
                // If scanf didn't return 1, the input was invalid.
                printf("Invalid input! Please enter a number.\n");

                // Clear the bad input from the buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
                
                //you alr know we loopin' again yung blud
                iChoice = -1;
            }
            else{
                if(iChoice == 1){
                    //entering a new user
                    //Idea for later (prob won't implement)
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
                    printf("\nEnter Triage level: ");
                    //if invalid triage level is entered
                    if(scanf("%d", &newpatient.tl) != 1){
                        newpatient.tl = -1;
                        // Clear the bad input from the buffer
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                    }
                    //if any of the inputs were invalid, don't add it the the heap
                    if(newpatient.id == -1 || newpatient.tl == -1){
                        printf("\nError in input, patient not added to queue.\n");
                    }
                    else{
                        int finalposi = 0;
                        //return position of dupe, if not found (it's a unique id) return -1
                        int oldheadposi = findoldhead(&heap, newpatient.id);
                        //if patient is already in waiting list, update position according to most recent status
                        if(oldheadposi != -1){
                            //update the queue using position of existing id
                            updih(&heap, oldheadposi, newpatient.tl, &finalposi);
                            printf("Patient position updated, now position %d in line\n", finalposi);
                        }
                        //it's new
                        else{
                            addtoqueue(&heap, newpatient, &finalposi);
                        }
                        
                        

                        //if there are doctors available (reminder to ADD IF STATEMENT HERE once hash is implemented)
                        //{
                        patient booted;
                        //should always be true
                        //if(getOUT(&heap, &booted)==1){
                            //now sned patient to hash, will do once implemented
                        //    printf("\nPatient %d was assigned doctor (1ID).\n", booted.id);
                            
                        //}

                        //}
                        //else
                        printf("No doctors available, added to waiting list.\nPatient is number %d something in line.\n", finalposi);
                    }
                
                }
                //if dischargin a patient
                else if(iChoice == 2){
                    //dishcharge them, maybe doctor enters their id and patients id
                    printf("Doctor (ID) has discharded patient (ID)\n");

                    //now check if there is a patient waiting to be treated
                    //-1 is an invalid id
                    if(heap.currentpatients > 0){
                        patient booted;
                        //SHOULD always be true
                        if(getOUT(&heap, &booted) == 1){
                            //now sned patient to hash, will do once implemented
                            printf("Patient %d was assigned doctor (ID).\n", booted.id);
                        }
                    }
                    else{
                        printf("Doctor (ID) is now on standby.\n");
                    }
                }
                else if(iChoice == 3){
                    //viewing queue
                    
                    for(int i = 0; i < heap.currentpatients; i++){
                        printf("ID: %d\nTriage level: %d\n\n", heap.patients[i].id, heap.patients[i].tl);
                    }
                }
                else if(iChoice == 4){
                    //quitting
                    quit = 1;
                    //so can leave the input loop
                    iChoice = -1;
                    printf("Quitting... seeyuh\n");
                }
                else{
                //error
                    printf("Error, try again.\n");
                }
            }
        }while (iChoice > 0 && iChoice < 5);
    }   
    return 0;
}