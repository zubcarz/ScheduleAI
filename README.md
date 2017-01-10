# ScheduleAI

El programa se construyó usando dos clases :

## FNavigationRobot
  Controla la lógica de navegación. <br/>
  Valida los archivos recibidos y la correctitud del mapa. <br/>
  Ordena los puntos de entrega de acuerdo a la cercanía con el punto inicial.  <br/>
  Ordena los paquetes de acuerdo a la cercanía de los puntos de entrega. <br/>

## FPathFindingA
  Planea el camino.  <br/>
  Implementa un algoritmo de navegación A*. <br/>
  Retorna los comandos necesarios para seguir un trayecto.  <br/>

# En construcción 
  Se evaluaron diferentes algoritmos de búsqueda en grafos para determinar la ruta más corta, repitiendo nodo. <br/>
  Método que no funciono de la mejor manera se comenzó una implementación de selección por medio de la heurística. <br/>
  
# Recomendaciones 
  Evitar mínimos locales, debido a que el método empleado se basa en una discriminación del método de campos potenciales para la planificación de trayectorias.

# Instrucciones
  El Archivo de salida se crea en la raiz del proyecto, con nombre "Solution.txt"
