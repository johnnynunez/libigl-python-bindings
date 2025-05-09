#include "default_types.h"
#include <igl/upsample.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for the first overload of upsample that computes S and newF
  auto upsample_matrix(
    const nb::DRef<const Eigen::MatrixXI> &F,
    int n_)
  {
    const auto n = n_? n_ : F.maxCoeff() + 1;
    Eigen::SparseMatrix<Numeric> S;
    Eigen::MatrixXI NF;
    igl::upsample(n, F, S, NF);
    return std::make_tuple(S, NF);
  }

  // Wrapper for the second overload of upsample that returns NV and NF
  auto upsample(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    int number_of_subdivs)
  {
    Eigen::MatrixXN NV;
    Eigen::MatrixXI NF;
    igl::upsample(V, F, NV, NF, number_of_subdivs);
    return std::make_tuple(NV, NF);
  }

}

// Bind the wrapper to the Python module
void bind_upsample(nb::module_ &m)
{
  m.def(
    "upsample_matrix",
    &pyigl::upsample_matrix,
    "F"_a,
    "n"_a = 0,
    R"(Subdivide a mesh without moving vertices. Returns the subdivision matrix and new faces.

@param[in] n_verts Number of mesh vertices
@param[in] F       #F by 3 matrix of triangle faces
@return A tuple containing:
        - S: Sparse subdivision matrix
        - NF: Matrix of new faces)");

  m.def(
    "upsample",
    &pyigl::upsample,
    "V"_a,
    "F"_a,
    "number_of_subdivs"_a = 1,
    R"(Subdivide a mesh without moving vertices using loop subdivision. Returns new vertices and faces.

@param[in] V               #V by dim matrix of mesh vertices
@param[in] F               #F by 3 matrix of triangle faces
@param[in] number_of_subdivs Number of subdivisions (default is 1)
@return A tuple containing:
        - NV: New vertex positions with original vertices at the top
        - NF: Matrix of new face indices)");

}
