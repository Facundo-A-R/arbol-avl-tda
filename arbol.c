/*
 * ============================================================================
 * ARCHIVO: arbol.c
 * DESCRIPCIÓN: Implementación del Árbol AVL genérico con soporte void*
 * 
 * Este archivo contiene la implementación completa de todas las operaciones
 * del Árbol AVL, incluyendo:
 * - Creación y destrucción
 * - Inserción y eliminación con balance automático
 * - Búsqueda
 * - Recorridos (in-orden, pre-orden, post-orden)
 * - Métricas del árbol (altura, peso, hojas, etc.)
 * - Rotaciones (simples y dobles)
 * ============================================================================
 */

#include "arbol.h"

/*
 * ============================================================================
 * ESTRUCTURA PRIVADA DEL NODO
 * ============================================================================
 */

/*
 * Estructura NodoAVL
 * Representa cada nodo del árbol AVL.
 * 
 * Campos:
 *  - dato: Puntero al dato almacenado (void* para genericidad)
 *  - tamaño: Tamaño en bytes del dato (para poder copiarlo)
 *  - altura: Altura del nodo en el árbol (usada para balanceo)
 *  - izquierdo: Puntero al hijo izquierdo
 *  - derecho: Puntero al hijo derecho
 */
struct NodoAVL {
    void* dato;              // Dato genérico almacenado
    size_t tamaño;           // Tamaño del dato en bytes
    int altura;              // Altura del nodo
    struct NodoAVL* izquierdo;  // Hijo izquierdo
    struct NodoAVL* derecho;    // Hijo derecho
};

/*
 * ============================================================================
 * ESTRUCTURA PRIVADA DEL ÁRBOL
 * ============================================================================
 */

/*
 * Estructura Arbol (privada)
 * Encapsula la raíz del árbol y las funciones de operación
 * 
 * Campos:
 *  - raiz: Puntero a la raíz del árbol
 *  - comparar: Función de comparación entre elementos
 *  - destructor: Función para liberar memoria de elementos
 */
struct Arbol {
    struct NodoAVL* raiz;           // Raíz del árbol
    FuncionComparacion comparar;    // Función de comparación
    FuncionDestructor destructor;   // Función de destrucción
};

/*
 * ============================================================================
 * FUNCIONES PRIVADAS (AUXILIARES)
 * ============================================================================
 */

/*
 * Función: _obtener_altura
 * Descripción: Obtiene la altura de un nodo (privada)
 * 
 * Parámetros:
 *  - nodo: Nodo a evaluar
 * 
 * Retorna: Altura del nodo (0 si es NULL)
 */
static int _obtener_altura(struct NodoAVL* nodo) {
    // Si el nodo es NULL, su altura es 0
    if (nodo == NULL) {
        return 0;
    }
    // Retorna la altura almacenada en el nodo
    return nodo->altura;
}

/*
 * Función: _actualizar_altura
 * Descripción: Actualiza la altura de un nodo basada en sus hijos
 * La altura es 1 + el máximo entre las alturas de sus hijos
 * 
 * Parámetros:
 *  - nodo: Nodo a actualizar
 */
static void _actualizar_altura(struct NodoAVL* nodo) {
    // Si el nodo es NULL, no hacer nada
    if (nodo == NULL) {
        return;
    }
    
    // Obtener alturas de los hijos
    int altura_izq = _obtener_altura(nodo->izquierdo);
    int altura_der = _obtener_altura(nodo->derecho);
    
    // Altura del nodo es 1 + el máximo de sus hijos
    nodo->altura = 1 + (altura_izq > altura_der ? altura_izq : altura_der);
}

/*
 * Función: _obtener_balance
 * Descripción: Calcula el factor de balance de un nodo
 * Factor de balance = altura_derecha - altura_izquierda
 * 
 * Parámetros:
 *  - nodo: Nodo a evaluar
 * 
 * Retorna: Factor de balance
 */
static int _obtener_balance(struct NodoAVL* nodo) {
    // Si el nodo es NULL, balance es 0
    if (nodo == NULL) {
        return 0;
    }
    
    // Balance = altura derecha - altura izquierda
    return _obtener_altura(nodo->derecho) - _obtener_altura(nodo->izquierdo);
}

/*
 * ============================================================================
 * OPERACIONES DE ROTACIÓN
 * ============================================================================
 */

/*
 * Función: _rotar_izquierda
 * Descripción: Realiza una rotación simple a la izquierda
 * 
 * Caso de uso: Cuando el balance es > 1 (árbol pesado a la derecha)
 * 
 *     A                B
 *      \              / \
 *       B      =>    A   C
 *        \
 *         C
 * 
 * Parámetros:
 *  - nodo: Puntero al nodo raíz de la subregión a rotar
 */
static void _rotar_izquierda(struct NodoAVL** nodo) {
    // Si el nodo es NULL, no hacer nada
    if (nodo == NULL || *nodo == NULL) {
        return;
    }
    
    // Guardar referencia al hijo derecho que será la nueva raíz
    struct NodoAVL* nueva_raiz = (*nodo)->derecho;
    
    // Si el nuevo hijo derecho es NULL, no se puede rotar
    if (nueva_raiz == NULL) {
        return;
    }
    
    // Realizar la rotación: el hijo derecho sube, su hijo izquierdo baja
    (*nodo)->derecho = nueva_raiz->izquierdo;
    nueva_raiz->izquierdo = *nodo;
    
    // Actualizar alturas (primero el nodo antiguo, luego el nuevo)
    _actualizar_altura(*nodo);
    _actualizar_altura(nueva_raiz);
    
    // Actualizar el puntero al nodo
    *nodo = nueva_raiz;
}

/*
 * Función: _rotar_derecha
 * Descripción: Realiza una rotación simple a la derecha
 * 
 * Caso de uso: Cuando el balance es < -1 (árbol pesado a la izquierda)
 * 
 *       C            B
 *      /            / \
 *     B      =>    A   C
 *    /
 *   A
 * 
 * Parámetros:
 *  - nodo: Puntero al nodo raíz de la subregión a rotar
 */
static void _rotar_derecha(struct NodoAVL** nodo) {
    // Si el nodo es NULL, no hacer nada
    if (nodo == NULL || *nodo == NULL) {
        return;
    }
    
    // Guardar referencia al hijo izquierdo que será la nueva raíz
    struct NodoAVL* nueva_raiz = (*nodo)->izquierdo;
    
    // Si el nuevo hijo izquierdo es NULL, no se puede rotar
    if (nueva_raiz == NULL) {
        return;
    }
    
    // Realizar la rotación: el hijo izquierdo sube, su hijo derecho baja
    (*nodo)->izquierdo = nueva_raiz->derecho;
    nueva_raiz->derecho = *nodo;
    
    // Actualizar alturas (primero el nodo antiguo, luego el nuevo)
    _actualizar_altura(*nodo);
    _actualizar_altura(nueva_raiz);
    
    // Actualizar el puntero al nodo
    *nodo = nueva_raiz;
}

/*
 * ============================================================================
 * FUNCIÓN PRIVADA DE BALANCEO
 * ============================================================================
 */

/*
 * Función: _balancear_nodo
 * Descripción: Balancea un nodo realizando las rotaciones necesarias
 * 
 * Parámetros:
 *  - nodo: Puntero al nodo a balancear
 */
static void _balancear_nodo(struct NodoAVL** nodo) {
    // Si el nodo es NULL, no hacer nada
    if (nodo == NULL || *nodo == NULL) {
        return;
    }
    
    // Calcular el balance del nodo
    int balance = _obtener_balance(*nodo);
    
    // Caso 1: Balance < -1 (pesado a la izquierda)
    if (balance < -1) {
        // Verificar si el hijo izquierdo está pesado a la derecha
        if (_obtener_balance((*nodo)->izquierdo) > 0) {
            // Rotación doble: izq-derecha
            // Primero rotar el hijo izquierdo a la izquierda
            _rotar_izquierda(&((*nodo)->izquierdo));
        }
        // Luego rotar el nodo actual a la derecha
        _rotar_derecha(nodo);
    }
    // Caso 2: Balance > 1 (pesado a la derecha)
    else if (balance > 1) {
        // Verificar si el hijo derecho está pesado a la izquierda
        if (_obtener_balance((*nodo)->derecho) < 0) {
            // Rotación doble: derecha-izquierda
            // Primero rotar el hijo derecho a la derecha
            _rotar_derecha(&((*nodo)->derecho));
        }
        // Luego rotar el nodo actual a la izquierda
        _rotar_izquierda(nodo);
    }
}

/*
 * ============================================================================
 * FUNCIONES DE CREACIÓN Y DESTRUCCIÓN
 * ============================================================================
 */

/*
 * Función: _crear_nodo
 * Descripción: Crea un nuevo nodo del árbol (privada)
 * 
 * Parámetros:
 *  - dato: Dato a almacenar en el nodo
 *  - tamaño: Tamaño del dato en bytes
 *  - copydata: 1 si copiar el dato, 0 si solo guardar el puntero
 * 
 * Retorna: Puntero al nodo creado, NULL si error
 */
static struct NodoAVL* _crear_nodo(const void* dato, size_t tamaño, int copydata) {
    // Asignar memoria para el nuevo nodo
    struct NodoAVL* nodo = (struct NodoAVL*) malloc(sizeof(struct NodoAVL));
    
    // Si no hay memoria disponible, retornar NULL
    if (nodo == NULL) {
        return NULL;
    }
    
    // Si copydata es 1, copiar el dato
    if (copydata) {
        nodo->dato = malloc(tamaño);
        if (nodo->dato == NULL) {
            free(nodo);
            return NULL;
        }
        // Copiar el contenido del dato
        memcpy(nodo->dato, dato, tamaño);
    } else {
        // Si copydata es 0, solo guardar el puntero
        nodo->dato = (void*) dato;
    }
    
    // Inicializar campos del nodo
    nodo->tamaño = tamaño;
    nodo->altura = 1;              // Primera altura es 1
    nodo->izquierdo = NULL;        // Sin hijo izquierdo
    nodo->derecho = NULL;          // Sin hijo derecho
    
    return nodo;
}

/*
 * Función: _destruir_nodo_recursivo
 * Descripción: Destruye recursivamente todos los nodos del árbol
 * 
 * Parámetros:
 *  - nodo: Puntero al nodo a destruir
 *  - destructor: Función para liberar el dato
 *  - copydata: 1 si los datos fueron copiados, 0 si no
 */
static void _destruir_nodo_recursivo(struct NodoAVL* nodo, 
                                      FuncionDestructor destructor, 
                                      int copydata) {
    // Si el nodo es NULL, no hay nada que destruir
    if (nodo == NULL) {
        return;
    }
    
    // Destruir recursivamente el hijo izquierdo
    _destruir_nodo_recursivo(nodo->izquierdo, destructor, copydata);
    
    // Destruir recursivamente el hijo derecho
    _destruir_nodo_recursivo(nodo->derecho, destructor, copydata);
    
    // Liberar el dato almacenado
    if (copydata && nodo->dato != NULL) {
        // Si fue copiado, liberar la memoria
        free(nodo->dato);
    } else if (destructor != NULL) {
        // Si hay una función destructora, usarla
        destructor(nodo->dato);
    }
    
    // Liberar la memoria del nodo
    free(nodo);
}

/*
 * Función: crear_arbol
 * Descripción: Crea un árbol AVL vacío
 * 
 * Parámetros:
 *  - comparar: Función de comparación entre elementos
 *  - destructor: Función para liberar memoria de elementos
 * 
 * Retorna: Puntero al árbol creado
 */
ArbolAVL crear_arbol(FuncionComparacion comparar, FuncionDestructor destructor) {
    // Asignar memoria para la estructura del árbol
    struct Arbol* arbol = (struct Arbol*) malloc(sizeof(struct Arbol));
    
    // Si no hay memoria disponible, retornar NULL
    if (arbol == NULL) {
        return NULL;
    }
    
    // Inicializar campos del árbol
    arbol->raiz = NULL;             // Árbol vacío
    arbol->comparar = comparar;     // Guardar función de comparación
    arbol->destructor = destructor; // Guardar función de destrucción
    
    // Retornar el árbol como puntero genérico
    return (ArbolAVL) arbol;
}

/*
 * Función: vaciar_arbol
 * Descripción: Libera toda la memoria del árbol
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol a vaciar
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int vaciar_arbol(ArbolAVL* arbol) {
    // Si el puntero es NULL, error
    if (arbol == NULL || *arbol == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) *arbol;
    
    // Destruir todos los nodos recursivamente
    _destruir_nodo_recursivo(a->raiz, a->destructor, 1);
    
    // Liberar la estructura del árbol
    free(a);
    
    // Marcar como NULL
    *arbol = NULL;
    
    return 1;
}

/*
 * ============================================================================
 * OPERACIONES DE INSERCIÓN
 * ============================================================================
 */

/*
 * Función: _insertar_recursivo
 * Descripción: Inserta un elemento recursivamente en el árbol (privada)
 * 
 * Parámetros:
 *  - nodo: Puntero al nodo actual
 *  - dato: Dato a insertar
 *  - tamaño: Tamaño del dato
 *  - copydata: 1 si copiar, 0 si no
 *  - comparar: Función de comparación
 *  - insertado: Puntero a variable para indicar si se insertó
 * 
 * Retorna: Puntero al nodo actualizado
 */
static struct NodoAVL* _insertar_recursivo(struct NodoAVL* nodo,
                                            const void* dato,
                                            size_t tamaño,
                                            int copydata,
                                            FuncionComparacion comparar,
                                            int* insertado) {
    // Base: si el nodo es NULL, crear un nuevo nodo
    if (nodo == NULL) {
        nodo = _crear_nodo(dato, tamaño, copydata);
        if (nodo == NULL) {
            *insertado = 0;
        } else {
            *insertado = 1;
        }
        return nodo;
    }
    
    // Comparar el dato con el dato del nodo actual
    int comparacion = comparar(dato, nodo->dato);
    
    // Si el dato es igual, no insertamos (no permitir duplicados)
    if (comparacion == 0) {
        *insertado = 0;
        return nodo;
    }
    
    // Si el dato es menor, insertar en el hijo izquierdo
    if (comparacion < 0) {
        nodo->izquierdo = _insertar_recursivo(nodo->izquierdo, dato, tamaño, 
                                              copydata, comparar, insertado);
    }
    // Si el dato es mayor, insertar en el hijo derecho
    else {
        nodo->derecho = _insertar_recursivo(nodo->derecho, dato, tamaño, 
                                            copydata, comparar, insertado);
    }
    
    // Actualizar altura del nodo actual
    _actualizar_altura(nodo);
    
    // Balancear el nodo actual
    _balancear_nodo(&nodo);
    
    return nodo;
}

/*
 * Función: arbol_insertar
 * Descripción: Inserta un nuevo elemento en el árbol
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol
 *  - dato: Dato a insertar
 *  - tamaño: Tamaño del dato
 *  - copydata: 1 si copiar el dato, 0 si solo guardar el puntero
 * 
 * Retorna: 1 si éxito, 0 si error
 */
int arbol_insertar(ArbolAVL* arbol, const void* dato, size_t tamaño, int copydata) {
    // Validar argumentos
    if (arbol == NULL || *arbol == NULL || dato == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) *arbol;
    
    // Variable para indicar si se insertó
    int insertado = 0;
    
    // Insertar recursivamente
    a->raiz = _insertar_recursivo(a->raiz, dato, tamaño, copydata, 
                                   a->comparar, &insertado);
    
    return insertado;
}

/*
 * ============================================================================
 * OPERACIONES DE BÚSQUEDA
 * ============================================================================
 */

/*
 * Función: _buscar_recursivo
 * Descripción: Busca un elemento recursivamente en el árbol (privada)
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - dato: Dato a buscar
 *  - comparar: Función de comparación
 * 
 * Retorna: Puntero al dato encontrado, NULL si no existe
 */
static void* _buscar_recursivo(struct NodoAVL* nodo, 
                               const void* dato, 
                               FuncionComparacion comparar) {
    // Si el nodo es NULL, no encontrado
    if (nodo == NULL) {
        return NULL;
    }
    
    // Comparar el dato con el dato del nodo actual
    int comparacion = comparar(dato, nodo->dato);
    
    // Si son iguales, retornar el dato encontrado
    if (comparacion == 0) {
        return nodo->dato;
    }
    
    // Si el dato es menor, buscar en el hijo izquierdo
    if (comparacion < 0) {
        return _buscar_recursivo(nodo->izquierdo, dato, comparar);
    }
    // Si el dato es mayor, buscar en el hijo derecho
    else {
        return _buscar_recursivo(nodo->derecho, dato, comparar);
    }
}

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
void* arbol_buscar(ArbolAVL arbol, const void* dato) {
    // Validar argumentos
    if (arbol == NULL || dato == NULL) {
        return NULL;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Buscar recursivamente desde la raíz
    return _buscar_recursivo(a->raiz, dato, a->comparar);
}

/*
 * ============================================================================
 * OPERACIONES DE ELIMINACIÓN
 * ============================================================================
 */

/*
 * Función: _buscar_minimo
 * Descripción: Encuentra el nodo con el valor mínimo en un subárbol (privada)
 * El mínimo es el nodo más a la izquierda
 * 
 * Parámetros:
 *  - nodo: Raíz del subárbol
 * 
 * Retorna: Puntero al nodo con el valor mínimo
 */
static struct NodoAVL* _buscar_minimo(struct NodoAVL* nodo) {
    // Si el nodo es NULL, no hay nada
    if (nodo == NULL) {
        return NULL;
    }
    
    // Ir al hijo izquierdo hasta encontrar el más a la izquierda
    while (nodo->izquierdo != NULL) {
        nodo = nodo->izquierdo;
    }
    
    return nodo;
}

/*
 * Función: _eliminar_recursivo
 * Descripción: Elimina un elemento recursivamente del árbol (privada)
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - dato: Dato a eliminar
 *  - comparar: Función de comparación
 *  - destructor: Función para liberar el dato
 *  - eliminado: Puntero a variable para indicar si se eliminó
 * 
 * Retorna: Puntero al nodo actualizado
 */
static struct NodoAVL* _eliminar_recursivo(struct NodoAVL* nodo,
                                            const void* dato,
                                            FuncionComparacion comparar,
                                            FuncionDestructor destructor,
                                            int* eliminado) {
    // Si el nodo es NULL, no encontrado
    if (nodo == NULL) {
        *eliminado = 0;
        return NULL;
    }
    
    // Comparar el dato con el dato del nodo actual
    int comparacion = comparar(dato, nodo->dato);
    
    // Si el dato es menor, buscar en el hijo izquierdo
    if (comparacion < 0) {
        nodo->izquierdo = _eliminar_recursivo(nodo->izquierdo, dato, comparar, 
                                              destructor, eliminado);
    }
    // Si el dato es mayor, buscar en el hijo derecho
    else if (comparacion > 0) {
        nodo->derecho = _eliminar_recursivo(nodo->derecho, dato, comparar, 
                                            destructor, eliminado);
    }
    // Si el dato es igual, eliminar este nodo
    else {
        *eliminado = 1;
        
        // Caso 1: Nodo sin hijo izquierdo
        if (nodo->izquierdo == NULL) {
            struct NodoAVL* temp = nodo->derecho;
            free(nodo->dato);
            free(nodo);
            return temp;
        }
        // Caso 2: Nodo sin hijo derecho
        else if (nodo->derecho == NULL) {
            struct NodoAVL* temp = nodo->izquierdo;
            free(nodo->dato);
            free(nodo);
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        // Encontrar el sucesor (mínimo en el subárbol derecho)
        struct NodoAVL* sucesor = _buscar_minimo(nodo->derecho);
        
        // Reemplazar el dato del nodo actual con el del sucesor
        free(nodo->dato);
        nodo->dato = sucesor->dato;
        nodo->tamaño = sucesor->tamaño;
        
        // Eliminar el sucesor del subárbol derecho
        int temp_eliminado = 0;
        nodo->derecho = _eliminar_recursivo(nodo->derecho, sucesor->dato, 
                                            comparar, destructor, &temp_eliminado);
    }
    
    // Si el nodo fue eliminado completamente, retornar NULL
    if (nodo == NULL) {
        return NULL;
    }
    
    // Actualizar altura del nodo actual
    _actualizar_altura(nodo);
    
    // Balancear el nodo actual
    _balancear_nodo(&nodo);
    
    return nodo;
}

/*
 * Función: arbol_eliminar
 * Descripción: Elimina un elemento del árbol
 * 
 * Parámetros:
 *  - arbol: Puntero al árbol
 *  - dato: Dato a eliminar
 * 
 * Retorna: 1 si se eliminó, 0 si no encontrado
 */
int arbol_eliminar(ArbolAVL* arbol, const void* dato) {
    // Validar argumentos
    if (arbol == NULL || *arbol == NULL || dato == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) *arbol;
    
    // Variable para indicar si se eliminó
    int eliminado = 0;
    
    // Eliminar recursivamente
    a->raiz = _eliminar_recursivo(a->raiz, dato, a->comparar, 
                                  a->destructor, &eliminado);
    
    return eliminado;
}

/*
 * ============================================================================
 * OPERACIONES DE RECORRIDO
 * ============================================================================
 */

/*
 * Función: _recorrido_inorden_recursivo
 * Descripción: Realiza recorrido in-orden recursivamente (privada)
 * In-orden: izquierdo - raíz - derecho
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - imprimir: Función para imprimir cada elemento
 */
static void _recorrido_inorden_recursivo(struct NodoAVL* nodo, 
                                         FuncionImpresion imprimir) {
    // Si el nodo es NULL, no hay nada que recorrer
    if (nodo == NULL) {
        return;
    }
    
    // Recorrer hijo izquierdo
    _recorrido_inorden_recursivo(nodo->izquierdo, imprimir);
    
    // Procesar el nodo actual
    imprimir(nodo->dato);
    
    // Recorrer hijo derecho
    _recorrido_inorden_recursivo(nodo->derecho, imprimir);
}

/*
 * Función: arbol_recorrido_inorden
 * Descripción: Realiza un recorrido in-orden del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_inorden(ArbolAVL arbol, FuncionImpresion imprimir) {
    // Validar argumentos
    if (arbol == NULL || imprimir == NULL) {
        return;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Recorrer desde la raíz
    _recorrido_inorden_recursivo(a->raiz, imprimir);
}

/*
 * Función: _recorrido_preorden_recursivo
 * Descripción: Realiza recorrido pre-orden recursivamente (privada)
 * Pre-orden: raíz - izquierdo - derecho
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - imprimir: Función para imprimir cada elemento
 */
static void _recorrido_preorden_recursivo(struct NodoAVL* nodo, 
                                          FuncionImpresion imprimir) {
    // Si el nodo es NULL, no hay nada que recorrer
    if (nodo == NULL) {
        return;
    }
    
    // Procesar el nodo actual
    imprimir(nodo->dato);
    
    // Recorrer hijo izquierdo
    _recorrido_preorden_recursivo(nodo->izquierdo, imprimir);
    
    // Recorrer hijo derecho
    _recorrido_preorden_recursivo(nodo->derecho, imprimir);
}

/*
 * Función: arbol_recorrido_preorden
 * Descripción: Realiza un recorrido pre-orden del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_preorden(ArbolAVL arbol, FuncionImpresion imprimir) {
    // Validar argumentos
    if (arbol == NULL || imprimir == NULL) {
        return;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Recorrer desde la raíz
    _recorrido_preorden_recursivo(a->raiz, imprimir);
}

/*
 * Función: _recorrido_postorden_recursivo
 * Descripción: Realiza recorrido post-orden recursivamente (privada)
 * Post-orden: izquierdo - derecho - raíz
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - imprimir: Función para imprimir cada elemento
 */
static void _recorrido_postorden_recursivo(struct NodoAVL* nodo, 
                                           FuncionImpresion imprimir) {
    // Si el nodo es NULL, no hay nada que recorrer
    if (nodo == NULL) {
        return;
    }
    
    // Recorrer hijo izquierdo
    _recorrido_postorden_recursivo(nodo->izquierdo, imprimir);
    
    // Recorrer hijo derecho
    _recorrido_postorden_recursivo(nodo->derecho, imprimir);
    
    // Procesar el nodo actual
    imprimir(nodo->dato);
}

/*
 * Función: arbol_recorrido_postorden
 * Descripción: Realiza un recorrido post-orden del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a recorrer
 *  - imprimir: Función para imprimir cada elemento
 */
void arbol_recorrido_postorden(ArbolAVL arbol, FuncionImpresion imprimir) {
    // Validar argumentos
    if (arbol == NULL || imprimir == NULL) {
        return;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Recorrer desde la raíz
    _recorrido_postorden_recursivo(a->raiz, imprimir);
}

/*
 * ============================================================================
 * OPERACIONES DE MÉTRICAS
 * ============================================================================
 */

/*
 * Función: arbol_altura
 * Descripción: Calcula la altura del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a medir
 * 
 * Retorna: Altura del árbol
 */
int arbol_altura(ArbolAVL arbol) {
    // Si el árbol es NULL, altura es 0
    if (arbol == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Retornar la altura de la raíz
    return _obtener_altura(a->raiz);
}

/*
 * Función: _calcular_peso
 * Descripción: Calcula la cantidad de nodos recursivamente (privada)
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 * 
 * Retorna: Cantidad de nodos en el subárbol
 */
static int _calcular_peso(struct NodoAVL* nodo) {
    // Si el nodo es NULL, peso es 0
    if (nodo == NULL) {
        return 0;
    }
    
    // Peso = 1 (nodo actual) + peso izquierdo + peso derecho
    return 1 + _calcular_peso(nodo->izquierdo) + _calcular_peso(nodo->derecho);
}

/*
 * Función: arbol_peso
 * Descripción: Calcula la cantidad total de nodos en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a contar
 * 
 * Retorna: Cantidad de nodos
 */
int arbol_peso(ArbolAVL arbol) {
    // Si el árbol es NULL, peso es 0
    if (arbol == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Calcular peso desde la raíz
    return _calcular_peso(a->raiz);
}

/*
 * Función: _calcular_hojas
 * Descripción: Calcula la cantidad de hojas recursivamente (privada)
 * Una hoja es un nodo sin hijos
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 * 
 * Retorna: Cantidad de hojas en el subárbol
 */
static int _calcular_hojas(struct NodoAVL* nodo) {
    // Si el nodo es NULL, no hay hojas
    if (nodo == NULL) {
        return 0;
    }
    
    // Si el nodo no tiene hijos, es una hoja
    if (nodo->izquierdo == NULL && nodo->derecho == NULL) {
        return 1;
    }
    
    // Cantidad de hojas = hojas izquierda + hojas derecha
    return _calcular_hojas(nodo->izquierdo) + _calcular_hojas(nodo->derecho);
}

/*
 * Función: arbol_cantidad_hojas
 * Descripción: Cuenta la cantidad de hojas en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a contar
 * 
 * Retorna: Cantidad de hojas
 */
int arbol_cantidad_hojas(ArbolAVL arbol) {
    // Si el árbol es NULL, no hay hojas
    if (arbol == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Calcular hojas desde la raíz
    return _calcular_hojas(a->raiz);
}

/*
 * Función: arbol_balance
 * Descripción: Calcula el factor de balance de la raíz
 * 
 * Parámetros:
 *  - arbol: Árbol a evaluar
 * 
 * Retorna: Factor de balance
 */
int arbol_balance(ArbolAVL arbol) {
    // Si el árbol es NULL, balance es 0
    if (arbol == NULL) {
        return 0;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Calcular balance de la raíz
    return _obtener_balance(a->raiz);
}

/*
 * Función: _buscar_nivel
 * Descripción: Busca el nivel de un elemento recursivamente (privada)
 * 
 * Parámetros:
 *  - nodo: Nodo actual
 *  - dato: Dato a buscar
 *  - nivel_actual: Nivel actual en el árbol
 *  - comparar: Función de comparación
 * 
 * Retorna: Nivel del elemento, -1 si no encontrado
 */
static int _buscar_nivel(struct NodoAVL* nodo, const void* dato, 
                         int nivel_actual, FuncionComparacion comparar) {
    // Si el nodo es NULL, no encontrado
    if (nodo == NULL) {
        return -1;
    }
    
    // Comparar el dato con el dato del nodo actual
    int comparacion = comparar(dato, nodo->dato);
    
    // Si son iguales, retornar el nivel actual
    if (comparacion == 0) {
        return nivel_actual;
    }
    
    // Si el dato es menor, buscar en el hijo izquierdo
    if (comparacion < 0) {
        return _buscar_nivel(nodo->izquierdo, dato, nivel_actual + 1, comparar);
    }
    // Si el dato es mayor, buscar en el hijo derecho
    else {
        return _buscar_nivel(nodo->derecho, dato, nivel_actual + 1, comparar);
    }
}

/*
 * Función: arbol_nivel
 * Descripción: Encuentra el nivel de un elemento en el árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 *  - dato: Elemento a localizar
 * 
 * Retorna: Nivel del elemento, -1 si no encontrado
 */
int arbol_nivel(ArbolAVL arbol, const void* dato) {
    // Si el árbol es NULL, no encontrado
    if (arbol == NULL || dato == NULL) {
        return -1;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Buscar desde la raíz (nivel 0)
    return _buscar_nivel(a->raiz, dato, 0, a->comparar);
}

/*
 * Función: arbol_minimo
 * Descripción: Obtiene el elemento mínimo del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 * 
 * Retorna: Puntero al elemento mínimo, NULL si árbol vacío
 */
void* arbol_minimo(ArbolAVL arbol) {
    // Si el árbol es NULL, no hay mínimo
    if (arbol == NULL) {
        return NULL;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Buscar el mínimo desde la raíz
    struct NodoAVL* minimo = _buscar_minimo(a->raiz);
    
    // Si no hay mínimo, retornar NULL
    if (minimo == NULL) {
        return NULL;
    }
    
    // Retornar el dato del nodo mínimo
    return minimo->dato;
}

/*
 * Función: _buscar_maximo
 * Descripción: Encuentra el nodo con el valor máximo en un subárbol (privada)
 * El máximo es el nodo más a la derecha
 * 
 * Parámetros:
 *  - nodo: Raíz del subárbol
 * 
 * Retorna: Puntero al nodo con el valor máximo
 */
static struct NodoAVL* _buscar_maximo(struct NodoAVL* nodo) {
    // Si el nodo es NULL, no hay nada
    if (nodo == NULL) {
        return NULL;
    }
    
    // Ir al hijo derecho hasta encontrar el más a la derecha
    while (nodo->derecho != NULL) {
        nodo = nodo->derecho;
    }
    
    return nodo;
}

/*
 * Función: arbol_maximo
 * Descripción: Obtiene el elemento máximo del árbol
 * 
 * Parámetros:
 *  - arbol: Árbol a buscar
 * 
 * Retorna: Puntero al elemento máximo, NULL si árbol vacío
 */
void* arbol_maximo(ArbolAVL arbol) {
    // Si el árbol es NULL, no hay máximo
    if (arbol == NULL) {
        return NULL;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Buscar el máximo desde la raíz
    struct NodoAVL* maximo = _buscar_maximo(a->raiz);
    
    // Si no hay máximo, retornar NULL
    if (maximo == NULL) {
        return NULL;
    }
    
    // Retornar el dato del nodo máximo
    return maximo->dato;
}

/*
 * Función: arbol_es_vacio
 * Descripción: Verifica si el árbol está vacío
 * 
 * Parámetros:
 *  - arbol: Árbol a verificar
 * 
 * Retorna: 1 si está vacío, 0 si contiene elementos
 */
int arbol_es_vacio(ArbolAVL arbol) {
    // Si el árbol es NULL, está vacío
    if (arbol == NULL) {
        return 1;
    }
    
    // Acceder a la estructura privada del árbol
    struct Arbol* a = (struct Arbol*) arbol;
    
    // Si la raíz es NULL, el árbol está vacío
    return (a->raiz == NULL) ? 1 : 0;
}
