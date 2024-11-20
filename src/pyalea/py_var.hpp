#include <alps/alea.hpp>

template<class T>
class py_var_result {
public:
  py_var_result(const alps::alea::var_result<T>& res) : res_(res) {
    if (this->size() != 1) throw std::logic_error("py_var_result: size error");
  }
  auto count() const { return res_.count(); }
  auto size() const { return res_.size(); }
  auto mean() { return alps::alea::column<T>(res_.mean())[0]; }
  auto var() { return alps::alea::column<T>(res_.var())[0]; }
  auto stderror() { return alps::alea::column<T>(res_.stderror())[0]; }
private:
  alps::alea::var_result<T> res_;
};

template<class T>
class py_var_acc {
public:
  py_var_acc() : acc_(1) {}
  void add(const T& v) { acc_ << v; }
  auto count() const { return acc_.count(); }
  auto result() { return py_var_result<T>(acc_.result()); }
  auto finalize() { return py_var_result<T>(acc_.finalize()); }
private:
  alps::alea::var_acc<T> acc_;
};
