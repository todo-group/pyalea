#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <alps/alea.hpp>

inline int xy2i(int L, int x, int y) { return L * y + x; }

inline int i2x(int L, int i) { return i % L; }

inline int i2y(int L, int i) { return i / L; }

inline int left(int L, int i) {
  int x = (i2x(L, i) + L - 1) % L;
  int y = i2y(L, i);
  return xy2i(L, x, y);
}

inline int right(int L, int i) {
  int x = (i2x(L, i) + 1) % L;
  int y = i2y(L, i);
  return xy2i(L, x, y);
}

inline int up(int L, int i) {
  int x = i2x(L, i);
  int y = (i2y(L, i) + 1) % L;
  return xy2i(L, x, y);
}

inline int down(int L, int i) {
  int x = i2x(L, i);
  int y = (i2y(L, i) + L - 1) % L;
  return xy2i(L, x, y);
}

int main() {
  int L = 8;
  int N = L * L;
  double T = 2.269185314213022;
  int nsamples = (1 << 12);
  int ntherm = nsamples / 8;

  std::vector<int> spins(N, 1);

  std::mt19937 engine(0);
  std::uniform_real_distribution<> uniform;

  alps::alea::autocorr_acc<double> ene;
  alps::alea::batch_acc<double> ene2(2);
  alps::alea::autocorr_acc<double> mag2;

  for (int m = 0; m < (ntherm + nsamples); ++m) {
    for (int i = 0; i < N; ++i) {
      double dE = 2.0 * spins[i] * (spins[left(L, i)] + spins[right(L, i)] + spins[up(L, i)] + spins[down(L, i)]);
      if (uniform(engine) < std::exp(-dE / T))
        spins[i] = -spins[i];
    }
    if (m >= ntherm) {
      double E = 0.0;
      double m = 0.0;
      for (int i = 0; i < N; ++i) {
        E -= spins[i] * (spins[right(L, i)] + spins[up(L, i)]);
        m += spins[i];
      }
      E /= N;
      m /= N;
      ene << E;
      ene2 << alps::alea::column<double>{ E, E * E };
      mag2 << m * m;
    }
  }

  std::cout << "L = " << L << std::endl;
  std::cout << "T = " << T << std::endl;
  std::cout << "Ns = " << nsamples << std::endl;
  
  auto ene_corr = ene.finalize();
  std::cout << "<E> = " << ene_corr << std::endl;
  std::cout << "tau(E) = " << ene_corr.tau() << std::endl;

  auto ene2_batch = ene2.finalize();
  std::function<double(double, double)> f = [](double x0, double x1) { return x1 - x0 * x0; };
  auto ene2_prop = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f), ene2_batch);
  std::cout << "C = " << N * ene2_prop.mean() / (T * T) << " +/- " << N * ene2_prop.stderror() / (T * T) << std::endl;

  auto mag2_corr = mag2.finalize();
  std::cout << "<m^2> = " << mag2_corr << std::endl;
  std::cout << "tau(m^2) = " << mag2_corr.tau() << std::endl;
}
