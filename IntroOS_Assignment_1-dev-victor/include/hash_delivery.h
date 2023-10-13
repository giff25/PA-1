#ifndef HASH_DELIVERY_H
#define HASH_DELIVERY_H

#include <stdlib.h>
#include <stdio.h>
#include "sha256.h"

void send_hash_to_file(char *result_hash, char *filename);

char *get_child_hashPtr(char *filename);

#endif