# Problema E - El número misterioso

Tiempo: 1,0 s

El número misterioso, también conocido como constante de **Kaprekar**, es el
número **6174**. Este número se obtiene siempre que se realizan las
siguientes operaciones con cualquier número de cuatro cifras (las 4 no pueden
ser iguales).

1. Obtener el mayor número que resulta de permutar las 4 cifras del número.
2. Obtener el menor número que resulta de permutar las 4 cifras del número.
3. Al mayor número restarle el menor número.
4. Si el número obtenido en el paso 3 no es 6174, volver a repetir los tres
   primeros pasos con el número obtenido en el paso 3.

Para cualquier número de 4 cifras, en las que las 4 no pueden ser iguales (no
valdría para el 1111, o el 2222, o el 3333 etc.), en un máximo de 7
iteraciones se obtiene siempre el 6174.

Por ejemplo, supongamos que lo probamos para el número 7283.

- Iteración 1: máximo $= 8732$, mínimo $= 2378$, diferencia $= 8732 - 2378 = 6354$
- Iteración 2: máximo $= 6543$, mínimo $= 3456$, diferencia $= 3087$
- Iteración 3: máximo $= 8730$, mínimo $= 378$, diferencia $= 8352$
- Iteración 4: máximo $= 8532$, mínimo $= 2358$, diferencia $= 6174$

Como se puede apreciar, se obtiene el 6174 en 4 iteraciones.

El problema consiste en calcular cuantas iteraciones son necesarias para
obtener el número misterioso para un número dado de 4 cifras que no son todas
iguales.

## Entrada
De la entrada estándar se leerá un número entero de 4 cifras, en el cual las
cuatro cifras no pueden ser iguales.

## Salida
Utilizando la salida estándar se mostrará un número entero, que representa el
número de iteraciones necesarias para obtener el número misterioso.

## Entrada de ejemplo
```
7283
```

## Salida de ejemplo
```
4
```
