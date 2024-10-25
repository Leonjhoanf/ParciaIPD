#!/usr/bin/env bash
#
# Este script procesa todas las imágenes PNG en el directorio images/
# Primero las convierte a binario para su procesamiento,
# y finalmente guarda las imágenes procesadas
#
# Autor: Juan Camilo Narváez Tascón - juan.narvaez.tascon@correounivalle.edu.co
# Modificado para procesamiento por lotes
#

# Procesar cada imagen PNG en el directorio images/
for image in images/*.png; do
    basename=$(basename "$image" .png)
    
    touch "images/${basename}.bin"
    
    python3 fromPNG2Bin.py "$image"
    ./main "images/${basename}.bin"
    python3 fromBin2PNG.py "images/${basename}.bin.new"
    
done

# Limpiar archivos temporales
rm -f "images/*.bin" "images/*.bin.new"

echo "Procesamiento de todas las imágenes completado."
