# Paralelismo-Actividad-Tres
# Control de Concurrencia con Semáforos Nombrados en C++

Este proyecto demuestra el uso de **semáforos nombrados** y **múltiples hilos** en C++ para controlar el acceso a una variable compartida de forma segura.

## Descripción

El programa crea `5` hilos que incrementan concurrentemente una variable compartida `1000` veces cada uno. Para evitar condiciones de carrera (race conditions), se utiliza un **semáforo nombrado POSIX** que regula el acceso a la variable.

## Características del Script

- Usa `std::thread` para crear hilos.
- Controla el acceso a `variableCompartida` mediante un semáforo nombrado (`sem_t*`).
- El semáforo se elimina si ya existe, y se vuelve a crear al inicio.
- Al finalizar, se muestra el valor correcto de la variable compartida: `5000`.

## Código Principal

Archivo: `main.cpp`
