# Versión secuencial
# all: compile exe

# compile:
# 	gcc -o main main.c

# exe:
# 	./all.sh

# clean:
# 	rm -f main *.bin*


# Versión paralela
all: compile exe

compile:
	gcc -fopenmp -o main main.c

exe:
	./all.sh

clean:
	rm -f main *.bin*
