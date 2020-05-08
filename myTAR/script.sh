#! /bin/bash

file1= /mytar
file2=/tmp2
a=-1

clear
if [ -f mytar ]
then
	echo -e "$? el archivo $file1 esta en el directorio\n"
else
	echo -e "el archivo $file1  NO EXISTE \n"
fi

#parada
read -n1 -r -p "press any key" key


if [ -x mytar ]
then
	echo -e "\n $? el archivo es ejecutable \n"
else
	echo -e "\n el archivo no es EJECUTBLE \n"
fi

#parada
read -n1 -r -p "press any key" key

if [ -d /tmp ]
then
	echo -e "\n $? Borrando fichero tmp"
	rm -r tmp/
	mkdir tmp
	echo -e "Creando fichero tmp y entrando\n"
else
	mkdir tmp
	echo -e "Creando fichero tmp y entrando\n"
fi

#parada
read -n1 -r -p "press any key" key

cd tmp
touch file1.txt
echo "Hello world!" >> file1.txt
echo -e "\n fichero file1.txt creado \n"

#parada
read -n1 -r -p "press any key" key

touch file2.txt
head -n 10 /etc/passwd >> file2.txt  #no es necesario -n predet 10
echo -e "\n fichero file2.txt creado \n"

#parada
read -n1 -r -p "press any key" key

touch file3.dat
tr -dc A-Za-z0-9_ < /dev/urandom | head -c 1k >> file3.dat
echo -e "\n fichero file3.dat creado \n"

#parada
read -n1 -r -p "press any key" key

#llamada a mytar con 3 fich

../mytar -c -f filetar.mtar file1.txt file2.txt file3.dat

#parada
read -n1 -r -p "press any key" key

mkdir out
cp filetar.mtar out/
echo -e "\n directorio out y copia de filetar.mtar correcta\n"

#parada
read -n1 -r -p "press any key" key

cd out
../../mytar -x -f filetar.mtar
echo -e "entro en el dir out ejecuto mtar y descomprimo\n"

#parada
read -n1 -r -p "press any key" key

diff file1.txt ../file1.txt && diff file2.txt ../file2.txt && diff file3.dat ../file3.dat ; x=$?
if [ $x = 0 ]
then
	echo -e "\n Correct"
	echo $x
	cd ../..
	
else
	echo $x
fi



