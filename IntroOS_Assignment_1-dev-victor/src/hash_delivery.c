#include "hash_delivery.h"

void send_hash_to_file(char *result_hash, char *filename){
    FILE* output_file;

    output_file = fopen(filename, "w");
    if(output_file == NULL){    
        perror("Error opening hash file"); 
        exit(-1); 
    }
    
    size_t written = fwrite(result_hash, 1, SHA256_BLOCK_SIZE * 2 + 1, output_file);

    if (written != SHA256_BLOCK_SIZE * 2 + 1) {
        perror("Error: Failed to write to file");
        fclose(output_file);
        exit(-1);
    }

    // Close the files and exit
    fclose(output_file);
    return;
}

char *get_child_hashPtr(char *filename){
    char *child_hash_ptr = malloc(SHA256_BLOCK_SIZE * 2 + 1);
    FILE* child_hash_filename;

    child_hash_filename = fopen(filename, "r");
    if (child_hash_filename == NULL) { 
        perror("Error opening hash file"); 
        exit(-1);
    }

    if ((fwrite(child_hash_ptr, 1, SHA256_BLOCK_SIZE * 2 + 1, child_hash_filename)< 0)) {
        perror("Error: Failed to buff file");
        fclose(child_hash_filename);
        exit(-1);
    }

    fclose(child_hash_filename);
    
    return child_hash_ptr;
}