#include <random>
#include <iostream>
#include <alps/alea.hpp>

int main() {
    int nsamples = (1 << 16);

    alps::alea::autocorr_acc<double> xa;
    alps::alea::batch_acc<double> xb;

    // random number generator
    std::mt19937 engine(0);
    std::uniform_real_distribution<double> uniform;

    double x = 0.5;
    for (int i = 0; i < nsamples; ++i) {
        x = 0.5 * x + 0.5 * uniform(engine);
        xa << x;
        xb << x;
    }

    auto xcorr = xa.finalize();
    auto xbatch = xb.finalize();

    std::cout << "<X> = " << xbatch << std::endl;
    std::cout << "tau(X) = " << xcorr.tau() << std::endl;

    // Estimate <X^2>
    std::function<double(double)> f0 = [](double x) { return x * x; };
    auto prop0 = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f0), xbatch);
    std::cout << "<X^2> = " << prop0 << "\n";

    // Estimate <1/X>
    std::function<double(double)> f1 = [] (double x) { return 1 / x; };
    auto prop1 = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f1), xbatch);
    std::cout << "<1/X> = " << prop1 << "\n";
}
