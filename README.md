# Planificador de viajes
La funcionalidad de Planificador es la de, en base a un archivo txt, donde se encuentran ciudades con sus respectivas coordenadas x e y, procesar la información del archivo y brindar mediante las funciones correspondientes una determinada visualización de las ciudades. El usuario tiene la posibilidad de ordenar dichas ciudades de forma ascendente y descendente dependiendo la distancia en la que se encuentren, y además puede organizar su viaje para poder reducir sus horas de manejo. Todo esto mediante un menú de usuario ejecutado por consola. El propósito general del proyecto, es poder brindarle al usuario una herramienta para poder organizar sus viajes de la forma que deseen.

Proceso de instalación 💻  
Al momento de ejecutar el programa se eben seguir una serie de pasos:
  1. Ejecutar la consola en el directorio donde se encuentre el programa.
  2. Ingresar la siguiente línea de comandos, donde gcc es el compilador utilizado, los archivos con extensión .c son los módulos de código y Planificador.exe es el nombre del programa. Si lo desea, puede cambiar el nombre del programa. gcc -o Planificador.exe planificador.c colacp.c Lista.c
  3. Una vez compilado el código anterior, se generará un ejecutable Planificador.exe correspondiente al programa en cuestión.  
Es fundamental para llevar a cabo la instalación contar con los servicios del compilador GCC, de lo contrario producirá un error.

Para invocar Planificador.exe se hace uso de la consola con la siguiente invocación: /.Planificador.exe “archivo.txt”

Formato del documento📄  
[nombre de la cuidad];[coordenada x];[coordenada y]  
EJ:  
Buenos Aires;123;450
Rosario;100;52
La Plata;900;423

Construido con 🛠️  
C

Autores ✒️  
Franco Leon - Desarrollador  
Aguistín Vera - Desarrollador

Proyecto acadéico realizado para la materia Organizacion de Computadoras, Universidad Nacional del Sur, Bahía Blanca.

