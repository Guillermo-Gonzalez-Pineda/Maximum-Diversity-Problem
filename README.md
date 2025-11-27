# Problema de Máxima Diversidad - Algoritmos Exactos y de Aproximación

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.1%2B-064F8C.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-Academic-green.svg)]()

## 📋 Descripción General

Este proyecto implementa y compara múltiples algoritmos de optimización para resolver el **Problema de Máxima Diversidad (MDP)**, un problema fundamental de optimización combinatoria NP-Duro con aplicaciones en localización de instalaciones, asignación de recursos y reconocimiento de patrones.

### Definición del Problema

Dado un conjunto de *n* elementos en un espacio de *k* dimensiones, seleccionar un subconjunto de *m* elementos que maximice la suma de las distancias entre pares de elementos seleccionados.

**Definición Formal:**

```
Maximizar: z = Σ d(i,j) para todo i,j en S, i≠j
Sujeto a: |S| = m, S ⊆ {1,...,n}
```

Donde `d(i,j)` es la distancia euclidiana entre los elementos *i* y *j*.

---

## 🚀 Características

### Algoritmos Implementados

#### 1. **Algoritmo Greedy Constructivo**
- Enfoque basado en centros de gravedad
- Selecciona iterativamente elementos más alejados del centroide
- Complejidad temporal: O(n·m·k)
- Heurística base rápida

#### 2. **GRASP (Greedy Randomized Adaptive Search Procedure)**
- Construcción semi-greedy aleatorizada con Lista de Candidatos Restringida (LRC)
- Estrategia multi-arranque con iteraciones configurables
- Mecanismo de diversificación adaptativa
- Tamaño de LRC configurable (2-3 elementos)

#### 3. **Búsqueda Local**
- Vecindario basado en intercambios con primera mejora
- Aplicada como post-optimización a métodos constructivos
- Continúa hasta alcanzar un óptimo local

#### 4. **Ramificación y Poda (Algoritmo Exacto)**
- Exploración completa con poda inteligente
- **Cálculo de cota superior** utilizando:
  - z₁: Valor de la solución parcial actual
  - z₂: Distancias a elementos ya seleccionados
  - z₃: Promedio de distancias a los k-1 candidatos más lejanos
- Dos estrategias de selección:
  - **Estándar**: Mejor nodo primero
  - **Modificada**: Segundo mejor nodo primero (variante experimental)
- Cota inferior inicial desde heurísticas greedy o GRASP

#### 5. **Métodos Híbridos**
- Greedy + Búsqueda Local
- GRASP + Búsqueda Local
- Combina velocidad de construcción con calidad de refinamiento

---

## 📁 Estructura del Proyecto

```
.
├── code/
│   ├── include/              # Archivos de cabecera
│   │   ├── problem_instance.h
│   │   ├── solution.h
│   │   ├── greedy_algorithm.h
│   │   ├── grasp_algorithm.h
│   │   ├── grasp_runner.h
│   │   ├── local_search.h
│   │   ├── branch_and_bound_solver.h
│   │   ├── bnb_node.h
│   │   ├── parser_data.h
│   │   ├── table_generator.h
│   │   └── utils.h
│   │
│   ├── src/                  # Archivos de implementación
│   │   ├── problem_instance.cpp
│   │   ├── solution.cpp
│   │   ├── greedy_algorithm.cpp
│   │   ├── grasp_algorithm.cpp
│   │   ├── grasp_runner.cpp
│   │   ├── local_search.cpp
│   │   ├── branch_and_bound_solver.cpp
│   │   ├── bnb_node.cpp
│   │   ├── parser_data.cpp
│   │   ├── table_generator.cpp
│   │   └── utils.cpp
│   │
│   ├── main.cpp              # Punto de entrada principal
│   ├── CMakeLists.txt        # Configuración de compilación
│   ├── build/                # Salida de compilación Release
│   └── debug/                # Salida de compilación Debug
│
├── data/                     # Instancias de prueba
│   ├── max_div_15_2.txt
│   ├── max_div_15_3.txt
│   ├── max_div_20_2.txt
│   ├── max_div_20_3.txt
│   ├── max_div_30_2.txt
│   └── max_div_30_3.txt
│
└── README.md
```

---

## 🔧 Instrucciones de Compilación

### Requisitos Previos

- Compilador compatible con C++17 (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.1 o superior
- Entorno Linux/Unix (probado en Ubuntu/Debian)

### Compilación

#### Compilación Release (Optimizada)

```bash
cd code
mkdir -p build
cd build
cmake ..
make
```

El ejecutable `MaximumDiversity` se creará en `code/build/`.

#### Compilación Debug (con símbolos de depuración)

```bash
cd code
mkdir -p debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

El ejecutable se creará en `code/debug/`.

---

## 🎮 Uso

### Modos de Ejecución

El programa soporta tres modos de ejecución:

#### 1. Modo de Algoritmos de Aproximación

```bash
cd code/build
./MaximumDiversity approx
```

Ejecuta y compara:
- Greedy
- Greedy + Búsqueda Local
- GRASP + Búsqueda Local (con múltiples configuraciones)

#### 2. Modo de Algoritmo Exacto

```bash
./MaximumDiversity exact
```

Ejecuta Ramificación y Poda con:
- Solución inicial Greedy
- Solución inicial GRASP

#### 3. Modo R&P Modificado (Experimental)

```bash
./MaximumDiversity exact_mod
```

Ejecuta Ramificación y Poda con estrategia de selección del segundo mejor nodo.

### Formato de Entrada

Los archivos de entrada deben seguir esta estructura:

```
n k
x₁₁ x₁₂ ... x₁ₖ
x₂₁ x₂₂ ... x₂ₖ
...
xₙ₁ xₙ₂ ... xₙₖ
```

Donde:
- `n`: número de elementos
- `k`: dimensión del espacio
- Cada línea representa las coordenadas de un elemento

**Nota**: El programa maneja automáticamente valores separados por comas y los convierte a puntos.

---

## 📊 Formato de Salida

### Salida de Algoritmos de Aproximación

```
Problema        n       K       m       z         S                             CPU
max_div_15_2    15      2       2       47.85     {0, 14}                       0.00012450
```

### Salida de Algoritmo Exacto

```
Problema        n       K       m       z         S                             CPU             Nodos
max_div_15_2    15      2       2       47.85     {0, 14}                       0.12345678      127
```

**Columnas:**
- `Problema`: Nombre de la instancia
- `n`: Número total de elementos
- `K`: Dimensión del espacio
- `m`: Tamaño del subconjunto
- `z`: Valor de la función objetivo (suma de distancias)
- `S`: Índices de elementos seleccionados
- `CPU`: Tiempo de ejecución en milisegundos
- `Nodos`: Número de nodos generados (solo Ramificación y Poda)

---

## 🧪 Configuración Experimental

### Instancias de Prueba

Se incluyen seis instancias de referencia:
- **Pequeñas**: 15 elementos (2D y 3D)
- **Medianas**: 20 elementos (2D y 3D)
- **Grandes**: 30 elementos (2D y 3D)

### Configuraciones de Parámetros

- **Valores de m**: 2, 3, 4, 5 (tamaños de subconjunto)
- **Configuraciones GRASP**:
  - Tamaños de LRC: 2, 3
  - Iteraciones: 10, 20
- **Total de combinaciones GRASP**: 4 × 2 × 2 = 16 por instancia

---

## 🏗️ Arquitectura

### Componentes Principales

#### `ProblemInstance`
Encapsula los datos del problema:
- Coordenadas de elementos
- Matriz de distancias precalculada
- Información dimensional

#### `Solution`
Representa una solución con:
- Índices de elementos seleccionados
- Valor de la función objetivo
- Metadatos de ejecución (tiempo CPU, parámetros)

#### `GreedyAlgorithm` / `GraspAlgorithm`
Heurísticas constructivas que implementan diferentes estrategias de selección.

#### `LocalSearch`
Mejora post-optimización usando exploración de vecindario basado en intercambios.

#### `BranchAndBoundSolver`
Solucionador exacto con:
- Cola de prioridad para gestión de nodos
- Cálculo de cota superior para poda
- Métodos configurables de solución inicial

#### `BnBNode`
Nodo del árbol de Ramificación y Poda que contiene:
- Estado de solución parcial
- Estimación de cota superior
- Candidatos restantes

---

## 🔬 Detalles Algorítmicos

### Cota Superior de Ramificación y Poda

Para una solución parcial con *s* elementos seleccionados, la cota superior es:

```
UB = z₁ + Σᵢ₌₁ᵐ⁻ˢ (z₂(cᵢ) + z₃(cᵢ))
```

Donde:
- **z₁**: Suma de distancias entre elementos ya seleccionados
- **z₂(cᵢ)**: Suma de distancias del candidato *cᵢ* a elementos seleccionados
- **z₃(cᵢ)**: Distancia promedio de *cᵢ* a sus *(m-s-1)* candidatos restantes más lejanos

Los candidatos se ordenan por *z₂ + z₃* y se utilizan los *(m-s)* primeros.

### Análisis de Complejidad

| Algoritmo              | Complejidad Temporal | Complejidad Espacial |
|------------------------|---------------------|---------------------|
| Greedy                 | O(n·m·k)            | O(n·k)           |
| GRASP                  | O(I·n·m·k)          | O(n·k)           |
| Búsqueda Local         | O(n·m²)             | O(n)             |
| Ramificación y Poda    | O(2ⁿ) peor caso   | O(n·m)           |

Donde: *I* = número de iteraciones de GRASP

---

## 📈 Características de Rendimiento

### Greedy
- **Ventajas**: Rápido, determinístico, buenas soluciones iniciales
- **Desventajas**: Decisiones miopes, sin diversificación

### GRASP
- **Ventajas**: Mejor exploración, aleatorización controlada
- **Desventajas**: Más lento, requiere ajuste (tamaño LRC, iteraciones)

### Búsqueda Local
- **Ventajas**: Mejoras consistentes, convergencia rápida
- **Desventajas**: Sensible a la calidad de la solución inicial

### Ramificación y Poda
- **Ventajas**: Garantiza solución óptima
- **Desventajas**: Crecimiento exponencial para instancias grandes

### Métodos Híbridos
- **Ventajas**: Balance entre calidad y eficiencia
- **Desventajas**: Tiempo de ejecución acumulativo

---

## 💡 Casos de Uso

El Problema de Máxima Diversidad tiene aplicaciones en:

1. **Localización de Instalaciones**: Distribuir instalaciones para maximizar cobertura
2. **Selección de Portafolios**: Diversificar carteras de inversión
3. **Selección de Características**: Elegir características diversas en aprendizaje automático
4. **Colocación de Sensores**: Posicionar sensores para maximizar cobertura
5. **Asignación de Recursos**: Distribuir recursos en sistemas heterogéneos

---

## 🧑‍💻 Calidad del Código

### Principios de Diseño

- **Separación de Responsabilidades**: Límites claros de módulos
- **Responsabilidad Única**: Cada clase tiene un propósito bien definido
- **DRY (Don't Repeat Yourself)**: Utilidades compartidas en `utils.h/cpp`
- **RAII**: Gestión de recursos mediante constructores/destructores
- **Corrección de Const**: Uso apropiado de calificadores const

### Flags de Compilación

**Modo Release:**
```cmake
-O3                    # Optimización máxima
```

**Modo Debug:**
```cmake
-g                     # Símbolos de depuración
-O0                    # Sin optimización
-Wall                  # Todas las advertencias
-Wextra                # Advertencias extra
-Wpedantic             # Advertencias pedantes
-Weffc++               # Advertencias de C++ efectivo
```

---

## 📚 Referencias

### Conceptos Clave

1. **Problema de Máxima Diversidad**: Optimización combinatoria NP-hard
2. **Algoritmos Greedy**: Heurísticas constructivas con decisiones locales
3. **GRASP**: Feo, T. A., & Resende, M. G. (1995). Greedy randomized adaptive search procedures
4. **Ramificación y Poda**: Optimización exacta con poda inteligente
5. **Búsqueda Local**: Métodos de mejora basados en vecindario

---


## 👨‍🎓 Autor

**Guillermo González Pineda**
- alu0101574899@ull.edu.es
- Universidad de La Laguna
- Escuela Superior de Ingeniería y Tecnología
- Grado en Ingeniería Informática

---

## 📄 Licencia

Este proyecto ha sido desarrollado con fines académicos en la Universidad de La Laguna.
