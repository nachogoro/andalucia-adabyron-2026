# Problema J - El planificador de procesos de AByronOS

Tiempo: 1,0 s

El equipo de desarrollo del sistema operativo AByronOS está finalizando una
nueva versión del planificador de procesos. Hasta ahora, los procesos se
atendían estrictamente según el orden de llegada, pero el nuevo sistema
incorpora cancelaciones y clasificaciones por prioridades, permitiendo una
gestión más eficiente de la carga del sistema. Para validar su
funcionamiento, debes simular exactamente cómo se planifican los procesos
recibidos y generar la lista final de procesos en el orden en que serán
enviados a ejecución.

El procesamiento consta de dos fases:

### FASE 1. Registro y cancelación de procesos

El sistema recibe $N$ valores en orden $P_1, P_2, \dots, P_N$. Cada $P_i$ es
un número entero y representa:

- **Llegada de procesos**. Si $P_i \geq 0$, representa el PID del proceso a
  incluir:
  - El proceso se registra y se añade al final de la lista $S$.
- **Cancelación de procesos**. Si $P_i < 0$, representa el número de procesos
  a cancelar:
  - El planificador debe eliminar $|P_i|$ procesos del final de la lista $S$.
  - Si $|P_i|$ es mayor que el número de procesos actuales en $S$, entonces
    $S$ se queda vacía.

Al finalizar esta fase, la lista $S$ contiene los procesos válidos en orden
para la fase 2.

### FASE 2. Organización en la cola de ejecución

A partir de $S$, se genera la lista final $E$:

- La lista $S$ se divide en bloques consecutivos de 4 procesos (el último
  bloque puede tener menos elementos). Para cada bloque:
  1. Primero se incluyen los procesos **pares** del bloque (manteniendo su
     orden).
  2. Después se incluyen los procesos **impares** del bloque (manteniendo su
     orden).
- La lista final $E$ es la concatenación, bloque a bloque, de los bloques
  reorganizados. **La agrupación es por bloque, no global.**

## Entrada
Una línea que contiene $N$ enteros: $P_1, P_2, \dots, P_N$:

- $10 \leq N \leq 10^5$.
- $-10^9 \leq P_i \leq 10^9$.

## Salida
Una línea que contiene los valores de $E$:

- Si $E$ tiene elementos: los elementos de $E$ separados por un espacio, sin
  espacios adicionales ni salto de línea al final.
- Si $E$ está vacía: se imprimirá $NOPROCESO$, sin espacios adicionales ni
  salto de línea al final.

## Entrada de ejemplo
```
5 2 9 12 7 8 -1 -2 4 11 6
```

## Salida de ejemplo
```
2 4 5 9 6 11
```

### Explicación paso a paso

**Fase 1. Registro y cancelaciones**

- $5 \to S = [5]$
- $2 \to S = [5, 2]$
- $9 \to S = [5, 2, 9]$
- $12 \to S = [5, 2, 9, 12]$
- $7 \to S = [5, 2, 9, 12, 7]$
- $8 \to S = [5, 2, 9, 12, 7, 8]$
- $-1 \to$ cancelación de 1 proceso $\to S = [5, 2, 9, 12, 7]$
- $-2 \to$ cancelación de 2 procesos $\to S = [5, 2, 9]$
- $4 \to S = [5, 2, 9, 4]$
- $11 \to S = [5, 2, 9, 4, 11]$
- $6 \to S = [5, 2, 9, 4, 11, 6]$

**Fase 2. Organización por bloques**

Dividimos $S = [5, 2, 9, 4, 11, 6]$ en bloques de 4:

- $[5, 2, 9, 4]$
  - Pares: $[2, 4]$ (en el orden del bloque)
  - Impares: $[5, 9]$ (en el orden del bloque)
  - Orden del bloque: $[2, 4, 5, 9]$
- $[11, 6]$ (bloque no completo por falta de elementos)
  - Pares: $[6]$
  - Impares: $[11]$
  - Orden del bloque: $[6, 11]$

$E = [2, 4, 5, 9, 6, 11]$
Salida: `2 4 5 9 6 11`
