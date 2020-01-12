import os
import sys
import numpy as np 
from scipy.stats import t
import subprocess
import os
import random


def devolverN(n,h,d,var):
    valor = max(n+1, np.round((h**2 * var) / d**2))
    return int(valor)
def pesos(n,h,d,Num,s):
    val1 = 1 - ((Num-n)*d**2)/(s*h**2)
    val2 = np.sqrt(1- (Num/n)*val1)
    val3 = 1 + val2

    w1 = (n/Num) * val3
    w2 = 1 - w1

    return w1, w2


n=int(sys.argv[1])
d=0.1
k=4
h=3.003

datosTotal_vel = np.genfromtxt("datosVel.txt",dtype=np.float)
datosTotal_torm = np.genfromtxt("datosTor.txt",dtype=np.float)
datos_vel = datosTotal_vel[:n]
datos_torm = datosTotal_torm[:n]

datosTotal_4 = np.genfromtxt("datos4.txt",dtype=np.float)
datosTotal_5 = np.genfromtxt("datos5.txt",dtype=np.float)
datos_4 = datosTotal_4[:n]
datos_5 = datosTotal_5[:n]


m_vel = np.mean(datos_vel)
v_vel = np.var(datos_vel)
m_torm = np.mean(datos_torm)
v_torm = np.var(datos_torm)
m_5 = np.mean(datos_5)
v_5 = np.var(datos_5)
m_4 = np.mean(datos_4)
v_4 = np.var(datos_4)


n_4 = devolverN(n,h,d,v_4)
n_5 = devolverN(n,h,d,v_5)
n_torm = devolverN(n,h,d,v_torm)
n_vel = devolverN(n,h,d,v_vel)

m2_vel = np.mean(datosTotal_vel[n:n_vel])
m2_torm = np.mean(datosTotal_torm[n:n_torm])
m2_5 = np.mean(datosTotal_5[n:n_5])
m2_4 = np.mean(datosTotal_4[n:n_4])


w1_4, w2_4 = pesos(n,h,d,n_4,v_4)
w1_5, w2_5 = pesos(n,h,d,n_5,v_5)
w1_vel, w2_vel = pesos(n,h,d,n_vel,v_vel)
w1_torm, w2_torm = pesos(n,h,d,n_torm,v_torm)

x_4 = w1_4 * m_4 + w2_4 * m2_4
x_5 = w1_5 * m_5 + w2_5 * m2_5
x_vel = w1_vel * m_vel + w2_vel * m2_vel 
x_torm = w1_torm * m_torm + w2_torm * m2_torm

print("Mejora:Media1:var:N:Media2:W1:W2:Xp")
print(f"tormenta:{m_torm}:{v_torm}:{n_torm}:{m2_torm}:{w1_torm}:{w2_torm}:{x_torm}")
print(f"Velocidad:{m_vel}:{v_vel}:{n_vel}:{m2_vel}:{w1_vel}:{w2_vel}:{x_vel}")
print(f"4Atraques:{m_4}:{v_4}:{n_4}:{m2_4}:{w1_4}:{w2_4}:{x_4}")
print(f"5Atraques:{m_5}:{v_5}:{n_5}:{m2_5}:{w1_5}:{w2_5}:{x_5}")
