/*
 * ============================================================================
 * ARCHIVO: arbol.h
 * DESCRIPCIÓN: Interfaz (header) del Árbol AVL con soporte genérico (void*)
 * 
 * Este archivo define la estructura y las operaciones del Árbol AVL.
 * Utiliza void* para permitir almacenar cualquier tipo de dato.
 * Las funciones de comparación deben ser proporcionadas por el usuario.
 * ============================================================================
 */

#ifndef __ARBOL_H__
#define __ARBOL_H__

#include <stdio.h>      // Librerías estándar para entrada/salida
#include <stdlib.h>     // Librerías para memoria dinámica
#include <string.h>     // Para manejo de strings

/*
 * ============================================================================
 * TIPOS Y DEFINICIONES
 * ============================================================================
 */

/* Estructura opaca del nodo del árbol (oculta la implementación) */
typedef struct NodoAVL* ArbolAVL;

/*
 * Tipo de función para comparación de elementos genéricos
 * 
 * Parámetros:
 *  - dato1: Primer elemento a comparar
 *  - dato2: Segundo elemento a comparar
 * 
 * Retorna:
 *  - < 0 si dato1 < dato2
 *  - 0 si dato1 == dato2
 *  - > 0 si dato1 > dato2
 */
typedef int (*FuncionComparacion)(const void* dato1, const void* dato2);

/*
 * Tipo de función para destruir/liberar memoria de un elemento
 * 
 * Parámetro:
 *  - dato: Puntero al elemento a liberar
 */
typedef void (*FuncionDestructor)(void* dato);

/*
 * Tipo de función para imprimir un elemento
 * 
 * Parámetro:
 *  - dato: Puntero al elemento a imprimir
 */
typedef void (*FuncionImpresion)(const void* dato);

/*
 * ============================================================================
 * OPERACIONES BÁSICAS
 * ============================================================================
 */

/*
 * Función: crear_arbol
 * Descripción: Crea un árbol AVL vacío
 * 
 * Parámetros:
 *  - comparar: Función de comparación entre elementos
 *  - destructor: Función para liberar memoria de elementos (puede ser NULL)
 * 
 * Retorna: Puntero al árbol creado
 */
ArbolAVL crear_arbol(FuncionComparacion comparar, FuncionDestructor destructor);

/*
 * Función: vaciar_arbol
 * Descripción: Libera toda la memoria del árbol y lo deja vacío
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol a vaciar
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int vaciar_arbol(ArbolAVL* arbol);

/*
 * ============================================================================
 * OPERACIONES DE INSERCIÓN Y ELIMINACIÓN
 * ============================================================================
 */

/*
 * Función: arbol_insertar
 * Descripción: Inserta un nuevo elemento en el árbol manteniendo el balance AVL
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol
 *  - dato: Dato a insertar (será copiado si copydata es true)
 *  - tamaño: Tamaño del dato en bytes
 *  - copydata: 1 si copiar el dato, 0 si solo guardar el puntero
 * 
 * Retorna: 1 si éxito, 0 si error (elemento duplicado o memoria insuficiente)
 */
int arbol_insertar(ArbolAVL* arbol, const void* dato, size_t tamaño, int copydata);

/*
 * Función: arbol_eliminar
 * Descripción: Elimina un elemento del árbol manteniendo el balance AVL
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol
 *  - dato: Dato a eliminar
 * 
 * Retorna: 1 si se eliminó, 0 si no encontrado
 */
int arbol_eliminar(ArbolAVL* arbol, const void* dato);

/*
 * ============================================================================
 * OPERACIONES DE BÚSQUEDA
 * ============================================================================
 */

/*
 * Función: arbol_buscar
 * Descripción: Busca un elemento en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 *  - dato: Dato a buscar
 * 
 * Retorna: Puntero al dato encontrado, NULL si no existe
 */
void* arbol_buscar(ArbolAVL arbol, const void* dato);

/*
 * ============================================================================
 * OPERACIONES DE RECORRIDO
 * ============================================================================
 */

/*
 * Función: arbol_recorrido_inorden
 * Descripción: Realiza un recorrido in-orden del árbol (izq-raíz-der)
 * Imprime los elementos en orden ascendente
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_inorden(ArbolAVL arbol, FuncionImpresion imprimir);

/*
 * Función: arbol_recorrido_preorden
 * Descripción: Realiza un recorrido pre-orden del árbol (raíz-izq-der)
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_preorden(ArbolAVL arbol, FuncionImpresion imprimir);

/*
 * Función: arbol_recorrido_postorden
 * Descripción: Realiza un recorrido post-orden del árbol (izq-der-raíz)
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_postorden(ArbolAVL arbol, FuncionImpresion imprimir);

/*
 * ============================================================================
 * OPERACIONES DE MÉTRICAS Y PROPIEDADES
 * ============================================================================
 */

/*
 * Función: arbol_altura
 * Descripción: Calcula la altura del árbol
 * La altura de un árbol vacío es 0
 * 
 * Parámetros:
 *  - arbol: Árbol a medir
 * 
 * Retorna: Altura del árbol
 */
int arbol_altura(ArbolAVL arbol);

/*
 * Función: arbol_peso
 * Descripción: Calcula la cantidad total de nodos en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a contar
 * 
 * Retorna: Cantidad de nodos
 */
int arbol_peso(ArbolAVL arbol);

/*
 * Función: arbol_cantidad_hojas
 * Descripción: Cuenta la cantidad de hojas (nodos sin hijos) en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a contar
 * 
 * Retorna: Cantidad de hojas
 */
int arbol_cantidad_hojas(ArbolAVL arbol);

/*
 * Función: arbol_balance
 * Descripción: Calcula el factor de balance de un nodo
 * Factor de balance = altura_derecha - altura_izquierda
 * 
 * Parámetros:
 *  - arbol: Nodo a evaluar
 * 
 * Retorna: Factor de balance (-2 a 2 en un AVL balanceado)
 */
int arbol_balance(ArbolAVL arbol);

/*
 * Función: arbol_nivel
 * Descripción: Encuentra el nivel de un elemento en el árbol
 * La raíz está en nivel 0
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 *  - dato: Elemento a localizar
 * 
 * Retorna: Nivel del elemento, -1 si no encontrado
 */
int arbol_nivel(ArbolAVL arbol, const void* dato);

/*
 * Función: arbol_minimo
 * Descripción: Obtiene el elemento mínimo del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 * 
 * Retorna: Puntero al elemento mínimo, NULL si árbol vacío
 */
void* arbol_minimo(ArbolAVL arbol);

/*
 * Función: arbol_maximo
 * Descripción: Obtiene el elemento máximo del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 * 
 * Retorna: Puntero al elemento máximo, NULL si árbol vacío
 */
void* arbol_maximo(ArbolAVL arbol);

/*
 * Función: arbol_es_vacio
 * Descripción: Verifica si el árbol está vacío
 * 
 * Parámetros:
 *  - arbol: Árbol a verificar
 * 
 * Retorna: 1 si está vacío, 0 si contiene elementos
 */
int arbol_es_vacio(ArbolAVL arbol);

#endif // __ARBOL_H__
