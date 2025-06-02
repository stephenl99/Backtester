#include "PythonBinding.h"
#include <pybind11/pybind11.h>
#include "Portfolio.h"
namespace py = pybind11;
int add() {
    return 0;
};
int run() {
    return main() + 95;
}
auto getHoldings() {
    main();
    return appleHoldings;
}
PYBIND11_MODULE(PythonBinding, m) {
    m.def("run", &run, "Run the simulation");
    m.def("add", &add, "A function that adds two numbers");
    m.def("getHoldings", &getHoldings, "Return the holdings every day for AAPL for now");
}