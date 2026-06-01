# Documentación Técnica del Árbol AVL Genérico

## Tabla de Contenidos

1. [Introducción](#introducción)
2. [Arquitectura y Diseño](#arquitectura-y-diseño)
3. [Estructuras de Datos](#estructuras-de-datos)
4. [Operaciones Principales](#operaciones-principales)
5. [Algoritmos de Rotación](#algoritmos-de-rotación)
6. [Complejidad de Tiempo](#complejidad-de-tiempo)
7. [Genericidad con void*](#genericidad-con-void)
8. [Gestión de Memoria](#gestión-de-memoria)
9. [Ejemplos de Uso](#ejemplos-de-uso)

---

## Introducción

Un **Árbol AVL** es un árbol binario de búsqueda autobalanceado donde la diferencia de alturas entre los subárboles izquierdo y derecho de cualquier nodo no excede 1.

### Características Principales

- **Balance Automático**: Mantiene el árbol balanceado en todo momento
- **Búsqueda Eficiente**: O(log n) garantizado
- **Genericidad**: Soporta cualquier tipo de dato mediante `void*`
- **Funciones de Comparación**: Permite al usuario definir el criterio de ordenamiento
- **Gestión de Memoria**: Manejo completo de memoria dinámica

---

## Arquitectura y Diseño

### Patrón de Diseño: TDA (Tipo de Dato Abstracto)

La implementación utiliza el paradigma TDA para encapsular la complejidad:

```
┌─────────────────────────────────────────┐
│      INTERFAZ PÚBLICA (arbol.h)         │
│  - crear_arbol()                        │
│  - arbol_insertar()                     │
│  - arbol_buscar()                       │
│  - arbol_eliminar()                     │
│  - arbol_recorridos()                   │
│  - arbol_metricas()                     │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   IMPLEMENTACIÓN PRIVADA (arbol.c)      │
│  - struct NodoAVL                       │
│  - struct Arbol                         │
│  - _rotar_izquierda()                   │
│  - _rotar_derecha()                     │
│  - _balancear_nodo()                    │
│  - Funciones recursivas internas        │
└─────────────────────────────────────────┘
```

### Ventajas del Diseño TDA

✓ **Encapsulamiento**: Los detalles de implementación están ocultos  
✓ **Facilidad de Uso**: Interfaz clara y simple  
✓ **Mantenibilidad**: Cambios internos no afectan el código cliente  
✓ **Seguridad**: El usuario no puede acceder directamente a estructuras internas  

---

## Estructuras de Datos

### 1. Estructura NodoAVL (Privada)

```c
struct NodoAVL {
    void* dato;              // Dato genérico del nodo
    size_t tamaño;           // Tamaño del dato en bytes
    int altura;              // Altura para cálculo de balance
    struct NodoAVL* izquierdo;  // Puntero al hijo izquierdo
    struct NodoAVL* derecho;    // Puntero al hijo derecho
};
```

**Campos:**

| Campo | Tipo | Descripción |
|-------|------|-------------|
| `dato` | `void*` | Puntero genérico al dato almacenado |
| `tamaño` | `size_t` | Tamaño en bytes del dato (para copias) |
| `altura` | `int` | Altura del nodo en el árbol (para balance) |
| `izquierdo` | `struct NodoAVL*` | Referencia al hijo izquierdo |
| `derecho` | `struct NodoAVL*` | Referencia al hijo derecho |

### 2. Estructura Arbol (Privada)

```c
struct Arbol {
    struct NodoAVL* raiz;           // Raíz del árbol
    FuncionComparacion comparar;    // Función para comparar elementos
    FuncionDestructor destructor;   // Función para liberar elementos
};
```

**Campos:**

| Campo | Tipo | Descripción |
|-------|------|-------------|
| `raiz` | `struct NodoAVL*` | Puntero a la raíz del árbol |
| `comparar` | `FuncionComparacion` | Función de comparación definida por usuario |
| `destructor` | `FuncionDestructor` | Función para liberar memoria de datos |

### 3. Tipos de Función

#### FuncionComparacion

```c
typedef int (*FuncionComparacion)(const void* dato1, const void* dato2);
```

**Retorna:**
- Negativo si `dato1 < dato2`
- 0 si `dato1 == dato2`
- Positivo si `dato1 > dato2`

#### FuncionDestructor

```c
typedef void (*FuncionDestructor)(void* dato);
```

Libera la memoria del dato si es necesario.

#### FuncionImpresion

```c
typedef void (*FuncionImpresion)(const void* dato);
```

Imprime el dato en un formato legible.

---

## Operaciones Principales

### 1. Creación

```c
ArbolAVL arbol = crear_arbol(comparar_enteros, NULL);
```

**Complejidad**: O(1)

### 2. Inserción

```c
int resultado = arbol_insertar(&arbol, &dato, sizeof(int), 1);
```

**Proceso:**
1. Búsqueda recursiva del lugar de inserción (como BST)
2. Crear nuevo nodo
3. Actualizar alturas
4. Balancear si es necesario (rotaciones)

**Complejidad**: O(log n)

### 3. Búsqueda

```c
void* encontrado = arbol_buscar(arbol, &dato);
```

**Proceso:**
1. Comparación recursiva desde la raíz
2. Ir izquierda si el dato es menor
3. Ir derecha si el dato es mayor
4. Retornar si se encuentra

**Complejidad**: O(log n)

### 4. Eliminación

```c
int resultado = arbol_eliminar(&arbol, &dato);
```

**Casos:**
- **Sin hijos**: Eliminar directamente
- **Un hijo**: Reemplazar con el hijo
- **Dos hijos**: Encontrar sucesor (mínimo en subárbol derecho), reemplazar datos, eliminar sucesor

**Complejidad**: O(log n)

### 5. Recorridos

#### In-Orden (Izquierda - Raíz - Derecha)
Produce elementos en orden ascendente

```
        2
       / \
      1   3
    
Recorrido: 1 → 2 → 3
```

#### Pre-Orden (Raíz - Izquierda - Derecha)
Útil para copiar árboles

```
Recorrido: 2 → 1 → 3
```

#### Post-Orden (Izquierda - Derecha - Raíz)
Útil para eliminar árboles

```
Recorrido: 1 → 3 → 2
```

---

## Algoritmos de Rotación

### Factor de Balance

```
balance = altura(derecho) - altura(izquierdo)
```

**Valores válidos en AVL**: -1, 0, +1

**Desbalance:**
- Si balance > 1: árbol pesado a la derecha
- Si balance < -1: árbol pesado a la izquierda

### Rotación Simple Izquierda

Se ejecuta cuando `balance > 1` y el hijo derecho no está pesado a la izquierda.

**Antes:**
```
    A                   B
     \                 / \
      B        =>     A   C
       \
        C
```

**Código:**
```c
(*nodo)->derecho = nueva_raiz->izquierdo;
nueva_raiz->izquierdo = *nodo;
*nodo = nueva_raiz;
```

### Rotación Simple Derecha

Se ejecuta cuando `balance < -1` y el hijo izquierdo no está pesado a la derecha.

**Antes:**
```
      C                B
     /                / \
    B         =>     A   C
   /
  A
```

**Código:**
```c
(*nodo)->izquierdo = nueva_raiz->derecho;
nueva_raiz->derecho = *nodo;
*nodo = nueva_raiz;
```

### Rotación Doble Izquierda-Derecha

Se ejecuta cuando `balance < -1` pero el hijo izquierdo está pesado a la derecha.

**Antes:**
```
      C              C              B
     /              /              / \
    A      =>      B       =>     A   C
     \            /
      B          A
```

**Código:**
```c
// Primero: rotar izquierdo del lado izquierdo
_rotar_izquierda(&((*nodo)->izquierdo));
// Luego: rotar derecha del nodo actual
_rotar_derecha(nodo);
```

### Rotación Doble Derecha-Izquierda

Se ejecuta cuando `balance > 1` pero el hijo derecho está pesado a la izquierda.

**Antes:**
```
    A              A              B
     \              \            / \
      C      =>      B     =>   A   C
     /                \
    B                  C
```

**Código:**
```c
// Primero: rotar derecha del lado derecho
_rotar_derecha(&((*nodo)->derecho));
// Luego: rotar izquierda del nodo actual
_rotar_izquierda(nodo);
```

---

## Complejidad de Tiempo

| Operación | Mejor Caso | Caso Promedio | Peor Caso |
|-----------|-----------|---------------|-----------|
| Búsqueda | O(1) | O(log n) | O(log n) |
| Inserción | O(log n) | O(log n) | O(log n) |
| Eliminación | O(log n) | O(log n) | O(log n) |
| Altura | O(1) | O(1) | O(1) |
| Peso (nodos) | O(n) | O(n) | O(n) |
| Recorrido | O(n) | O(n) | O(n) |

**Nota**: A diferencia de un BST normal, el AVL garantiza O(log n) para búsqueda, inserción y eliminación incluso en el peor caso.

---

## Genericidad con void*

### ¿Cómo Funciona?

1. **Almacenamiento**: El árbol guarda punteros `void*` genéricos
2. **Comparación**: El usuario proporciona una función de comparación
3. **Copia Optional**: El árbol puede copiar datos o guardar solo punteros

### Ventajas

✓ Un solo código fuente para múltiples tipos de datos  
✓ No necesita plantillas (templates)  
✓ Flexible y reutilizable  

### Desventajas

✗ Menos seguridad de tipos en tiempo de compilación  
✗ Requiere casting manual  
✗ Función de comparación es responsabilidad del usuario  

### Ejemplo

```c
// Para enteros
int comparar_enteros(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Para personas
int comparar_personas(const void* a, const void* b) {
    Persona* p1 = (Persona*)a;
    Persona* p2 = (Persona*)b;
    return p1->id - p2->id;
}

// Mismo árbol funciona con ambos tipos
ArbolAVL arbol_int = crear_arbol(comparar_enteros, NULL);
ArbolAVL arbol_personas = crear_arbol(comparar_personas, NULL);
```

---

## Gestión de Memoria

### Asignación de Memoria

1. **Creación del Árbol**: 1 estructura `Arbol`
2. **Cada Nodo**: 1 estructura `NodoAVL` + copia del dato (opcional)

### Liberación de Memoria

```c
// Destrucción recursiva de todos los nodos
_destruir_nodo_recursivo(nodo, destructor, copydata);

// Destrucción del árbol
vaciar_arbol(&arbol);
```

**Proceso:**
1. Recorrido post-orden (izquierda, derecha, raíz)
2. Liberar cada dato
3. Liberar cada nodo
4. Liberar estructura del árbol

### Manejo de Fugas

El programa implementa correctamente la gestión de memoria:

- ✓ Todas las asignaciones tienen desasignación correspondiente
- ✓ Se libera en orden correcto (post-orden)
- ✓ No hay referencias después de liberar
- ✓ Se pueden detectar fugas con Valgrind: `make valgrind`

---

## Ejemplos de Uso

### Ejemplo 1: Árbol de Enteros

```c
// Crear árbol
ArbolAVL arbol = crear_arbol(comparar_enteros, NULL);

// Insertar elementos
int vals[] = {50, 25, 75, 10, 30};
for (int i = 0; i < 5; i++) {
    arbol_insertar(&arbol, &vals[i], sizeof(int), 1);
}

// Buscar
int buscar = 25;
if (arbol_buscar(arbol, &buscar) != NULL) {
    printf("Encontrado\n");
}

// Recorrer
arbol_recorrido_inorden(arbol, imprimir_entero);

// Eliminar
arbol_eliminar(&arbol, &buscar);

// Limpiar
vaciar_arbol(&arbol);
```

### Ejemplo 2: Árbol de Estructuras

```c
// Definir estructura
typedef struct {
    int id;
    char nombre[50];
} Persona;

// Función de comparación
int comparar_personas(const void* a, const void* b) {
    return ((Persona*)a)->id - ((Persona*)b)->id;
}

// Crear árbol
ArbolAVL arbol = crear_arbol(comparar_personas, NULL);

// Usar como antes
Persona p = {1, "Juan"};
arbol_insertar(&arbol, &p, sizeof(Persona), 1);
```

---

## Conclusión

Esta implementación del Árbol AVL proporciona:

✓ **Eficiencia**: Garantías de O(log n) en todas las operaciones  
✓ **Genericidad**: Funciona con cualquier tipo de dato  
✓ **Robustez**: Gestión correcta de memoria  
✓ **Facilidad de uso**: Interfaz clara y bien documentada  
✓ **Educativo**: Código completamente comentado  

---

*Última actualización: 2026-06-01*
