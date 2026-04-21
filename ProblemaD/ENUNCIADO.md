# Problema D - Tunelando el futuro

Tiempo: 1,0 s

Por alguna razón que ya nadie recuerda, los humanos que sobreviven en la
Tierra en el año 2626 habitan en ciudades-búnker bajo tierra. La Comisión
Europea decide invertir en infraestructuras para conectar todas las
ciudades-búnker de las regiones de Europa, construyendo túneles entre ellas.
Pero el dinero es escaso y el coste de construcción es alto: 1 millón de
euros por día. La Comisión dota a cada región de una tuneladora y un único
equipo de trabajo que debe construir todos los túneles entre las
ciudades-búnker. El tiempo que tarda el equipo en construir los túneles
depende del material que tenga que excavar. En particular, estas son las
velocidades a las que pueden excavar los distintos materiales:

- Granito: 1 metro por día
- Arenisca: 4 metros por día
- Pizarra: 10 metros por día
- Limo: 20 metros por día

Los gobiernos regionales deciden que van a optimizar los recursos al máximo y
van a crear tan solo los túneles mínimos necesarios para permitir los viajar
entre cualesquiera dos ciudades-búnker cualesquiera de su región. Además,
escogerán estos túneles de tal forma que el coste de construcción sea mínimo.

La empresa a la que perteneces, te encomienda la labor de calcular ese coste
mínimo requerido para conectar las ciudades-búnker de una región dada su
matriz de distancias y el material que se puede encontrar entre cada par de
ellas.

## Entrada
La primera línea de la entrada contiene el número de ciudades-búnker de la
región. Se cumple que $3 \leq N \leq 1000$.

A continuación viene la matriz de distancias expresadas en kilómetros. La
matriz se representa con $N$ líneas de $N$ números enteros separados por
espacios.

Por último, se puede encontrar una matriz con los materiales entre las
ciudades-búnker. Esta matriz tiene también $N$ filas ycon $N$ letras (G, A, P
o L) separadas por espacios que indican el material: (G)ranito, (A)renisca,
(P)izarra y (L)imo.

## Salida
La salida es el coste mínimo de construcción en millones de euros.

## Entrada de ejemplo
```
3
0 2 3
2 0 4
3 4 0
G A P
A G L
P L G
```

## Salida de ejemplo
```
500
```
