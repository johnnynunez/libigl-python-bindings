#include <nanobind/nanobind.h>
namespace nb = nanobind;

// generated by cmake
#include "copyleft/BINDING_DECLARATIONS.in"

NB_MODULE(pyigl_copyleft_core, m) {
  m.doc() = "libigl copyleft module python bindings";
  // generated by cmake
#include "copyleft/BINDING_INVOCATIONS.in"
}

