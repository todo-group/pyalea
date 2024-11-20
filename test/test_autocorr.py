import numpy as np
from pytest import approx
import pyalea

def test_autocorr():
    np.random.seed(1234)
    obs = pyalea.autocorr()
    for i in range(1 << 16):
        obs.add(np.random.random())
    res = obs.finalize()
    print("<X> = {} +/- {}".format(res.mean(), res.stderror()))
    print("tau = {}".format(res.tau()))
    assert res.mean() == approx(0.5012844926525544)


if __name__ == "__main__":
    test_autocorr()
