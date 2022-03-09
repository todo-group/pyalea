# coding:utf-8

import os, sys
currentdir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(currentdir, '../../src'))

import random
from alps import alea

random.seed(1234)

obs = alea.mean()
for i in range(1 << 16):
    obs.add(random.random())

res = obs.finalize()
print("<X> = {}".format(res.mean()))

assert(abs(res.mean() - 0.5006153053752365) < 1e-8)