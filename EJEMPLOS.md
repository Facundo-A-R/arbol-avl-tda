# Ejemplos de Uso del Árbol AVL Genérico

## Tabla de Contenidos

1. [Ejemplo 1: Árbol de Enteros Simples](#ejemplo-1-árbol-de-enteros-simples)
2. [Ejemplo 2: Árbol de Strings](#ejemplo-2-árbol-de-strings)
3. [Ejemplo 3: Árbol de Estructuras Complejas](#ejemplo-3-árbol-de-estructuras-complejas)
4. [Ejemplo 4: Árbol de Números Flotantes](#ejemplo-4-árbol-de-números-flotantes)
5. [Ejemplo 5: Casos Avanzados](#ejemplo-5-casos-avanzados)

---

## Ejemplo 1: Árbol de Enteros Simples

### Código Completo

```c
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

// Función de comparación para enteros
int comparar_enteros(const void* a, const void* b) {
    int val_a = *(int*) a;
    int val_b = *(int*) b;
    return val_a - val_b;
}

// Función de impresión para enteros
void imprimir_entero(const void* dato) {
    printf("%d ", *(int*) dato);
}

int main() {
    // Crear árbol de enteros
    ArbolAVL arbol = crear_arbol(comparar_enteros, NULL);
    
    if (arbol == NULL) {
        printf("Error al crear el árbol\n");
        return 1;
    }
    
    // Insertar números
    int numeros[] = {50, 25, 75, 10, 30, 60, 80};
    int cantidad = 7;
    
    printf("Insertando números: ");
    for (int i = 0; i < cantidad; i++) {
        printf("%d ", numeros[i]);
        if (!arbol_insertar(&arbol, &numeros[i], sizeof(int), 1)) {
            printf("\nError al insertar %d\n", numeros[i]);
        }
    }
    printf("\n\n");
    
    // Mostrar métricas
    printf("Altura del árbol: %d\n", arbol_altura(arbol));
    printf("Cantidad de nodos: %d\n", arbol_peso(arbol));
    printf("Cantidad de hojas: %d\n", arbol_cantidad_hojas(arbol));
    printf("\n");
    
    // Recorrer in-orden
    printf("Recorrido In-Orden: ");
    arbol_recorrido_inorden(arbol, imprimir_entero);
    printf("\n\n");
    
    // Buscar un elemento
    int buscar = 30;
    if (arbol_buscar(arbol, &buscar)) {
        printf("✓ Elemento %d encontrado\n", buscar);
        int nivel = arbol_nivel(arbol, &buscar);
        printf("  Nivel: %d\n", nivel);
    } else {
        printf("✗ Elemento %d NO encontrado\n", buscar);
    }
    printf("\n");
    
    // Eliminar un elemento
    int eliminar = 25;
    printf("Eliminando elemento %d...\n", eliminar);
    if (arbol_eliminar(&arbol, &eliminar)) {
        printf("✓ Elemento eliminado\n");
        printf("Nuevo recorrido: ");
        arbol_recorrido_inorden(arbol, imprimir_entero);
        printf("\n");
    }
    printf("\n");
    
    // Información del árbol
    printf("Elemento mínimo: %d\n", *(int*) arbol_minimo(arbol));
    printf("Elemento máximo: %d\n", *(int*) arbol_maximo(arbol));
    printf("\n");
    
    // Limpiar
    vaciar_arbol(&arbol);
    printf("✓ Árbol destruido\n");
    
    return 0;
}
```

### Salida Esperada

```
Insertando números: 50 25 75 10 30 60 80 

Altura del árbol: 3
Cantidad de nodos: 7
Cantidad de hojas: 3

Recorrido In-Orden: 10 25 30 50 60 75 80 

✓ Elemento 30 encontrado
  Nivel: 2

Eliminando elemento 25...
✓ Elemento eliminado
Nuevo recorrido: 10 30 50 60 75 80 

Elemento mínimo: 10
Elemento máximo: 80

✓ Árbol destruido
```

---

## Ejemplo 2: Árbol de Strings

### Código Completo

```c
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función de comparación para strings
int comparar_strings(const void* a, const void* b) {
    return strcmp((const char*) a, (const char*) b);
}

// Función de impresión para strings
void imprimir_string(const void* dato) {
    printf("\"%s\" ", (const char*) dato);
}

// Función destructora para strings
void destruir_string(void* dato) {
    free(dato);
}

int main() {
    // Crear árbol de strings
    ArbolAVL arbol = crear_arbol(comparar_strings, destruir_string);
    
    if (arbol == NULL) {
        printf("Error al crear el árbol\n");
        return 1;
    }
    
    // Países a insertar
    const char* paises[] = {
        "España", "Argentina", "México", "Brasil",
        "Chile", "Colombia", "Perú", "Uruguay"
    };
    int cantidad = 8;
    
    printf("Insertando países: \n");
    for (int i = 0; i < cantidad; i++) {
        // Copiar el string porque el original es constante
        char* copia = malloc(strlen(paises[i]) + 1);
        strcpy(copia, paises[i]);
        
        printf("  - %s\n", paises[i]);
        
        // Insertar con copydata=0 porque ya copiamos
        if (!arbol_insertar(&arbol, copia, strlen(copia) + 1, 0)) {
            printf("    Error al insertar\n");
        }
    }
    printf("\n");
    
    // Mostrar ordenados
    printf("Países en orden alfabético:\n");
    arbol_recorrido_inorden(arbol, imprimir_string);
    printf("\n\n");
    
    // Buscar un país
    char* buscar = "México";
    if (arbol_buscar(arbol, buscar)) {
        printf("✓ País encontrado: %s\n", buscar);
    } else {
        printf("✗ País NO encontrado: %s\n", buscar);
    }
    printf("\n");
    
    // Información
    printf("Primer país (alfabético): %s\n", (char*) arbol_minimo(arbol));
    printf("Último país (alfabético): %s\n", (char*) arbol_maximo(arbol));
    printf("Total de países: %d\n\n", arbol_peso(arbol));
    
    // Limpiar
    vaciar_arbol(&arbol);
    printf("✓ Árbol destruido\n");
    
    return 0;
}
```

### Salida Esperada

```
Insertando países: 
  - España
  - Argentina
  - México
  - Brasil
  - Chile
  - Colombia
  - Perú
  - Uruguay

Países en orden alfabético:
"Argentina" "Brasil" "Chile" "Colombia" "España" "México" "Perú" "Uruguay" 

✓ País encontrado: México

Primer país (alfabético): Argentina
Último país (alfabético): Uruguay
Total de países: 8

✓ Árbol destruido
```

---

## Ejemplo 3: Árbol de Estructuras Complejas

### Código Completo

```c
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de Estudiante
typedef struct {
    int matricula;      // Número de matrícula (clave)
    char nombre[100];   // Nombre del estudiante
    float promedio;     // Promedio académico
    int anio;           // Año de estudio
} Estudiante;

// Función de comparación por matrícula
int comparar_estudiantes(const void* a, const void* b) {
    Estudiante* est_a = (Estudiante*) a;
    Estudiante* est_b = (Estudiante*) b;
    return est_a->matricula - est_b->matricula;
}

// Función de impresión
void imprimir_estudiante(const void* dato) {
    Estudiante* est = (Estudiante*) dato;
    printf("[Mat: %d, Nombre: %s, Promedio: %.2f, Año: %d]\n",
           est->matricula, est->nombre, est->promedio, est->anio);
}

int main() {
    // Crear árbol de estudiantes
    ArbolAVL arbol = crear_arbol(comparar_estudiantes, NULL);
    
    if (arbol == NULL) {
        printf("Error al crear el árbol\n");
        return 1;
    }
    
    // Crear estudiantes
    Estudiante estudiantes[] = {
        {1005, "Juan Pérez", 8.5, 2},
        {1001, "María García", 9.2, 1},
        {1008, "Carlos López", 7.8, 3},
        {1003, "Ana Martínez", 9.0, 1},
        {1007, "David Sánchez", 8.1, 2},
        {1002, "Laura Fernández", 9.5, 1},
        {1004, "Roberto Díaz", 8.3, 2}
    };
    int cantidad = 7;
    
    // Insertar estudiantes
    printf("Insertando %d estudiantes...\n\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        arbol_insertar(&arbol, &estudiantes[i], sizeof(Estudiante), 1);
    }
    
    // Mostrar en orden de matrícula
    printf("Estudiantes en orden de matrícula:\n");
    arbol_recorrido_inorden(arbol, imprimir_estudiante);
    printf("\n");
    
    // Buscar un estudiante
    Estudiante buscar = {1005, "", 0, 0};
    Estudiante* encontrado = (Estudiante*) arbol_buscar(arbol, &buscar);
    if (encontrado != NULL) {
        printf("✓ Estudiante encontrado:\n");
        imprimir_estudiante(encontrado);
        printf("\n");
    }
    
    // Información del árbol
    printf("Estadísticas del Árbol:\n");
    printf("  Total de estudiantes: %d\n", arbol_peso(arbol));
    printf("  Altura del árbol: %d\n", arbol_altura(arbol));
    printf("  Nodos hoja: %d\n\n", arbol_cantidad_hojas(arbol));
    
    // Alumno con menor matrícula
    Estudiante* primero = (Estudiante*) arbol_minimo(arbol);
    printf("Primer estudiante (menor matrícula): %s\n", primero->nombre);
    
    // Alumno con mayor matrícula
    Estudiante* ultimo = (Estudiante*) arbol_maximo(arbol);
    printf("Último estudiante (mayor matrícula): %s\n\n", ultimo->nombre);
    
    // Eliminar un estudiante
    Estudiante eliminar = {1003, "", 0, 0};
    printf("Eliminando estudiante con matrícula 1003...\n");
    if (arbol_eliminar(&arbol, &eliminar)) {
        printf("✓ Eliminado correctamente\n");
        printf("Nuevos estudiantes:\n");
        arbol_recorrido_inorden(arbol, imprimir_estudiante);
    }
    printf("\n");
    
    // Limpiar
    vaciar_arbol(&arbol);
    printf("✓ Árbol destruido\n");
    
    return 0;
}
```

### Salida Esperada

```
Insertando 7 estudiantes...

Estudiantes en orden de matrícula:
[Mat: 1001, Nombre: María García, Promedio: 9.20, Año: 1]
[Mat: 1002, Nombre: Laura Fernández, Promedio: 9.50, Año: 1]
[Mat: 1003, Nombre: Ana Martínez, Promedio: 9.00, Año: 1]
[Mat: 1004, Nombre: Roberto Díaz, Promedio: 8.30, Año: 2]
[Mat: 1005, Nombre: Juan Pérez, Promedio: 8.50, Año: 2]
[Mat: 1007, Nombre: David Sánchez, Promedio: 8.10, Año: 2]
[Mat: 1008, Nombre: Carlos López, Promedio: 7.80, Año: 3]

✓ Estudiante encontrado:
[Mat: 1005, Nombre: Juan Pérez, Promedio: 8.50, Año: 2]

Estadísticas del Árbol:
  Total de estudiantes: 7
  Altura del árbol: 3
  Nodos hoja: 2

Primer estudiante (menor matrícula): María García
Último estudiante (mayor matrícula): Carlos López

Eliminando estudiante con matrícula 1003...
✓ Eliminado correctamente
Nuevos estudiantes:
[Mat: 1001, Nombre: María García, Promedio: 9.20, Año: 1]
[Mat: 1002, Nombre: Laura Fernández, Promedio: 9.50, Año: 1]
[Mat: 1004, Nombre: Roberto Díaz, Promedio: 8.30, Año: 2]
[Mat: 1005, Nombre: Juan Pérez, Promedio: 8.50, Año: 2]
[Mat: 1007, Nombre: David Sánchez, Promedio: 8.10, Año: 2]
[Mat: 1008, Nombre: Carlos López, Promedio: 7.80, Año: 3]

✓ Árbol destruido
```

---

## Ejemplo 4: Árbol de Números Flotantes

### Código Completo

```c
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función de comparación para flotantes
int comparar_flotantes(const void* a, const void* b) {
    float val_a = *(float*) a;
    float val_b = *(float*) b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

// Función de impresión
void imprimir_flotante(const void* dato) {
    printf("%.2f ", *(float*) dato);
}

int main() {
    // Crear árbol de flotantes
    ArbolAVL arbol = crear_arbol(comparar_flotantes, NULL);
    
    if (arbol == NULL) {
        printf("Error al crear el árbol\n");
        return 1;
    }
    
    // Números flotantes a insertar
    float numeros[] = {3.14, 2.71, 1.41, 1.73, 2.23, 3.33, 1.23};
    int cantidad = 7;
    
    printf("Insertando números flotantes: ");
    for (int i = 0; i < cantidad; i++) {
        printf("%.2f ", numeros[i]);
        arbol_insertar(&arbol, &numeros[i], sizeof(float), 1);
    }
    printf("\n\n");
    
    // Recorrer ordenado
    printf("Números en orden: ");
    arbol_recorrido_inorden(arbol, imprimir_flotante);
    printf("\n\n");
    
    // Búsqueda
    float buscar = 2.71;
    if (arbol_buscar(arbol, &buscar)) {
        printf("✓ Número %.2f encontrado\n", buscar);
    }
    printf("\n");
    
    // Estadísticas
    printf("Mínimo: %.2f\n", *(float*) arbol_minimo(arbol));
    printf("Máximo: %.2f\n", *(float*) arbol_maximo(arbol));
    printf("Cantidad de números: %d\n\n", arbol_peso(arbol));
    
    // Limpiar
    vaciar_arbol(&arbol);
    
    return 0;
}
```

---

## Ejemplo 5: Casos Avanzados

### Uso Avanzado: Árbol con Destructor Personalizado

```c
// Estructura que necesita limpieza
typedef struct {
    int id;
    char* descripcion;  // Asignado dinámicamente
    int tamaño;
} Dato;

// Comparador
int comparar_datos(const void* a, const void* b) {
    return ((Dato*)a)->id - ((Dato*)b)->id;
}

// Destructor personalizado
void destruir_dato(void* d) {
    Dato* dato = (Dato*) d;
    if (dato->descripcion != NULL) {
        free(dato->descripcion);
    }
}

// Uso
int main() {
    ArbolAVL arbol = crear_arbol(comparar_datos, destruir_dato);
    
    // Crear dato con string dinámico
    Dato* d1 = malloc(sizeof(Dato));
    d1->id = 1;
    d1->descripcion = malloc(50);
    strcpy(d1->descripcion, "Primer elemento");
    d1->tamaño = strlen(d1->descripcion);
    
    // Insertar (con copydata=0 porque es complejo)
    arbol_insertar(&arbol, d1, sizeof(Dato), 0);
    
    // Al destruir, llamará a destruir_dato automáticamente
    vaciar_arbol(&arbol);
    
    return 0;
}
```

---

## Comparación de Complejidades

### Árbol AVL vs Otros

| Operación | Array Desordenado | Array Ordenado | BST Normal | Árbol AVL |
|-----------|------------------|-----------------|-----------|-----------|
| Búsqueda | O(n) | O(log n) | O(n) | **O(log n)** |
| Inserción | O(1) | O(n) | O(n) | **O(log n)** |
| Eliminación | O(n) | O(n) | O(n) | **O(log n)** |
| Espacio | O(n) | O(n) | O(n) | O(n) |

---

## Consejos de Uso

1. **Elija copydata=1** si los datos van a ser modificados después de insertar
2. **Elija copydata=0** si los datos son constantes o responsabilidad del usuario
3. **Proporcione destructor** si los datos contienen punteros internos
4. **Valide comparaciones** para evitar resultados inesperados
5. **Use valgrind** para verificar fugas de memoria en debug

---

*Última actualización: 2026-06-01*
