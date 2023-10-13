#include "compute_hashes.h"
#include "hash_delivery.h"

/***********   used by leaf processes to create, and write hashes into hash files assoiated with their child_id   ***********/
void leaf_hashing(int BUFFER_SIZE, int child_id, int n){
    //local variables
    FILE* input_file;
    char result_hash[SHA256_BLOCK_SIZE * 2 + 1];
    int out_txt = child_id-(n-1);

    // Filenames
    char hash_filename[BUFFER_SIZE];
    sprintf(hash_filename, "output/hashes/%d.out", child_id);

    char block_filename[BUFFER_SIZE];
    sprintf(block_filename, "output/blocks/%d.txt", out_txt);
    

    // Open block file
    input_file = fopen(block_filename, "r");
    if (input_file == NULL) { 
        perror("Error opening block file"); 
        exit(-1);
    }

    // Hash the block and store in result_hash
    hash_data_block(result_hash, block_filename);
    send_hash_to_file(result_hash, hash_filename);
}


/***********   used by parent process to retrieve, process and send hashes up the tree   ***********/
void get_dualHash_and_pass(int BUFFER_SIZE, int child_id, int child_id_left, int child_id_right, int n) {    
    // Buffer for computed dual hash
    char result_hash[SHA256_BLOCK_SIZE * 2 + 1];
    memset(result_hash, '\0',SHA256_BLOCK_SIZE * 2 + 1);
    
    // Filenames
    char hash_filename[BUFFER_SIZE];
    char left_filename[BUFFER_SIZE];
    char right_filename[BUFFER_SIZE];
    sprintf(hash_filename, "output/hashes/%d.out", child_id);
    sprintf(left_filename, "output/hashes/%d.out", (child_id_left));
    sprintf(right_filename, "output/hashes/%d.out", (child_id_right));

    printf("%s",hash_filename);
    printf("%s",left_filename);
    printf("%s",right_filename);
    fflush(stdout);
    // retrieve and store left and right hash values 
    char *left_hash_ptr = get_child_hashPtr(left_filename);
    char *right_hash_ptr = get_child_hashPtr(right_filename);
    printf("*************************%s*************", left_hash_ptr);
    // Compute the dual hash for the result
    // If the pointers don't work, this a different way
    compute_dual_hash(result_hash, left_hash_ptr, right_hash_ptr);
    send_hash_to_file(result_hash, hash_filename);
}