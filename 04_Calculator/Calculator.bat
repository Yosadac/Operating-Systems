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
echo 1. Multiplicar
echo 2. Sumar
echo 3. Dividir
echo 4. Encontrar la suma de 5 numeros enteros
echo 5. Promedio de 3 numeros
echo 6. Mostrar un saludo
echo 7. Media de 2 numeros
echo 8. Salir
echo.
set /p op=Ingrese una opcion:
if "%op%"=="1" goto Multiplicar
if "%op%"=="2" goto Sumar
if "%op%"=="3" goto Dividir
if "%op%"=="4" goto 5num
if "%op%"=="5" goto Promedio
if "%op%"=="6" goto Saludo
if "%op%"=="7" goto media
if "%op%"=="8" goto salir
echo Opcion invalida. Presione cualquier tecla para volver al menú.
pause >nul
goto menu
:Multiplicar
echo Por favor ingrese dos numeros que desee que se multipliquen
Set /p num1=Ingrese el primer numero:
Set /p num2=Ingrese el segundo numero:
Set /a mult=%num1% * %num2%
echo El resutado de la multiplicacion es %mult%
pause
goto menu
:Sumar
echo Por favor ingrese dos numeros que desee que se sumen
Set /p num1=Ingrese el primer numero:
Set /p num2=Ingrese el segundo numero:
Set /a sum=%num1%+%num2%
echo El resutado de la suma es %sum%
pause
goto menu
:Dividir
echo Por favor ingrese dos numeros que desee que se dividan
Set /p num1=Ingrese el primer numero:
Set /p num2=Ingrese el segundo numero:
Set /a div=%num1% / %num2%
set /a record=%num1% %% %num2%
set /a decimal=%record% * 100 / %num2%
echo La division de los numeros es: %div%.%decimal%
pause
goto menu
:5num
echo Suma de 5 numeros enteros
set /p num1=Ingresa el primer numero:
set /p num2=Ingresa el segundo numero:
set /p num3=Ingresa el tercer numero:
set /p num4=Ingresa el cuarto numero:
set /p num5=Ingresa el quinto numero:
set /a resultado=%num1%+%num2%+%num3%+%num4%+%num5%
echo El resultado de la suma es: %resultado%
pause
goto menu
:Promedio
echo Promedio de 3 numeros
set /p num1=Ingresa el primer numero:
set /p num2=Ingresa el segundo numero:
set /p num3=Ingresa el tercer numero:
set /a suma=%num1%+%num2%+%num3%
set /a resultado=%suma%/3
set /a record=suma %% 3
set /a decimal=%record% * 100 / 3
echo El promedio es: %resultado%.%decimal%
pause
goto menu
:Saludo
set /p nombre=Favor de ingresar su nombre:
set /p carrera=Famor de escribir su carrera:
echo Hola %nombre% de la carrera de %carrera%
pause
goto menu
:media
echo Media de 2 numeros
set /p num1=Ingresa el primer numero:
set /p num2=Ingresa el segundo numero:
set /a suma=%num1%+%num2%
set /a resultado=%suma%/2
set /a record=suma %% 2
set /a decimal=%record% * 100 / 2
echo El promedio es: %resultado%.%decimal%
pause
goto menu
:salir
echo Adios.
rem Eliminar
rem DEL /F /A Img_1.jpg
pause