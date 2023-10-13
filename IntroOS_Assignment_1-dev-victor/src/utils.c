#include "utils.h"
#include "math.h"

// Create N files and distribute the data from the input file evenly among them
// See section 3.1 of the project writeup for important implementation details

// Create N files and distribute the data from the input file evenly among them
// See section 3.1 of the project writeup for important implementation details
void partition_file_data(char *input_file, int n, char *blocks_folder) {
    // Hint: Use fseek() and ftell() to determine the size of the file
    FILE* input_file_ptr = fopen(input_file, "r"); //open the input file DO WE READ HERE???
    if (input_file_ptr == NULL) {   //if the input file is empty
        perror("Error opening input file"); //error statement
        exit(1);   //exit
    }
//check

    fseek(input_file_ptr, 0, SEEK_END); //fseek moves file pointer of a given file to specific position
    int file_size = ftell(input_file_ptr); //ftell finds position of file pointer in respect to start of file
    fseek(input_file_ptr, 0, SEEK_SET); //do we need to fseek again to put it at the beginning of the file once we know the size??

    char buffer[1024]; //do I need an array buffer???
    for(int i = 0; i < n; i++){
        int blocksize = floor(file_size / n);
        if(i == (n-1)){
                blocksize += (file_size % n);
        }
        long read_bytes = 0;
        char out_arr[1024]; //character array to hold output information
        sprintf(out_arr, "output/blocks/%d.txt", i); //similar to lab prints to output file
        //creates formatted string like in lab and stores it in out_arr
        //The format string "output/blocks/%d.txt" has a placeholder %d, gets replaced by i (value associated with nth block)
        // creates a file name "output/blocks/i.txt" depending on the value of i.

        FILE* output_file = fopen(out_arr, "w"); //opens output file 
        if(output_file == NULL){    //if the output file is empty
            perror("Error opening output file");    //error statement
            exit(1);   //exit
        }
        //char *out_arr_ptr = out_arr; //new pointer to track output buffer
        while(blocksize > 0) { //file position of pointer is > 0
        if(blocksize < BUFFER_SIZE){
             read_bytes = fread(buffer, 1, blocksize, input_file_ptr); 

        }else
        {
            read_bytes = fread(buffer, 1, BUFFER_SIZE, input_file_ptr); 
        }
        // long read_bytes = 0;
            //read_bytes = fread(buffer, 1, blocksize, input_file_ptr);     //fread reads the read bytes from the input file and stores them in the buffer
            buffer[read_bytes] = '\n';
            if(fwrite(buffer, 1, read_bytes, output_file) < read_bytes ){
                perror("Error");    //error statement
                exit(1);   //exit
            }
            blocksize -= read_bytes;
        }
        fclose(output_file); //closes output file
    }
    fclose(input_file_ptr); //closes input files
}
    
// ##### DO NOT MODIFY THIS FUNCTION #####
void setup_output_directory(char *block_folder, char *hash_folder) {
    // Remove output directory
    pid_t pid = fork();
    if (pid == 0) {
        char *argv[] = {"rm", "-rf", "./output/", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(1);
        }
        exit(0);
    } else {
        wait(NULL);
    }

    sleep(1);

    // Creating output directory
    if (mkdir("output", 0777) < 0) {
        printf("ERROR: mkdir output failed\n");
        exit(1);
    }

    sleep(1);

    // Creating blocks directory
    if (mkdir(block_folder, 0777) < 0) {
        printf("ERROR: mkdir output/blocks failed\n");
        exit(1);
    }

    // Creating hashes directory
    if (mkdir(hash_folder, 0777) < 0) {
        printf("ERROR: mkdir output/hashes failed\n");
        exit(1);
    }
}
