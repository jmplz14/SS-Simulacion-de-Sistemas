#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 29 21:46:24 2019

@author: jose
"""
import matplotlib.pyplot as plt

#P2
#array_prob = [(100 - i) / 5050 for i in range(100)]
array_prob = [i / 2500 for i in range(50)]
#plt.titt
array_prob += [(100-i) / 2500 for i in range(50,100)]
array_x = [i for i in range(100)]

plt.plot(array_x,array_prob, color = "b")
#plt.title("Proporcional")

plt.title("Triangular")
plt.ylabel("Probabilidad")
plt.xlabel("Demanda")
plt.show()

