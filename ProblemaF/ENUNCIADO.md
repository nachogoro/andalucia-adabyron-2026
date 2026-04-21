# Problema F - El historial de problemas de AdaByron

Tiempo: 1,0 s

El comité organizador del concurso AdaByron está preparando un conjunto de
$N$ problemas. Cada problema tiene una cierta longitud (en número de
palabras), que va cambiando a medida que se revisan enunciados, se añaden
ejemplos o alguien decide "explicar mejor" algo que ya era suficientemente
largo.

Para mantener cierto control, el equipo ha desarrollado un sistema que guarda
versiones del conjunto de problemas. Cada vez que se modifica la longitud de
un problema, se crea automáticamente una nueva versión del conjunto de
problemas. A veces interesa consultar el estado actual, pero otras veces...
también es útil comprobar cuánto medían los problemas antes de aquella
"pequeña mejora" que duplicó su tamaño.

Entonces, se dispone inicialmente de $N$ problemas, cada uno con una longitud
en palabras. A partir de ahí, se irán realizando $Q$ operaciones de dos
tipos:

- `U i x`: se crea una nueva versión a partir de la más reciente, cambiando
  la longitud del problema `i` a `x`.
- `S v l r`: se consulta la suma de longitudes de los problemas desde el `l`
  hasta el `r` (ambos inclusive) en la versión `v`.

Cada operación `U` genera una nueva versión numerada consecutivamente (siendo
la versión 0 la inicial). Las operaciones `S` no crean nuevas versiones.

## Entrada
La primera línea contiene dos enteros $N$ y $Q$ ($1 \leq N, Q \leq 300{,}000$).

La segunda línea contiene $N$ enteros $a_1, a_2, \dots, a_N$, donde $a_i$ es
la longitud inicial (en palabras) del problema $i$ ($1 \leq a_i \leq 10^9$).

Las siguientes $Q$ líneas contienen operaciones:

- `U i x` ($1 \leq i \leq N$, $1 \leq x \leq 10^9$)
- `S v l r` ($0 \leq v \leq$ número de versiones existentes, $1 \leq l \leq r \leq N$)

Se garantiza que todas las consultas hacen referencia a versiones válidas.

## Salida
Para cada operación de tipo `S`, imprimir en una línea la suma de longitudes
solicitada.

## Entrada de ejemplo
```
5 7
100 200 150 300 250
S 0 1 3
U 2 500
S 1 1 3
U 5 100
S 2 3 5
S 0 4 5
S 2 1 5
```

## Salida de ejemplo
```
450
750
550
550
1150
```
