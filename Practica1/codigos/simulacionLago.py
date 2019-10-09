#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct  9 19:54:28 2019

@author: jose
"""

import matplotlib.pyplot as plt
import matplotlib
import numpy as np
# pesca anual = 90285.2
# pesa semanal al 0.07 = 560092
# pesca diara del 0.01 = 557025
# pesca cada dos semanas 0.14 = 562135
lagoEstable = np.genfromtxt('../datos/lagoPrueba50.csv', delimiter=":")

"""plt.subplot(121)
plt.plot(lagoEstable[:, 0], lagoEstable[:, 1], 'b-')
#plt.plot(lagoEstable[:, 0], lagoEstable[:, 2], 'r-')
plt.title('Peces pequeños')
plt.ylabel('Nº de peces')
plt.xlabel('Días')

plt.subplot(122)
plt.plot(lagoEstable[:, 0], lagoEstable[:, 2], 'r-')
plt.title('Peces grandes')
plt.xlabel('Días')
plt.ylabel('Nº de peces')"""
#plt.xticks(np.arange(inicio, fin-1, 3))



plt.plot(lagoEstable[:, 1], lagoEstable[:, 2], 'k-')
plt.title('Peces pequeños y grandes')
plt.xlabel('Peces pequeños')
plt.ylabel('Peces grandes')

"""x = ("semanal","mensual","trimestral","semestral")
y = (560092,555694,529367,439416)

plt.bar(x,y,align='center') # A bar chart
plt.xlabel('Tipo de pesca')
plt.ylabel('Nº de peces pescados')"""

plt.show()

