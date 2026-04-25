# Introducción a la solución

El problema pide repartir los $N$ tramos de muralla entre como mucho $K$
brigadas de modo que cada brigada reciba un bloque **contiguo** de tramos y
que la brigada con más trabajo (la más lenta) termine cuanto antes, ya que
el reparto acaba cuando la última brigada finaliza su parte.

Se trata de un problema de **"minimizar el máximo"**: queremos el menor valor
$H$ para el cual existe un reparto válido en el que ninguna brigada acumule más
de $H$ horas.

## Estrategias que no funcionan

Antes de llegar a la idea correcta, podemos descartar algunas ideas
naturales para entender qué propiedades del problema nos condicionan.

### Fuerza bruta: probar todos los repartos

La primera idea que viene a la cabeza es probarlos todos y quedarnos con el
mejor. Esta opción es inviable por el tamaño del problema.

Repartir los $N$ tramos entre $K$ brigadas respetando la contigüidad
equivale a elegir los puntos de corte: hay $N - 1$ huecos entre tramos
consecutivos y tenemos que escoger $K - 1$ de ellos para separar las
brigadas. Eso da $\binom{N - 1}{K - 1}$
repartos distintos con $K$ brigadas no vacías (si permitimos brigadas
vacías, el número es aún mayor: $\binom{N + K - 1}{K - 1}$).

Con los límites del problema, $N, K \leq 10^5$, este número es
astronómico: para $N = 10^5$ y $K = 50$, por ejemplo, $\binom{99\,999}{49}$
ya es del orden de $10^{180}$.

### Repartir la carga total entre $K$ a partes iguales

Otra intuición es: "si la suma total de horas es $T$, cada brigada
debería hacer $T / K$ horas". Pero los tramos son **indivisibles y
contiguos**, así que no podemos ajustar la carga con esa precisión. Si
existe un tramo con $h_i > T / K$, esa supuesta cota inferior ya es
inalcanzable: ese tramo, él solo, fuerza a alguna brigada a trabajar más
de $T/K$. Por ejemplo, con $h = [48, 12, 0, 20, 50]$ y $K = 2$ la media es
$65$, pero la respuesta óptima es $70$.

### Asignar cada tramo a la brigada menos cargada

Un greedy tipo *load balancing* ("pon el siguiente tramo en la brigada
que lleve menos horas") resolvería el problema si las brigadas pudieran
coger tramos cualesquiera, pero aquí cada brigada debe trabajar sobre
**tramos contiguos**. Saltar de un extremo al otro de la muralla no está
permitido, así que este tipo de reparto no es válido aunque diera un
máximo más bajo.

### Programación dinámica directa

También se puede plantear una DP: sea $f(i, k)$ el mínimo del máximo al
repartir los primeros $i$ tramos entre $k$ brigadas. La recurrencia
$f(i, k) = \min_{j < i} \max\bigl(f(j, k-1),\; h_{j+1} + \dots + h_i\bigr)$
es correcta, pero cuesta $O(N^2 K)$ tiempo y $O(N K)$ memoria. Con $N, K
\leq 10^5$, ni el tiempo ni la memoria entran dentro de los límites.

## Estrategia óptima: reformular como un problema de decisión

En lugar de buscar directamente el $H$ óptimo, es mucho más cómodo
responder a la pregunta auxiliar:

> Dado un valor $H$, ¿existe un reparto en $K$ bloques contiguos tal que ningún
> bloque tenga una suma superior a $H$?

Llamemos a este predicado $\text{factible}(H)$. Vemos que $\text{factible}$
es **monótono**: si con $H$ horas podemos repartir el trabajo, con $H + 1$
también podemos (basta con el mismo reparto). Y, al revés, si $H$ no es
suficiente, ningún valor menor lo será.

Esa monotonía es exactamente lo que necesitamos para aplicar **búsqueda
binaria** sobre $H$.

## Paso 1: búsqueda binaria sobre la respuesta

Los extremos naturales del intervalo de búsqueda son:

- **Cota inferior** $\text{lo} = \max_i h_i$. Ninguna brigada puede hacer
  menos horas que el tramo más grande, porque un tramo es indivisible.
- **Cota superior** $\text{hi} = \sum_i h_i$. Con una única brigada que
  haga toda la muralla, nunca hacen falta más horas que la suma total.

Iteramos:

1. $\text{mid} = (\text{lo} + \text{hi}) / 2$
2. Si $\text{factible}(\text{mid})$, el óptimo es $\leq \text{mid}$, así que
   $\text{hi} = \text{mid}$.
3. Si no, hace falta más tiempo, así que $\text{lo} = \text{mid} + 1$.

Terminamos cuando $\text{lo} = \text{hi}$; ese valor es la respuesta.

Cada iteración reduce el rango a la mitad, por lo que hacemos
$O(\log(\sum h_i))$ pasos.

## Paso 2: comprobar $\text{factible}(H)$ de forma greedy

Queda decidir, para un $H$ dado, si existe un reparto válido en como mucho
$K$ bloques contiguos. La clave es que se puede hacer con una estrategia
**greedy** muy sencilla:

1. Empezamos con una brigada vacía y un acumulador $s = 0$.
2. Recorremos los tramos en orden. Para cada $h_i$:
   - Si $s + h_i \leq H$, el tramo entra en la brigada actual:
     $s \gets s + h_i$.
   - Si no, cerramos la brigada actual (tal como está) y abrimos una nueva
     que empieza con $h_i$: $s \gets h_i$.
3. Al terminar, contamos cuántas brigadas hemos usado. $\text{factible}(H)$
   es cierto si y solo si hemos usado $\leq K$ brigadas.

Además, si en algún momento aparece un tramo con $h_i > H$, la respuesta
es inmediatamente "no": ese tramo no cabe ni siquiera en una brigada vacía.
Por eso empezamos la búsqueda binaria con $\text{lo} = \max_i h_i$.

Para cada $H$ que probemos, deberemos recorrer una vez el vector, luego el
coste de cada comprobación es $O(N)$, donde $N$ es el número de tramos de la
muralla.

### Optimización: evitar recorrer la muralla entera en cada comprobación

El greedy lineal ya resuelve $\text{factible}(H)$ en $O(N)$, pero podemos
hacerlo todavía más rápido observando que la estrategia "*mete el
siguiente tramo en la brigada actual siempre que quepa*" es equivalente a
decir: *"extiende la brigada actual el mayor bloque contiguo posible
empezando donde toca, con suma $\leq H$"*.

Enfocado así, ya no tiene por qué recorrerse el array tramo a tramo: el
final de cada brigada se puede localizar directamente con una **búsqueda
binaria sobre las sumas prefijas**.

#### Precomputación

Calculamos una vez el array de sumas prefijas:
$P_0 = 0,\qquad P_i = h_1 + h_2 + \dots + h_i$.

Como los $h_i$ son no negativos, $P$ es **no decreciente**. La suma del
bloque $(l, r]$ (tramos $l+1, \dots, r$) es simplemente $P_r - P_l$.

#### Algoritmo de factibilidad

Para un $H$ fijado:

1. $\text{pos} = 0$, $\text{brigadas} = 0$.
2. Mientras $\text{pos} < N$ y $\text{brigadas} < K$:
   - Buscamos con **búsqueda binaria** sobre $P$ el mayor índice $j$ tal
     que $P_j \leq P_{\text{pos}} + H$. Ese $j$ es el final del bloque
     contiguo más largo que puede asumir la brigada actual empezando en
     $\text{pos} + 1$.
   - Si $j = \text{pos}$, significa que el siguiente tramo por sí solo
     excede $H$: ninguna brigada puede empezar aquí, así que
     $\text{factible}(H)$ es falso.
   - Avanzamos: $\text{pos} \gets j$, $\text{brigadas} \gets
     \text{brigadas} + 1$.
3. Al salir del bucle, $\text{factible}(H)$ es cierto si y solo si
   $\text{pos} = N$ (hemos cubierto toda la muralla con como mucho $K$
   brigadas).

En otras palabras: asignamos a cada una de las $K$ brigadas la sección
contigua más larga que cumple la restricción de $H$. Si con eso agotamos
la muralla, el reparto es posible; si no, no.

### Complejidad del test

Cada brigada se resuelve con una búsqueda binaria de coste $O(\log N)$, y
hacemos como mucho $K$ iteraciones: $O(K \log N)$
por llamada a $\text{factible}(H)$, en lugar de $O(N)$. Cuando $K \ll N$, la
mejora es notable; en el peor caso $K = N$ no mejora al lineal, pero tampoco
empeora mucho.

## Complejidad total

- Precomputación de sumas prefijas: $O(N)$.
- Búsqueda binaria externa sobre $H$: $O(\log(\sum h_i))$ iteraciones.
- Cada iteración llama a $\text{factible}(H)$ con coste $O(K \log N)$.

Coste total: $O\bigl(N + K \log N \cdot \log(\sum h_i)\bigr)$, que con
$N, K \leq 10^5$ y $h_i \leq 10^9$ queda holgadamente dentro del límite de
tiempo.

(Si se usa el test lineal del Paso 3, el coste total es $O(N \log(\sum h_i))$,
que también cumple.)

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [G.cpp](src/G.cpp) | :white_check_mark: |
