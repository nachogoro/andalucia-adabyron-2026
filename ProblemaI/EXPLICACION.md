# Introducción a la solución

El problema es interactivo: proponemos una secuencia $G$ de longitud $L$ con
valores en $\{1, \dots, N\}$, el juez responde con el número de verdes $v$ y
amarillas $a$, y debemos acertar el secreto $S$ en a lo sumo $Q$ consultas.
Como $L, N \le 6$ y $Q \le 20$, el espacio de candidatos es a lo sumo
$N^L \le 46\,656$, y se puede mantener en memoria sin problema.

La idea base en cualquier estrategia razonable es la misma: después de cada
respuesta, reducimos el conjunto de candidatos a los que son consistentes con
todas las respuestas anteriores. Una secuencia $c$ es consistente con un par
(consulta $g$, respuesta $(v, a)$) si y solo si al comparar $g$ con $c$ se
obtendrían esos mismos $(v, a)$. Lo que varía entre estrategias es cómo se
elige cada siguiente consulta.

# Fuerza bruta (suficiente)

La estrategia más directa ya basta para resolver el problema dentro del
límite $Q \le 20$: recorremos los candidatos en orden y elegimos el primero
que sea consistente con todas las respuestas anteriores. Lo consultamos,
recibimos $(v, a)$ y, si $v = L$, hemos terminado; en caso contrario
filtramos el conjunto y repetimos.

Esto equivale a ir "adivinando con el primero que encaja". Este método no
minimiza el número de consultas necesarias hasta su límite teórico, pero entra
en los límites del problema porque cada respuesta poda mucho el conjunto de
candidatos.

# Estrategia Mastermind (minimax de Knuth)

Se puede reducir el número medio de consultas eligiendo cada consulta con un
criterio de máxima información. El razonamiento clásico de Knuth para
Mastermind:

- Sea $C$ el conjunto de candidatos consistentes con las respuestas previas.
- Para cada posible consulta $g$, y para cada candidato $c \in C$, calculamos
  $(v, a) = \mathrm{compare}(g, c)$. Esto particiona $C$ en clases según la
  respuesta.
- Si consultamos $g$ y el secreto resulta ser un $c$ concreto, tras la
  respuesta nos quedará exactamente la clase $(v, a)$ correspondiente. En el
  peor caso, ese conjunto es el más grande de la partición.
- Elegimos el $g$ que minimiza ese peor caso (tamaño máximo entre las clases
  que induce).

Esta estrategia es óptima, pero puede ser muy lenta, por tener un coste
cuadrático sobre el tamaño del conjunto de candidatos en cada paso. Se pueden
hacer unas simplificaciones para aliviar estos problemas:

1. Restringir los candidatos a probar como consulta al propio conjunto $C$,
   en lugar de probar todas las $N^L$ secuencias posibles como haría el
   minimax completo de Knuth.
2. Para la primera consulta, cuando $C$ es todo el espacio, usar una
   heurística en vez de minimax (minimax sobre $46\,656$ candidatos es
   $46\,656^2$ comparaciones, inviable). Una heurística sencilla es recorrer
   los dígitos $1, 2, \dots, N$ en ciclo hasta cubrir las $L$ posiciones
   (por ejemplo, `123456` para $L = N = 6$, `1212` para $L = 4, N = 2$).
3. Si tras filtrar el conjunto $C$ sigue siendo muy grande, evaluar todos los
   $|C|$ candidatos como consulta también se encarece. Se acota el trabajo
recorriendo los candidatos como consulta con un paso uniforme $\lceil |C| / K
\rceil$ para algún $K$ moderado. Se siguen evaluando todos los candidatos en el
histograma de particiones, así que la calidad del minimax apenas se ve
afectada, pero cada evaluación reduce el número de comparaciones a $1/K$.

## Optimización en tiempo a cambio de memoria

La función que compara dos candidatos con la estrategia Mastermind se llama
$O(|C|^2)$ veces por consulta, y es el cuello de botella. Si conseguimos que sea
más rápida, podemos disminuir considerablemente el tiempo de ejecución (aunque
no es necesario para que entre en tiempo).

Como la comparación naïve de dos números calcula dos histogramas y el array de
dígitos de cada uno, la función se puede acelerar precomputando, para cada
candidato:

- El array de dígitos `d[0..L-1]`.
- El histograma `cnt[1..N]` con el número de veces que aparece cada dígito.

Con esos datos, `compare` se reduce a dos recorridos muy cortos, usando la
identidad

$$\text{amarillas} = \sum_{i=1}^{N} \min(\text{cnt}_a[i], \text{cnt}_b[i]) - \text{verdes},$$

que se apoya en que el número de coincidencias ignorando posición
(`sum min(cnt)`) es exactamente verdes + amarillas.

El coste en memoria es modesto: cada candidato pasa de ocupar un `int`
(4 bytes) a una estructura de unos 20 bytes. Para el peor caso ($L = N = 6$,
$46\,656$ candidatos) son unos $900$ KB frente a $190$ KB, un delta
asumible para un speed-up considerable en tiempo.

# Juez local para pruebas

Como el problema es interactivo, no se puede probar con un fichero de
entrada fijo. En [`src/judge.py`](src/judge.py) hay un juez que ejecuta la
solución como subproceso, le habla por stdin/stdout siguiendo el protocolo
del enunciado y verifica que acierta en todos los casos. Usa 700 tests
aleatorios deterministas (misma secuencia en cada ejecución) con $L, N$
elegidos aleatoriamente en $[1, 6]$ y un secreto aleatorio para cada test.

Para lanzarlo:

```
python3 src/judge.py ./a.out
python3 src/judge.py python3 solucion.py
```

Escribe en `judge_log.txt` el detalle de los fallos y, al terminar, imprime
el número de tests superados y la media de consultas usadas.

# Soluciones

| Solución | Descripción | Verificado con el juez |
| :------: | :---------- | :--------------------: |
| [I.cpp](src/I.cpp) | Fuerza bruta | :white_check_mark: |
| [I_mastermind_simple.cpp](src/I_mastermind_simple.cpp) | Minimax de Knuth restringido a candidatos, con muestreo | :white_check_mark: |
| [I_mastermind.cpp](src/I_mastermind.cpp) | Igual que la anterior, pero precomputando dígitos e histogramas por candidato | :white_check_mark: |
