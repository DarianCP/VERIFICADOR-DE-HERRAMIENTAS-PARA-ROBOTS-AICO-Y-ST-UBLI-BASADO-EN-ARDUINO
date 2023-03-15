# DESCRIPCIÓN: VERIFICADOR-DE-HERRAMIENTAS-PARA-ROBOTS-AICO-Y-STAUBLI-BASADO-EN-ARDUINO
## Mediante este programa se diseña una interfaz gráfica usando una patalla LCD y botones de navegación. La estructura de este programa facilita la incorporación de nuevas pantallas y subpantallas. Aunque tiene ciertos límites como un máximo de 5 pantallas principales.
* Se emplean solamente dos librerias, una para realizar la comunicacion I2C con el microcontrolador: https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
* y una librería que facilita la creación y configuración del menu LCD:
  * Para la versión 1.5.1: https://github.com/VaSe7u/LiquidMenu/releases/tag/v1.5.1 (La que usamos en este programa)
  * Para la versión 1.6 https://github.com/VaSe7u/LiquidMenu (Actualización de la anterior, es necasario modificarla poniendo a True I2C)
  * Existe otra librería propia de arduino para crear menús y submenús por pantalla LCD, pero se emplea esta librería porque aunque esta mas limitada es mas fácil de configurar.
# IMPORTANTE:
* Tener en cuenta que el tamaño del sketch supera la memoria de un Arduino UNO. Usar Arduino MEGA con 256kB de memoria FLASH
* El número de E/S requeridas para el programa es de un mínimo de 20, aunque en el programa se contemplan ampliaciones para 40 E/S.
* También se contempla ampliación para comunicación PROFIBUS, manómetros y elementos que mejoren la configuracion y el uso del verificador.
* En el directorio src de LiquidMenu comentar las lineas 33 34 y 35 del archivo y descomentar las líneas 43 44 y 45, porque estamos usando la interfaz I2C.
* Podrían observarse parpadeos que pueden deberse a interferencias y mala conexión, a la actualización o refresco de pantalla (cambiar delay) o al mal estado de la propia pantalla.
* Si con lcd.begin() da error al ejecutar el programa, podeis comentarlo y deberia funcionar correctamente porque no es necesario.
### Observaciones:
 * Destacar que este proyecto se basa en una máquina verificadora anterior que realizaba las mismas funciones,pero que su diseño se basaba exclusivamente en electrónica. Este enfoque presentaba ciertas limitaciones a la hora de reproducir y añadir mejoras en el funcionamiento de la máquina. Por ello, se ha mantenido la nomenclatura y los esquemas eléctricos utilizados en la máquina original para establecer una relación y hacerla más comprensible.
