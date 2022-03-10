# coding:utf-8

import os, sys
currentdir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(currentdir, '../../src'))

import math
import numpy as np
from alps import alea

def xy2i(L, x, y):
    return L * y + x

def i2x(L, i):
    return i % L

def i2y(L, i):
    return i // L

def left(L, i):
  x = (i2x(L, i) + L - 1) % L
  y = i2y(L, i)
  return xy2i(L, x, y)

def right(L, i):
  x = (i2x(L, i) + 1) % L
  y = i2y(L, i)
  return xy2i(L, x, y)

def up(L, i):
  x = i2x(L, i)
  y = (i2y(L, i) + 1) % L
  return xy2i(L, x, y)

def down(L, i):
  x = i2x(L, i)
  y = (i2y(L, i) + L - 1) % L
  return xy2i(L, x, y)

L = 8
N = L * L
T = 2.269185314213022
nsamples = (1 << 12)
ntherm = nsamples // 8

spins = np.ones(N, dtype=int)

np.random.seed(1234)

ene = alea.autocorr()
ene2 = alea.batch_2()
mag2 = alea.autocorr()

for m in range(ntherm + nsamples):
    for i in range(N):
        dE = 2.0 * spins[i] * (spins[left(L, i)] + spins[right(L, i)] + spins[up(L, i)] + spins[down(L, i)])
        if (np.random.random() < math.exp(-dE / T)):
            spins[i] = -1 * spins[i]
    if (m >= ntherm):
        E = 0.0
        m = 0.0;
        for i in range(N):
            E -= 1.0 * spins[i] * (spins[right(L, i)] + spins[up(L, i)])
            m += 1.0 * spins[i]
        E /= N
        m /= N
        ene.add(E)
        ene2.add(E, E * E)
        mag2.add(m * m)

print("L =", L)
print("T =", T)
print("Ns =", nsamples)
  
ene = ene.finalize()
print("<E> = {} +/- {}".format(ene.mean(), ene.stderror()))
print("tau(E) =", ene.tau())

ene2 = ene2.finalize()
ene2 = ene2.variance()
print("<C> = {} +/- {}".format(N * ene2.mean(0) / (T * T), N * ene2.stderror(0) / (T * T)))

mag2 = mag2.finalize()
print("<m^2> = {} +/- {}".format(mag2.mean(), mag2.stderror()))
print("tau(m^2) =", mag2.tau())
