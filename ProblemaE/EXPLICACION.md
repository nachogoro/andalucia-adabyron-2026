# Introducción a la solución

Es una simple simulación. Debemos extraer los dígitos del número y reordenarlos
en orden creciente para obtener el mínimo número posible (el máximo será ese
mismo número leído al revés).

Lo más cómodo es convertir el número en una cadena de caracteres, reordenar los
caracteres y reconvertir a número. Algunos lenguajes ofrecen formas de hacerlo
con la librería estándar, pero es posible hacerlo manualmente fácilmente:
```cpp
// Dado un número n, podemos extraer su i-ésimo dígito como...
int digito = (n / (int)pow(10, i)) % 10;

// Dado una lista v de cuatro dígitos ordenada, podemos reconstruir el número como...
int num = v[0]*1000 + v[1]*100 + v[2]*10 + v[3];
```

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [E.cpp](src/E.cpp) | :x: |

