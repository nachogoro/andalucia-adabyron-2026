# Introducción a la solución

Podemos utilizar una matriz 8x8 para representar el tablero, convirtiendo cada
coordenada de ajedrez a una coordenada de la matriz (la columna 'a' del tablero
será la columna 0 de la matriz, la columna 'b' será la columna 1 de la matriz,
etc.).

Por simplicidad, podríamos inicializar la matriz con el patrón vacío, como si
no hubiese piezas, y sobreescribir cada cuadrado según se lee cada pieza.

Para decidir si una casilla es clara u oscura, podemos ver que hay dos posibilidades:
- Si la fila es par (0, 2, 4...), las columnas pares son oscuras y las impares claras.
- Si la fila es impar (1, 3, 5...), las columnas impares son oscuras y las pares claras.

Podemos expresar esa condición simplemente como:
```
(fila + columna) par: oscuro
(fila + columna) impar: claro
```

En C/C++ hay que tener en cuenta que los caracteres Unicode en general no caben
en un `char`. La forma práctica de imprimirlos es guardarlos directamente como
`std::string` con su codificación UTF-8 y volcarlos a `std::cout`: la salida
estándar es un flujo de bytes, así que escribir los bytes UTF-8 correctos
basta para que la terminal los renderice. Usar `char32_t` o `std::u32string`
no sirve de forma directa, porque la librería estándar no tiene
`operator<<` para esos tipos y habría que convertirlos a UTF-8 antes de
imprimirlos igualmente.

En la práctica se puede definir una tabla (`std::map` o similar) que asocie
cada código de pieza al literal `std::string` con su símbolo Unicode, por
ejemplo:

```cpp
std::map<char, std::string> simbolo = {
    {'R', "\u2654"}, {'D', "\u2655"}, {'T', "\u2656"},
    {'A', "\u2657"}, {'C', "\u2658"}, {'P', "\u2659"},
    {'r', "\u265A"}, {'d', "\u265B"}, {'t', "\u265C"},
    {'a', "\u265D"}, {'c', "\u265E"}, {'p', "\u265F"},
};
```

y al imprimir la casilla hacer simplemente `std::cout << simbolo[ficha]`.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [A.cpp](src/A.cpp) | :white_check_mark: |

