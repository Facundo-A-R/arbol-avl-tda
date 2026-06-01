# Guía de Compilación y Ejecución

## Requisitos Previos

- **Sistema Operativo**: Linux, macOS o Windows (con WSL)
- **Compilador**: GCC (GNU Compiler Collection)
- **Make**: Herramienta de automatización (opcional, pero recomendada)

### Verificar que tengas los requisitos:

```bash
# Verificar versión de GCC
gcc --version

# Verificar si Make está instalado
make --version
```

---

## Opción 1: Compilación con Make (Recomendado)

### Compilar el proyecto:
```bash
make
```

### Ejecutar el programa:
```bash
make run
```

### Compilar y ejecutar en un comando:
```bash
make clean && make run
```

### Limpiar archivos compilados:
```bash
make clean
```

### Compilar con información de depuración:
```bash
make debug
```

### Ejecutar con Valgrind (detección de fugas de memoria):
```bash
make valgrind
```

---

## Opción 2: Compilación Manual sin Make

### Compilación paso a paso:

```bash
# Compilar archivo arbol.c a objeto arbol.o
gcc -Wall -Wextra -std=c99 -O2 -c arbol.c -o arbol.o

# Compilar archivo main.c a objeto main.o
gcc -Wall -Wextra -std=c99 -O2 -c main.c -o main.o

# Enlazar los objetos para crear el ejecutable
gcc -Wall -Wextra -std=c99 -O2 -o arbol_avl arbol.o main.o -lm
```

### Compilación en una sola línea:
```bash
gcc -Wall -Wextra -std=c99 -O2 -o arbol_avl arbol.c main.c -lm
```

### Ejecutar el programa:
```bash
./arbol_avl
```

---

## Explicación de Flags de Compilación

| Flag | Descripción |
|------|-------------|
| `-Wall` | Mostrar todas las advertencias |
| `-Wextra` | Mostrar advertencias adicionales |
| `-std=c99` | Usar estándar C99 |
| `-O2` | Optimización de nivel 2 (velocidad) |
| `-g` | Incluir información de depuración |
| `-O0` | Sin optimización (para depuración) |
| `-o archivo` | Especificar nombre del ejecutable |
| `-lm` | Enlazar librería matemática |
| `-c` | Compilar sin enlazar |

---

## Solución de Problemas

### Error: `gcc: command not found`
**Solución**: Instalar GCC
- **Ubuntu/Debian**: `sudo apt-get install build-essential`
- **macOS**: `xcode-select --install`
- **Windows**: Instalar MinGW o usar WSL

### Error: `make: command not found`
**Solución**: Instalar Make
- **Ubuntu/Debian**: `sudo apt-get install make`
- **macOS**: Ya incluido con Xcode
- **Windows**: Instalar desde MinGW o usar WSL

### Error de compilación con flags antiguos
**Solución**: Usar `-std=c99` explícitamente en la compilación

### Errores de memoria (detectar con Valgrind)
```bash
# Instalar Valgrind
sudo apt-get install valgrind

# Ejecutar con Valgrind
make valgrind
```

---

## Estructura de Archivos

```
arbol-avl-tda/
├── arbol.h           # Header del Árbol AVL
├── arbol.c           # Implementación del Árbol AVL
├── main.c            # Programa de prueba
├── Makefile          # Automatización de compilación
├── COMPILACION.md    # Este archivo
└── README.md         # Descripción del proyecto
```

---

## Archivos Generados Después de Compilar

```
arbol-avl-tda/
├── arbol.o           # Objeto compilado de arbol.c
├── main.o            # Objeto compilado de main.c
└── arbol_avl         # Ejecutable final
```

---

## Salida Esperada

Al ejecutar el programa, deberías ver:

1. **PRUEBA 1: ÁRBOL AVL CON ENTEROS**
   - Inserción de números
   - Métricas del árbol
   - Recorridos (in-orden, pre-orden, post-orden)
   - Búsqueda de elementos
   - Eliminación y rebalanceo

2. **PRUEBA 2: ÁRBOL AVL CON ESTRUCTURAS (PERSONAS)**
   - Creación e inserción de personas
   - Búsqueda y nivel de elementos
   - Información de mínimo y máximo
   - Eliminación con mantenimiento del balance

3. **PRUEBA 3: ROTACIONES AUTOMÁTICAS DEL ÁRBOL AVL**
   - Rotación simple derecha
   - Rotación simple izquierda
   - Rotación doble izquierda-derecha
   - Rotación doble derecha-izquierda

---

## Desarrollo y Depuración

### Compilar con información de depuración:
```bash
make debug
```

### Usar GDB (GNU Debugger):
```bash
# Compilar con información de depuración
make debug

# Iniciar GDB
gdb ./arbol_avl

# Comandos GDB útiles:
# run                 - Ejecutar el programa
# break main          - Establecer punto de quiebre
# step                - Ejecutar una línea
# continue            - Continuar ejecución
# print variable      - Imprimir valor de variable
# quit                - Salir de GDB
```

### Detectar fugas de memoria:
```bash
make valgrind
```

---

## Notas Importantes

- **Memoria dinámica**: El programa maneja correctamente la memoria dinámica
- **Genericidad**: El árbol puede almacenar cualquier tipo de dato mediante `void*`
- **Balance automático**: Las rotaciones se ejecutan automáticamente
- **Eficiencia**: Las operaciones tienen complejidad O(log n) en promedio

---

## Contacto y Soporte

Si encuentras problemas durante la compilación, verifica:
1. Que todos los archivos (`.h`, `.c`, `Makefile`) estén en el mismo directorio
2. Que tengas permisos de lectura en los archivos
3. Que el compilador GCC esté correctamente instalado

---

*Última actualización: 2026-06-01*
