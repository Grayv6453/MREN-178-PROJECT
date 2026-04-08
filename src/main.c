#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Heap
//Patient added, inserted based on priority to heap

//Starting at root, remove patient from heap and assign doctor in hash table

//max resource the hospital can distribute
#define TOTAL_DOCTORS 2 // CHANGE THIS to the number of doctors you want
#define PAT_TBL_SIZE 23 // Make sure this is prime to reduce collisions in the hash table

//Max Heap Size (only so many people can be waiting in line)
#define MHS 2000 // CHANGE THIS to the size of the waiting list you want

typedef struct doctor{
    int doctor_id;
    int patient_id;
} doctor;

typedef struct {
    doctor* arr[TOTAL_DOCTORS];
    int front;
    int rear;
    int count;
} doc_queue;

//might add temperature, heart rate, and other symptoms of being a league player
typedef struct patient {
    int id;
    int tl;
    doctor* assigned_doc;
    struct patient* next; // for hash table chaining
}patient;

typedef struct{
    patient patients[MHS];
    int currentpatients;
}daheap;

typedef struct {
    int patient_id;
    int bed_num;
} bed;

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
        *finalposi = largest + 1;
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

    *finalposi = index + 1;
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
        return 0;
    }
    //store root as to be booted, make last item the new root
    *booty = heap->patients[0];
    heap->patients[0] = heap->patients[heap->currentpatients - 1];
    heap->currentpatients--;

    //bubble down from root
    int filler = 0;
    heapify(heap, 0, &filler);
    return 1;
}

//Heap sort!!!!
void showmedasauce(daheap* heap) {
    if (heap->currentpatients == 0) {
        printf("No patients in the waiting list.\n");
        return;
    }

    // making a clean copy so that the OG is untouched (lebroooonnn jaaaaamessss)
    daheap copy = *heap;

    printf("Waiting list (priority order):\n");
    printf("------------------------------------\n");
    printf("Position\tID\tTriage Level\n");
    //counter to go through the copy heap
    int posi = 1;
    //gonna store the booty from each call of getOUT here
    patient booty;
    //loop through heap for amount of patients
    while (copy.currentpatients > 0) {
        //get OUT function removes root from heap, and stores it in the booty
        getOUT(&copy, &booty);
        //print with the booty and current posi
        printf("%d\t\t%d\t%d\n", posi, booty.id, booty.tl);
        posi++;
    }
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
        *finalposi = index + 1;
    }
}

bool q_is_full(doc_queue* q) {
    return q->count >= TOTAL_DOCTORS;
}

bool q_is_empty(doc_queue* q) {
    return q->count == 0;
}

// Initialize a queue containing doctors with max size of TOTAL_DOCTORS.
doc_queue* init_doc_queue() {
    doc_queue* q = (doc_queue*)malloc(sizeof(doc_queue));
    if (q == NULL) {
        return NULL;
    }
    q->front = -1;
    q->rear = -1;
    q->count = 0;
    for (int i = 0; i < TOTAL_DOCTORS; i++) {
        q->arr[i] = NULL;
    }
    return q;
}

// Enqueues a doctor into queue q. Returns true if successful, else false.
bool q_enqueue(doc_queue* q, doctor* new_doc) {
    if (q_is_full(q)) {
        // Should never be possible for there to be more drs than total drs,
        // but check just in case.
        printf("Error: Doctor queue is full\n");
        return false;
    }
    q->rear = (++q->rear) % TOTAL_DOCTORS;
    q->arr[q->rear] = new_doc;
    q->count++;
    if (q->front == -1) {
        q->front = 0;
    }
    return true;
}

// Dequeues a doctor from queue q. Returns pointer to doctor if successful, 
// else NULL.
doctor *q_dequeue(doc_queue* q) {
    if (q_is_empty(q)) {
        printf("Error: Doctor queue is empty\n");
        return NULL;
    }
    doctor* doc = q->arr[q->front]; // Grab the actual pointer
    q->front = (q->front + 1) % TOTAL_DOCTORS;
    q->count--;
    if (q_is_empty(q)) {
        q->front = -1;
        q->rear = -1;
    }
    return doc;
}

// Simple division hash function. Ensure table_size is prime to reduce collisions.
int hash (int id, int table_size){
    return id % table_size;
}

// Inserts new_pat into pat_table. Handles collisions via chaining. Returns
// true if successful, else false.
bool pat_table_insert(patient* pat_table, int size, patient* new_pat) {
    if (pat_table == NULL || new_pat == NULL) {
        return false; // Invalid input
    }
    int index = hash(new_pat->id, size);
    // Chain the new patient to the head of the list at the hashed index
    patient* head = &pat_table[index];

    if (head->id == -1) {
        // No collision
        *head = *new_pat;
        head->next = NULL;
    } else { 
        // Collision. Move current head down and place new patient at head.
        patient* moved = (patient*)malloc(sizeof(patient));
        *moved = *head;
        new_pat->next = moved;
        *head = *new_pat;
    }
    return true;
}

// Searches for patient_id in pat_table. Returns pointer to patient if found, 
// else NULL.
patient* pat_table_search(patient* pat_table, int size, int patient_id) {
    if (pat_table == NULL) {
        return NULL; 
    }
    
    int index = hash(patient_id, size);
    patient* current = &pat_table[index];
    while (current != NULL) {
        if (current->id == patient_id) {
            return current; 
        }
        current = current->next; 
    }

    // If no patient found
    return NULL; 
}

// Removes patient with patient_id from pat_table and returns pointer to removed
// patient. Returns NULL if patient not found.
patient *pat_table_pop(patient* pat_table, int size, int patient_id) {
    int index = hash(patient_id, size);
    patient* current = &pat_table[index];
    patient* prev = NULL;

    //find da patient
    while (current != NULL && current->id != patient_id) {
        prev = current;
        current = current->next;
    }
    //not found
    if (current == NULL) return NULL;

    // Create a safe copy of the patient to return to main
    patient* PoppedPatty = (patient*)malloc(sizeof(patient));
    *PoppedPatty = *current; 
    PoppedPatty->next = NULL;

    //patch hole in tha hashbrown
    if (prev == NULL) {
        //it's null so we are popping the head
        if (current->next == NULL) {
            //mark head as empty (airhead bruh)
            current->id = -1;
        } else {
            // Move node after current up
            patient* temp = current->next; // TODO: idk if this is correct.    Nah u good homie
            //copy all tha data
            *current = *temp;
            //free the node that was shifted up
            free(temp);
        }
    } else {
        //popping form teh middle of the chain
        prev->next = current->next;
        free(current);
    }
    return PoppedPatty;
}

patient* init_pat_table (int size) {
    patient* pat_table = (patient*)malloc(size * sizeof(patient));
    if (pat_table == NULL) {
        return NULL; 
    }

    for (int i = 0; i < size; i++) {
        pat_table[i].id = -1;
        pat_table[i].next = NULL;
    }
    return pat_table;
}

void display_pat_table(patient* pat_table, int size) {
    printf("Current patients being treated:\n");
    printf("------------------------------------\n");
    printf("ID\tTriage Level\tAssigned Doctor ID\n");
    for (int i = 0; i < size; i++) {
        patient* current = &pat_table[i];
        // Go through the chain and print all nodes
        while (current != NULL && current->id != -1) {
            printf("%d\t%d\t\t%d\n", 
                current->id, current->tl, current->assigned_doc->doctor_id);
            current = current->next;
        }
    }
}

doctor *init_doctor(int doctor_id, int patient_id) {
    doctor* new_doc = (doctor*)malloc(sizeof(doctor));
    if (new_doc == NULL) {
        return NULL; 
    }

    new_doc->doctor_id = doctor_id;
    new_doc->patient_id = patient_id; // no patient assigned yet
    return new_doc;
}

int main(void){
    //create the heap type stuff
    daheap heap;
    heapbirth(&heap);

    // Create queue containing free doctors and hash table containing patients
    // being treated
    doc_queue *free_drs = init_doc_queue();
    for (int i = 1; i < TOTAL_DOCTORS+1; i++) {
        doctor* new_doc = init_doctor(i, -1);
        if (new_doc == NULL) {
            printf("Error initializing doctor with ID %d\n", i);
        }
        else {
            q_enqueue(free_drs, new_doc);
        }
    }

    patient* in_treatment = init_pat_table(PAT_TBL_SIZE);

    printf("\n====== HOSPITAL RESOURCE MANAGER ======\nThis program allows you to add patients to a hospital, automatically assign doctors, and arrange waiting patients in terms of triage severity.\n");
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
            // for (int i = 0; i < free_drs->count; i++) {
            //     printf("%d is free\n", free_drs->arr[(free_drs->front+i) % TOTAL_DOCTORS]->doctor_id);
            // } // debugging

            printf("------------------------------------\nSelect an option:\n1. Enter new patient\n2. Discharge patient\n3. View waiting list\n4. View patients being treated\n5. Quit\n");
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
                    if(newpatient.id < 0 || newpatient.tl < 0){
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
                        //okay the id isn't in the waiting list, but is it already in the hash (being treated)?
                        else{
                            // 2. Check the treatment room (hash table)
                            patient* already_treating = pat_table_search(in_treatment, PAT_TBL_SIZE, newpatient.id);
    
                            if (already_treating != NULL) {
                                // THEY ARE IN A BED
                                printf("Hold up! Patient %d is currently being treated by Doctor %d. Cannot add to waiting list.\n", 
                                    already_treating->id, already_treating->assigned_doc->doctor_id);
                            }
                            //ok it really IS a new patient
                            else{
                                //add it to the waiting list
                                addtoqueue(&heap, newpatient, &finalposi);
                                //if there are doctors available (reminder to ADD IF STATEMENT HERE once hash is implemented)
                                // Check if there are free doctors available
                                if (!q_is_empty(free_drs)) {
                                    patient booted;
                                    //should always be true
                                    if(getOUT(&heap, &booted)){
                                        //now sned patient to hash

                                        //first get doctor pointer from queue, and set patient id to patient being from waiting list to hashbrown
                                        doctor* DocPoi = q_dequeue(free_drs);
                                        DocPoi->patient_id = booted.id;
                                        
                                        //then allocate memory in heap for a patient node to put in the hash table
                                        patient* HeapPatty = (patient*)malloc(sizeof(patient));
                                        *HeapPatty = booted; // Copy the data from patient being booted over to the heap copy of it
                                        HeapPatty->assigned_doc = DocPoi;
                                        HeapPatty->next = NULL;
                                        
                                        //now insert the heapversion of da patty into the table
                                        pat_table_insert(in_treatment, PAT_TBL_SIZE, HeapPatty);

                                        printf("\nPatient %d was assigned doctor %d.\n", HeapPatty->id, HeapPatty->assigned_doc->doctor_id);
                                    }
                                }
                                else {
                                    printf("No doctors available, added to waiting list.\n");
                                }
                                //^^ maybe I can add some way to see position in line later
                            }
                        }
                    }
                
                }
                //if dischargin a patient
                else if(iChoice == 2){
                    int pat_id;
                    printf("Enter patient ID to discharge: ");
                    if(scanf("%d", &pat_id) != 1){
                        pat_id = -1;
                        // Clear the bad input from the buffer
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                    }
                    if (pat_id < 0) {
                        printf("Invalid patient ID entered.\n");
                        continue;
                    }
                    patient *discharged = pat_table_pop(in_treatment, PAT_TBL_SIZE, pat_id);
                    if (discharged == NULL) {
                        printf("Error: No patient with ID %d currently being treated.\n", pat_id);
                        continue;
                    }

                    q_enqueue(free_drs, discharged->assigned_doc);

                    //dishcharge them, maybe doctor enters their id and patients id
                    printf("Doctor %d has discharged patient %d\n", discharged->assigned_doc->doctor_id, discharged->id);

                    //now check if there is a patient waiting to be treated
                    //-1 is an invalid id
                    if(heap.currentpatients > 0){
                        patient booted;
                        //SHOULD always be true
                        if(getOUT(&heap, &booted) == 1){
                            //now sned patient to hash, smae stff as in option 1
                            //first get doctor pointer from queue, and set patient id to patient being from waiting list to hashbrown
                            doctor* DocPoi = q_dequeue(free_drs);
                            DocPoi->patient_id = booted.id;
                            
                            //then allocate memory in heap for a patient node to put in the hash table
                            patient* HeapPatty = (patient*)malloc(sizeof(patient));
                            *HeapPatty = booted; // Copy the data from patient being booted over to the heap copy of it
                            HeapPatty->assigned_doc = DocPoi;
                            HeapPatty->next = NULL;
                            
                            //now insert the heapversion of da patty into the table
                            pat_table_insert(in_treatment, PAT_TBL_SIZE, HeapPatty);

                            printf("\nPatient %d was assigned doctor %d.\n", HeapPatty->id, HeapPatty->assigned_doc->doctor_id);
                        }
                    }
                    else{
                        printf("Doctor %d is now on standby.\n", discharged->assigned_doc->doctor_id);
                    }
                    free(discharged);
                }
                else if(iChoice == 3){
                    //viewing queue
                    showmedasauce(&heap);
                }
                else if(iChoice == 5){ // lol ik these arent in order but im too lazy to switch
                    //quitting
                    quit = 1;
                    //so can leave the input loop
                    iChoice = -1;
                    printf("Quitting... seeyuh\n");
                }
                else if (iChoice == 4) {
                    //see who bein treated
                    display_pat_table(in_treatment, PAT_TBL_SIZE);
                }
                else{
                //error
                    printf("Error, try again.\n");
                }
            }
        }while (iChoice > 0 && iChoice < 6);
    }   
    return 0;
}