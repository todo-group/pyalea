import random

from pytest import approx

import pyalea


def test_var():
    random.seed(1234)

    obs = pyalea.var()
    for i in range(1 << 16):
        obs.add(random.random())

    res = obs.finalize()
    print("<X> = {} +/- {}".format(res.mean(), res.stderror()))

    assert res.mean() == approx(0.5006153053752365)


if __name__ == "__main__":
    test_var()
