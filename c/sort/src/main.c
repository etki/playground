#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "nervous_allocator.c"
#include "table.c"

typedef struct int_array {
    int32_t *data;
    size_t length;
} int_array;

typedef struct source {
    int_array *random;
    int_array *sorted;
} source;

typedef struct result {
    size_t input_length;
    char sorted;
    char correctness;
    long time;
} result;

typedef struct benchmark {
    char *name;
    result *results;
} benchmark;

int_array * create_array(size_t length) {
    int_array *payload = allocate(sizeof(int_array));
    payload->data = allocate(sizeof(int32_t) * length);
    payload->length = length;
    return payload;
}

int_array * copy_array(int_array *source) {
    int_array *copy = create_array(source->length);
    copy->data = allocate(source->length * sizeof(int));
    memcpy(copy->data, source->data, copy->length);
    return copy;
}

int_array * generate_random_array(size_t length) {
    int_array *payload = create_array(length);
    for (size_t i = 0; i < length; i++) {
        payload->data[i] = rand();
    }
    return payload;
}

int int_comparison(const void * left, const void * right) {
    return *((int*) left) - *((int*) right);
}

source * generate_source(size_t length) {
    source *result = allocate(sizeof(source));
    result->random = generate_random_array(length);
    result->sorted = copy_array(result->random);
    qsort(result->sorted->data, length, sizeof(int), int_comparison);
}

void release_data(int_array *payload) {
    free(payload->data);
    free(payload);
}

int_array * read_configuration(int argc, char *argv[]) {
    int_array *data = create_array((size_t) argc - 1);
    for (int i = 1; i < argc; i++) {
        int value = (int) strtol(argv[i], NULL, 10);
        if (value < 1) {
            printf("Invalid value supplied: `%s` is either not a number or is less than one\n", argv[i]);
            exit(1);
        }
        data->data[i - 1] = (int) strtol(argv[i], NULL, 10);
    }
    return data;
}

int_array * get_default_configuration() {
    uint length = 3;
    int_array *data = create_array(length);
    for (int i = 0; i < length; i++) {
        uint multiplier = (uint) pow(100, i);
        data->data[i] = 1000 * multiplier;
    }
    return data;
}

int main(int argc, char *argv[]) {
    int_array * configuration;
    printf("Testing various sort functions!\n");
    if (argc < 2) {
        printf("No array lengths provided in arguments, using defaults\n");
        configuration = get_default_configuration();
    } else {
        configuration = read_configuration(argc, argv);
    }
    printf("Generating test data...\n");
    for (size_t i = 0; i < configuration->length; i++) {
        printf("> Generating test data of %i elements\n", configuration->data[i]);
        generate_source((size_t) configuration->data[i]);
    }
    printf("Done!\n");
    return 0;
}

void __attribute__ ((used)) sort_baseline(int_array * payload) {

}
