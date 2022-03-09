# coding:utf-8

import os, sys
currentdir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(currentdir, '../../src'))

import random
from alps import alea

obs = alea.var()
for i in range(1 << 16):
    obs.add(random.random())

res = obs.finalize()
print("<X> = {} +/- {}".format(res.mean(), res.stderror()))
