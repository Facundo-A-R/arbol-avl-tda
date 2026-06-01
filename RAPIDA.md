# Referencia Rápida - Árbol AVL

## Resumen Ejecutivo

| Aspecto | Descripción |
|--------|-------------|
| **Tipo** | Árbol Binario de Búsqueda Autobalanceado (AVL) |
| **Balance** | Altura izquierda y derecha difieren en máximo 1 |
| **Complejidad** | O(log n) garantizado para búsqueda/inserción/eliminación |
| **Memoria** | O(n) |
| **Genericidad** | void* con funciones de comparación personalizadas |

---

## Compilación Rápida

### Opción 1: Make
```bash
make run          # Compilar y ejecutar
make clean        # Limpiar
make debug        # Con depuración
make valgrind     # Detectar fugas
```

### Opción 2: Manual
```bash
gcc -Wall -Wextra -std=c99 -O2 -o arbol_avl arbol.c main.c -lm
./arbol_avl
```

---

## API Rápida

### Creación
```c
ArbolAVL arbol = crear_arbol(comparar, destructor);
```

### Operaciones Básicas
```c
arbol_insertar(&arbol, dato, tamaño, copydata);    // Insertar
void* resultado = arbol_buscar(arbol, dato);       // Buscar
arbol_eliminar(&arbol, dato);                      // Eliminar
vaciar_arbol(&arbol);                              // Destruir
```

### Recorridos
```c
arbol_recorrido_inorden(arbol, imprimir);          // Ordenado
arbol_recorrido_preorden(arbol, imprimir);         // Raíz primero
arbol_recorrido_postorden(arbol, imprimir);        // Raíz al final
```

### Métricas
```c
int altura = arbol_altura(arbol);                  // Altura
int peso = arbol_peso(arbol);                      // Cantidad nodos
int hojas = arbol_cantidad_hojas(arbol);           // Hojas
int balance = arbol_balance(arbol);                // Factor balance
int nivel = arbol_nivel(arbol, dato);              // Nivel elemento
void* min = arbol_minimo(arbol);                   // Mínimo
void* max = arbol_maximo(arbol);                   // Máximo
```

---

## Funciones de Soporte

### Comparador
```c
// Retorna: negativo (<), 0 (==), positivo (>)
int comparar(const void* a, const void* b) {
    // Implementar lógica de comparación
    return resultado;
}
```

### Destructor (Opcional)
```c
// Libera memoria interna si es necesario
void destruir(void* dato) {
    // Liberar recursos si existen
}
```

### Impresión
```c
void imprimir(const void* dato) {
    // Imprimir el dato
}
```

---

## Plantilla Básica

```c
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

// Función de comparación
int comparar(const void* a, const void* b) {
    // Implementar
    return 0;
}

// Función de impresión
void imprimir(const void* dato) {
    // Implementar
}

int main() {
    // Crear árbol
    ArbolAVL arbol = crear_arbol(comparar, NULL);
    
    // Insertar datos
    int dato = 42;
    arbol_insertar(&arbol, &dato, sizeof(int), 1);
    
    // Usar árbol...
    
    // Limpiar
    vaciar_arbol(&arbol);
    
    return 0;
}
```

---

## Parámetro copydata

| copydata | Comportamiento | Cuándo Usar |
|----------|---|---|
| **1** | Árbol copia el dato | Datos locales que van a cambiar |
| **0** | Árbol guarda puntero | Datos constantes o dinámicos |

---

## Casos de Uso Comunes

### 1. Ordenar y Buscar Rápidamente
```c
// Insertar datos desordenados
for (int i = 0; i < n; i++) {
    arbol_insertar(&arbol, datos[i], tamaño, 1);
}
// Recorrer en orden
arbol_recorrido_inorden(arbol, imprimir);
```

### 2. Autocomplete
```c
// Árbol de strings ordenados
// Buscar elementos que comienzan con prefijo
```

### 3. Índice de Base de Datos
```c
// Mantener índice ordenado de registros
// Búsqueda rápida sin escanear todo
```

### 4. Estadísticas en Rango
```c
// Encontrar min/max en O(log n)
int minimo = *(int*) arbol_minimo(arbol);
```

---

## Depuración

### Detectar Fugas de Memoria
```bash
make valgrind
```

### Compilar con Debug
```bash
make debug
gdb ./arbol_avl
```

### Comandos GDB Útiles
```
break main          # Punto de quiebre
run                 # Ejecutar
step                # Paso a paso
print variable      # Ver valor
continue            # Continuar
quit                # Salir
```

---

## Estructura de Archivos

```
.
├── arbol.h          # Header (interfaz)
├── arbol.c          # Implementación
├── main.c           # Pruebas
├── Makefile         # Compilación
├── README.md        # Descripción
├── COMPILACION.md   # Guía compilación
├── TECNICO.md       # Documentación técnica
├── EJEMPLOS.md      # Ejemplos de uso
└── RAPIDA.md        # Este archivo
```

---

## Complejidades Garantizadas

### Búsqueda
- **Peor caso**: O(log n)
- **Promedio**: O(log n)
- **Mejor caso**: O(1)

### Inserción
- **Peor caso**: O(log n)
- **Promedio**: O(log n)
- **Mejor caso**: O(1)

### Eliminación
- **Peor caso**: O(log n)
- **Promedio**: O(log n)
- **Mejor caso**: O(1)

### Recorrido Completo
- **Siempre**: O(n)

---

## Limitaciones

⚠️ **Importante:**
- Requiere función de comparación válida
- No permite duplicados
- Memoria O(n)
- No es thread-safe (para uso concurrente, agregar sincronización)

---

## Ventajas vs Desventajas

### ✅ Ventajas
- Balance automático
- O(log n) garantizado
- Búsqueda eficiente
- Genericidad con void*
- Código comentado y educativo

### ❌ Desventajas
- Mayor complejidad que array
- Overhead de rotaciones
- Requiere función comparación
- No es óptimo para datos muy pequeños

---

## Checklist de Implementación

- [x] Estructura NodoAVL
- [x] Estructura Arbol (privada)
- [x] Creación/destrucción
- [x] Inserción recursiva
- [x] Rotación izquierda
- [x] Rotación derecha
- [x] Rotación doble izquierda-derecha
- [x] Rotación doble derecha-izquierda
- [x] Eliminación con balanceo
- [x] Búsqueda recursiva
- [x] Recorrido in-orden
- [x] Recorrido pre-orden
- [x] Recorrido post-orden
- [x] Cálculo altura
- [x] Cálculo peso
- [x] Cálculo hojas
- [x] Factor de balance
- [x] Nivel de nodo
- [x] Mínimo y máximo
- [x] Programa de pruebas
- [x] Documentación completa
- [x] Makefile

---

## Referencias

### Complejidad AVL
- Altura máxima: log₁.₆₁(n+2) - 1
- Factor de balance: -1, 0, o +1

### Número de Rotaciones
- **Inserción**: 0 o 1 rotación
- **Eliminación**: O(log n) rotaciones

### Altura Garantizada
- n nodos → altura ≤ 1.44 log₂(n+1)

---

## Solución Rápida de Problemas

| Problema | Causa | Solución |
|----------|-------|----------|
| Compilación falla | Archivos faltantes | Verificar .h y .c en directorio |
| Error compilador | GCC no instalado | `sudo apt install build-essential` |
| Segmentation fault | Árbol NULL | Verificar `crear_arbol` retornó válido |
| Elemento no encontrado | Comparador incorrecto | Verificar función de comparación |
| Fugas de memoria | No liberó árbol | Llamar `vaciar_arbol(&arbol)` |

---

## Próximos Pasos

1. **Compilar**: `make run`
2. **Revisar salida**: Verificar que todas las pruebas pasen
3. **Estudiar código**: Entender cada función
4. **Modificar**: Agregar más pruebas o tipos de datos
5. **Optimizar**: Analizar rendimiento con perfiles

---

## Contacto y Soporte

- **Documentación**: Ver `TECNICO.md`, `EJEMPLOS.md`
- **Compilación**: Ver `COMPILACION.md`
- **Código**: Ver comentarios en `arbol.c` y `arbol.h`

---

*Última actualización: 2026-06-01*  
*Proyecto: Árbol AVL Genérico - TDA*
