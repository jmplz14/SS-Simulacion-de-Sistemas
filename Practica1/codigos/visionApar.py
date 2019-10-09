#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  7 10:28:07 2019

@author: jose
"""

from subprocess import call
import numpy as np
from os import remove
import seaborn as sns
import pandas as pd

from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter



inicio = 2
fin = 31

##Obtiene los datos
"""nube = open("nubeVision","w")

total_datos = fin-inicio
datos_finales = np.empty((total_datos,3))
pos_datos = 0
for j in range(inicio,fin):
    print(j)

    f = open("datos", "w")
    for i in range(10):
        call(['./aparcamiento', '100000', '100', str(j), '0.9'], stdout=f)
    f.close
    
    datos_media = np.genfromtxt('datos', delimiter=":")
    datos_finales[pos_datos][0]=j
    datos_finales[pos_datos][1]= datos_media[:, 1].sum(axis=0)/10
    datos_finales[pos_datos][2]= datos_media[:, 0].sum(axis=0)/10
    b = np.full((10,3),float(j))
    b[:,:-1] = datos_media
    np.savetxt(nube,b)
    
    pos_datos += 1

remove("datos")
np.savetxt("../datos/datosVisionv2.csv", datos_finales, delimiter=":")
nube.close()"""
datos_finales = np.genfromtxt('../datos/visionProb.csv', delimiter=":")

"""plt.plot(datos_finales[:, 0],datos_finales[:, 1],'b-')
plt.ylabel('Distancia aparcamiento')
plt.xlabel('Visión del aparcamiento')
plt.title('Aumento de vision y distancia')
plt.xticks(np.arange(inicio, fin-1, 3))
plt.show()

"""
"""print(datos_finales)
plt.plot(datos_finales[:, 0],datos_finales[:, 2],'b-')
plt.ylabel('Posicion Inicio(c)')
plt.xlabel('Visión del aparcamiento')
plt.title('Aumento de visión y posición de inicio')
plt.xticks(np.arange(inicio, fin-1, 3))
plt.show()"""

"""datos_nube = np.genfromtxt('nubeVision')
y = datos_nube[:, 0]
x = datos_nube[:, 2]
p = np.polyfit(x, y, 1)
y_ajuste = p[0]*x + p[1]
print(np.size(datos_nube[:, 0]))
# Dibujamos los datos experimentales
#p_datos, = plt.plot(x, y, 'b.')
# Dibujamos la recta de ajuste
p_ajuste, = plt.plot(x, y_ajuste, 'r-')

plt.title('Aumento de visión parametro c')
plt.xlabel('Alcance visión')
plt.ylabel('Empieza a buscar aparcamiento(c)')
plt.xticks(np.arange(inicio, fin-1, 3))

#plt.legend(('Datos experimentales', 'Ajuste lineal'), loc="upper left")
plt.show()


y_ajuste = p[0]*x + p[1]
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

print(datos_finales)
#datos_finales = np.genfromtxt('../datos/datosProb.csv', delimiter=":")


N = 2000
X = np.random.normal(size=N)
Y = np.random.normal(size=N)
Z = (X**2+Y**2)**(1/2.0)

plt.scatter(X,Y,c=Z,linewidths=.1)
plt.axis('equal')
plt.show()
 # Representamos la última matriz con matshow
# Colocamos líneas de contorno para la matriz mat
#plt.contour(np.arange(25), np.arange(25), mat, 10, colors = 'k')