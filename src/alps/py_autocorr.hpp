#include <alps/alea.hpp>

template<class T>
class py_autocorr_result {
public:
  py_autocorr_result(const alps::alea::autocorr_result<T>& res) : res_(res) {}
  auto count() const { return res_.count(); }
  auto mean() { return std::vector<T>(res_.mean())[0]; }
  auto var() { return std::vector<T>(res_.var())[0]; }
  auto stderror() { return std::vector<T>(res_.stderror())[0]; }
  auto tau() { return std::vector<T>(res_.tau())[0]; }
private:
  alps::alea::autocorr_result<T> res_;
};

template<class T>
class py_autocorr_acc {
public:
  py_autocorr_acc() : acc_(1) {}
  void add(const T& v) { acc_ << v; }
  auto count() const { return acc_.count(); }
  auto result() { return py_autocorr_result<T>(acc_.result()); }
  auto finalize() { return py_autocorr_result<T>(acc_.finalize()); }
private:
  alps::alea::autocorr_acc<T> acc_;
};
