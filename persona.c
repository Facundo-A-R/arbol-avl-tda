/*
 * ============================================================================
 * ARCHIVO: persona.c
 * DESCRIPCIÓN: Implementación de la estructura Persona
 * 
 * Contiene la implementación de todas las funciones definidas en persona.h
 * incluyendo getters, setters, validación e impresión.
 * ============================================================================
 */

#include "persona.h"

/*
 * ============================================================================
 * FUNCIONES DE CREACIÓN Y DESTRUCCIÓN
 * ============================================================================
 */

/*
 * Función: persona_crear
 * Descripción: Crea una nueva persona e inicializa sus campos
 * 
 * Parámetros:
 *  - id: Identificador único de la persona
 *  - nombre: Nombre de la persona (string)
 *  - edad: Edad de la persona en años
 * 
 * Retorna: Puntero a la nueva persona (asignada dinámicamente)
 *          NULL si hay error de memoria
 */
Persona* persona_crear(int id, const char* nombre, int edad) {
    // Validar que el nombre no sea NULL
    if (nombre == NULL) {
        printf("Error: nombre NULL en persona_crear\n");
        return NULL;
    }
    
    // Asignar memoria para la nueva persona
    Persona* p = (Persona*) malloc(sizeof(Persona));
    
    // Si no hay memoria disponible, retornar NULL
    if (p == NULL) {
        printf("Error: No hay memoria para crear persona\n");
        return NULL;
    }
    
    // Inicializar los campos de la persona
    p->id = id;
    
    // Copiar el nombre (máximo 99 caracteres)
    strncpy(p->nombre, nombre, 99);
    // Asegurar que el string termine con null terminator
    p->nombre[99] = '\0';
    
    // Establecer la edad
    p->edad = edad;
    
    // Retornar la persona creada
    return p;
}

/*
 * Función: persona_destruir
 * Descripción: Libera la memoria de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona a destruir
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_destruir(Persona* p) {
    // Si el puntero es NULL, no hay nada que destruir
    if (p == NULL) {
        return 0;
    }
    
    // Liberar la memoria asignada
    free(p);
    
    // Retornar 1 indicando éxito
    return 1;
}

/*
 * ============================================================================
 * FUNCIONES GETTER (Obtener valores)
 * ============================================================================
 */

/*
 * Función: persona_obtener_id
 * Descripción: Obtiene el ID de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona
 * 
 * Retorna: ID de la persona (0 si p es NULL)
 */
int persona_obtener_id(const Persona* p) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_obtener_id\n");
        return 0;
    }
    
    // Retornar el ID
    return p->id;
}

/*
 * Función: persona_obtener_nombre
 * Descripción: Obtiene el nombre de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona
 * 
 * Retorna: Puntero al nombre (string constante)
 *          NULL si p es NULL
 */
const char* persona_obtener_nombre(const Persona* p) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_obtener_nombre\n");
        return NULL;
    }
    
    // Retornar el nombre
    return p->nombre;
}

/*
 * Función: persona_obtener_edad
 * Descripción: Obtiene la edad de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona
 * 
 * Retorna: Edad de la persona en años (0 si p es NULL)
 */
int persona_obtener_edad(const Persona* p) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_obtener_edad\n");
        return 0;
    }
    
    // Retornar la edad
    return p->edad;
}

/*
 * ============================================================================
 * FUNCIONES SETTER (Establecer valores)
 * ============================================================================
 */

/*
 * Función: persona_establecer_id
 * Descripción: Establece el ID de una persona
 * 
 * Parámetros:
 *  - p: Puntero a la persona a modificar
 *  - id: Nuevo ID a asignar
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_establecer_id(Persona* p, int id) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_establecer_id\n");
        return 0;
    }
    
    // Validar que el ID sea positivo
    if (id <= 0) {
        printf("Error: ID debe ser positivo (recibido: %d)\n", id);
        return 0;
    }
    
    // Establecer el nuevo ID
    p->id = id;
    
    // Retornar 1 indicando éxito
    return 1;
}

/*
 * Función: persona_establecer_nombre
 * Descripción: Establece el nombre de una persona
 * 
 * Parámetros:
 *  - p: Puntero a la persona a modificar
 *  - nombre: Nuevo nombre a asignar
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_establecer_nombre(Persona* p, const char* nombre) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_establecer_nombre\n");
        return 0;
    }
    
    // Validar que el nombre no sea NULL
    if (nombre == NULL) {
        printf("Error: nombre NULL en persona_establecer_nombre\n");
        return 0;
    }
    
    // Validar que el nombre no esté vacío
    if (strlen(nombre) == 0) {
        printf("Error: nombre vacío en persona_establecer_nombre\n");
        return 0;
    }
    
    // Copiar el nuevo nombre (máximo 99 caracteres)
    strncpy(p->nombre, nombre, 99);
    
    // Asegurar que el string termine con null terminator
    p->nombre[99] = '\0';
    
    // Retornar 1 indicando éxito
    return 1;
}

/*
 * Función: persona_establecer_edad
 * Descripción: Establece la edad de una persona
 * 
 * Parámetros:
 *  - p: Puntero a la persona a modificar
 *  - edad: Nueva edad a asignar
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_establecer_edad(Persona* p, int edad) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_establecer_edad\n");
        return 0;
    }
    
    // Validar que la edad esté en rango válido (0 a 150 años)
    if (edad < 0 || edad > 150) {
        printf("Error: edad fuera de rango (recibido: %d, rango: 0-150)\n", edad);
        return 0;
    }
    
    // Establecer la nueva edad
    p->edad = edad;
    
    // Retornar 1 indicando éxito
    return 1;
}

/*
 * ============================================================================
 * FUNCIONES DE UTILIDAD
 * ============================================================================
 */

/*
 * Función: persona_imprimir
 * Descripción: Imprime los datos de una persona en formato legible
 * 
 * Parámetro:
 *  - p: Puntero a la persona a imprimir
 */
void persona_imprimir(const Persona* p) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_imprimir\n");
        return;
    }
    
    // Imprimir los datos en formato: ID | Nombre | Edad
    printf("[ID: %5d | Nombre: %-30s | Edad: %3d años]\n",
           p->id, p->nombre, p->edad);
}

/*
 * Función: persona_comparar
 * Descripción: Compara dos personas por su ID
 * Útil para usar con el árbol AVL
 * 
 * Parámetros:
 *  - p1: Primera persona a comparar
 *  - p2: Segunda persona a comparar
 * 
 * Retorna:
 *  - Negativo si p1->id < p2->id
 *  - 0 si p1->id == p2->id
 *  - Positivo si p1->id > p2->id
 */
int persona_comparar(const Persona* p1, const Persona* p2) {
    // Validar que ambas personas no sean NULL
    if (p1 == NULL || p2 == NULL) {
        printf("Error: persona NULL en persona_comparar\n");
        return 0;
    }
    
    // Comparar por ID (resto de p1->id - p2->id)
    return p1->id - p2->id;
}

/*
 * Función: persona_es_valida
 * Descripción: Verifica si los datos de una persona son válidos
 * 
 * Validaciones:
 *  - ID debe ser positivo
 *  - Nombre no debe estar vacío
 *  - Edad debe estar entre 0 y 150
 * 
 * Parámetro:
 *  - p: Puntero a la persona a validar
 * 
 * Retorna: 1 si es válida, 0 si no
 */
int persona_es_valida(const Persona* p) {
    // Validar que la persona no sea NULL
    if (p == NULL) {
        printf("Error: persona NULL en persona_es_valida\n");
        return 0;
    }
    
    // Validar que el ID sea positivo
    if (p->id <= 0) {
        printf("Error de validación: ID debe ser positivo (actual: %d)\n", p->id);
        return 0;
    }
    
    // Validar que el nombre no esté vacío
    if (strlen(p->nombre) == 0) {
        printf("Error de validación: nombre no puede estar vacío\n");
        return 0;
    }
    
    // Validar que la edad esté en rango válido
    if (p->edad < 0 || p->edad > 150) {
        printf("Error de validación: edad fuera de rango (actual: %d, rango: 0-150)\n", p->edad);
        return 0;
    }
    
    // Si todas las validaciones pasaron, la persona es válida
    return 1;
}

/*
 * Función: persona_copiar
 * Descripción: Copia todos los datos de una persona a otra
 * 
 * Parámetros:
 *  - origen: Persona de la cual copiar datos
 *  - destino: Persona donde copiar los datos
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_copiar(const Persona* origen, Persona* destino) {
    // Validar que ambas personas no sean NULL
    if (origen == NULL || destino == NULL) {
        printf("Error: persona NULL en persona_copiar\n");
        return 0;
    }
    
    // Copiar el ID
    destino->id = origen->id;
    
    // Copiar el nombre
    strncpy(destino->nombre, origen->nombre, 99);
    destino->nombre[99] = '\0';
    
    // Copiar la edad
    destino->edad = origen->edad;
    
    // Retornar 1 indicando éxito
    return 1;
}
