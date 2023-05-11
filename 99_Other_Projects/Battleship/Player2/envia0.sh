#!/bin/bash

destino="192.168.0.166"
puerto="1234"

while true
do

#----recibir coordenada (tuberia 1)-------------

	
	# Liberar el puerto si está en uso
    	sudo fuser -k $puerto/tcp >/dev/null 2>&1

    # Pasa a modo receptor para recibir cualquier archivo que envíe el receptor
       echo "Esperando archivo del receptor 1..."
       ncat -l $puerto > tuberia1.txt
       echo "Archivo recibido."
        
         # Leer y mostrar el contenido actual del archivo
    if [ -f "tuberia1.txt" ]
    then
        cat tuberia1.txt
    fi
    
 #---enviar SI/NO (tuberia 2)-----------------------------------------------------------
    
    # Liberar el puerto si está en uso
    	sudo fuser -k $puerto/tcp >/dev/null 2>&1

    # Esperar hasta que haya un cambio en el archivo
    inotifywait -q -e modify tuberia2.txt
    
    # Leer y mostrar el contenido actual del archivo
    if [ -f "tuberia2.txt" ]
    then
        cat tuberia2.txt
    fi
    
     # Envia el archivo al receptor
        echo "Enviando $archivo..."
        cat "tuberia2.txt" | ncat $destino $puerto
        echo "Archivo enviado."
    
#----enviar coordenada (tuberia 1)---------------------------------------------

	# Liberar el puerto si está en uso
    	sudo fuser -k $puerto/tcp >/dev/null 2>&1

    # Esperar hasta que haya un cambio en el archivo
    inotifywait -q -e modify tuberia1.txt
    
    # Leer y mostrar el contenido actual del archivo
    if [ -f "tuberia1.txt" ]
    then
        cat tuberia1.txt
    fi
    
     # Envia el archivo al receptor
        echo "Enviando $archivo..."
        cat "tuberia1.txt" | ncat $destino $puerto
        echo "Archivo enviado."
    
#-----Esperando SI/NO (tuberia 2)--------------------------------------------------------------------
    
    # Liberar el puerto si está en uso
    sudo fuser -k $puerto/tcp >/dev/null 2>&1
    
     # Pasa a modo receptor para recibir cualquier archivo que envíe el receptor
       echo "Esperando archivo del receptor 1..."
       ncat -l $puerto > tuberia2.txt
       echo "Archivo recibido."
        
         # Leer y mostrar el contenido actual del archivo
    if [ -f "tuberia2.txt" ]
    then
        cat tuberia2.txt
    fi
    
    #------------------------
    
    
    #------------------------------------------------------------------
   
    
    #--------------------------------------------------------------
    
done
