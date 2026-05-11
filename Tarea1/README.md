# Tarea 1: R-tree en c++

Este proyecto contiene la implementacion de un R-Tree en c++.

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

