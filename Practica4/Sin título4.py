#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 15 16:20:11 2020

@author: jose
"""
import pylab as pl  
import csv  
import sys
entrada = open(sys.argv[2])  
tabla = []  
for fila in csv.reader(entrada):  
  tabla.append(fila)  
entrada.close()  
conejos=[]  
zorros=[]
x = []
for fila in range(1, len(tabla)):  
    conejos.append(float(tabla[fila][1]))  
    zorros.append(float(tabla[fila][2]))  
    x.append(float(tabla[fila][0]))
pl.plot(x,conejos, label = "Conejos")
pl.plot(x,zorros, label = "Zorros")  
pl.xlabel('Tiempo')  
pl.ylabel('Nº individuos')  
pl.title('Grafica zorros y conejos')  
pl.legend()
pl.show()

pl.plot(zorros,conejos)
pl.xlabel('Tiempo')  
pl.ylabel('Nº individuos')  
pl.title('Grafica x-y')  
pl.show()