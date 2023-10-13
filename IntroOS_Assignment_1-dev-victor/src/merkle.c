#include "utils.h"
#include "print_tree.h"

// ##### DO NOT MODIFY THESE VARIABLES #####
char *blocks_folder = "output/blocks";
char *hashes_folder = "output/hashes";
char *visualization_file = "output/visualization.txt";


int main(int argc, char* argv[]) {

    if (argc != 3) {
        // N is the number of data blocks to split <file> into (should be a power of 2)
        // N will also be the number of leaf nodes in the merkle tree
        printf("Usage: ./merkle <file> <N>\n");
        return 1;
    }

    // TODO: Read in the command line arguments and validate them
    char *input_file = argv[1];
    int n = atoi(argv[2]);

    char n_char[3] = "";
    char child_id_char[3] = "";

    if (n < 1 || (n % 2) != 0) {
        printf("N: %i", n);
        printf("ERROR: N must be a power of 2 that is greater than 1...\n");
        exit(-1);
    }

    // ##### DO NOT REMOVE #####
    setup_output_directory(blocks_folder, hashes_folder);

    // TODO: Implement this function in utils.c
    partition_file_data(input_file, n, blocks_folder);

    //Starts the recursive merkle tree computation by spawning first child process (root)
    sprintf(n_char, "%i", n); 
    sprintf(child_id_char, "%i", 0);
    execl("./child_process", "do not remove or this will break :)",blocks_folder, hashes_folder, n_char, child_id_char, NULL);

    // ##### DO NOT REMOVE #####
    #ifndef TEST_INTERMEDIATE
        // Visually display the merkle tree using the output in the hashes_folder
        print_merkle_tree(visualization_file, hashes_folder, n);
    #endif

    return 0;
}