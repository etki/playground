#pragma once

typedef struct cell {
    cell *previous;
    cell *next;
    char *value;
} cell;

typedef struct row {
    cell *head;
    cell *tail;
    row *previous;
    row *next;
    size_t width;
} row;

typedef struct table {
    row *head;
    row *tail;
    size_t height;
} table;

table * table_create() {
    table *table = allocate(sizeof(table));
    table->height = 0;
    return table;
}

void table_destroy(table *table) {
    row *cursor = table->head;
    while (cursor != NULL) {
        row *next = cursor->next;
        row_destroy(cursor);
        cursor = next;
    }
    free(table);
}

row * row_create(table *table) {
    row* row = allocate(sizeof(row));
    row->width = 0;
    if (table->head == NULL) {
        table->head = row;
    } else {
        table->tail->next = row;
        row->previous = table->tail;
    }
    table->tail = row;
    table->height++;
    return row;
}

void row_destroy(row *row) {
    cell *cursor = row->head;
    while (cursor != NULL) {
        cell *next = cursor->next;
        free(cursor);
        cursor = next;
    }
    free(row);
}

cell * cell_create(row *row) {
    cell *cell = allocate(sizeof(cell));
    row->width++;
    if (row->cells == NULL) {
        row->cells = cell;
        return;
    }

    return cell;
}

void cell_destroy(cell *cell) {
    free(cell);
}

void row_append(row *row, char *value) {
    cell *cell = cell_create(row);
    cell->value = value;
}
