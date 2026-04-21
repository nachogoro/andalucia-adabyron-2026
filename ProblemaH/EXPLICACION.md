# Introducción a la solución

El problema se reduce a una **simulación lineal** del registro de eventos.
Basta con mantener un contador con la ocupación actual de la sala y
verificar tres condiciones mientras se recorre la cadena:

1. La ocupación nunca se vuelve negativa (nadie sale con la sala vacía).
2. La ocupación nunca supera la capacidad máxima $C$.
3. Al terminar el recorrido, la ocupación es 0 (la sala queda vacía).

Si alguna de las tres falla, la secuencia es `INVALIDO`; si las tres se
cumplen, es `VALIDO`.

## Paso a paso

Para cada registro:

1. Leemos la capacidad $C$ y la cadena $s$.
2. Inicializamos $\text{ocupacion} = 0$.
3. Recorremos los caracteres de $s$ en orden:
   - Si es `E`: $\text{ocupacion} \gets \text{ocupacion} + 1$. Si
     $\text{ocupacion} > C$, podemos salir del bucle porque es inválida
(en este punto, $\text{ocupacion} \neq 0$, así que se considerará inválida).
   - Si es `S`: $\text{ocupacion} \gets \text{ocupacion} - 1$. Si
     $\text{ocupacion} < 0$, podemos salir del bucle porque es inválida
(en este punto, $\text{ocupacion} \neq 0$, así que se considerará inválida).
4. Al terminar, si $\text{ocupacion} \neq 0$, es inválido, si no, es válido.
5. Imprimimos `VALIDO` o `INVALIDO` según corresponda.

No hace falta ninguna estructura de datos adicional: un único entero para la
ocupación y un flag son suficientes.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [H.cpp](src/H.cpp) | :x: |
