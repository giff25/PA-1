Assignment 1
Group #54

Victor Butkov | butko034 
Jaanon Anbar | anbar005 
Kristina Cummings | cummi657

CSELabs Machine: csel-kh1250-01.cselabs.umn.edu

MakeFile: We have added several source code and header files to compile with make. We have linked them to the project code and provided additional files to clean.

Contributions:
    Viktor: Create process tree, create abstract source code, tree visualization, [child_process compute_hashes hash_delivery Makefile]
    Kristina: Hashing each file block, [child_process compute_hashes hash_delivery Makefile]
    Jaanon: Partitioning file function, ReadME for intermediate submission, configure compilation.

Plan:
Merkle tree

execl(./child_process) should be the last to run in merkle.c with id 0 to become root process
—----------------------------------------------------------------------------------------------------------------------------
Process tree:

//loop twice:
	//if (i am child) then:
		// if(i am leaf) then:
                		//read in the associated block file and compute the hash of the block
                		//TODO: void hash_data_block(char *result_hash, char *block_filename);
                		//TODO: write hash to hashes_folder
                		//have each of the leaf processes use vis_hash function to print to vis file]
		//if (i am not leaf) then:
			//run execl(./child_process) for current process
	//if (i am parent) then:
		//go to next (loop or exit loop)
//parent wait on both children
//parent takes in hashes
//print out hash values to file
