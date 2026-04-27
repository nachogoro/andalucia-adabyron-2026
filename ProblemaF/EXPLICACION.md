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

# Alternativa 1: Fenwick tree persistente

El truco anterior aprovecha que el problema permite resolver las
consultas en cualquier orden (offline). Si los updates y las consultas
tuviesen que atenderse en el momento (como pasaría en un sistema de
control de versiones de verdad), ya no se podría reordenar y haría
falta una estructura que mantuviese explícitamente todas las versiones
a la vez.

## Recordatorio de cómo funciona un Fenwick

En un Fenwick tree clásico, `bit[i]` no almacena `a[i]` directamente:
guarda la suma de un rango de longitud `lowbit(i)` que termina en `i`,
es decir,

$$
\text{bit}[i] = a[i - \text{lowbit}(i) + 1] + \dots + a[i],
$$

donde $\text{lowbit}(i) = i \,\&\, (-i)$. Por ejemplo, con $N = 8$:

| $i$ | rango cubierto |
| :-: | :-----------: |
| 1   | $[1, 1]$      |
| 2   | $[1, 2]$      |
| 3   | $[3, 3]$      |
| 4   | $[1, 4]$      |
| 5   | $[5, 5]$      |
| 6   | $[5, 6]$      |
| 7   | $[7, 7]$      |
| 8   | $[1, 8]$      |

Con esa convención:

- `prefix(i)` (suma de $a[1..i]$) baja desde `i` saltando con
  `i -= lowbit(i)` y acumula los `bit[i]` que va tocando, $O(\log N)$
  posiciones en total.
- `update(i, delta)` sube desde `i` con `i += lowbit(i)` sumando
  `delta` en cada `bit[i]` que toca, también $O(\log N)$ posiciones.

Ese conjunto de $O(\log N)$ posiciones es la huella del nodo en la
estructura, y es lo único que cambia entre versiones consecutivas.

## Modificación necesaria para mantener versiones

Como cada update modifica únicamente $O(\log N)$ celdas del Fenwick, lo
único que necesitamos para reconstruir el estado en cualquier versión es
saber **qué valor tenía cada celda en cada versión**. Pero la mayoría
de las celdas no cambian de una versión a la siguiente, así que no tiene
sentido guardar copias completas.

En su lugar, cada celda guarda solo los puntos en los que su valor
cambia: una lista de pares $(\text{version},\ \text{valor})$. La lista
queda automáticamente ordenada por versión porque las inserciones llegan
siempre en el orden en que se aplican los updates.

Para consultar `bit[i]` en la versión $v$ basta con localizar el último
par de la lista cuyo $\text{version} \leq v$: el valor de esa entrada es
el que tenía la celda en ese momento, porque después no hubo otro update
que la tocase hasta el siguiente par. Como la lista está ordenada,
es una búsqueda binaria.

## Operaciones detalladas

**Update de `a[i]` a $x$ en la versión $v$.** Calculamos el incremento
$\Delta = x - a[i]$ y recorremos las $O(\log N)$ posiciones del Fenwick
afectadas. Para cada una de ellas, leemos el último valor registrado
(el final de su lista), le sumamos $\Delta$ y añadimos un nuevo par
$(v,\ \text{último} + \Delta)$. La lista crece en una entrada y queda
ordenada porque $v$ es estrictamente mayor que cualquier versión
anterior.

**Consulta `S v l r`.** Calculamos
$\text{prefix}(v, r) - \text{prefix}(v, l-1)$. Cada llamada a
`prefix(v, j)` recorre las $O(\log N)$ posiciones que tocaría un
Fenwick normal y, en cada una, hace una búsqueda binaria sobre la lista
de esa posición para localizar el valor en la versión $v$. La búsqueda
binaria cuesta $O(\log Q)$ porque la lista tiene a lo sumo una entrada
por update.

## Coste

- Updates: $O(Q \log N)$.
- Consultas: $O(Q \log N \cdot \log Q)$ (un $\log Q$ extra por la
  búsqueda binaria en cada celda visitada).
- Memoria: $O(N + Q \log N)$.

Frente a la versión offline gana en que responde online; frente al
segment tree persistente, gana en sencillez de código pero pierde un
factor $\log Q$ por consulta.

# Alternativa 2: segment tree persistente

## El segment tree de partida

Un segment tree para sumas es un árbol binario (casi) balanceado: cada
hoja corresponde a una posición del array y cada nodo interno guarda la
suma del rango de sus dos hijos. Una consulta de rango baja desde la
raíz y combina como mucho $O(\log N)$ nodos para cubrir el intervalo
pedido. Un update de una posición sube desde la hoja correspondiente
hasta la raíz, recalculando $O(\log N)$ nodos en el camino.

Como un update solo modifica los nodos del camino de la raíz al nodo
hoja afectado. Todo el resto del árbol (del orden de
$2N - O(\log N)$ nodos) sigue siendo correcto. Esa observación es la
que abre la puerta a la persistencia.

## Modificación necesaria para mantener versiones

En vez de modificar los nodos del camino, los duplicamos: para cada
nodo del camino creamos uno nuevo con los nuevos valores, y dejamos los
originales intactos. Los nodos del nuevo camino apuntan, en sus
"lados no afectados", a los mismos hijos que en la versión anterior.
Así cada update genera $O(\log N)$ nodos nuevos y deja los demás
$2N - O(\log N)$ nodos compartidos entre la versión vieja y la nueva.

Cada versión $v$ se identifica por el índice de su raíz, que se
guarda en un array $\text{roots}[v]$. La versión $0$ es la raíz del
árbol original; cada update produce una nueva raíz que se añade al
array.

## Ejemplo con $N = 4$

Partimos del array $[3, 1, 4, 1]$. El árbol inicial (versión $0$)
podría dibujarse así (cada nodo lleva su rango y su suma):

```
            [1..4]=9                <-- roots[0]
           /         \
       [1..2]=4    [3..4]=5
       /     \      /     \
    [1]=3 [2]=1  [3]=4  [4]=1
```

Si ahora aplicamos `U 3 10` (cambiar $a[3]$ de 4 a 10), el camino
afectado es la rama que va a $[3]$, es decir, raíz → $[3..4]$ → $[3]$.
Creamos tres nodos nuevos para ese camino y los demás los reusamos:

```
   roots[0]: [1..4]=9
              /     \
       [1..2]=4    [3..4]=5
       /   \       /     \
    [1]=3 [2]=1  [3]=4  [4]=1

   roots[1]: [1..4]=15        <-- nodo nuevo
              /     \
       [1..2]=4    [3..4]=11   <-- nodo nuevo
       (compart.)   /     \
                 [3]=10  [4]=1   <-- [3]=10 es nuevo; [4]=1 se comparte
```

La rama izquierda completa de la nueva raíz apunta al mismo $[1..2]$ de
la versión $0$, sin copiar nada. Hemos creado tres nodos para
representar la nueva versión, y todos los nodos no afectados se
comparten entre las dos versiones. La memoria por update queda en
$O(\log N)$.

## Operaciones detalladas

**Update.** Una función recursiva que recibe la raíz `prev` de la
versión vigente, el rango actual y la posición a modificar. En cada
nivel, crea un nodo nuevo y elige un hijo: el lado afectado es
recursivo (recibe la raíz hija de `prev`); el otro lado se copia tal
cual del nodo `prev`. Devuelve el índice del nuevo nodo creado en este
nivel. La raíz devuelta por la llamada de mayor nivel es la nueva raíz
para el array `roots`.

**Consulta.** Igual que en un segment tree no persistente, pero
arrancando desde `roots[v]` en lugar de la raíz "actual". Se suman los
nodos cuyo rango está totalmente contenido en el intervalo de la
consulta y se desciende cuando hay solapamiento parcial.

## Coste

- Updates: $O(\log N)$ tiempo y $O(\log N)$ nodos nuevos por update.
- Consultas: $O(\log N)$.
- Memoria: $O(N + Q \log N)$ nodos en total.

Estrictamente más rápido que el Fenwick persistente (perdemos el
$\log Q$ por consulta) pero el código es más largo.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [F.cpp](src/F.cpp) | Reordenación offline de queries por versión + Fenwick tree | :white_check_mark: |
| [F_fenwickper.cpp](src/F_fenwickper.cpp) | Fenwick tree persistente con lista de pares (versión, valor) por posición | :white_check_mark: |
| [F_persistente.cpp](src/F_persistente.cpp) | Segment tree persistente; responde online manteniendo todas las versiones | :white_check_mark: |
