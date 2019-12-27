import os
import sys
import numpy as np 
from scipy.stats import t
import subprocess
import os
import random

"""datos_torm = np.empty(tam, dtype=np.float)
datos_vel = np.empty(tam, dtype=np.float)

for i in range(0,tam):
    
    os.system("./ejecutar 1 3 1 >> datos.txt")
    proceso1 = subprocess.Popen("./"+ str(sys.argv[2])+ " 1", stdout=subprocess.PIPE, shell=True)
    (out, err) = proceso1.communicate()
    print(out)
    valor = out.decode("utf-8")
    valor = float(valor.split(":")[0])
    datos_torm[i] = valor

    valor = os.popen('./'+ sys.argv[2]+' 1 3 0 1').read()
    valor = float(valor.split(":")[0])
    datos_vel[i] = valor

    print("Pasada " , i)"""

datos_vel = np.genfromtxt("datosVel.txt",dtype=np.float)
datos_torm = np.genfromtxt("datosTor.txt",dtype=np.float)
datos_vel = datos_vel[:int(sys.argv[1])]
datos_torm = datos_torm[:int(sys.argv[1])]
tam = np.size(datos_vel)
diferencia = datos_vel-datos_torm
print(diferencia)
print(datos_vel)
print(datos_torm)
media = np.mean(diferencia)
varianza = np.var(diferencia)

valores_student = t.interval(0.95,tam-1)

intervalo = [media + t * np.sqrt(varianza/tam) for t in valores_student]




print("Intervalo=",intervalo," media=",media, " varianza=",varianza)








