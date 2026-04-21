# Problema I - Numble

Tiempo: 1,0 s

Los creadores del aclamado juego Wordle están diseñando su próximo gran
éxito: Numble. A diferencia de Wordle, en Numble no tendremos que adivinar
una palabra sino una secuencia de números. Cada día se elige en secreto una
secuencia $S$ de longitud $L$. En cada intento, tú propones una secuencia
$G$ también de longitud $L$, usando números entre 1 y $N$. El sistema
devuelve únicamente dos valores:

- **Verdes**: cuántas posiciones $i$ cumplen $G[i] = S[i]$ (número correcto
  en posición correcta).
- **Amarillas**: cuántos números de $G$ aparecen en $S$ pero en posición
  distinta, contando multiplicidades y sin contar los ya contados como
  verdes.

Los números de tu secuencia que no aparecen en la secuencia secreta son $L -
verdes - amarillas$.

Sin embargo, tras un par de intentos te has dado cuenta de que es más difícil
que el juego original Wordle, por lo que decides escribir un programa que te
ayude a resolverlo.

Este es un problema interactivo. Tu programa debe comunicarse con el juez
siguiendo el protocolo descrito a continuación. Cada caso de prueba consta de
varios ejemplos. Al inicio de cada ejemplo, tu programa debe leer tres
números enteros separados por espacio $L$, $N$ y $Q$:

- $L$ ($1 \leq L \leq 6$): longitud de la secuencia secreta.
- $N$ ($1 \leq N \leq 6$): valores posibles en cada posición ($1, \dots, N$).
- $Q$ ($1 \leq Q \leq 20$): número máximo de intentos permitidos.

A partir de ese momento, tu programa puede realizar consultas. Para consultar
una secuencia $G$:

- Imprime una línea con el formato:

  `? g1g2...gL`

  donde cada $g_i$ debe estar entre 1 y $N$.

- A continuación, el juez responderá por la entrada estándar con una línea:

  `v a`

  donde `v` es el número de **verdes** y `a` el número de **amarillas** para
  esa consulta.

Cuando tu programa conozca la secuencia secreta debe imprimir una línea con
el formato:

`! s1s2...sL`

El final de la entrada se indica con una línea que contiene un único `0`.

A continuación, aparece un ejemplo de ejecución. En _cursiva_ aparece lo
leído por la entrada estándar y en **negrita** lo escrito por la salida
estándar.

```
4 6 8
? 1111
1 0
? 1234
3 0
? 1224
4 0
! 1224
2 2 5
? 11
0 0
? 22
2 0
! 22
0
```

## Notas
Al tratarse de un problema interactivo es importante que cada vez que tu
solución escriba algo que el juez deba leer se asegure de volcar la salida
(usando terminología inglesa, haga "flush"). La forma de hacerlo varía entre
lenguajes. En los admitidos en la competición puede hacerse con:

- **C**: `fflush(stdout);`
- **C++**: `cout << endl;` o `cout << flush;`
- **Java**: `System.out.flush();`
- **Python**: `print(..., flush=True)` o `sys.stdout.flush()`

El envío de una secuencia de longitud incorrecta, el uso de un formato
incorrecto para las consultas o exceder el número máximo de intentos
provocará que el juez devuelva un veredicto **WRONG-ANSWER**.
