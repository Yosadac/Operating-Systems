@echo off
:menu
cls
echo
===================================================================================
=======
echo Autores: Espinosa Razo Uriel Alejandro, Ramirez Osorio Yosadac, Balam Gael
Damian Roldan
echo MENU
echo
===================================================================================
=======
echo Porfavor elija una opcion
echo 1. Copiar
echo 2. Mover
echo 3. Eliminar
echo 4. Ocultar
echo 5. Mostrar
echo 6. Salir
echo.
set /p op=Ingrese una opcion:
if "%op%"=="1" goto Copiar
if "%op%"=="2" goto Mover
if "%op%"=="3" goto Eliminar
if "%op%"=="4" goto Ocultar
if "%op%"=="5" goto Mostrar
if "%op%"=="6" goto salir
echo Opcion invalida. Presione cualquier tecla para volver al menú.
pause >nul
goto menu
:Copiar
set /p "origen=Porfavor escriba la direccion del archivo que desea copiar: "
set /p "destino=Por favor escriba la direccion de destino del archivo: "
copy "%origen%" "%destino%"
pause
goto menu
:Mover
set /p "origen=Porfavor escriba la direccion del archivo que desea mover: "
set /p "destino=Por favor escriba la direccion de destino del archivo: "
MOVE "%origen%" "%destino%"
pause
goto menu
:Eliminar
set /p "arch=Porfavor escriba la direccion del archivo que desea eliminar: "
DEL /F /A "%arch%"
pause
goto menu
:Ocultar
set /p "arch=Porfavor escriba la direccion del archivo que desea ocultar: "
attrib +h "%arch%"
pause
goto menu
:Mostrar
set /p "arch=Porfavor escriba la direccion del archivo que desea mostrar: "
attrib -s -h "%arch%"
pause
goto menu
:salir
echo Adios.
rem Eliminar
rem DEL /F /A Img_1.jpg
pause