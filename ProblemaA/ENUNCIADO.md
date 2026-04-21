# Problema A - Dibujando tableros con fichas

Tiempo: 1,0 s

Teresa se considera a sí misma una auténtica fan de los juegos de tablero y
está buscando formas de aprender mejores técnicas y estrategias. Recientemente
está aprendiendo a jugar al ajedrez, y para ello ha estado estudiando partidas
famosas y analizando los movimientos de los grandes maestros. Sin embargo,
Teresa se ha dado cuenta de que no es suficiente con entender las jugadas,
sino que también es importante visualizar el tablero y las piezas en su mente
para anticipar las posibles jugadas futuras.

Cada vez que ella ve una retransmisión de una partida de ajedrez, ve que las
partidas se resumen con una secuencia de movimientos en una notación muy
concreta. Por ejemplo, la secuencia "e4 e5 Nf3 Nc6 Bb5 a6" representa una
apertura de ajedrez muy común llamada Ruy López. Teresa se ha dado cuenta de
que, aunque puede entender los movimientos, a veces le cuesta visualizar el
tablero y las piezas en su mente, lo que dificulta su capacidad para anticipar
las jugadas futuras. Para mejorar su capacidad de visualización, Teresa apunta
las coordenadas de las fichas cuando quiere pensar una jugada y trata de
imaginar cómo es el tablero en cada momento.

Sin embargo, ella quiere comprobar si el tablero que imagina es el mismo que
tiene anotado en su listado de coordenadas. Para ello, nos encarga la tarea de
escribir un programa que, dado el listado de coordenadas de las fichas,
imprima por pantalla un tablero de ajedrez con las piezas colocadas en las
posiciones correspondientes.

## Entrada
- La primera línea contiene un entero $T$ ($1 \leq T \leq 10^5$), que indica
  el número de casos de prueba.
- A continuación, cada caso de prueba contiene un entero $P$ ($0 \leq P \leq
  32$), que indica el número de piezas en el tablero, seguido de $P$ líneas,
  cada una con una cadena $C$ y una coordenada $X$.
- La cadena $C$ representa el tipo de pieza con la inicial de la palabra
  correspondiente. Rey: $R$, Dama: $D$, Torre: $T$, Alfil: $A$ Caballo: $C$,
  Peón: $P$. Las fichas blancas se representan con letras mayúsculas, mientras
  que las negras se representan con letras minúsculas.
- La coordenada $X$ se representa con una letra (de la 'a' a la 'h') seguida
  de un número (del 1 al 8), indicando la posición de la pieza en el tablero.
  Por ejemplo, 'e4' indica la casilla en la columna 'e' y la fila '4'.

## Salida
El tablero de ajedrez se representa con 8 filas y 8 columnas. Por lo que las
casillas no ocupadas por piezas se deberán imprimir correspondientemente según
sean Casilla clara (`"\u25FB"`) o Casilla oscura (`"\u25FC"`). La casilla 'a1'
es una casilla oscura, y las casillas alternan entre clara y oscura tanto en
filas como en columnas. **Ten cuidado si usas el modo oscuro en tu equipo,
porque los colores puedes estan intercambiados.**

Se deben imprimir por tanto 8 líneas, y cada línea contener exactamente 8
símbolos, ya sean casillas vacías o piezas. Para ayudar a que la salida esté
estructurada, entre cada símbolo deberá introducirse un espacio.

La primera línea del tablero corresponde a la fila 8, y la última línea
corresponde a la fila 1. La primera columna del tablero corresponde a la
columna 'a', y la última columna corresponde a la columna 'h'.

Las fichas se representan como caracter Unicode traduciendo su código de pieza
a su correspondiente símbolo.

- Piezas blancas: R = `"\u2654"`, D = `"\u2655"`, T = `"\u2656"`, A =
  `"\u2657"`, C = `"\u2658"`, P = `"\u2659"`
- Piezas negras: r = `"\u265A"`, d = `"\u265B"`, t = `"\u265C"`, a =
  `"\u265D"`, c = `"\u265E"`, p = `"\u265F"`

Las fichas deben imprimirse en la posición correcta y con los caracteres
Unicode correspondientes. Esto puede hacerse de la siguiente manera según el
lenguaje de programación utilizado:

- En Python se puede usa formato cadena para convertir el código Unicode a su
  correspondiente carácter. e.g.: `a = "\u265F"`.
- En Java se usa también el formato cadena, con una String donde su contenido
  debe ser similar al de python. e.g.: `String a = "\u265F";`.
- En C++ sucede algo similar, se puede usar un char con formato cadena. e.g.:
  `char a = "\u265F";`.
- En C se puede usar el mismo formato que en C++. e.g.: `char a = "\u265F";`.

De esta forma se garantiza que la salida se corresponda con los símbolos
Unicode de las piezas de ajedrez. Las separaciones entre símbolos se deben
hacer con un espacio.

## Entrada de ejemplo
```
1
32
t a8
c b8
a c8
d d8
r e8
a f8
c g8
t h8
p a7
p b7
p c7
p d7
p e7
p f7
p g7
p h7
P a2
P b2
P c2
P d2
P e2
P f2
P g2
P h2
T a1
C b1
A c1
D d1
R e1
A f1
C g1
T h1
```

## Salida de ejemplo
```
♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
◻ ◼ ◻ ◼ ◻ ◼ ◻ ◼
◼ ◻ ◼ ◻ ◼ ◻ ◼ ◻
◻ ◼ ◻ ◼ ◻ ◼ ◻ ◼
◼ ◻ ◼ ◻ ◼ ◻ ◼ ◻
♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖
```
