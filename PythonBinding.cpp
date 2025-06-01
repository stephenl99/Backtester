#include "PythonBinding.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;
int add() {
    return 0;
};
int run() {
    return main();
}
PYBIND11_MODULE(PythonBinding, m) {
    m.def("run", &run, "Run the simulation");
    m.def("add", &add, "A function that adds two numbers");
}