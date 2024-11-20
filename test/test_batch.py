import numpy as np
from pytest import approx
import pyalea


def test_batch_1():
    np.random.seed(1234)
    obs = pyalea.batch_1()
    for _ in range(1 << 16):
        obs.add(np.random.random())

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


def test_batch_2():
    np.random.seed(1234)
    obs = pyalea.batch_2()
    for _ in range(1 << 16):
        x = np.random.random()
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

    assert p.mean(0) == approx(1.3318848110792674)


def test_batch_3():
    np.random.seed(1234)
    obs = pyalea.batch_3()
    for _ in range(1 << 16):
        s = 1 if np.random.random() > 0.2 else -1
        x = np.random.random()
        obs.add(s, x, x * x)

    res = obs.finalize()
    print("<S> = {} +/- {}".format(res.mean(0), res.stderror(0)))
    print("<X> = {} +/- {}".format(res.mean(1), res.stderror(1)))
    print("<X^2> = {} +/- {}".format(res.mean(2), res.stderror(2)))

    p = res.ratio_10()
    print("<X>/<S> = {} +/- {}".format(p.mean(0), p.stderror(0)))

    p = res.ratio_20()
    print("<X^2>/<S> = {} +/- {}".format(p.mean(0), p.stderror(0)))

    p = res.ratio_variance()
    print("(<x^2>/<S>)-(<X>/<S>)^2 = {} +/- {}".format(p.mean(0), p.stderror(0)))

    assert p.mean(0) == approx(-0.1383860235343999)


if __name__ == "__main__":
    test_batch_1()
    test_batch_2()
    test_batch_3()
