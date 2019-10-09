#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  7 10:28:07 2019

@author: jose
"""

from subprocess import call
import matplotlib.pyplot as plt
import numpy as np
from os import remove

prob = 0.1

"""nube = open("nubeProb","w")
total_datos = 17
datos_finales = np.empty((total_datos,3))
pos_datos = 0

while (prob <= 0.95):
    print(prob)
    f = open("datos", "w")
    for i in range(10):
        call(['./aparcamiento', '100000', '100', '2', str(prob)], stdout=f)
    f.close
    
    datos_media = np.genfromtxt('datos', delimiter=":")
    print(datos_media)
    datos_finales[pos_datos][0]=prob
    datos_finales[pos_datos][1]= datos_media[:, 1].sum(axis=0)/10
    datos_finales[pos_datos][2]= datos_media[:, 0].sum(axis=0)/10
    
    b = np.full((10,3),prob)
    b[:,:-1] = datos_media
    np.savetxt(nube,b)
    
    pos_datos += 1
    prob += 0.05

remove("datos")
np.savetxt("../datos/datosProb.csv", datos_finales, delimiter=":")
nube.close()"""


datos_finales = np.genfromtxt('../datos/datosProb.csv', delimiter=":")

plt.plot(datos_finales[:, 0],datos_finales[:, 1],'b-')
plt.ylabel('Distancia del aparcamiento')
plt.xlabel('Probabilidad de Aparcamiento')
plt.title('Aumento de probabilididad de aparcamiento y distancia de aparcamiento')
plt.xticks(np.arange(0.1, 0.95, 0.1))
plt.show()

"""datos_finales = np.genfromtxt('../datos/datosProb.csv', delimiter=":")

plt.plot(datos_finales[:, 0],datos_finales[:, 2],'b-')
plt.ylabel('Posición de inicio')
plt.xlabel('Probabilidad de Aparcamiento')
plt.title('Aumento de probabilididad de aparcamiento y parametro(c)')
plt.xticks(np.arange(0.1, 0.95, 0.1))
plt.show()"""


"""datos_nube = np.genfromtxt('nubeProb')
y = datos_nube[:, 0]
x = datos_nube[:, 2]
p = np.polyfit(x, y, 1)
y_ajuste = p[0]*x + p[1]
print(np.size(datos_nube[:, 0]))
# Dibujamos los datos experimentales
p_datos, = plt.plot(x, y, 'b.')
# Dibujamos la recta de ajuste
p_ajuste, = plt.plot(x, y_ajuste, 'r-')

plt.title('Aumento de visión parametro c')
plt.xlabel('Alcance visión')
plt.ylabel('Empieza a buscar aparcamiento(c)')
#plt.xticks(np.arange(0.1, 0.9, 0.5))

#plt.legend(('Datos experimentales', 'Ajuste lineal'), loc="upper left")
plt.show()"""


"""y_ajuste = p[0]*x + p[1]
print(np.size(datos_nube[:, 0]))
# Dibujamos los datos experimentales
#p_datos, = plt.plot(x, y, 'b.')
# Dibujamos la recta de ajuste
p_ajuste, = plt.plot(x, y_ajuste, 'r-')

plt.title('Aumento de visión distancia')
plt.xlabel('Alcance visión')
plt.ylabel('Distancia')
plt.xticks(np.arange(inicio, fin-1, 3))

#plt.legend(('Datos experimentales', 'Ajuste lineal'), loc="upper left")
plt.show()"""

