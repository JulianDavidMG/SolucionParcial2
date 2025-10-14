#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    int id;
    char name[40];
    int stock;
    struct Node* next;
};

struct Node* create_node(int id, const char* name, int stock);
int id_exists(struct Node* head, int id);
void insert_front(struct Node** head);
void insert_end(struct Node** head);
struct Node* find_by_id(struct Node* head, int id);
void update_stock(struct Node* head);
void delete_by_id(struct Node** head);
void list_all(struct Node* head);
void free_list(struct Node** head);

void read_line(char* buffer, size_t size);
int read_int(const char* prompt);
void read_string(const char* prompt, char* buffer, size_t size);
void clear_stdin(void);

int main(void) {
    struct Node* head = NULL;
    int option;

    do {
        printf("\n--- Inventario (Lista Simple) ---\n");
        printf("1. Insertar producto al inicio\n");
        printf("2. Insertar producto al final\n");
        printf("3. Buscar producto por ID\n");
        printf("4. Actualizar stock por ID\n");
        printf("5. Eliminar producto por ID\n");
        printf("6. Listar inventario completo\n");
        printf("0. Salir\n");
        option = read_int("Elige una opcion: ");

        switch (option) {
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");
        }
    } while (option != 0);

    return 0;
}




struct Node* create_node(int id, const char* name, int stock) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->id = id;
    strncpy(n->name, name, sizeof(n->name)-1);
    n->name[sizeof(n->name)-1] = '\0';
    n->stock = stock;
    n->next = NULL;
    return n;
}

int id_exists(struct Node* head, int id) {
    struct Node* cur = head;
    while (cur) {
        if (cur->id == id) return 1;
        cur = cur->next;
    }
    return 0;
}

void insert_front(struct Node** head) {
    int id = read_int("ID: ");
    if (id_exists(*head, id)) {
        printf("Error: Ya existe un producto con ID %d\n", id);
        return;
    }
    char name[40];
    read_string("Nombre: ", name, sizeof(name));
    int stock = read_int("Stock inicial: ");
    struct Node* n = create_node(id, name, stock);
    n->next = *head;
    *head = n;
    printf("Producto insertado al inicio.\n");
}

void insert_end(struct Node** head) {
    int id = read_int("ID: ");
    if (id_exists(*head, id)) {
        printf("Error: Ya existe un producto con ID %d\n", id);
        return;
    }
    char name[40];
    read_string("Nombre: ", name, sizeof(name));
    int stock = read_int("Stock inicial: ");
    struct Node* n = create_node(id, name, stock);
    if (!*head) {
        *head = n;
    } else {
        struct Node* cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }
    printf("Producto insertado al final.\n");
}

struct Node* find_by_id(struct Node* head, int id) {
    struct Node* cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

void update_stock(struct Node* head) {
    int id = read_int("ID a actualizar: ");
    struct Node* p = find_by_id(head, id);
    if (!p) {
        printf("No existe producto con ID %d\n", id);
        return;
    }
    printf("Producto encontrado: %s (stock actual: %d)\n", p->name, p->stock);
    int change = read_int("Nuevo stock (valor entero, reemplaza el anterior): ");
    p->stock = change;
    printf("Stock actualizado.\n");
}