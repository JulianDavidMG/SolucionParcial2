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
