#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  7 10:28:07 2019

@author: jose
"""

from subprocess import call
import matplotlib.pyplot as plt
import matplotlib
import numpy as np
from os import remove

from mpl_toolkits.mplot3d import axes3d


prob = 0.1
inicio = 1
fin = 11


total_datos = 17*(fin-inicio)
datos_finales = np.empty((total_datos,4))
pos_datos = 0



while (prob <= 0.95):
    print(prob)
    
    
    for i in range(inicio,fin): 
        print(i)
        f = open("datos", "w")
        for i in range(10):
            call(['./aparcamiento', '100000', '100', str(i), str(prob)], stdout=f)
        f.close
        
        datos_media = np.genfromtxt('datos', delimiter=":")
        
        datos_finales[pos_datos][0]=prob
        datos_finales[pos_datos][1]=i
        datos_finales[pos_datos][2]= datos_media[:, 1].sum(axis=0)/10
        datos_finales[pos_datos][3]= datos_media[:, 0].sum(axis=0)/10
        pos_datos += 1
    
    
    
    prob += 0.05
np.savetxt("../datos/visionProb.csv", datos_finales, delimiter=":")
remove("datos")

"""datos_finales = np.genfromtxt('../datos/datosVisionv2.csv', delimiter=":")
print(datos_finales)
#datos_finales = np.genfromtxt('../datos/datosProb.csv', delimiter=":")
x = datos_finales[:, 0]
y = datos_finales[:, 1]
z = datos_finales[:, 3]
print(y)
print(x)
print(z)

x=np.unique(x)
y=np.unique(y)
X,Y = np.meshgrid(x,y)

Z=z.reshape(len(y),len(x))

plt.pcolormesh(X,Y,Z)

plt.show()"""