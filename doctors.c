// #define DOC_TBL_SIZE 23 // put this with the other defines al-ja'ydeen

// // put this with the other typedefs al-ja'ydeen
// typedef struct {
//     int patient_id;
//     int bed_num;
// } bed;

// typedef struct {
//     int doctor_id;
//     int patient_id;
//     struct doctor* next; // for hash table chaining
// } doctor;

// typedef struct {
//     doctor* arr[TOTAL_DOCTORS];
//     int front;
//     int rear;
// } doc_queue;



// doc_queue* init_doc_queue() {
//     doc_queue* q = (doc_queue*)malloc(sizeof(doc_queue));
//     if (q == NULL) {
//         return NULL;
//     }
//     q->front = 0;
//     q->rear = -1;
//     for (int i = 0; i < TOTAL_DOCTORS; i++) {
//         q->arr[i] = NULL;
//     }
//     return q;
// }

// bool q_enqueue(doc_queue* q, doctor* new_doc) {
//     if (q->rear == TOTAL_DOCTORS - 1) {
//         return false; // Queue is full
//     }
//     q->arr[++q->rear] = new_doc;
//     return true;
// }

// // Dequeues a doctor from queue and stores in the double pointer doc.
// // Returns true if successful, else false.
// bool q_dequeue(doc_queue* q, doctor** doc) {
//     if (q->front > q->rear) {
//         return false; // Queue is empty
//     }
//     *doc = q->arr[q->front++];
//     return true;
// }

// bool q_is_empty(doc_queue* q) {
//     return q->front > q->rear || q->front == -1;
// }

// int hash (int id, int table_size){
//     return id % table_size;
// }

// bool doc_table_insert(doctor* doc_table, int size, doctor* new_doc) {
//     if (doc_table == NULL || new_doc == NULL) {
//         return false; // Invalid input
//     }
//     int index = hash(new_doc->doctor_id, size);
//     // Chain the new doctor to the head of the list at the hashed index
//     doctor* head = &doc_table[index];

//     if (head->doctor_id == -1) {
//         *head = *new_doc;
//         head->next = NULL;
//     } else {
//         new_doc->next = head->next; 
//         head->next = new_doc; 
//     }
//     return true;
// }

// doctor* doc_table_search(doctor* doc_table, int size, int doctor_id) {
//     if (doc_table == NULL) {
//         return NULL; 
//     }
    
//     int index = hash(doctor_id, size);
//     doctor* current = &doc_table[index];
//     while (current != NULL) {
//         if (current->doctor_id == doctor_id) {
//             return current; 
//         }
//         current = current->next; 
//     }

//     // If no doctor found
//     return NULL; 
// }

// doctor *doc_table_pop(doctor* doc_table, int size, int doctor_id) {
//     int index = hash(doctor_id, size);
//     doctor* current = &doc_table[index];
//     doctor* prev = NULL;
//     while (current != NULL && current->doctor_id != doctor_id) {
//         prev = current;
//         current = current->next;
//     }
//     if (current == NULL) return NULL;
//     if (prev == NULL) {
//         // If prev == NULL, we are at the head of chain.
//         if (current->next == NULL) {
//             // current is the only node in the chain
//             current->doctor_id = -1; // Mark as empty
//             current->patient_id = -1;
//         } else {
//             // Move node after current up
//             doctor* temp = current->next; // TODO: idk if this is correct
//             doc_table[index].doctor_id = temp->doctor_id;
//             doc_table[index].patient_id = temp->patient_id;
//             doc_table[index].next = temp->next;
//         }
//     } else {
//         prev->next = current->next;
//     }
//     return current;
// }

// doctor* init_doc_table (int size) {
//     doctor* doc_table = (doctor*)malloc(size * sizeof(doctor));
//     for (int i = 0; i < size; i++) {
//         doc_table[i].doctor_id = -1;
//         doc_table[i].patient_id = -1;
//         doc_table[i].next = NULL;
//     }
//     return doc_table;
// }