# Problema M - La cascada de copas

Tiempo: 1,5 s

Tras el éxito de la última gala, los organizadores han decidido montar una
pirámide de copas para el brindis. En esta estructura, la copa del nivel
superior ($nivel = 0$) se apoya sobre cuatro copas en el nivel inferior
($nivel = 1$), formando una cuadrícula de $2 \times 2$. A su vez, cada una
de estas se apoya sobre otras cuatro, y así sucesivamente. De manera
opuesta, cada copa de un nivel inferior: (1) sostiene a 4 copas del nivel
inmediatamente superior si es una copa "interior", (2) sostiene a 2 copas
del nivel superior, si la copa está en un extremo del nivel y (3) solo
sostiene a una única copa del nivel superior si la copa es una de la
esquinas del nivel.

![Figura 1: Diagrama de la pirámide de copas y el flujo](images/diagrama.png)

En esta pirámide se sirve toda la bebida sobre la copa en la cima de la
pirámide. Cuando una copa se llena hasta su capacidad máxima, el líquido
sobrante desborda y se distribuye **equitativamente entre las cuatro copas
situadas inmediatamente debajo**, como se muestra en el diagrama superior
(Figura 1). Dado que las copas pueden tener capacidades diversas (medidas en
litros), el volumen de líquido retenido en cada una tras el vertido será, en
general, heterogéneo.

Dada la configuración de una pirámide de $H$ niveles y una cantidad de
líquido $L$ vertida en la cima, determina cuánto líquido contiene una copa
específica $(n, f, c)$.

Cada copa situada en el nivel $n$, fila $f$ y columna $c$, reparte su
sobrante a las copas del nivel inferior $n + 1$ en las posiciones:

- $(n + 1, f, c)$
- $(n + 1, f + 1, c)$
- $(n + 1, f, c + 1)$
- $(n + 1, f + 1, c + 1)$

## Entrada
- Una línea con el líquido inicial $L$ (real) y el número de niveles $H$
  ($1 \leq H \leq 100$).
- $H$ líneas, donde la línea $i$ contiene $(i + 1)^2$ valores reales
  representando la capacidad de cada copa en ese nivel (orden fila-columna).
- Una línea con el número de consultas $Q$. Seguidamente, $Q$ líneas con
  tres enteros: nivel $n$, fila $f$ y columna $c$.

## Salida
Para cada consulta, una línea con el volumen contenido en la copa con **6
decimales** de precisión.

## Entrada de ejemplo
```
2.000 3
0.500
0.450 0.150 0.250 0.125
0.300 0.150 0.300 0.150 0.150 0.150 0.300 0.150 0.275
4
0 0 0
1 0 0
2 1 1
2 2 2
```

## Salida de ejemplo
```
0.500000
0.375000
0.150000
0.062500
```
