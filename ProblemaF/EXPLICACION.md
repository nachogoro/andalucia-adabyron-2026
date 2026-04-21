# Introducción a la solución

El problema pide mantener un histórico de versiones de un array y permitir
consultas de suma de rangos sobre cualquier versión anterior. Cada `U`
genera una nueva versión del array (cambiando un único valor) y cada `S v l
r` pregunta por la suma de `a[l..r]` en la versión `v`.

A primera vista, el planteamiento más directo sería **guardar una copia del
array completo tras cada update**. Con $N, Q \leq 3 \cdot 10^5$, esto supone
hasta $3 \cdot 10^5$ versiones de arrays de hasta $3 \cdot 10^5$ elementos,
es decir, del orden de $9 \cdot 10^{10}$ enteros en memoria, claramente
inviable. Aunque nos limitásemos a copiar perezosamente, la suma de las
operaciones seguiría siendo cuadrática.

Por tanto, necesitamos un enfoque más inteligente: o bien una estructura
persistente que comparta memoria entre versiones (p. ej. un *persistent
segment tree*), o bien **reordenar el trabajo** para evitar tener que
reconstruir versiones pasadas. Esta última idea es mucho más sencilla de
implementar y es la que seguiremos.

## Paso 1: reordenar las queries

El problema nos obliga a contestar consultas sobre versiones arbitrarias
del array. Si procesamos las operaciones en el mismo orden en que vienen,
entonces tras aplicar un update nos encontramos en la versión más reciente,
pero una consulta posterior podría pedirnos la versión 3, o la 7, o la 0…
y no tenemos forma de "volver atrás" sin haber guardado copias previas, que
es justo lo que queremos evitar.

La clave es darse cuenta de que **no estamos obligados a responder las
consultas en el orden en que aparecen en la entrada**. El enunciado solo
exige que la salida respete ese orden; internamente podemos resolverlas en
el orden que queramos, siempre que al final las imprimamos en su posición
original.

Dicho eso, el orden natural para procesar el problema es el **orden de
versión**. Las versiones se generan siempre de manera creciente: la
versión 0 es la inicial y cada `U` produce la siguiente versión
consecutiva. Así que si recorremos las versiones de 0 a la última:

1. Empezamos con el array en su estado inicial (versión 0).
2. Antes de pasar a la versión siguiente, respondemos todas las consultas
   `S` que apuntan a la versión actual (independientemente de en qué
   posición de la entrada aparecieran).
3. Aplicamos el `U` correspondiente para avanzar a la siguiente versión.
4. Repetimos hasta agotar las versiones.

De esta forma **solo avanzamos**, nunca volvemos atrás. Cada actualización
se aplica una única vez y mantenemos una única estructura de datos que va
evolucionando. No se guarda ninguna copia del array.

En la práctica, esto se traduce en:

- Asignar a cada consulta `S` un índice de salida (su posición en la
  entrada) para poder imprimir los resultados ordenados al final.
- Agrupar las consultas por la versión a la que se refieren (por ejemplo,
  en una lista `queries[v]` por cada versión `v`).
- Recorrer `v = 0, 1, 2, ...` y, en cada paso, resolver todas las consultas
  de `queries[v]` y luego aplicar el update que lleva a `v + 1`.

El coste en memoria pasa de $O(N \cdot V)$ a $O(N + Q)$, y el trabajo se
reduce a una actualización por cada `U` y una consulta por cada `S`.

## Paso 2: estructura de datos para sumas de rangos con updates

Una vez resuelto el problema del histórico, queda responder eficientemente:

- `update(i, x)`: fijar el valor del elemento $i$ a $x$.
- `query(l, r)`: suma de $a[l..r]$.

Con $N$ y $Q$ del orden de $3 \cdot 10^5$, necesitamos ambas operaciones
en $O(\log N)$. Dos candidatos clásicos:

- **Segment tree**
- **Fenwick tree** (también conocido como *Binary Indexed Tree* o **BIT**)

Para este problema, en el que solo necesitamos sumas de prefijos con
actualizaciones puntuales, el **Fenwick tree** es la opción más directa y
compacta: mucho menos código que un segment tree, con las mismas garantías
asintóticas ($O(\log N)$ por operación y $O(N)$ en memoria). Una consulta
de rango $[l, r]$ se obtiene como $\text{prefix}(r) - \text{prefix}(l-1)$, y
un update se traduce en sumar la diferencia $x - a[i]$ al Fenwick tree en
la posición $i$.

Si no lo conoces, una buena referencia es el artículo de Wikipedia sobre
[Fenwick tree](https://en.wikipedia.org/wiki/Fenwick_tree).

## Resumen del algoritmo

1. Leer `N`, `Q` y el array inicial en un Fenwick tree de tamaño `N`.
2. Leer las `Q` operaciones:
   - Cada `U` queda asociada a la versión que genera.
   - Cada `S v l r` se guarda en `queries[v]` junto con su índice de
     salida.
3. Recorrer las versiones de 0 a la última:
   - Responder todas las consultas de `queries[v]`.
   - Aplicar el `U` que lleva a la versión `v + 1` (si existe).
4. Imprimir las respuestas en el orden original de la entrada.

La complejidad total es $O((N + Q) \log N)$ en tiempo y $O(N + Q)$ en
memoria, que cabe holgadamente dentro de los límites del problema.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [F.cpp](src/F.cpp) | :x: |
