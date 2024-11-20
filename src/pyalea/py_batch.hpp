#include <alps/alea.hpp>
#include "ternary.hpp"

template<class T>
class py_batch_result {
public:
  py_batch_result(const alps::alea::batch_result<T>& res) : res_(res) {}
  auto count() const { return res_.count(); }
  auto size() const { return res_.size(); }
  auto mean(int k) const { return alps::alea::column<T>(res_.mean())[k]; }
  auto var(int k) const { return alps::alea::column<T>(res_.var())[k]; }
  auto stderror(int k) const { return alps::alea::column<T>(res_.stderror())[k]; }

  auto convert_1(std::function<double(double)> f) const {
    if (this->size() != 1) throw std::logic_error("py_batch_result: size error");
    auto p = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f), res_);
    return py_batch_result<T>(p);
  }
  auto inverse() const { return convert_1([] (double x) { return 1 / x; }); }
  auto square() const { return convert_1([] (double x) { return x * x; }); }
  auto sqrt() const { return convert_1([] (double x) { return std::sqrt(x); }); }
  auto log() const { return convert_1([] (double x) { return std::log(x); }); }

  auto convert_2(std::function<double(double, double)> f) const {
    if (this->size() != 2) throw std::logic_error("py_batch_result: size error");
    auto p = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f), res_);
    return py_batch_result<T>(p);
  }
  auto variance() { return convert_2([] (double x0, double x1) { return x1 - x0 * x0; }); }
  auto ratio() { return convert_2([] (double x0, double x1) { return x1 / x0; }); }
  auto binder() { return convert_2([] (double x0, double x1) { return x1 / (x0 * x0); }); }

  auto convert_3(std::function<double(double, double, double)> f) const {
    if (this->size() != 3) throw std::logic_error("py_batch_result: size error");
    auto p = alps::alea::transform(alps::alea::jackknife_prop(), alps::alea::make_transformer(f), res_);
    return py_batch_result<T>(p);
  }
  auto ratio_10() { return convert_3([] (double x0, double x1, double) { return x1 / x0; }); }
  auto ratio_20() { return convert_3([] (double x0, double, double x2) { return x2 / x0; }); }
  auto ratio_variance() { return convert_3([] (double x0, double x1, double x2) { return (x2 / x0) - (x1 / x0) * (x1 / x0); }); }
private:
  alps::alea::batch_result<T> res_;
};

template<class T>
class py_batch_acc_1 {
public:
  py_batch_acc_1() : acc_(1) {}
  void add(const T& v) { acc_ << v; }
  auto count() const { return acc_.count(); }
  auto result() { return py_batch_result<T>(acc_.result()); }
  auto finalize() { return py_batch_result<T>(acc_.finalize()); }
private:
  alps::alea::batch_acc<T> acc_;
};

template<class T>
class py_batch_acc_2 {
public:
  py_batch_acc_2() : acc_(2) {}
  void add(const T& v0, const T& v1) { acc_ << alps::alea::column<double>{ v0, v1 }; }
  auto count() const { return acc_.count(); }
  auto result() { return py_batch_result<T>(acc_.result()); }
  auto finalize() { return py_batch_result<T>(acc_.finalize()); }
private:
  alps::alea::batch_acc<T> acc_;
};

template<class T>
class py_batch_acc_3 {
public:
  py_batch_acc_3() : acc_(3) {}
  void add(const T& v0, const T& v1, const T& v2) { acc_ << alps::alea::column<double>{ v0, v1, v2 }; }
  auto count() const { return acc_.count(); }
  auto result() { return py_batch_result<T>(acc_.result()); }
  auto finalize() { return py_batch_result<T>(acc_.finalize()); }
private:
  alps::alea::batch_acc<T> acc_;
};
