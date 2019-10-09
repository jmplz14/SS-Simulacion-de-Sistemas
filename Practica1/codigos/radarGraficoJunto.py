#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct  9 09:27:05 2019

@author: jose
"""
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

año1 = np.genfromtxt('../datos/radar-1.csv', delimiter=":")
año5 = np.genfromtxt('../datos/radar-5.csv', delimiter=":")
año10 = np.genfromtxt('../datos/radar-10.csv', delimiter=":")
año10v2 = np.genfromtxt('../datos/radar-10v2.csv', delimiter=":")
año10v3 = np.genfromtxt('../datos/radar-10v3.csv', delimiter=":")
año50 = np.genfromtxt('../datos/radar-50.csv', delimiter=":")
año100 = np.genfromtxt('../datos/radar-100.csv', delimiter=":")
año500 = np.genfromtxt('../datos/radar-500.csv', delimiter=":")
año1000_v10 = np.genfromtxt('../datos/radar-1000-vu-10.csv', delimiter=":")
año1000_v15 = np.genfromtxt('../datos/radar-1000-vu-15.csv', delimiter=":")
año1000_v30 = np.genfromtxt('../datos/radar-1000-vu-30.csv', delimiter=":")
año1000_v25 = np.genfromtxt('../datos/radar-1000-vu-25.csv', delimiter=":")
año1000 = np.genfromtxt('../datos/radar-1000.csv', delimiter=":")
año1000_ta_5_20 = np.genfromtxt('../datos/radar-1000-ta-5-20.csv', delimiter=":")
año1000_ta_10_25 = np.genfromtxt('../datos/radar-1000-ta-10-25.csv', delimiter=":")
año1000_ta_20_35 = np.genfromtxt('../datos/radar-1000-ta-20-35.csv', delimiter=":")
año1000_ta_25_40 = np.genfromtxt('../datos/radar-1000-ta-25-40.csv', delimiter=":")
año1000_ta_23_30 = np.genfromtxt('../datos/radar-1000-ta-23-30.csv', delimiter=":")
año1000_ta_15_22 = np.genfromtxt('../datos/radar-1000-ta-15-22.csv', delimiter=":")

#plt.plot(año10[8:, 0], año10[8:, 1], 'b-')
#plt.plot(año10v2[8:, 0], año10v2[8:, 1], 'g-')
#plt.plot(año10v3[8:, 0], año10v3[8:, 1], 'r-')
#plt.plot(año10[8:, 0], año10[8:, 1], 'r-')
#plt.plot(año50[8:, 0], año50[8:, 1], 'c-')
plt.plot(año1000_ta_23_30[:, 0], año1000_ta_23_30[:, 1], 'm-')



#plt.plot(año1000_v10[:, 0], año1000_v10[:, 1], 'm-')
#plt.plot(año1000_v15[:, 0], año1000_v15[:, 1], 'y-')
plt.plot(año1000[:, 0], año1000[:, 1], 'k-')
#plt.plot(año1000_v25[:, 0], año1000_v25[:, 1], 'r-')
#plt.plot(año1000_v30[:, 0], año1000_v30[:, 1], 'c-')
plt.plot(año1000_ta_15_22[:, 0], año1000_ta_15_22[:, 1], 'r-')



plt.title('Cambios en tasa de arreglo')
plt.xlabel('Nº de piezas')
plt.ylabel('Porcentaje de desprotección')
#plt.xticks(np.arange(inicio, fin-1, 3))



plt.legend(('tasa arreglo entre 15 y 22.5','tasa arreglo entre 15 y 30','tasa arreglo entre 22.5 y 30'), loc="upper right")
plt.show()