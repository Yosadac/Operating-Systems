@echo off
echo Autores: Espinosa Razo Uriel Alejandro, Ramirez Osorio Yosadac, Balam Gael
Damian Roldan
echo Informacion del sistema
echo ================================
echo Nombre del host: %COMPUTERNAME%
systeminfo | find "Idioma de entrada:"
systeminfo | find "Tipo de sistema:"
echo Sistema operativo: %OS%
echo Procesador: %PROCESSOR_IDENTIFIER%
echo Memoria fisica utilizada:
wmic OS get FreePhysicalMemory /value | findstr /c:"="
pause