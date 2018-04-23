#pragma once

// it's nervous because it screams whenever bad thing happens

void * allocate(size_t length) {
    void *result = malloc(length);
    if (result == NULL) {
        perror("Failed to perform memory allocation");
        exit(1);
    }
    return result;
}
