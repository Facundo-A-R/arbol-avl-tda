# ============================================================================
# MAKEFILE: Compilación del Árbol AVL Genérico + Persona TDA
# ============================================================================
# 
# Este Makefile automatiza la compilación del proyecto del Árbol AVL.
# 
# Comandos disponibles:
#   make              - Compila el proyecto
#   make clean        - Elimina archivos compilados
#   make run          - Compila y ejecuta el programa
#   make debug        - Compila con información de depuración
#   make valgrind     - Ejecuta con Valgrind (detección de fugas de memoria)
#
# ============================================================================

# ============================================================================
# VARIABLES DE COMPILACIÓN
# ============================================================================

# Compilador de C a usar
CC = gcc

# Flags de compilación
# -Wall: Mostrar todas las advertencias
# -Wextra: Mostrar advertencias adicionales
# -std=c99: Usar estándar C99
# -O2: Optimización de nivel 2
CFLAGS = -Wall -Wextra -std=c99 -O2

# Flags para compilación con depuración
# -g: Incluir información de depuración
# -O0: Sin optimización (para depuración)
DEBUG_FLAGS = -Wall -Wextra -std=c99 -g -O0

# Librerías a enlazar
LIBS = -lm

# ============================================================================
# ARCHIVOS DEL PROYECTO
# ============================================================================

# Archivos fuente (.c)
SOURCES = arbol.c main.c persona.c

# Archivos objeto (.o) generados durante la compilación
OBJECTS = $(SOURCES:.c=.o)

# Archivos header (.h)
HEADERS = arbol.h persona.h

# Nombre del ejecutable final
EXECUTABLE = arbol_avl

# ============================================================================
# OBJETIVOS (TARGETS)
# ============================================================================

# Objetivo por defecto: compilar el proyecto
all: $(EXECUTABLE)

# Crear el ejecutable a partir de los objetos
# $^ = todos los prerrequisitos (archivos .o)
# $@ = nombre del objetivo (ejecutable)
$(EXECUTABLE): $(OBJECTS)
	@echo "Enlazando... $@"
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "✓ Compilación exitosa: $(EXECUTABLE)"

# Compilar archivos .c a archivos .o
# $< = primer prerrequisito (archivo .c)
# $@ = nombre del objetivo (archivo .o)
%.o: %.c $(HEADERS)
	@echo "Compilando... $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
# -f: No preguntar, solo eliminar
# -v: Mostrar archivos eliminados
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "✓ Limpieza completada"

# Compilar y ejecutar el programa
run: $(EXECUTABLE)
	@echo ""
	@echo "Ejecutando $(EXECUTABLE)..."
	@echo ""
	./$(EXECUTABLE)

# Compilar con información de depuración
debug: clean
	@echo "Compilando con información de depuración..."
	$(CC) $(DEBUG_FLAGS) -o $(EXECUTABLE) $(SOURCES) $(LIBS)
	@echo "✓ Compilación de depuración exitosa"

# Ejecutar con Valgrind para detectar fugas de memoria
# --leak-check=full: Realizar verificación completa de fugas
# --show-leak-kinds=all: Mostrar todas las clases de fugas
# --track-origins=yes: Rastrear el origen de datos no inicializados
valgrind: debug
	@echo ""
	@echo "Ejecutando con Valgrind (detección de fugas de memoria)..."
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXECUTABLE)

# Compilar sin optimización (útil para depuración)
unoptimized:
	@echo "Compilando sin optimización..."
	$(CC) -Wall -Wextra -std=c99 -g -o $(EXECUTABLE) $(SOURCES) $(LIBS)
	@echo "✓ Compilación sin optimización exitosa"

# Objetivo ficticio (phony) para que make no busque archivos con estos nombres
.PHONY: all clean run debug valgrind unoptimized

# ============================================================================
# INFORMACIÓN DEL PROYECTO
# ============================================================================

# Mostrar información del proyecto
info:
	@echo "========================================"
	@echo "Proyecto: Árbol AVL Genérico + Persona TDA"
	@echo "========================================"
	@echo "Archivos fuente: $(SOURCES)"
	@echo "Archivos header: $(HEADERS)"
	@echo "Ejecutable: $(EXECUTABLE)"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "========================================"

.PHONY: info
