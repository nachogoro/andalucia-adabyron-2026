# Introducción a la solución

El problema es una simulación directa en dos fases. No hay que aplicar ningún
algoritmo especial: basta con reproducir al pie de la letra lo que describe el
enunciado.

La estructura óptima es una cola doblemente terminada (deque), que nos permite
usarla como una pila en la primera fase y como una cola en la segunda.

# Fase 1: registro y cancelación

Mantenemos una lista $S$  que funciona como una pila por el extremo derecho.
Para cada valor $P_i$ leído:

- Si $P_i \ge 0$, lo añadimos al final de $S$.
- Si $P_i < 0$, queremos eliminar los últimos $|P_i|$ elementos de $S$. Si
  $|P_i|$ excede el tamaño actual de $S$, la lista queda vacía.

# Fase 2: reordenación por bloques de 4

Recorremos $S$ en bloques consecutivos de 4 elementos. Para cada bloque
$B = [b_0, b_1, b_2, b_3]$ (el último puede tener menos elementos):

1. Primero añadimos a $E$ los elementos pares de $B$ en su orden original.
2. Después añadimos a $E$ los elementos impares de $B$, también en orden.

La implementación más limpia es hacer dos pasadas sobre el bloque: una que
copia los pares y otra que copia los impares. La complejidad total es
$O(N)$.

# Salida

La salida es una única línea con los elementos de $E$ separados por un
espacio, o la cadena `NOPROCESO` si $E$ está vacía.

> **Nota sobre el salto de línea final.** El enunciado original indica que la
> salida no lleva salto de línea al final. Durante el concurso se emitió una
> aclaración el juez para exigir el salto de línea, por lo que la solución que
> se incluye termina la salida con `'\n'` en ambos casos. Sin ese salto de
> línea, el juez rechaza la solución.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [J.cpp](src/J.cpp) | :white_check_mark: |
