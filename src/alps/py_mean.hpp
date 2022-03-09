#include <alps/alea.hpp>

template<class T>
class py_mean_result {
public:
  py_mean_result(const alps::alea::mean_result<T>& res) : res_(res) {}
  auto count() const { return res_.count(); }
  auto mean() const { return std::vector<T>(res_.mean())[0]; }
private:
  alps::alea::mean_result<T> res_;
};

template<class T>
class py_mean_acc {
public:
  py_mean_acc() : acc_(1) {}
  void add(const T& v) { acc_ << v; }
  auto count() const { return acc_.count(); }
  auto result() { return py_mean_result<T>(acc_.result()); }
  auto finalize() { return py_mean_result<T>(acc_.finalize()); }
private:
  alps::alea::mean_acc<T> acc_;
};
