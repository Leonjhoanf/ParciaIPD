### Análisis de Desempeño y Speedup del Programa Paralelizado

Este análisis tiene como objetivo evaluar el desempeño tanto del programa paralelo como del secuencial, calcular el **speedup** logrado con la paralelización, y discutir la **eficiencia** del uso de múltiples núcleos. Las pruebas fueron realizadas en un equipo con las siguientes características de hardware:


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

Este procesador tiene **8 núcleos físicos** y puede manejar hasta **16 hilos** en paralelo.

### Modificación del Makefile

El **Makefile** fue modificado para compilar la versión paralela del programa utilizando **OpenMP**. De esta forma, las versiones paralelas se ejecutan correctamente con soporte de múltiples hilos, mientras que la versión secuencial se corre utilizando el comando `time make`.

### Resultados de Ejecución

#### Ejecución Secuencial:
Los tiempos obtenidos para la versión secuencial fueron:
- **real:** 0m10.506s, 0m7.466s, 0m7.466s, 0m7.668s, 0m10.489s

Siguiendo el procedimiento de eliminar los tiempos más bajos y más altos, y calcular el promedio:

1. **Eliminar el tiempo más bajo**: 0m7.466s
2. **Eliminar el tiempo más alto**: 0m10.506s
3. **Tiempos restantes**: 0m7.466s, 0m7.668s, 0m10.489s
4. **Promedio**:

   $$
   \frac{7.466 + 7.668 + 10.489}{3} = \frac{25.623}{3} = 8.541 \text{ segundos}
   $$
   
El tiempo promedio de ejecución secuencial es **8.541 segundos**.

#### Ejecución Paralela con N hilos (Número de núcleos = 8):
Los tiempos obtenidos para la versión paralela fueron:
- **real:** 0m7.388s, 0m7.506s, 0m7.385s, 0m7.188s, 0m10.957s

Siguiendo el mismo procedimiento:

1. **Eliminar el tiempo más bajo**: 0m7.188s
2. **Eliminar el tiempo más alto**: 0m10.957s
3. **Tiempos restantes**: 0m7.388s, 0m7.506s, 0m7.385s
4. **Promedio**:

$$
\frac{7.388 + 7.506 + 7.385}{3} = \frac{22.279}{3} = 7.426 \text{ segundos}
$$
  
Por lo tanto, el tiempo promedio de ejecución con esta versión es **7.426 segundos**.

#### Ejecución Paralela con 2N hilos (Número de hilos = 16):
Los tiempos obtenidos para la versión con 16 hilos fueron:
- **real:** 0m7.035s, 0m7.385s, 0m7.385s, 0m7.120s

Siguiendo el procedimiento:

1. **Eliminar el tiempo más bajo**: 0m7.035s
2. **Eliminar el tiempo más alto**: 0m7.385s (uno de los dos, ya que ambos tienen el mismo valor)
3. **Tiempos restantes**: 0m7.385s, 0m7.120s
4. **Promedio**:

$$
\frac{7.385 + 7.120}{2} = \frac{14.505}{2} = 7.253 \text{ segundos}
$$

Por lo tanto, el tiempo promedio de ejecución con los hilos configurados es **7.253 segundos**.

### Cálculo del Speedup

El **speedup** se calcula usando la fórmula:

$$
S = \frac{T_s}{T_p}
$$

donde:
- $T_s$ es el tiempo de ejecución secuencial.
- $T_p$ es el tiempo de ejecución paralelo.

#### Speedup para N hilos (8 hilos):

$$
S = \frac{8.541}{7.426} = 1.150
$$

#### Speedup para 2N hilos (16 hilos):

$$
S = \frac{8.541}{7.253} = 1.178
$$

### Cálculo de la Eficiencia

La **eficiencia** se calcula usando la fórmula:

$$
E = \frac{S}{P}
$$

donde:
- $S$ es el speedup.
- $P$ es el número de hilos.

#### Eficiencia para N hilos (8 hilos):

$$
E = \frac{1.150}{8} = 0.144
$$

#### Eficiencia para 2N hilos (16 hilos):

$$
E = \frac{1.178}{16} = 0.0736
$$

### Discusión de la Eficiencia

La eficiencia obtenida muestra que, aunque se logra una mejora en el tiempo de ejecución al paralelizar el código, la ganancia es modesta en términos de speedup. La eficiencia disminuye significativamente cuando se incrementa el número de hilos a 16, lo cual indica que el programa no escala linealmente con el número de hilos. Esto puede deberse a varios factores, tales como la **sobrecarga de sincronización**, la **contención en la memoria** o las **dependencias entre tareas**, que limitan el beneficio de agregar más hilos.

La eficiencia de **0.144** con 8 hilos sugiere que el programa está utilizando aproximadamente el **14.4%** de la capacidad de paralelización teórica. Al aumentar a 16 hilos, la eficiencia baja a **7.36%**, lo que indica una **saturación** del rendimiento en este caso.

### Conclusión

El uso de OpenMP permitió una mejora moderada en el tiempo de ejecución, pero la escalabilidad se ve limitada por la naturaleza del código y las características del hardware. Una posible área de optimización sería reducir la sobrecarga de sincronización y mejorar el paralelismo de las secciones críticas del código.
# IPD
