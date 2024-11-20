#include <pybind11/pybind11.h>
#include "py_mean.hpp"
#include "py_var.hpp"
#include "py_autocorr.hpp"
#include "py_batch.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
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
    .def("var", &py_autocorr_result<double>::var)
    .def("stderror", &py_autocorr_result<double>::stderror)
    .def("tau", &py_autocorr_result<double>::tau);

  py::class_<py_autocorr_acc<double>>(m, "autocorr")
    .def(py::init<>())
    .def("add", &py_autocorr_acc<double>::add)
    .def("result", &py_autocorr_acc<double>::result)
    .def("finalize", &py_autocorr_acc<double>::finalize);

  py::class_<py_batch_result<double>>(m, "batch_result")
    .def(py::init<py_batch_result<double>>())
    .def("count", &py_batch_result<double>::count)
    .def("mean", &py_batch_result<double>::mean)
    .def("var", &py_batch_result<double>::var)
    .def("stderror", &py_batch_result<double>::stderror)
    .def("inverse", &py_batch_result<double>::inverse)
    .def("square", &py_batch_result<double>::square)
    .def("sqrt", &py_batch_result<double>::sqrt)
    .def("log", &py_batch_result<double>::log)
    .def("variance", &py_batch_result<double>::variance)
    .def("ratio", &py_batch_result<double>::ratio)
    .def("binder", &py_batch_result<double>::binder)
    .def("ratio_10", &py_batch_result<double>::ratio_10)
    .def("ratio_20", &py_batch_result<double>::ratio_20)
    .def("ratio_variance", &py_batch_result<double>::ratio_variance);

  py::class_<py_batch_acc_1<double>>(m, "batch_1")
    .def(py::init<>())
    .def("add", &py_batch_acc_1<double>::add)
    .def("result", &py_batch_acc_1<double>::result)
    .def("finalize", &py_batch_acc_1<double>::finalize);

  py::class_<py_batch_acc_2<double>>(m, "batch_2")
    .def(py::init<>())
    .def("add", &py_batch_acc_2<double>::add)
    .def("result", &py_batch_acc_2<double>::result)
    .def("finalize", &py_batch_acc_2<double>::finalize);

  py::class_<py_batch_acc_3<double>>(m, "batch_3")
    .def(py::init<>())
    .def("add", &py_batch_acc_3<double>::add)
    .def("result", &py_batch_acc_3<double>::result)
    .def("finalize", &py_batch_acc_3<double>::finalize);
}
