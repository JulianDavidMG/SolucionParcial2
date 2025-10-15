# SolucionParcial2
# Inventario - Lista Enlazada Simple

## Descripción
Programa en C que gestiona un inventario simple usando una lista enlazada simple. Cada producto tiene: `id`, `name`, `stock`.

## Operaciones implementadas
- Insertar producto al inicio.
- Insertar producto al final.
- Buscar producto por ID.
- Actualizar stock por ID.
- Eliminar producto por ID.
- Listar inventario completo.
- Menú por consola y entrada validada.

## Archivos
- `inventory.c` — implementación completa.
- `.gitignore` — archivos no versionados.
- `README.md` — este archivo.

## Ejemplo de uso
### Insertar productos
Ingrese ID: 101
Ingrese nombre: Pan
Ingrese stock: 20

Producto insertado al inicio correctamente.

### Listar inventario
ID: 101 | Nombre: Pan | Stock: 20
ID: 102 | Nombre: Leche | Stock: 10

### Actualizar stock
Ingrese ID del producto a actualizar: 101
Nuevo stock: 35

Stock actualizado correctamente.

### Eliminar producto
Ingrese ID del producto a eliminar: 102
Producto eliminado correctamente.


## Compilación y ejecución
Compilar:
gcc inventory.c -o inventario
./inventario
