# Problema G - La muralla del reino

Tiempo: 0,5 s

El reino está sufriendo una oleada de ataques por parte de sus enemigos
externos y, tras la última batalla, la gran muralla defensiva de la región
norte ha quedado seriamente dañada. Es vital llevar a cabo su reconstrucción
cuanto antes, pues la amenaza exterior permanece y el riesgo de un nuevo
ataque es muy elevado.

Por su arquitectura, la muralla está formada por $N$ tramos contiguos, cada
uno más o menos dañado. En función del nivel de daños, la reparación del
tramo $i$ se estima que requiere $h_i$ horas de trabajo de una brigada de
obreros. Para la reconstrucción completa se van a desplegar $K$ brigadas,
pero debido a la logística del transporte de materiales y maquinaria pesada,
cada brigada debe encargarse de una sección continua de cero o más tramos
completos de la muralla. El tiempo total que una brigada empleará es la suma
de las horas de reparación estimadas para los tramos que se le asignen.
Ahora bien, si una brigada recibe una carga de trabajo muy alta, terminará
agotada y retrasará la finalización de la obra, ya que esta se terminará
cuando la brigada con más trabajo finalice su parte.

Como hay que intentar terminar la reconstrucción de la muralla antes de que
los enemigos vuelvan al ataque, el objetivo es asignar los $N$ tramos a $K$
brigadas como mucho, de manera que todas ellas reciban tramos contiguos y la
obra termine lo antes posible. Todas las brigadas empezarán a trabajar a la
vez.

## Entrada
Está compuesta por varios casos de prueba, cada uno ocupando dos líneas:

- La primera contiene dos enteros $N$, el número de tramos, y $K$, el de
  brigadas de obreros disponibles, donde $(1 \leq K \leq N \leq 10^5)$.
- A continuación, en la segunda línea, vienen $N$ enteros, $h_1, h_2, \dots,
  h_N$ ($0 \leq h_i \leq 10^9$), separados por espacios, que son las horas de
  trabajo estimadas para cada tramo en el mismo orden en que se encuentran
  en la muralla.

La entrada termina cuando no hay más casos de prueba.

## Salida
Por cada caso de prueba se escribirá una línea con un único entero, el
mínimo de horas en el que se puede reparar la muralla.

## Entrada de ejemplo
```
6 3
10 15 10 15 10 10
5 2
48 12 0 20 50
4 3
50 15 20 10
```

## Salida de ejemplo
```
25
70
50
```

**Caso 1**

Una distribución óptima es _brigada1_, $10 + 15 = 25$; _brigada2_, $10 + 15 =
25$; _brigada3_, $10 + 10 = 20$.

La máxima carga de trabajo es 25 horas. Cualquier otro reparto de tramos
resultaría en una carga máxima de al menos 25 horas.

**Caso 2**

Una distribución óptima es _brigada1_, $48 + 12 + 0 = 60$; _brigada2_, $20 +
50 = 70$.

La máxima carga de trabajo es 70 horas. Cualquier otro reparto de tramos
resultaría en una carga máxima de al menos 70 horas.

**Caso 3**

Una distribución óptima es _brigada1_, $50$; _brigada2_, $15 + 20 + 10 = 45$;
_brigada3_, $0$.

La máxima carga de trabajo es 50 horas. Cualquier otro reparto de tramos
resultaría en una carga máxima de al menos 50 horas.
