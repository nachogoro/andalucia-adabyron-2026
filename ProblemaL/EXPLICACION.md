# Introducción a la solución

El enunciado pide la subcadena contigua más corta que contenga apariciones
completas de al menos $K$ motivos distintos. Es una variante del
clásico "ventana deslizante con $K$ elementos distintos", pero con dos
añadidos que la complican:

1. Lo que cuenta no es un carácter, sino una aparición completa de un
   motivo, que ocupa varias posiciones consecutivas. Una ventana puede
   incluir el principio de un motivo pero no su final, y entonces no
   debe contar.
2. Los motivos pueden tener longitudes distintas y aparecer múltiples
   veces, así que tracking simple por carácter no basta.

La idea es reducir el problema a una ventana deslizante sobre las
**apariciones**, no sobre los caracteres del ADN.

# Pasos

## 1. Localizar todas las apariciones

Para cada motivo, se busca su lista de posiciones de inicio dentro del
ADN. Cualquier algoritmo de búsqueda de patrones sirve: KMP, Aho-Corasick
o las funciones `find` / `indexOf` de la librería estándar en bucle. Con
$N \leq 10^4$, hasta 25 motivos y longitudes hasta 100, una búsqueda
ingenua $O(N \cdot \sum |motivo_i|)$ ya es admisible.

Cada aparición de un motivo $i$ que comience en la posición $p$ ocupa el
intervalo $[p,\ p + |motivo_i| - 1]$. El número total de apariciones está
acotado por $N$ por motivo y por $25 \cdot N$ globalmente.

## 2. Convertir cada aparición en dos eventos

Para cada aparición se generan dos eventos:

- Un evento de *inicio* en la posición $p$.
- Un evento de *fin* en la posición $p + |motivo_i| - 1$.

Cada evento lleva asociado el identificador del motivo y un marcador que
diferencia inicio de fin. Después se ordenan todos los eventos por
posición. Para varios eventos en la misma posición conviene un desempate
determinista, pero el orden concreto no afecta a los conteos: incluso
con motivos de longitud 1 (donde inicio y fin caen sobre el mismo
carácter), la comprobación que incrementa los contadores se basa en el
ancho de la ventana, no en cuál de los dos eventos se añadió antes.

## 3. Ventana deslizante sobre los eventos

Se barren los eventos en orden y se mantiene una ventana que va de la posición
del primer evento "vivo" hasta la posición del último evento añadido. La
ventana se acompaña de:

- Un contador `freq[i]` con el número de apariciones completas del
  motivo $i$ que están dentro de la ventana. Una aparición es completa
  cuando tanto su inicio como su fin caen dentro.
- Un contador con el número de motivos distintos para los que `freq[i] > 0`.

### Cuándo se incrementan los contadores

Al añadir un evento de fin del motivo $i$, se sabe que la aparición
correspondiente es completa si y solo si la posición del primer evento
de la ventana es menor o igual que la posición del inicio asociado a ese
fin. Eso es equivalente a comprobar que la longitud actual de la ventana
(rightmost − leftmost + 1) es mayor o igual que la longitud del motivo.
Si la aparición es completa, se incrementa `freq[i]`; si pasa de 0 a 1,
se aumenta el contador de motivos distintos.

Los eventos de inicio nunca tocan los contadores: por sí solos no
representan una aparición completa.

### Cuándo se contrae la ventana

El esquema de cada iteración es sencillo: primero se añade el evento
nuevo por la derecha, y a continuación, mientras el contador de motivos
distintos sea exactamente $K$, se anota la longitud actual de la ventana
y se elimina el evento más a la izquierda. La contracción se basa en
estas dos reglas:

- Si el evento eliminado era el inicio de una aparición completa que ya
  no podrá serlo, hay que decrementar `freq[i]` y, si llega a 0, el
  contador de distintos.
- Tras eliminar un inicio, pueden quedar eventos de fin "huérfanos" en
  el extremo izquierdo (apariciones cuyo inicio ya salió de la
  ventana); se descartan sin tocar contadores, porque ya no representan
  ninguna aparición útil.

La contracción acaba en cuanto el contador baja por debajo de $K$, y
entonces se pasa al siguiente evento. Como `increase` añade como mucho
un motivo nuevo distinto, después de cada contracción el contador es
estrictamente menor que $K$ y la siguiente iteración vuelve a empezar
con la misma invariante.

## 4. Respuesta

La menor longitud anotada durante todo el proceso es la respuesta. Si en
ningún momento el contador llega a $K$, no existe subcadena válida y se
responde 0.

# Por qué es correcto

La construcción garantiza que cualquier subcadena óptima
$[L^\star, R^\star]$ se considera al menos una vez. Cuando se procesa el
evento que hace que la ventana incluya por primera vez el último motivo
distinto necesario, $R^\star$ ya es la posición del evento añadido (o
una posterior). En ese momento se inicia la fase de contracción, que
prueba todos los recortes posibles por la izquierda manteniendo $K$
distintos, así que se examina alguna ventana cuya longitud es menor o
igual que la óptima. Como cada evento se añade una vez y se elimina como
mucho una vez, la pasada es lineal en el número de eventos.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [L.cpp](src/L.cpp) | :white_check_mark: |

