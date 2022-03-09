#include <random>
#include <iostream>
#include <alps/alea.hpp>

template<typename T>
struct transformer_var : public alps::alea::transformer<T> {
    alps::alea::column<T> operator() (const alps::alea::column<T>& in) const override {
        alps::alea::column<T> res(1);
        res(0) = in(1) - in(0) * in(0);
        return res;
    }
    size_t in_size() const override { return 2; }
    size_t out_size() const override { return 1; }
};

int main() {
    int nsamples = (1 << 16);

    alps::alea::autocorr_acc<double> xa(2);
    alps::alea::batch_acc<double> xb(2);

    // random number generator
    std::mt19937 engine(0);
    std::normal_distribution<> gauss(1.0, 0.5);

    for (int i = 0; i < nsamples; ++i) {
        auto x = gauss(engine);
        xa << alps::alea::column<double>{ x, x * x };
        xb << alps::alea::column<double>{ x, x * x };
    }

    auto xcorr = xa.finalize();
    auto xbatch = xb.finalize();

    std::cout << "<X> = " << xbatch.mean()[0] << " +/- " << xbatch.stderror()[0] << std::endl;
    std::cout << "tau(X) = " << xcorr.tau()[0] << std::endl;
    std::cout << "<X^2> = " << xbatch.mean()[1] << " +/- " << xbatch.stderror()[1] << std::endl;
    std::cout << "tau(X^2) = " << xcorr.tau()[1] << std::endl;

    // Estimate <x^2> - <x>^2
    // method 0
    std::function<double(double, double)> f0 = [](double x0, double x1) { return x1 - x0 * x0; };
    auto prop0 = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f0), xbatch);
    std::cout << "<X^2>-<x>^2 = " << prop0 << "\n";

    // method 1
    transformer_var<double> tf1;
    auto prop1 = alps::alea::transform(alps::alea::jackknife_prop(), tf1, xbatch);
    std::cout << "<X^2>-<x>^2 = " << prop1 << "\n";

    // Estimate <x^2>/<x>
    std::function<double(double, double)> f2 = [](double x0, double x1) { return x1 / x0; };
    auto prop2 = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f2), xbatch);
    std::cout << "<X^2>/<x> = " << prop2 << "\n";

    // Estimate <x^2>/<x>^2
    std::function<double(double, double)> f3 = [](double x0, double x1) { return x1 / (x0 * x0); };
    auto prop3 = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f3), xbatch);
    std::cout << "<X^2>/<x>^2 = " << prop3 << "\n";
}
