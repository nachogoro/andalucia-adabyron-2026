# Introducción a la solución

El enunciado pide, dado un conjunto de ciudades-búnker, los túneles
imprescindibles para poder viajar entre cualesquiera dos de ellas y con
coste de construcción mínimo. Ese es exactamente un árbol de expansión de
coste mínimo (MST, _Minimum Spanning Tree_) sobre el grafo completo cuyos
vértices son las ciudades y cuyas aristas son los posibles túneles entre
pares.

# Peso de cada arista

Como el coste son 1 millón de euros por día de excavación y es constante,
minimizar euros es lo mismo que minimizar días. El número de días para
excavar un túnel depende de su longitud y del material:

| Material     | Velocidad (m/día) | Días por km |
| :----------: | :---------------: | :---------: |
| Granito (G)  | 1                 | 1000        |
| Arenisca (A) | 4                 | 250         |
| Pizarra (P)  | 10                | 100         |
| Limo (L)     | 20                | 50          |

Trabajar en "días por km" es conveniente porque los cuatro valores son
enteros y la distancia ya viene dada en km enteros, así que todo el
cálculo se puede hacer con aritmética entera sin recurrir a `double`.

Para cada par $(i, j)$ con $i < j$ se genera una arista con peso
$\text{dist}_{ij} \cdot \text{diasPorKm}(\text{material}_{ij})$.

# Kruskal

El grafo es completo, con $N \leq 1000$, así que hay hasta
$\binom{N}{2} \approx 500\,000$ aristas. Kruskal es un buen encaje:

1. Construir la lista de aristas con sus pesos.
2. Ordenarla de menor a mayor peso.
3. Recorrerla manteniendo una estructura Union-Find. Cada arista cuyos
   extremos estén en componentes distintas se añade al árbol y se unen
   sus componentes. Podemos parar en cuanto llevemos $N - 1$ aristas
   aceptadas.

La suma de pesos de las aristas aceptadas es la respuesta en millones de
euros (un día = un millón).

# Complejidad

- Generación de aristas: $O(N^2)$.
- Ordenación: $O(N^2 \log N)$, dominante.
- Pasada de Kruskal con Union-Find (compresión de caminos + unión por
  rango): $O(N^2 \cdot \alpha(N))$, prácticamente lineal en el número de
  aristas.

Con $N = 1000$ quedan ~500\,000 aristas; la ordenación es cómoda en el
límite de 1,0 s del enunciado.

# Tamaño de los enteros

Aunque el enunciado no acota las distancias, conviene trabajar con
`long long` para el peso y el coste acumulado: el peso de una sola
arista ya puede alcanzar unos pocos miles de millones (distancia en km
por 1000 días/km en el caso del granito), y la suma sobre $N - 1$
aristas puede multiplicar eso por mil más.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [D.cpp](src/D.cpp) | :x: |

