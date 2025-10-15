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

// Prototipos
struct Node* create_node(int id, const char* name, int stock);
int id_exists(struct Node* head, int id);
void insert_front(struct Node** head);
void insert_end(struct Node** head);
struct Node* find_by_id(struct Node* head, int id);
void update_stock(struct Node* head);
void delete_by_id(struct Node** head);
void list_all(struct Node* head);
void free_list(struct Node** head);

// Helpers de entrada
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
            case 1:
                insert_front(&head);
                break;
            case 2:
                insert_end(&head);
                break;
            case 3: {
                int id = read_int("ID a buscar: ");
                struct Node* p = find_by_id(head, id);
                if (p) {
                    printf("Producto encontrado:\n");
                    printf("ID: %d\nNombre: %s\nStock: %d\n", p->id, p->name, p->stock);
                } else {
                    printf("No existe producto con ID %d\n", id);
                }
                break;
            }
            case 4:
                update_stock(head);
                break;
            case 5:
                delete_by_id(&head);
                break;
            case 6:
                list_all(head);
                break;
            case 0:
                printf("Saliendo... liberando memoria.\n");
                free_list(&head);
                break;
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");
        }
    } while (option != 0);

    return 0;
}

//Implementaciones

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

void delete_by_id(struct Node** head) {
    if (!*head) {
        printf("Inventario vacio.\n");
        return;
    }
    int id = read_int("ID a eliminar: ");
    struct Node* cur = *head;
    struct Node* prev = NULL;
    while (cur) {
        if (cur->id == id) break;
        prev = cur;
        cur = cur->next;
    }
    if (!cur) {
        printf("No existe producto con ID %d\n", id);
        return;
    }
    if (!prev) {
        // eliminar cabeza
        *head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
    printf("Producto con ID %d eliminado.\n", id);
}

void list_all(struct Node* head) {
    if (!head) {
        printf("Inventario vacio.\n");
        return;
    }
    printf("\n--- Inventario completo ---\n");
    struct Node* cur = head;
    while (cur) {
        printf("ID: %d | Nombre: %s | Stock: %d\n", cur->id, cur->name, cur->stock);
        cur = cur->next;
    }
}

void free_list(struct Node** head) {
    struct Node* cur = *head;
    while (cur) {
        struct Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}

//INPUT HELPERS

void read_line(char* buffer, size_t size) {
    if (!fgets(buffer, (int)size, stdin)) {
        // EOF o error
        buffer[0] = '\0';
        return;
    }
    // eliminar '\n'
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
}

int read_int(const char* prompt) {
    char line[128];
    long val;
    char* endptr;
    while (1) {
        if (prompt && prompt[0]) printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nEntrada no leida. Intentelo de nuevo.\n");
            clearerr(stdin);
            continue;
        }
        // eliminar espacios iniciales
        char* p = line;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') {
            printf("Entrada vacia. Ingrese un numero.\n");
            continue;
        }
        val = strtol(p, &endptr, 10);
        if (p == endptr) {
            printf("Por favor ingresa un numero entero valido.\n");
            continue;
        }
        // ok
        return (int)val;
    }
}

void read_string(const char* prompt, char* buffer, size_t size) {
    while (1) {
        if (prompt && prompt[0]) printf("%s", prompt);
        read_line(buffer, size);
        if (buffer[0] == '\0') {
            printf("No puede estar vacio. Intente de nuevo.\n");
            continue;
        }
        break;
    }
}

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}