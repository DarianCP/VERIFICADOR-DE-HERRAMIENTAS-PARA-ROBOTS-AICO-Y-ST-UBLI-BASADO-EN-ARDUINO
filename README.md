# DESCRIPCIÓN: VERIFICADOR-DE-HERRAMIENTAS-PARA-ROBOTS-AICO-Y-ST-UBLI-BASADO-EN-ARDUINO
## Mediante este programa se diseña una interfaz gráfica usando una patalla LCD y botones de navegación. La estructura de este programa facilita la incorporación de nuevas pantallas y subpantallas. Aunque tiene ciertos limites como un máximo de 5 pantallas principales.
* Se emplean solamente dos librerias, una para realizar la comunicacion I2C con el microcontrolador: https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
* y una libreria que facilita la creacion y configuración del menu LCD: https://github.com/VaSe7u/LiquidMenu 
  * Existe otra librería propia de arduino para crear menús y submenús por pantalla LCD, pero se emplea esta libreria porque aunque esta mas limitada es mas fácil de configurar.
# IMPORTANTE:
* Tener en cuenta que el tamaño del sketch supera la memoria de un Arduino UNO.
* El número de E/S requeridas para el programa es de un mínimo de 20, aunque en el programa se contemplan ampliaciones para 40 E/S.
* También se contempla ampliación para comunicación PROFIBUS, manómetros y elementos que mejoren la configuracion y el uso del verificador.
* En el directorio src de LiquidMenu comentar las lineas 33 34 y 35 del archivo y descomentar las lineas 43 44 y 45, porque estamos usando la interfaz I2C.
* Podrian observarse parpadeos que pueden deverse a interferencias y mala conexión, a la actualización o refresco de pantalla (cambiar delay) o al mal estado de la propia pantalla.
