# Problema H - Control de acceso en el laboratorio

Tiempo: 0,5 s

En un laboratorio de investigación (que, por supuesto, nunca ha tenido
problemas de seguridad), se ha instalado un sistema automático para
controlar el acceso a una sala restringida.

El sistema registra una secuencia de eventos:

- `E`: entra una persona
- `S`: sale una persona

Por motivos de seguridad (y de sentido común), el sistema debe cumplir
ciertas reglas:

- No puede salir nadie si la sala está vacía
- La sala tiene una capacidad máxima limitada
- Al finalizar el registro, la sala debe quedar vacía

Tu tarea es comprobar si un registro de eventos es válido.

## Entrada
- La primera línea contiene un entero $T$ ($T \geq 1$), el número de
  registros.
- Para cada registro:
  - Una línea con un entero $C$ ($C \geq 1$), la capacidad máxima de la sala
  - Una línea con una cadena $s$ formada únicamente por los caracteres `E` y
    `S`. La cantidad de caracteres de $s$ es al menos 1 y no supera $10^5$.

## Salida
Para cada registro, imprimir:

- `VALIDO` si la secuencia cumple todas las condiciones
- `INVALIDO` en caso contrario

## Entrada de ejemplo
```
5
3
EESESS
2
EESS
2
EESSS
2
ESEESEESSS
3
EEESSESSEES
```

## Salida de ejemplo
```
VALIDO
VALIDO
INVALIDO
INVALIDO
INVALIDO
```

- En el primer caso, la ocupación nunca supera 3, nunca se intenta salir con
  la sala vacía y la sala acaba sin nadie.
- En el segundo, también todo es correcto.
- En el tercero, hay una salida extra sin nadie dentro.
- En el cuarto, hay un momento con 3 personas, superando el aforo máximo.
- En el último caso, una persona se queda en el laboratorio sin salir.
