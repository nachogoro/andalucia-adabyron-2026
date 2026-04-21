# Problema K - Balanceando la Banda

Tiempo: 1,0 s

Edux es el líder de **Avalon**, una de las hermandades más prestigiosas del
universo Warcraft. En los últimos meses la hermandad ha crecido muchísimo,
pero eso también ha traído problemas de organización.

Después de volver de unas largas vacaciones, Edux descubrió que Lycanor y
Ragna habían estado organizando las bandas (grandes equipos de jugadores que
cooperan para completar incursiones y derrotar enemigos) con resultados
bastante caóticos. Los jugadores deben tomar distintos roles en el equipo,
pero, en este caso, algunos roles han terminado saturados mientras otros
están casi vacíos, haciendo imposible mantener el equilibrio necesario para
las incursiones.

Tú, como nuevo miembro de la hermandad (y hábil programador), decides ayudar
a resolver el problema.

En la hermandad hay $M$ jugadores de élite que quieren unirse a la próxima
banda. El juego considera en la actualidad $K$ roles posibles y, para
mantener el equilibrio del grupo, se ha establecido un valor $N$, de forma
que no debe haber más de $\left\lfloor \frac{N}{K} \right\rfloor$ jugadores
tomando un mismo rol. Además, debido a la enorme cantidad de tiempo que toma
dominar una rol, cada jugador se especializa únicamente en **dos roles
distintas**.

Tu tarea consiste en determinar si es posible organizar la banda de forma
que:

- Cada jugador participe tomando uno de los dos roles que domina.
- Ningún rol exceda su límite de jugadores permitido.

## Entrada
- La primera línea contiene un entero $T$, el número de casos de prueba.
- Para cada caso, la primera línea contiene tres enteros $N$, $M$ y $K$:
  - $N$ ($M \leq N \leq 200$) permite calcular el límite de jugadores con
    cada rol. $N$ siempre es múltiplo de $K$.
  - $M$ ($1 \leq M \leq 100$) es el número de jugadores.
  - $K$ ($1 \leq K \leq 20$) es el número de roles disponibles.
- La segunda línea contiene $K$ cadenas distintas separadas por espacios,
  representando los nombres de los roles disponibles.
- Las siguientes $M$ líneas describen a los jugadores. Cada línea contiene
  **dos cadenas distintas**, indicando los dos roles que el jugador domina.

Se garantiza que todos las roles dominados por los jugadores aparecen en la
lista inicial de roles disponibles. Las cadenas de texto solo contienen
letras mayúsculas del alfabeto inglés y su longitud está entre 1 y 15
caracteres.

## Salida
Para cada caso de prueba, debes imprimir una línea con la palabra `YES` si
existe al menos una distribución válida en la que todos los jugadores
reciben un rol que saben usar respetando los límites, o `NO` en caso
contrario.

## Entrada de ejemplo
```
3
12 4 3
MAGE PALADIN ROGUE
MAGE PALADIN
PALADIN ROGUE
ROGUE MAGE
MAGE ROGUE
4 4 2
EVOKER DRUID
EVOKER DRUID
EVOKER DRUID
EVOKER DRUID
EVOKER DRUID
6 5 3
WARLOCK MONK PRIEST
WARLOCK MONK
WARLOCK MONK
WARLOCK MONK
WARLOCK MONK
WARLOCK MONK
```

## Salida de ejemplo
```
YES
YES
NO
```
