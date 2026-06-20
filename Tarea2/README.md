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
./construction
```

### Windows
```bash
make construction
.\construction.exe 
```
En windows make no viene instalado por defecto asi que en caso de no funcionar el compilar se puede probar con 
```bash
mingw32-make contruction
```
Y para ejecutar bonus_query (consulta que devuelve los puntos de latitud/longitud cercanas a Italia)

### Linux
```bash
make bonus
./bonus construction <dataset>
./bonus query
```
### Windows
```bash
make bonus
.\bonus.exe construction <dataset>
.\bonus.exe query
```
Como fue descrito para test, en caso de no funcionar make se puede intentar con 
```bash
mingw32-make bonus
```
### Guardar en .txt

Si uno quiere guardar los datos obtenidos en un archivo de texto para luego graficarlo puede hacer 
```bash
./contruction > construction.txt
```
Esto funciona para cualquiera de los comandos ejecutables previamente escritos (los que no llevan make). El codigo previamente escrito guarda los puntos obtenidos en la query bonus para luego ser graficados con algun script.
