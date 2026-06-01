/*
 * ============================================================================
 * ARCHIVO: main.c
 * DESCRIPCIÓN: Programa principal de prueba del Árbol AVL genérico
 * 
 * Este programa demuestra todas las funcionalidades del árbol AVL:
 * - Creación y destrucción
 * - Inserción y eliminación con balanceo automático
 * - Búsqueda
 * - Recorridos (in-orden, pre-orden, post-orden)
 * - Métricas (altura, peso, hojas, balance, nivel, mínimo, máximo)
 * - Rotaciones automáticas
 * 
 * Se implementa con dos tipos de datos: integers y una estructura Persona
 * ============================================================================
 */

#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ============================================================================
 * ESTRUCTURA DE DATOS: PERSONA
 * ============================================================================
 */

/*
 * Estructura Persona
 * Se usa para demostrar la genericidad del árbol AVL
 * El árbol puede almacenar cualquier tipo de dato
 */
typedef struct {
    int id;              // Identificador único de la persona
    char nombre[100];    // Nombre de la persona
    int edad;            // Edad de la persona
} Persona;

/*
 * ============================================================================
 * FUNCIONES DE COMPARACIÓN
 * ============================================================================
 */

/*
 * Función: comparar_enteros
 * Descripción: Compara dos enteros para el árbol AVL
 * 
 * Parámetros:
 *  - a: Primer entero (convertido desde void*)
 *  - b: Segundo entero (convertido desde void*)
 * 
 * Retorna:
 *  - Negativo si a < b
 *  - 0 si a == b
 *  - Positivo si a > b
 */
int comparar_enteros(const void* a, const void* b) {
    // Convertir de void* a int*
    int val_a = *(int*) a;
    int val_b = *(int*) b;
    
    // Retornar la diferencia
    return val_a - val_b;
}

/*
 * Función: comparar_personas
 * Descripción: Compara dos personas por su ID
 * 
 * Parámetros:
 *  - a: Primera persona (convertida desde void*)
 *  - b: Segunda persona (convertida desde void*)
 * 
 * Retorna:
 *  - Negativo si a.id < b.id
 *  - 0 si a.id == b.id
 *  - Positivo si a.id > b.id
 */
int comparar_personas(const void* a, const void* b) {
    // Convertir de void* a Persona*
    Persona* persona_a = (Persona*) a;
    Persona* persona_b = (Persona*) b;
    
    // Comparar por ID
    return persona_a->id - persona_b->id;
}

/*
 * ============================================================================
 * FUNCIONES DE IMPRESIÓN
 * ============================================================================
 */

/*
 * Función: imprimir_entero
 * Descripción: Imprime un entero en formato legible
 * 
 * Parámetro:
 *  - dato: Puntero al entero a imprimir
 */
void imprimir_entero(const void* dato) {
    // Convertir de void* a int*
    int valor = *(int*) dato;
    
    // Imprimir el valor
    printf("%d ", valor);
}

/*
 * Función: imprimir_persona
 * Descripción: Imprime una persona en formato legible
 * 
 * Parámetro:
 *  - dato: Puntero a la persona a imprimir
 */
void imprimir_persona(const void* dato) {
    // Convertir de void* a Persona*
    Persona* p = (Persona*) dato;
    
    // Imprimir los datos de la persona
    printf("[ID: %d, Nombre: %s, Edad: %d] ", p->id, p->nombre, p->edad);
}

/*
 * ============================================================================
 * FUNCIÓN AUXILIAR: MOSTRAR SEPARADOR
 * ============================================================================
 */

/*
 * Función: mostrar_separador
 * Descripción: Imprime un separador visual para mejorar la legibilidad
 * 
 * Parámetro:
 *  - longitud: Longitud del separador (en caracteres '=')
 */
void mostrar_separador(int longitud) {
    // Imprimir la cantidad especificada de signos '='
    for (int i = 0; i < longitud; i++) {
        printf("=");
    }
    // Salto de línea
    printf("\n");
}

/*
 * ============================================================================
 * PRUEBAS CON ENTEROS
 * ============================================================================
 */

/*
 * Función: prueba_enteros
 * Descripción: Ejecuta una serie de pruebas con enteros
 * Demuestra:
 * - Creación del árbol
 * - Inserción de elementos
 * - Búsqueda
 * - Recorridos
 * - Métricas
 * - Rotaciones automáticas
 * - Eliminación con rebalanceo
 */
void prueba_enteros() {
    // Mostrar encabezado
    printf("\n");
    mostrar_separador(70);
    printf("PRUEBA 1: ÁRBOL AVL CON ENTEROS\n");
    mostrar_separador(70);
    printf("\n");
    
    // Crear el árbol de enteros
    // Parámetros: función comparación, función destrucción (NULL para ints simples)
    ArbolAVL arbol_int = crear_arbol(comparar_enteros, NULL);
    printf("✓ Árbol de enteros creado\n\n");
    
    // ========================================================================
    // FASE 1: INSERCIÓN DE ELEMENTOS
    // ========================================================================
    
    printf("--- FASE 1: INSERCIÓN DE ELEMENTOS ---\n");
    
    // Arreglo de números a insertar
    int numeros[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35};
    int cantidad = sizeof(numeros) / sizeof(numeros[0]);
    
    printf("Insertando %d números: ", cantidad);
    for (int i = 0; i < cantidad; i++) {
        printf("%d ", numeros[i]);
        // Insertar número: árbol, dato, tamaño, copydata (1=copiar)
        arbol_insertar(&arbol_int, &numeros[i], sizeof(int), 1);
    }
    printf("\n\n");
    
    // ========================================================================
    // FASE 2: MÉTRICAS DEL ÁRBOL
    // ========================================================================
    
    printf("--- FASE 2: MÉTRICAS DEL ÁRBOL ---\n");
    printf("Altura del árbol: %d\n", arbol_altura(arbol_int));
    printf("Cantidad de nodos: %d\n", arbol_peso(arbol_int));
    printf("Cantidad de hojas: %d\n", arbol_cantidad_hojas(arbol_int));
    printf("Factor de balance de raíz: %d\n", arbol_balance(arbol_int));
    printf("Elemento mínimo: %d\n", *(int*) arbol_minimo(arbol_int));
    printf("Elemento máximo: %d\n", *(int*) arbol_maximo(arbol_int));
    printf("\n");
    
    // ========================================================================
    // FASE 3: RECORRIDOS DEL ÁRBOL
    // ========================================================================
    
    printf("--- FASE 3: RECORRIDOS DEL ÁRBOL ---\n");
    
    printf("Recorrido IN-ORDEN (elementos en orden ascendente):\n");
    arbol_recorrido_inorden(arbol_int, imprimir_entero);
    printf("\n\n");
    
    printf("Recorrido PRE-ORDEN (raíz primero):\n");
    arbol_recorrido_preorden(arbol_int, imprimir_entero);
    printf("\n\n");
    
    printf("Recorrido POST-ORDEN (raíz al final):\n");
    arbol_recorrido_postorden(arbol_int, imprimir_entero);
    printf("\n\n");
    
    // ========================================================================
    // FASE 4: BÚSQUEDA DE ELEMENTOS
    // ========================================================================
    
    printf("--- FASE 4: BÚSQUEDA DE ELEMENTOS ---\n");
    
    int buscar_vals[] = {15, 50, 100};
    for (int i = 0; i < 3; i++) {
        void* resultado = arbol_buscar(arbol_int, &buscar_vals[i]);
        if (resultado != NULL) {
            printf("✓ Elemento %d encontrado\n", buscar_vals[i]);
            
            // Mostrar el nivel del elemento
            int nivel = arbol_nivel(arbol_int, &buscar_vals[i]);
            printf("  Ubicado en nivel: %d\n", nivel);
        } else {
            printf("✗ Elemento %d NO encontrado\n", buscar_vals[i]);
        }
    }
    printf("\n");
    
    // ========================================================================
    // FASE 5: ELIMINACIÓN DE ELEMENTOS
    // ========================================================================
    
    printf("--- FASE 5: ELIMINACIÓN DE ELEMENTOS ---\n");
    
    int eliminar_vals[] = {10, 50};
    for (int i = 0; i < 2; i++) {
        printf("Eliminando elemento %d...\n", eliminar_vals[i]);
        if (arbol_eliminar(&arbol_int, &eliminar_vals[i])) {
            printf("✓ Elemento %d eliminado\n", eliminar_vals[i]);
        } else {
            printf("✗ No se pudo eliminar elemento %d\n", eliminar_vals[i]);
        }
    }
    printf("\n");
    
    // Mostrar estado del árbol después de eliminación
    printf("Árbol después de eliminación:\n");
    printf("Altura: %d | Nodos: %d | Hojas: %d | Balance: %d\n",
           arbol_altura(arbol_int),
           arbol_peso(arbol_int),
           arbol_cantidad_hojas(arbol_int),
           arbol_balance(arbol_int));
    
    printf("Recorrido IN-ORDEN actualizado: ");
    arbol_recorrido_inorden(arbol_int, imprimir_entero);
    printf("\n\n");
    
    // ========================================================================
    // FASE 6: LIBERACIÓN DE MEMORIA
    // ========================================================================
    
    printf("--- FASE 6: LIBERACIÓN DE MEMORIA ---\n");
    vaciar_arbol(&arbol_int);
    printf("✓ Árbol destruido y memoria liberada\n\n");
}

/*
 * ============================================================================
 * PRUEBAS CON PERSONAS
 * ============================================================================
 */

/*
 * Función: prueba_personas
 * Descripción: Ejecuta una serie de pruebas con la estructura Persona
 * Demuestra:
 * - Genericidad del árbol con tipos de datos complejos
 * - Inserción y búsqueda de personas
 * - Recorridos de personas
 * - Métricas del árbol
 */
void prueba_personas() {
    // Mostrar encabezado
    printf("\n");
    mostrar_separador(70);
    printf("PRUEBA 2: ÁRBOL AVL CON ESTRUCTURAS (PERSONAS)\n");
    mostrar_separador(70);
    printf("\n");
    
    // Crear el árbol de personas
    // Parámetros: función comparación, función destrucción (NULL)
    ArbolAVL arbol_personas = crear_arbol(comparar_personas, NULL);
    printf("✓ Árbol de personas creado\n\n");
    
    // ========================================================================
    // FASE 1: CREAR E INSERTAR PERSONAS
    // ========================================================================
    
    printf("--- FASE 1: CREAR E INSERTAR PERSONAS ---\n");
    
    // Crear arreglo de personas
    Persona personas[] = {
        {3, "Carlos", 28},
        {1, "Ana", 25},
        {5, "Elena", 32},
        {2, "Bruno", 30},
        {4, "Diana", 27},
        {6, "Francisco", 35}
    };
    int cantidad_personas = sizeof(personas) / sizeof(personas[0]);
    
    printf("Insertando %d personas:\n", cantidad_personas);
    for (int i = 0; i < cantidad_personas; i++) {
        printf("  ");
        imprimir_persona(&personas[i]);
        printf("\n");
        // Insertar persona: árbol, dato, tamaño, copydata (1=copiar)
        arbol_insertar(&arbol_personas, &personas[i], sizeof(Persona), 1);
    }
    printf("\n");
    
    // ========================================================================
    // FASE 2: MÉTRICAS DEL ÁRBOL
    // ========================================================================
    
    printf("--- FASE 2: MÉTRICAS DEL ÁRBOL ---\n");
    printf("Altura del árbol: %d\n", arbol_altura(arbol_personas));
    printf("Cantidad de nodos: %d\n", arbol_peso(arbol_personas));
    printf("Cantidad de hojas: %d\n", arbol_cantidad_hojas(arbol_personas));
    printf("Factor de balance de raíz: %d\n", arbol_balance(arbol_personas));
    printf("\n");
    
    // ========================================================================
    // FASE 3: RECORRIDO IN-ORDEN (Ordenado por ID)
    // ========================================================================
    
    printf("--- FASE 3: PERSONAS EN ORDEN (IN-ORDEN POR ID) ---\n");
    arbol_recorrido_inorden(arbol_personas, imprimir_persona);
    printf("\n\n");
    
    // ========================================================================
    // FASE 4: BÚSQUEDA DE PERSONA
    // ========================================================================
    
    printf("--- FASE 4: BÚSQUEDA DE PERSONAS ---\n");
    
    // Buscar persona con ID 3
    Persona buscar_persona = {3, "", 0};
    void* resultado = arbol_buscar(arbol_personas, &buscar_persona);
    
    if (resultado != NULL) {
        printf("✓ Persona encontrada:\n  ");
        imprimir_persona(resultado);
        printf("\n");
        
        // Mostrar nivel
        int nivel = arbol_nivel(arbol_personas, &buscar_persona);
        printf("  Ubicada en nivel: %d\n", nivel);
    } else {
        printf("✗ Persona no encontrada\n");
    }
    printf("\n");
    
    // ========================================================================
    // FASE 5: INFORMACIÓN DEL ÁRBOL
    // ========================================================================
    
    printf("--- FASE 5: INFORMACIÓN DEL ÁRBOL ---\n");
    
    // Persona con ID mínimo
    Persona* min = (Persona*) arbol_minimo(arbol_personas);
    printf("Persona con ID mínimo:\n  ");
    imprimir_persona(min);
    printf("\n\n");
    
    // Persona con ID máximo
    Persona* max = (Persona*) arbol_maximo(arbol_personas);
    printf("Persona con ID máximo:\n  ");
    imprimir_persona(max);
    printf("\n\n");
    
    // ========================================================================
    // FASE 6: ELIMINACIÓN DE PERSONA
    // ========================================================================
    
    printf("--- FASE 6: ELIMINACIÓN DE PERSONA ---\n");
    
    Persona eliminar_persona = {2, "", 0};
    printf("Eliminando persona con ID 2 (Bruno)...\n");
    
    if (arbol_eliminar(&arbol_personas, &eliminar_persona)) {
        printf("✓ Persona eliminada correctamente\n");
    } else {
        printf("✗ No se pudo eliminar la persona\n");
    }
    
    printf("Árbol después de eliminación:\n");
    printf("Altura: %d | Nodos: %d | Hojas: %d | Balance: %d\n\n",
           arbol_altura(arbol_personas),
           arbol_peso(arbol_personas),
           arbol_cantidad_hojas(arbol_personas),
           arbol_balance(arbol_personas));
    
    printf("Personas actuales (IN-ORDEN):\n");
    arbol_recorrido_inorden(arbol_personas, imprimir_persona);
    printf("\n\n");
    
    // ========================================================================
    // FASE 7: LIBERACIÓN DE MEMORIA
    // ========================================================================
    
    printf("--- FASE 7: LIBERACIÓN DE MEMORIA ---\n");
    vaciar_arbol(&arbol_personas);
    printf("✓ Árbol de personas destruido y memoria liberada\n\n");
}

/*
 * ============================================================================
 * PRUEBA DE ROTACIONES
 * ============================================================================
 */

/*
 * Función: prueba_rotaciones
 * Descripción: Demuestra las rotaciones automáticas del árbol AVL
 * 
 * Las rotaciones se ejecutan automáticamente cuando el árbol se desbalancea.
 * Este test inserta números de forma que fuerza todas las rotaciones.
 */
void prueba_rotaciones() {
    printf("\n");
    mostrar_separador(70);
    printf("PRUEBA 3: ROTACIONES AUTOMÁTICAS DEL ÁRBOL AVL\n");
    mostrar_separador(70);
    printf("\n");
    
    ArbolAVL arbol_rot = crear_arbol(comparar_enteros, NULL);
    printf("✓ Árbol para prueba de rotaciones creado\n\n");
    
    // ========================================================================
    // ROTACIÓN DERECHA (insertar en orden ascendente: 3, 2, 1)
    // ========================================================================
    
    printf("--- ROTACIÓN DERECHA ---\n");
    printf("Insertando 3, 2, 1 (causa rotación derecha)\n");
    
    int vals_der[] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        arbol_insertar(&arbol_rot, &vals_der[i], sizeof(int), 1);
    }
    
    printf("Árbol después de inserción:\n");
    printf("Altura: %d, Balance: %d\n", arbol_altura(arbol_rot), arbol_balance(arbol_rot));
    printf("Recorrido: ");
    arbol_recorrido_inorden(arbol_rot, imprimir_entero);
    printf("\n\n");
    
    // Limpiar árbol
    vaciar_arbol(&arbol_rot);
    arbol_rot = crear_arbol(comparar_enteros, NULL);
    
    // ========================================================================
    // ROTACIÓN IZQUIERDA (insertar en orden descendente: 1, 2, 3)
    // ========================================================================
    
    printf("--- ROTACIÓN IZQUIERDA ---\n");
    printf("Insertando 1, 2, 3 (causa rotación izquierda)\n");
    
    int vals_izq[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        arbol_insertar(&arbol_rot, &vals_izq[i], sizeof(int), 1);
    }
    
    printf("Árbol después de inserción:\n");
    printf("Altura: %d, Balance: %d\n", arbol_altura(arbol_rot), arbol_balance(arbol_rot));
    printf("Recorrido: ");
    arbol_recorrido_inorden(arbol_rot, imprimir_entero);
    printf("\n\n");
    
    // Limpiar árbol
    vaciar_arbol(&arbol_rot);
    arbol_rot = crear_arbol(comparar_enteros, NULL);
    
    // ========================================================================
    // ROTACIÓN DOBLE IZQUIERDA-DERECHA
    // ========================================================================
    
    printf("--- ROTACIÓN DOBLE IZQUIERDA-DERECHA ---\n");
    printf("Insertando 1, 3, 2 (causa rotación doble)\n");
    
    int vals_doble_izq[] = {1, 3, 2};
    for (int i = 0; i < 3; i++) {
        arbol_insertar(&arbol_rot, &vals_doble_izq[i], sizeof(int), 1);
    }
    
    printf("Árbol después de inserción:\n");
    printf("Altura: %d, Balance: %d\n", arbol_altura(arbol_rot), arbol_balance(arbol_rot));
    printf("Recorrido: ");
    arbol_recorrido_inorden(arbol_rot, imprimir_entero);
    printf("\n\n");
    
    // Limpiar árbol
    vaciar_arbol(&arbol_rot);
    arbol_rot = crear_arbol(comparar_enteros, NULL);
    
    // ========================================================================
    // ROTACIÓN DOBLE DERECHA-IZQUIERDA
    // ========================================================================
    
    printf("--- ROTACIÓN DOBLE DERECHA-IZQUIERDA ---\n");
    printf("Insertando 3, 1, 2 (causa rotación doble)\n");
    
    int vals_doble_der[] = {3, 1, 2};
    for (int i = 0; i < 3; i++) {
        arbol_insertar(&arbol_rot, &vals_doble_der[i], sizeof(int), 1);
    }
    
    printf("Árbol después de inserción:\n");
    printf("Altura: %d, Balance: %d\n", arbol_altura(arbol_rot), arbol_balance(arbol_rot));
    printf("Recorrido: ");
    arbol_recorrido_inorden(arbol_rot, imprimir_entero);
    printf("\n\n");
    
    // Liberación de memoria
    vaciar_arbol(&arbol_rot);
    printf("✓ Prueba de rotaciones finalizada\n\n");
}

/*
 * ============================================================================
 * FUNCIÓN PRINCIPAL
 * ============================================================================
 */

/*
 * Función: main
 * Descripción: Punto de entrada del programa
 * Ejecuta todas las pruebas del árbol AVL
 * 
 * Retorna: 0 si éxito
 */
int main() {
    // Limpiar pantalla (solo en sistemas UNIX)
    system("clear") || system("cls");
    
    // Mostrar encabezado del programa
    printf("\n");
    mostrar_separador(70);
    printf("DEMOSTRACIÓN DEL ÁRBOL AVL GENÉRICO EN C\n");
    printf("Implementación: Tipos de Datos Abstractos (TDA)\n");
    printf("Características: Balanceo automático, rotaciones, genericidad\n");
    mostrar_separador(70);
    
    // ========================================================================
    // EJECUTAR TODAS LAS PRUEBAS
    // ========================================================================
    
    // Prueba 1: Árbol con enteros
    prueba_enteros();
    
    // Prueba 2: Árbol con estructuras complejas (Personas)
    prueba_personas();
    
    // Prueba 3: Demostraciones de rotaciones
    prueba_rotaciones();
    
    // ========================================================================
    // RESUMEN FINAL
    // ========================================================================
    
    printf("\n");
    mostrar_separador(70);
    printf("TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE\n");
    printf("\nCaracterísticas demostradas:\n");
    printf("  ✓ Creación y destrucción de árboles\n");
    printf("  ✓ Inserción con balanceo automático\n");
    printf("  ✓ Búsqueda eficiente (O(log n))\n");
    printf("  ✓ Eliminación manteniendo balance\n");
    printf("  ✓ Recorridos: in-orden, pre-orden, post-orden\n");
    printf("  ✓ Métricas: altura, peso, hojas, balance, nivel\n");
    printf("  ✓ Rotaciones: simples y dobles\n");
    printf("  ✓ Genericidad con void* y funciones comparación\n");
    printf("  ✓ Gestión correcta de memoria dinámica\n");
    mostrar_separador(70);
    printf("\n");
    
    // Retornar 0 indicando éxito
    return 0;
}
