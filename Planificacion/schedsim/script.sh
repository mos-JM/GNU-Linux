#! /bin/bash

declare -a Schedulers=( RR SJF FCFS PRIO TJF LOT TJFEX )

read -p "Fichero desea simular?: (ejemplo: examples/example.txt) " fichero
while [ ! -f $fichero ]
do
echo "el fichero no existe"
read -p "Intentalo de nuevo: " fichero
done

read -p "Numero de CPUs a ejecutar: " CPUs
while [ $CPUs -gt 8 -o $CPUs -lt 1 ]
do
echo "Tiene que ser entre 1 y 8"
read -p "Numero de CPUs a ejecutar: " CPUs
done

echo "Creando directorio resultado"
mkdir -p resultados

for nameSched in ${Schedulers[*]}
do
	cpus=1
	while [ $cpus -le $CPUs ]
		do
		./schedsim -i $fichero -n $cpus -s $nameSched
		i=`expr $cpus - 1`
		mv CPU_$i.log resultados/$nameSched-CPU-$i.log
		cd ../gantt-gplot/
		./generate_gantt_chart ../schedsim/resultados/$nameSched-CPU-$i.log
		cpus=`expr $cpus + 1`
		cd ../schedsim
	done
done
