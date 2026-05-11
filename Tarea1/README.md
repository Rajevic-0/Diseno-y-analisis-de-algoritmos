# Tarea 1: R-tree en c++

Este proyecto contiene la implementacion de un R-Tree en c++.

## Estructura del proyecto

```bash
Tarea1/
├── include/
│   ├── bulk_loading.hpp
│   ├── creation.hpp
│   ├── globals.hpp
│   └── rtree.hpp
├── src/
│   ├── construction.cpp
│   ├── consultas.cpp
│   ├── create_tree.cpp
│   ├── globals.cpp
│   ├── main.cpp
│   ├── nearest-x.cpp
│   ├── sort-tile-recursive.cpp
│   ├── test_load.cpp
│   └── tree.cpp
├── .gitignore
├── Makefile
└── README.md
```
## Ejecucion

Para ejecutar el proyecto uno puede hacer:

Linux
```bash
make test
./test construction <dataset_1> <dataset_2>
./test query
```

Windows
```bash
make test
.\test.exe construction <dataset_1> <dataset_2>
.\test.exe query
```

Y para ejecutar bonus_query (consulta que devuelve los puntos de latitud/longitud cercanas a Italia)

Linux
```bash
make bonus
./bonus construction <dataset>
./bonus query
```
Windows
```bash
make bonus
.\bonus.exe construction <dataset>
.\bonus.exe query
```
Este proyecto esta pensado para ser usado con los datasets encontrados en 
[Descargar datasets](https://github.com/claugaete/tarea1-cc4102-2026-1/releases/tag/Datos)

De la siguiente manera:

| Dataset | Archivo |
|---|---|
| Dataset 1 | `random.bin` |
| Dataset 2 | `europa.bin` |
| Dataset Bonus | `europa_bonus.bin` |

Puede ser ejecutado con otros datasets pero los nombres no coincidiran con lo ejecutado, ver src/main.cpp, src/construction.cpp y src/consultas.cpp si se quiere modificar este proyecto para ser ejecutado con otros datasets de puntos.
