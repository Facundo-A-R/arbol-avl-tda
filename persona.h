/*
 * ============================================================================
 * ARCHIVO: persona.h
 * DESCRIPCIÓN: Interfaz (header) de la estructura Persona
 * 
 * Define la estructura Persona y las operaciones para manipularla.
 * Incluye funciones de getters, setters, comparación e impresión.
 * ============================================================================
 */

#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stdio.h>      // Para entrada/salida
#include <stdlib.h>     // Para memoria dinámica
#include <string.h>     // Para manejo de strings

/*
 * ============================================================================
 * ESTRUCTURA PERSONA
 * ============================================================================
 */

/*
 * Estructura Persona
 * Representa una persona con identificación única y datos personales
 * 
 * Campos:
 *  - id: Número identificador único de la persona
 *  - nombre: Nombre completo de la persona (máximo 99 caracteres)
 *  - edad: Edad actual de la persona en años
 */
typedef struct {
    int id;              // ID único (1 a 99999)
    char nombre[100];    // Nombre (máximo 99 caracteres + null terminator)
    int edad;            // Edad en años (0 a 150)
} Persona;

/*
 * ============================================================================
 * FUNCIONES DE CREACIÓN
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
 * 
 * Nota: La memoria retornada debe ser liberada con persona_destruir()
 */
Persona* persona_crear(int id, const char* nombre, int edad);

/*
 * Función: persona_destruir
 * Descripción: Libera la memoria de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona a destruir
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int persona_destruir(Persona* p);

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
 * Retorna: ID de la persona
 */
int persona_obtener_id(const Persona* p);

/*
 * Función: persona_obtener_nombre
 * Descripción: Obtiene el nombre de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona
 * 
 * Retorna: Puntero al nombre (string constante)
 */
const char* persona_obtener_nombre(const Persona* p);

/*
 * Función: persona_obtener_edad
 * Descripción: Obtiene la edad de una persona
 * 
 * Parámetro:
 *  - p: Puntero a la persona
 * 
 * Retorna: Edad de la persona en años
 */
int persona_obtener_edad(const Persona* p);

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
int persona_establecer_id(Persona* p, int id);

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
int persona_establecer_nombre(Persona* p, const char* nombre);

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
int persona_establecer_edad(Persona* p, int edad);

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
void persona_imprimir(const Persona* p);

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
int persona_comparar(const Persona* p1, const Persona* p2);

/*
 * Función: persona_es_valida
 * Descripción: Verifica si los datos de una persona son válidos
 * 
 * Parámetro:
 *  - p: Puntero a la persona a validar
 * 
 * Retorna: 1 si es válida, 0 si no
 */
int persona_es_valida(const Persona* p);

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
int persona_copiar(const Persona* origen, Persona* destino);

#endif // __PERSONA_H__
