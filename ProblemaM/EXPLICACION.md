# Introducción a la solución

La pirámide se puede modelar directamente como una estructura tridimensional
indexada por $(n, f, c)$: el nivel, la fila y la columna dentro del nivel.
En el nivel $n$ hay $(n + 1) \times (n + 1)$ copas, así que la estructura
más natural es una lista de matrices cuadradas de tamaño creciente.

Para cada copa distinguimos dos magnitudes:

- Su capacidad $\text{cap}(n, f, c)$, que es dato de entrada.
- El volumen total de líquido que le llega $\text{flujo}(n, f, c)$, sin
  contar todavía qué parte se queda y qué parte rebosa.

El volumen retenido por la copa es simplemente
$\min(\text{cap}(n, f, c), \text{flujo}(n, f, c))$, que es lo que hay que
imprimir para cada consulta.

# Cuánto líquido le llega a cada copa

Cada copa $(n, f, c)$ vierte su excedente a las cuatro copas del nivel
$n + 1$ en las posiciones $(f, c)$, $(f + 1, c)$, $(f, c + 1)$ y
$(f + 1, c + 1)$. Con los rangos que da el enunciado, esas cuatro
posiciones siempre existen: si $0 \leq f, c \leq n$, entonces
$f + 1$ y $c + 1$ están en $[0, n + 1]$, que es el rango válido del
nivel $n + 1$. Por tanto, una copa interna de la pirámide siempre reparte
su sobrante a exactos cuatro hijos, y el reparto equitativo que describe
el enunciado significa que cada hijo recibe un cuarto del excedente.

Invirtiendo esa relación, una copa $(n, f, c)$ con $n \geq 1$ recibe
líquido de hasta cuatro padres en el nivel anterior: $(n - 1, f, c)$,
$(n - 1, f - 1, c)$, $(n - 1, f, c - 1)$ y $(n - 1, f - 1, c - 1)$.
Dependiendo de la posición, algunos de esos padres pueden caer fuera del
rango del nivel superior (índices negativos, o $f$/$c$ mayores que
$n - 1$). Los que no existen aportan $0$. Así se explica el enunciado sin
necesidad de casos especiales:

- Las copas en las esquinas de un nivel tienen sólo un padre válido, por
  lo que reciben a lo sumo un cuarto del excedente de esa copa.
- Las copas en el borde no esquina tienen dos padres válidos.
- Las copas interiores tienen los cuatro padres.

Formalmente, el flujo que le llega a $(n, f, c)$ es

$$
\text{flujo}(n, f, c) = \sum_{(p) \text{ padre válido}} \frac{\max\bigl(0,\ \text{flujo}(p) - \text{cap}(p)\bigr)}{4},
$$

con el caso base $\text{flujo}(0, 0, 0) = L$ y $\text{flujo}(p) = 0$ para
padres fuera de la pirámide.

# Cálculo

La recurrencia se puede evaluar de dos formas equivalentes:

- Hacia delante: se recorre la pirámide por niveles crecientes; al
  procesar cada copa se calcula su excedente y se suma un cuarto de él a
  los cuatro hijos. Al terminar el nivel $n$, los valores de
  $\text{flujo}$ del nivel $n + 1$ ya son definitivos.
- Hacia atrás con memoización: se resuelve cada consulta mediante una
  función recursiva que pide el flujo en la copa objetivo; ésta, a su
  vez, pide el flujo de sus (a lo sumo) cuatro padres, y así hasta la
  cima. Es importante memorizar los resultados intermedios: sin caché,
  cada copa se recomputaría un número exponencial de veces.

Cualquiera de los dos esquemas toca cada copa un número constante de
veces. Si se llaman $T$ al total de copas,
$T = \sum_{n = 0}^{H - 1} (n + 1)^2 = \frac{H (H + 1)(2H + 1)}{6}$, que
para $H = 100$ ronda las 340.000 copas, con coste tanto en tiempo como
en memoria perfectamente cómodo dentro del límite.

# Detalles numéricos

- Conviene usar punto flotante de doble precisión (`double` o
  equivalente). El número de divisiones por 4 en cadenas largas no
  acumula error perceptible para $H \leq 100$.
- La precisión exigida es de 6 decimales; basta con imprimir con formato
  fijo y seis decimales.
- Cuidado con el borde del caso base: si la copa de la cima tiene
  capacidad $\geq L$, no rebosa y todo el resto de la pirámide queda a
  cero.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [M.cpp](src/M.cpp) | Recursión hacia atrás con memoización: cada consulta pide el flujo de la copa y, si no está calculado, recurre a sus padres | :white_check_mark: |
| [M_delante.cpp](src/M_delante.cpp) | Simulación hacia delante por niveles: una sola pasada por la pirámide propagando el excedente a los cuatro hijos | :white_check_mark: |

