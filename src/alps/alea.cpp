#include <pybind11/pybind11.h>
#include "py_mean.hpp"
#include "py_var.hpp"
#include "py_autocorr.hpp"

namespace py = pybind11;

PYBIND11_MODULE(alea, m) {
  m.doc() = "Python binding of alpscore::alea";

  py::class_<py_mean_result<double>>(m, "mean_result")
    .def(py::init<py_mean_result<double>>())
    .def("count", &py_mean_result<double>::count)
    .def("mean", &py_mean_result<double>::mean);

  py::class_<py_mean_acc<double>>(m, "mean")
    .def(py::init<>())
    .def("add", &py_mean_acc<double>::add)
    .def("result", &py_mean_acc<double>::result)
    .def("finalize", &py_mean_acc<double>::finalize);

  py::class_<py_var_result<double>>(m, "var_result")
    .def(py::init<py_var_result<double>>())
    .def("count", &py_var_result<double>::count)
    .def("mean", &py_var_result<double>::mean)
    .def("var", &py_var_result<double>::var)
    .def("stderror", &py_var_result<double>::stderror);

  py::class_<py_var_acc<double>>(m, "var")
    .def(py::init<>())
    .def("add", &py_var_acc<double>::add)
    .def("result", &py_var_acc<double>::result)
    .def("finalize", &py_var_acc<double>::finalize);

  py::class_<py_autocorr_result<double>>(m, "autocorr_result")
    .def(py::init<py_autocorr_result<double>>())
    .def("count", &py_autocorr_result<double>::count)
    .def("mean", &py_autocorr_result<double>::mean)
    .def("var", &py_autocorr_result<double>::var  )
    .def("stderror", &py_autocorr_result<double>::stderror)
    .def("tau", &py_autocorr_result<double>::tau);

  py::class_<py_autocorr_acc<double>>(m, "autocorr")
    .def(py::init<>())
    .def("add", &py_autocorr_acc<double>::add)
    .def("result", &py_autocorr_acc<double>::result)
    .def("finalize", &py_autocorr_acc<double>::finalize);
}
