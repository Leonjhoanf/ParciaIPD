
### Análisis de Desempeño y Aceleración del Programa Paralelizado

Este análisis tiene como objetivo evaluar el rendimiento del programa en sus versiones secuencial y paralela, calcular el **speedup** con diferentes configuraciones de hilos, y discutir la **eficiencia** del uso de múltiples hilos. Las pruebas fueron realizadas en una máquina con las siguientes características de hardware:

#### Especificaciones del hardware:
```json
{
  "vendor_id": "GenuineIntel",
  "cpu_family": 6,
  "model": 140,
  "model_name": "11th Gen Intel(R) Core(TM) i5-11300H",
  "stepping": 1,
  "cpu_MHz": 6220.79,
  "cache_size": "512 KB",
  "physical_id": 0,
  "siblings": 8,
  "core_id": 0,
  "cpu_cores": 8
}
```

Este procesador tiene **8 núcleos físicos** y puede manejar hasta **8 hilos**.

### Modificación del Makefile

El **Makefile** fue ajustado para compilar la versión paralela del programa utilizando **OpenMP**. Se realizaron ejecuciones con 4 y 8 hilos, y se usó `time make` para la versión secuencial.

### Resultados de Ejecución

#### Ejecución Secuencial:
Los tiempos registrados para la versión secuencial fueron:
- **real:** 0m9.456s, 0m6.789s, 0m6.894s, 0m7.045s, 0m9.600s

Siguiendo el procedimiento de eliminar el tiempo más bajo y el más alto:

1. **Eliminar el tiempo más bajo**: 0m6.789s
2. **Eliminar el tiempo más alto**: 0m9.600s
3. **Tiempos restantes**: 0m6.894s, 0m7.045s, 0m9.456s
4. **Promedio**:

   $$ \frac{6.894 + 7.045 + 9.456}{3} = \frac{23.395}{3} = 7.798 \text{ segundos} $$

El tiempo promedio de ejecución secuencial es **7.798 segundos**.

#### Ejecución Paralela con 4 Hilos:
Los tiempos registrados usando 4 hilos fueron:
- **real:** 0m7.345s, 0m7.456s, 0m7.289s, 0m7.501s, 0m8.600s

Aplicando el mismo proceso:

1. **Eliminar el tiempo más bajo**: 0m7.289s
2. **Eliminar el tiempo más alto**: 0m8.600s
3. **Tiempos restantes**: 0m7.345s, 0m7.456s, 0m7.501s
4. **Promedio**:

$$ \frac{7.345 + 7.456 + 7.501}{3} = \frac{22.302}{3} = 7.434 \text{ segundos} $$

El tiempo promedio de ejecución paralela con **4 hilos** es **7.434 segundos**.

#### Ejecución Paralela con 8 Hilos:
Los tiempos registrados usando 8 hilos fueron:
- **real:** 0m6.550s, 0m6.689s, 0m6.410s, 0m6.305s, 0m9.107s

Aplicando el mismo procedimiento:

1. **Eliminar el tiempo más bajo**: 0m6.305s
2. **Eliminar el tiempo más alto**: 0m9.107s
3. **Tiempos restantes**: 0m6.550s, 0m6.689s, 0m6.410s
4. **Promedio**:

$$ \frac{6.550 + 6.689 + 6.410}{3} = \frac{19.649}{3} = 6.549 \text{ segundos} $$

El tiempo promedio de ejecución paralela con **8 hilos** es **6.549 segundos**.

### Cálculo del Speedup

El **speedup** se calcula usando la fórmula:

$$ S = \frac{T_s}{T_p} $$

donde:
- $T_s$ es el tiempo de ejecución secuencial.
- $T_p$ es el tiempo de ejecución paralelo.

#### Speedup con 4 hilos:

$$ S = \frac{7.798}{7.434} = 1.049 $$

#### Speedup con 8 hilos:

$$ S = \frac{7.798}{6.549} = 1.190 $$

### Cálculo de la Eficiencia

La **eficiencia** se calcula como:

$$ E = \frac{S}{P} $$

donde:
- $S$ es el speedup.
- $P$ es el número de hilos.

#### Eficiencia con 4 hilos:

$$ E = \frac{1.049}{4} = 0.262 $$

#### Eficiencia con 8 hilos:

$$ E = \frac{1.190}{8} = 0.149 $$

### Discusión de la Eficiencia

Con **4 hilos**, el programa presenta una eficiencia de **26.2%**, lo que indica un buen aprovechamiento de los recursos de paralelización en esa configuración. Sin embargo, al aumentar a **8 hilos**, la eficiencia baja a **14.9%**, lo que sugiere que el programa encuentra ciertos cuellos de botella que impiden un uso eficiente de todos los hilos disponibles.

La **sobrecarga de sincronización** y posibles **dependencias** entre las tareas paralelas pueden ser factores que influyen negativamente en la escalabilidad.

### Conclusión

El uso de OpenMP mejora el rendimiento del programa, pero la escalabilidad se ve limitada al aumentar el número de hilos. La eficiencia disminuye a medida que se incrementa el número de hilos, lo que sugiere áreas de optimización en la gestión de paralelismo y la minimización de la sobrecarga de sincronización.

