# Problema C - El Circo de la Luna

Tiempo: 1,0 s

El Circo de la Luna se enorgullece de ser una de las compañías de teatro más
prestigiosas del mundo. Sus espectáculos, famosos por combinar acrobacias
imposibles, ilusiones visuales y una sorprendente conexión emocional con el
público, llenan teatros allá donde van. Aunque no les guste admitirlo, el
verdadero secreto de su éxito reside en el uso de unos polvos mágicos
extremadamente raros, capaces de alterar sutilmente el estado de ánimo del
público y amplificar sus reacciones ante cada actuación.

Cada año, antes de comenzar una nueva temporada, el director artístico del
circo debe planificar la gira semanal de espectáculos. La temporada consta de
$M$ fines de semana, que deben programarse en orden y sin saltos: si no se
puede realizar un espectáculo en un fin de semana concreto, la temporada
termina inmediatamente en ese punto. Para cada fin de semana, el director
dispone de exactamente dos espectáculos posibles, denominados **A** y **B**.
Ambos son perfectamente válidos desde el punto de vista artístico, pero
difieren en los tipos de polvos mágicos que requieren para llevarse a cabo.

Cada espectáculo utiliza uno o varios tipos de polvo, identificados por un
código entero, y todos los polvos que aparecen en un espectáculo se utilizan
obligatoriamente si este es elegido. Cuando un tipo de polvo se utiliza, se
consume por completo y no puede volver a usarse durante el resto de la
temporada. La experiencia ha demostrado que intentar reutilizar polvos acaba
en denuncias, inspecciones y visitas incómodas de la Comisión de Prevención
de Polvos (CPP). Como un mismo tipo de polvo puede ser necesario para
espectáculos de fines de semana distintos, una mala planificación inicial
puede hacer imposible continuar la temporada más adelante.

Además, no todos los polvos son igual de seguros. Algunos tipos son
considerados inestables por la CPP, ya que dejan efectos persistentes en el
ambiente del teatro más allá del fin de semana en que se usan. Para evitar
problemas con el público, estos efectos deben compensarse inmediatamente: si
en un fin de semana se utilizan $u$ polvos inestables, el espectáculo elegido
en el fin de semana siguiente debe incluir al menos $u$ polvos
neutralizantes, capaces de restaurar el equilibrio del ambiente. Si no existe
ninguna forma de cumplir esta condición, la CPP obliga a detener la
temporada.

Con el objetivo de maximizar los beneficios, el director quiere planificar la
temporada de manera que el circo pueda realizar espectáculos durante el mayor
número posible de fines de semana consecutivos, empezando siempre desde el
primero y respetando todas las restricciones impuestas por el uso de los
polvos mágicos.

## Entrada
- La primera línea contiene un entero $T$ ($1 \leq T \leq 250$), el número de
  temporadas a organizar.
- Para cada temporada:
  - Una línea con un entero $M$ ($1 \leq M \leq 10^4$), el número de fines de
    semana.
  - Una línea con tres enteros $P$, $I$ y $N$:
    - $P$: número total de tipos de polvo distintos ($1 \leq P \leq 2 \cdot
      10^4$).
    - $I$: número de polvos inestables ($0 \leq I \leq P$).
    - $N$: número de polvos neutralizantes ($0 \leq N \leq P$).
  - Una línea con $I$ enteros distintos, indicando los identificadores de los
    polvos inestables.
  - Una línea con $N$ enteros distintos, indicando los identificadores de los
    polvos neutralizantes. Los polvos normales son aquellos que no aparecen
    en ninguna de las dos listas anteriores.
  - A continuación, para cada fin de semana $i = 1..M$, se describen los dos
    espectáculos posibles, siempre con dos líneas:
    - Línea del espectáculo **A**: `m x1 x2 ...xm`
    - Línea del espectáculo **B**: `k y1 y2 ...yk`

    donde $1 \leq m, k \leq 10$ es la cantidad de polvos necesarios para cada
    espectáculo y $x_1, x_2, \dots, x_m, y_1, y_2, \dots, y_k$ son los
    identificadores de los polvos.

Se garantiza que no existen polvos que sean simultáneamente inestables y
neutralizantes.

## Salida
Para cada temporada, imprime un entero con el máximo número posible de
espectáculos consecutivos que se pueden organizar, comenzando desde el primer
fin de semana.

## Entrada de ejemplo
```
1
4
8 2 2
1 2
3 4
3 1 2 5
1 6
2 3 4
2 7 8
1 3
1 4
1 2
1 1
```

## Salida de ejemplo
```
4
```
