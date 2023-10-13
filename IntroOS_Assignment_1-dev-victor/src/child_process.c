#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "hash.h"
#include "print_tree.h"
#include "compute_hashes.h"

#define PATH_MAX 1024

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Number of arguments invalid: %i\n", argc);
        printf("Usage: ./child_process <blocks_folder> <hashes_folder> <N> <child_id>\n");
        return 1;
    }

    // Local Variables
    int child_id = atoi(argv[4]);
    int n = atoi(argv[3]);
    int child_id_left = 2 * child_id + 1;
    int child_id_right = 2 * child_id + 2;
    char child_id_Char[10];
    char n_Char[10];         
    pid_t left_pid, right_pid;

    char *vis_file = "output/visualization.txt";         
    char blocks_folder[PATH_MAX] = ""; strcpy(blocks_folder, argv[1]);
    char hashes_folder[PATH_MAX] = ""; strcpy(hashes_folder, argv[2]);
    


    /***************    Attempt to spawn the child processes and exec()    ***************/
            
            /***************   attempt LEFT fork    ***************/
            
            //i am leaf
            if((n-1)<=(child_id)){
                printf("i am leaf#%i[%i]\n", child_id, getpid());
                leaf_hashing(PATH_MAX, child_id, n);
                return(0);
            }

            // i am not leaf
            else{

                left_pid = fork();
                if (left_pid < 0) {
                    printf("Error: Left fork failed");
                    // Before submission we might want to streamline our error checking... ???
                    exit(-1);
                } 
            }
            
            /***************   i am LEFT non-leaf child    ***************/
            
            if (left_pid == 0) {

                child_id_left = 2 * child_id + 1;
                sprintf(n_Char, "%i", n);
                sprintf(child_id_Char, "%i", child_id_left);
                //printf("i am child#%i pid[%i] i am execing with next id#%i\n", child_id, getpid(), child_id_left);
                execl("./child_process", "dont remove it will stop working", blocks_folder, hashes_folder, n_Char, child_id_Char, NULL);
                perror("Error: Left child exec failed");
                exit(-1);
            }
            
            
            /***************   i am LEFT parent    ***************/
            
            else {
                if(child_id > 0){
                    printf("i am parent node#[%i] with pid[%i]\n", child_id, getpid());
                }else{
                    printf("I am root node#[%i] with pid[%i]\n", child_id, getpid());
                }
                int status;
                waitpid(left_pid, &status, 0);
            }
            
            /***************   attempt RIGHT fork   ***************/
            
            //i am leaf
            if((n-1)<=(child_id)){
                printf("i am leaf#%i[%i]\n", child_id, getpid());
                fflush(stdout);
                leaf_hashing(PATH_MAX, child_id, n);
                return(0);
            }
            
            //i am not leaf
            else{    
                right_pid = fork();
                
                if (right_pid < 0) {
                    printf("Error: Right fork failed");
                    exit(-1);
                }
            }   
            /***************   I am RIGHT non-leaf child    ***************/    
            
            if (right_pid == 0) {
                child_id_right = 2 * child_id + 2;
                sprintf(n_Char, "%i", n);
                sprintf(child_id_Char, "%i", child_id_right);
                //printf("i am child#%i pid[%i] i am execing with next id#%i\n", child_id, getpid(), child_id_right);
                //fflush(stdout);
                execl("./child_process", "dont remove it will stop working", blocks_folder, hashes_folder, n_Char, child_id_Char, NULL);
                perror("Error: Left child exec failed");
                exit(-1);

            } 
            
            /***************   I am RIGHT parent    ***************/
            
            else {
                if(child_id > 0){
                    printf("i am parent node#[%i] with pid[%i]\n", child_id, getpid());
                }else{
                    printf("I am root node#[%i] with pid[%i]\n", child_id, getpid());
                }
                fflush(stdout);
                int status;
                waitpid(right_pid, &status, 0);
            }

            //get childrens hashes and send to output file
            get_dualHash_and_pass(PATH_MAX, child_id, child_id_left, child_id_right, n);

            /***************    print merkle tree    ***************/

            print_merkle_tree(vis_file, hashes_folder, n);

            /***************    clean up memory    ***************/
            

                // char right_hash[SHA256_BLOCK_SIZE * 2 + 1];
                // char left_hash[SHA256_BLOCK_SIZE * 2 + 1];
}