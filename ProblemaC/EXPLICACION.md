# Introducción a la solución

El enunciado pide la mayor cantidad de fines de semana consecutivos,
empezando por el primero, en los que se puede programar un espectáculo
respetando las dos restricciones de polvos: cada polvo se utiliza a lo
sumo en un espectáculo de toda la temporada, y los polvos inestables de
un fin de semana deben compensarse con al menos esa cantidad de
polvos neutralizantes en el siguiente.

La estrategia se divide en dos partes:

1. Búsqueda binaria sobre la longitud $k$ de la temporada. La
   factibilidad es monótona en $k$: si se pueden programar los
   $k + 1$ primeros fines de semana, los $k$ primeros también
   (las restricciones de la versión corta son un subconjunto de las
   de la larga).
2. Para cada candidato $k$, decidir si se puede programar la temporada
   de longitud $k$ se reduce a un problema 2-SAT, que se resuelve en
   tiempo lineal sobre su grafo de implicación.

# 2-SAT y grafo de implicación

2-SAT es el caso particular de SAT en el que cada cláusula tiene
exactamente dos literales:

$$
(\ell_{1,1} \lor \ell_{1,2}) \land (\ell_{2,1} \lor \ell_{2,2}) \land \dots
$$

A diferencia de SAT general (que es NP-completo), 2-SAT se resuelve en
tiempo lineal apoyándose en un grafo dirigido llamado _grafo de implicación_.

## Construcción del grafo

Para $n$ variables booleanas se introducen $2n$ vértices: uno por cada
literal $x_i$ y otro por cada literal $\lnot x_i$. Cada cláusula
$(a \lor b)$ se traduce en las dos implicaciones equivalentes:

$$
\lnot a \Rightarrow b
\qquad\text{y}\qquad
\lnot b \Rightarrow a
$$

Cada implicación $u \Rightarrow v$ se representa como una arista
dirigida $u \to v$. Toda cláusula aporta exactamente dos aristas.

## Criterio de satisfacibilidad

La fórmula es satisfacible si y solo si para toda variable $x_i$ los
vértices $x_i$ y $\lnot x_i$ pertenecen a componentes fuertemente
conexas (SCC) distintas. Si compartieran SCC, existiría una cadena de
implicaciones que llevaría de un literal al otro y, dando la vuelta, el
otro al primero, lo que equivaldría a "$x_i$ cierto $\Rightarrow x_i$
falso": contradicción.

## Algoritmo

1. Construir el grafo de implicación a partir de las cláusulas.
2. Calcular sus SCC con un algoritmo lineal (Tarjan, Kosaraju, etc.).
3. Comprobar la condición de SCC distintas.

El coste es $O(V + E)$ donde $V = 2n$ y $E$ es dos veces el número de
cláusulas.

# Modelado del Problema C

## Variables

Para cada fin de semana $i \in [0, k)$ se introduce una variable
booleana $x_i$:

- $x_i = $ cierto $\Longleftrightarrow$ se elige el espectáculo $A$.
- $x_i = $ falso $\Longleftrightarrow$ se elige el espectáculo $B$.

## Cláusulas de polvos que se agotan

Como cada polvo se gasta tras usarse, no puede aparecer en más de un
espectáculo elegido. Si un mismo polvo aparece en el espectáculo $S_i$
del fin de semana $i$ y en el $S_j$ del fin de semana $j$ (con $i < j$),
no pueden elegirse los dos a la vez. La cláusula es:

$$
\lnot \langle x_i = S_i \rangle \;\lor\; \lnot \langle x_j = S_j \rangle,
$$

con la convención de que $\langle x_i = A \rangle$ es el literal $x_i$
y $\langle x_i = B \rangle$ es $\lnot x_i$. Las cuatro combinaciones
posibles dan estas cláusulas concretas:

| $S_i$ | $S_j$ | Cláusula |
| :--: | :--: | :------: |
| A | A | $\lnot x_i \lor \lnot x_j$ |
| A | B | $\lnot x_i \lor x_j$ |
| B | A | $x_i \lor \lnot x_j$ |
| B | B | $x_i \lor x_j$ |

La forma directa de generarlas es: para cada polvo, recoger la lista de
espectáculos que lo usan y, para cada par de espectáculos de esa lista,
añadir la cláusula correspondiente. Si un polvo aparece en $r$
espectáculos, esto produce $\binom{r}{2}$ cláusulas.

## Cláusulas de neutralizantes

Solo afectan a pares de fines de semana consecutivos. Para cada par
$(i, i+1)$ y cada combinación $(s_i, s_{i+1}) \in \{A, B\}^2$ se
calculan:

$$
u = \#\text{inestables}(s_i)
\qquad
v = \#\text{neutralizantes}(s_{i+1}).
$$

Si $v < u$, esa combinación no se puede dar y se añade la cláusula

$$
\lnot \langle x_i = s_i \rangle \;\lor\; \lnot \langle x_{i+1} = s_{i+1} \rangle.
$$

Hay como mucho cuatro cláusulas por cada par consecutivo, así que en
total son $O(M)$.

## Resolución

Construido el grafo de implicación con todas las cláusulas anteriores,
se calculan sus SCC y se comprueba que para cada $x_i$ los dos
literales viven en SCC distintas. Si es así, la temporada de longitud
$k$ es factible.

# Búsqueda binaria

Con la monotonía descrita en la introducción, basta una búsqueda
binaria estándar sobre $k \in [0, M]$:

- $\text{lo} = 0$, $\text{hi} = M$.
- Mientras $\text{lo} < \text{hi}$, tomar $\text{mid} = \lceil (\text{lo} + \text{hi}) / 2 \rceil$ y resolver el 2-SAT para $k = \text{mid}$.
- Si es factible, $\text{lo} = \text{mid}$; si no, $\text{hi} = \text{mid} - 1$.

Al terminar, $\text{lo}$ es la respuesta.

# Complejidad

Sea $E$ el número total de cláusulas y $V$ el número total de
literales. Cada llamada al 2-SAT cuesta $O(V + E)$. La búsqueda binaria
introduce un factor $\log M$ y hay $T$ temporadas, así que el coste
global es $O(T \cdot (V + E) \cdot \log M)$.

Las cláusulas de neutralizantes y la traducción de las elecciones
binarias por fin de semana aportan $O(M)$ cláusulas. La parte
potencialmente costosa es la de polvos: si un polvo aparece en muchos
espectáculos, su contribución $\binom{r}{2}$ puede ser grande. En el
peor caso teórico esto explota, pero con datos razonables la fórmula
sigue siendo lineal en el tamaño de la entrada.

# (Opcional) Optimización "como mucho uno" (AMO)

La codificación pareja a pareja de las cláusulas de polvos que se agotan puede
volverse cuadrática si un polvo concreto aparece en muchos espectáculos. Hay un
truco estándar para mantenerse en lineal incluso en ese caso.

Para cada polvo, la restricción "como mucho un espectáculo de su lista
puede elegirse" es una instancia de "como mucho uno cierto" sobre los
literales correspondientes. La codificación secuencial introduce
$r - 1$ variables auxiliares $z_1, \dots, z_{r-1}$ con la lectura
"alguno de los $i$ primeros literales es cierto", y añade $O(r)$
cláusulas:

- $y_i \Rightarrow z_i$ (si $y_i$ es cierto, $z_i$ debe serlo).
- $z_{i-1} \Rightarrow z_i$ (monotonía del prefijo).
- $z_{i-1} \Rightarrow \lnot y_i$ (si algún anterior fue cierto, $y_i$ ya no puede serlo).

Con esta codificación, el coste agregado de las cláusulas de polvos
pasa de $\sum_d \binom{r_d}{2}$ a $\sum_d O(r_d)$, que está acotado por
el número total de apariciones de polvos en espectáculos
($\leq 20 M = 2 \cdot 10^5$).

Para datos donde ningún polvo aparece muchas veces, la versión sin AMO
es más simple y suficiente; la optimización solo se nota cuando algún
polvo está repartido por toda la temporada.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [C_pares.cpp](src/C_pares.cpp) | Cláusulas pareja a pareja para las restricciones de polvos | :white_check_mark: |
| [C_amo.cpp](src/C_amo.cpp) | Igual, pero con codificación AMO secuencial para los polvos que aparecen en muchos espectáculos | :white_check_mark: |

