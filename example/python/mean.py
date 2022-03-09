# coding:utf-8

import os, sys
currentdir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(currentdir, '../../src'))

import random
from alps import alea

obs = alea.mean()
for i in range(1024):
    obs.add(random.random())

res = obs.finalize()
print(res.count(), res.mean())
