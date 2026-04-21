# Problema L - Descubriendo Patrones Genómicos Asociados a Enfermedades

Tiempo: 1,0 s

Trabajas como bioinformático en un prestigioso laboratorio de investigación
del genoma humano. Tu equipo está investigando las bases genéticas de
diversas enfermedades complejas. Una parte crucial de vuestro trabajo
consiste en analizar extensas secuencias de ADN de pacientes y buscar
patrones específicos, conocidos como "motivos", que se sospecha están
relacionados con predisposiciones o el desarrollo de estas enfermedades.

El laboratorio ha compilado una lista de motivos de ADN que se han
identificado como posibles marcadores genéticos. Ahora, tu tarea es
desarrollar un programa informático eficiente que pueda analizar largas
secuencias de ADN en busca de regiones que contengan una cantidad
significativa de estos marcadores. Concretamente, se busca identificar las
**subcadenas contiguas más cortas que alberguen una diversidad mínima de
estos motivos**.

El problema a resolver es el siguiente: Dada una secuencia de ADN muy larga
obtenida de un paciente y una lista de motivos de ADN previamente
identificados, encontrar la **longitud de la subcadena contigua más corta**
dentro de la secuencia de ADN que contenga al menos $k$ motivos diferentes
de la lista proporcionada.

## Entrada
- La primera línea contiene una cadena de texto de $N$ caracteres que
  representa la secuencia de ADN del paciente ($1 \leq N \leq 10^4$).
- La segunda línea contiene una lista de cadenas de texto (separadas por
  espacios) que representan los motivos de ADN asociados a enfermedades. El
  número máximo de motivos es 25 y pueden tener diferentes longitudes entre
  1 y 100.
- La tercera línea contiene un número entero $K$ ($1 \leq K \leq 25$) que
  indica el número mínimo de motivos diferentes que deben estar presentes en
  la subcadena para ser considerada relevante.

## Salida
Un número entero que representa la longitud de la subcadena contigua más
corta que contiene al menos $k$ motivos diferentes. Si no se encuentra
ninguna subcadena que cumpla este criterio, devuelve 0.

## Entrada de ejemplo
```
ATGCAGTAGCTAGCTAGCATG
GCTA TAGC CATG
2
```

## Salida de ejemplo
```
6
```

## Entrada de ejemplo
```
AAAAACCCCCGGGGTTTTT
AAAA CCCC GGGG TTTT
3
```

## Salida de ejemplo
```
12
```

## Entrada de ejemplo
```
AAACCCCCGGGTTTTT
AAAA CCCC GGGG TTTT
3
```

## Salida de ejemplo
```
0
```

## Entrada de ejemplo
```
AAAAACCCCCGGGGTTTTT
AAAA CCCC GGGG TTTT
5
```

## Salida de ejemplo
```
0
```
