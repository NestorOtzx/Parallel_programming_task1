# Repositorio 1 Programación paralela

Este repositorio contiene multiples programas en c++ que requieren ser compilados para poder ser ejecutados, esta guía utilizará g++ para su compilación.

# Cómo compilar los archivos

A continuación, se explican los pasos para compilar y ejecutar los archivos en cada una.

## Requisitos Previos

Asegúrate de tener instalado un compilador de C++, como `g++`. Puedes verificarlo ejecutando:

```sh
g++ --version
```

## Compilación

Todos los programas en este repositorio se compilan de la siguiente manera:

1. Ve a la carpeta correspondiente:  
   ```sh
   cd ruta/a/carpeta
   ```
2. Compila el código:  
   ```sh
   g++ -o programa programa.cpp
   ```
   
### Nota importante: 
si el programa utiliza hilos y su equipo no reconoce pthreads debe compilar utilizando:

```sh
   g++ -o programa programa.cpp -lp threads
```



## Ejecución

### Activity 1

Estos programas son los requeridos para la actividad 1 de programación paralela.

### Quiz Part 1 Code

Esta carpeta contiene 3 programas

#### taylorpi.cpp

Este programa, una vez compilado, requiere de un argumento para ejecutarse y es el número de iteraciones, por lo que la ejecución de este programa sería de la siguiente manera:

```sh
   ./taylorpi <numero_de_iteraciones>
```

#### montepi.cpp

Este programa, una vez compilado, requiere de un argumento para ejecutarse y es el número de lanzamientos, por lo que la ejecución de este programa sería de la siguiente manera:

```sh
   ./montepi <numero_de_iteraciones>
```

#### carlopi.cpp

Este programa, una vez compilado, requiere de dos argumentos para ejecutarse y es el número de hilos que se le quiera dar al programa y el número de lanzamientos, por lo que la ejecución de este programa sería de la siguiente manera:

```sh
   ./montepi <número de hilos> <numero_de_iteraciones>
```

