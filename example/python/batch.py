# coding:utf-8

import os
import sys

currentdir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(currentdir, "../../src"))

import random

import pyalea

random.seed(1234)

obs = pyalea.batch_1()
for i in range(1 << 16):
    obs.add(random.random())

res = obs.finalize()
print("<X> = {} +/- {}".format(res.mean(0), res.stderror(0)))

p = res.inverse()
print("1/<X> = {} +/- {}".format(p.mean(0), p.stderror(0)))

p = res.square()
print("<X>^2 = {} +/- {}".format(p.mean(0), p.stderror(0)))

p = res.sqrt()
print("sqrt(<X>) = {} +/- {}".format(p.mean(0), p.stderror(0)))

p = res.log()
print("log(<X>) = {} +/- {}".format(p.mean(0), p.stderror(0)))

obs = pyalea.batch_2()
for i in range(1 << 16):
    x = random.random()
    obs.add(x, x * x)

res = obs.finalize()
print("<X> = {} +/- {}".format(res.mean(0), res.stderror(0)))
print("<X^2> = {} +/- {}".format(res.mean(1), res.stderror(1)))

p = res.variance()
print("<x^2>-<X>^2 = {} +/- {}".format(p.mean(0), p.stderror(0)))

p = res.ratio()
print("<x^2>/<X> = {} +/- {}".format(p.mean(0), p.stderror(0)))

p = res.binder()
print("<x^2>/<X>^2 = {} +/- {}".format(p.mean(0), p.stderror(0)))

assert abs(p.mean(0) - 1.3322541278262399) < 1e-8
