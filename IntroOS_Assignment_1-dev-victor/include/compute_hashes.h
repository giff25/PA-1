#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdio.h>
#include "sha256.h"
#include "hash.h"
#include "hash_delivery.h"

void leaf_hashing(int BUFFER_SIZE, int child_id, int n);

void get_dualHash_and_pass(int BUFFER_SIZE, int child_id, int child_id_left, int child_id_right, int n);

#endif