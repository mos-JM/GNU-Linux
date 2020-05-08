#!/bin/bash

MPOINT="./mount-point"
TEMP="./temp"



#a) 

cp ./src/fuseLib.c ./src/myFS.h $MPOINT
mkdir $TEMP
cp ./src/fuseLib.c ./src/myFS.h $TEMP
echo -e 'copiado de archivos'
read -p "Press enter..."




#b) 		

./my-fsck virtual-disk


read -p "Press enter..."

diff ./src/fuseLib.c $MPOINT/fuseLib.c
diff ./src/myFS.h $MPOINT/myFS.h
echo -e 'se han comparado los archivos copiados al SF con los originales'
read -p "Press enter..."
echo -e 
truncate -o -s -1 $TEMP/fuseLib.c
truncate -o -s -1 $MPOINT/fuseLib.c
echo -e 'se han truncado los archivos fuseLib.c copiados con un bloque menos'
read -p "Press enter..."



#c)

./my-fsck virtual-disk

read -p "Press enter..."

diff ./src/fuseLib.c $TEMP/fuseLib.c

echo -e 'Se ha comparado el archivo original con el de '$TEMP
read -p "Press enter..."

diff ./src/fuseLib.c $MPOINT/fuseLib.c

echo -e 'Se ha comparado el archivo original con el de '$MPOINT
read -p "Press enter..."



#d) 

cp script.sh $MPOINT
echo -e 'se ha copiado script.sh a '$MPOINT
read -p "Press enter..."



#e) 

./my-fsck virtual-disk

read -p "Press enter..."

diff script.sh $MPOINT/script.sh
echo -e 'se han comparado los script.sh'
read -p "Press enter..."



#f ) 	

truncate -o -s +1 $TEMP/myFS.h
truncate -o -s +1 $MPOINT/myFS.h
echo -e 'se han truncado los archivos myFS.h copiados con un bloque de más'
read -p "Press enter..."

#g) 
./my-fsck virtual-disk

read -p "Press enter..."

diff ./src/myFS.h $TEMP/myFS.h

echo -e 'Se ha comparado el archivo original con el de '$TEMP
read -p "Press enter..."
diff ./src/myFS.h $MPOINT/myFS.h

echo -e 'Se ha comparado el archivo original con el de '$MPOINT
read -p "Press enter..."

