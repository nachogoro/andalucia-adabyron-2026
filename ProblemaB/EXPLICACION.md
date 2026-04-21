# Introducción a la solución

El problema es una simple simulación.

Podemos utilizar las siguientes operaciones a nivel de bit:
- Desplazar a la derecha $i$ posiciones, seguido de AND con 0x1 para obtener el
  valor del $i$-ésimo bit.
- Desplazar a la izquierda de una posición, seguido de OR con el bit $b$ para
  añadir el bit $b$ a la derecha de un número ya existente.

Para rotar una serie de números, podemos almacenarlos en un deque (double-ended
queue): rotar en sentido horario consistirá en extraer el último elemento y
añadirlo al principio, mientras que rotar en sentido antihorario consistirá en
extraer el primer elemento y añadirlo al final.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [B.cpp](src/B.cpp) | :x: |

