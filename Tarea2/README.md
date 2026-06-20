# Tarea 2: AVL-trees y Splay-trees en c++

Este proyecto contiene la implementacion de AVL y Splay trees en c++.

## Estructura del proyecto

```bash
Tarea2/
├── include/
│   ├── avl-tree.hpp
│   ├── splay-tree.hpp
│   └── tree-rotation.hpp
├── src/
│   ├── avl-tree.cpp
│   ├── construction.cpp
│   ├── main.cpp
│   ├── splay-tree.cpp
│   └── tree-rotations.cpp
├── .gitignore
├── Makefile
└── README.md
```
## Ejecucion

Para ejecutar el proyecto uno puede hacer:

### Linux
```bash
make construction
./construction (mode)
```

### Windows
```bash
make construction
.\construction.exe (mode)
```
En windows make no viene instalado por defecto asi que en caso de no funcionar el compilar se puede probar con 
```bash
mingw32-make contruction
```
### Guardar en .txt

## Mode

Hay 4 modos con los cuales se puede correr construction

1. construction (no escbribir mode): Construye los datasets
2. base: Ejecuta construccion y busqueda en AVL y Splay.
3. sequential: Ejecuta pruebas para el teorema de acceso secuencial.
4. working: Ejectua pruebas para el teorema de conjunto de trabajo.

* Para ejecutar 2,3 y 4 se debe haber ejecutado 1 antes 

Si uno quiere guardar los datos obtenidos en un archivo de texto para luego graficarlo puede hacer 
```bash
./contruction > construction.txt
```
Esto funciona para cualquiera de los comandos ejecutables previamente escritos (los que no llevan make).
