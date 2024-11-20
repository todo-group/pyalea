import numpy as np
from pytest import approx
import pyalea


def test_mean():
    np.random.seed(1234)
    obs = pyalea.mean()
    for i in range(1 << 16):
        obs.add(np.random.random())

    res = obs.finalize()
    print("<X> = {}".format(res.mean()))

    assert res.mean() == approx(0.5012844926525544)


if __name__ == "__main__":
    test_mean()
