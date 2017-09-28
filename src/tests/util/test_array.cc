/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "atlas/array.h"
#include "atlas/array/MakeView.h"
#include "tests/AtlasTestEnvironment.h"
#include "eckit/testing/Test.h"

using namespace eckit::testing;
using namespace atlas::array;

namespace atlas {
namespace test {

//-----------------------------------------------------------------------------

CASE("test_array") {
  Array* ds = Array::create<double>(4ul);
  auto hv = atlas::array::gridtools::make_gt_host_view<double, 1>(*ds);
  hv(3) = 4.5;

  array::ArrayView<double, 1> atlas_hv = make_host_view<double, 1>(*ds);

  EXPECT(hv(3) == 4.5);
  EXPECT(atlas_hv(3) == 4.5);

  delete ds;
}

CASE("test_array_zero_size") {
  Array* ds = Array::create<double>(0);

  EXPECT(ds->size() == 0);
  delete ds;
}

CASE("test_create") {
  Array* ds = Array::create(array::DataType::create<int>(), ArrayShape({4, 3}));
  auto hv = atlas::array::gridtools::make_gt_host_view<int, 2>(*ds);
  hv(3, 2) = 4;

  array::ArrayView<int, 2> atlas_hv = make_host_view<int, 2>(*ds);

  EXPECT(hv(3, 2) == 4);
  EXPECT(atlas_hv(3, 2) == 4);

  delete ds;
}

CASE("test_make_view") {
  Array* ds = Array::create<double>(4ul);
  auto hv = atlas::array::gridtools::make_gt_host_view<double, 1>(*ds);
  hv(3) = 4.5;

  array::ArrayView<double, 1> atlas_hv = make_view<double, 1>(*ds);

  EXPECT(hv(3) == 4.5);
  EXPECT(atlas_hv(3) == 4.5);

  delete ds;
}

CASE("test_localview") {
  Array* ds = Array::create<double>(8ul, 4ul, 2ul);
  auto hv = make_host_view<double, 3>(*ds);

  EXPECT(hv.shape(0) == 8ul);
  EXPECT(hv.shape(1) == 4ul);
  EXPECT(hv.shape(2) == 2ul);
  EXPECT(hv.size() == 8ul * 4ul * 2ul);

  // Initialize fields
  for (size_t i = 0; i < ds->shape(0); ++i) {
    for (size_t j = 0; j < ds->shape(1); ++j) {
      for (size_t k = 0; k < ds->shape(2); ++k) {
        hv(i, j, k) = (i * 100) + (j * 10) + (k);
      }
    }
  }

  // Check values
  for (size_t i = 0; i < ds->shape(0); ++i) {
    LocalView<double, 2> lv = hv.at(i);
    for (size_t j = 0; j < lv.shape(0); ++j) {
      for (size_t k = 0; k < lv.shape(1); ++k) {
        EXPECT(lv(j, k) == (i * 100) + (j * 10) + (k));
      }
    }
  }

  delete ds;
}

CASE("test_array_shape") {
  ArrayShape as{2, 3};
  Array* ds = Array::create<double>(as);
  auto hv = atlas::array::gridtools::make_gt_host_view<double, 2>(*ds);
  array::ArrayView<double, 2> atlas_hv = make_host_view<double, 2>(*ds);

  hv(1, 1) = 4.5;

  EXPECT(hv(1, 1) == 4.5);
  EXPECT(atlas_hv(1, 1) == 4.5);

  EXPECT(ds->size() == 6);
  EXPECT(ds->rank() == 2);
  EXPECT(ds->stride(0) == 3);
  EXPECT(ds->stride(1) == 1);
  EXPECT(ds->contiguous() == true);

  delete ds;
}

CASE("test_spec") {
  Array* ds = Array::create<double>(4, 5, 6);
  EXPECT(ds->spec().rank() == 3);
  EXPECT(ds->spec().size() == 4 * 5 * 6);
  EXPECT(ds->spec().shape()[0] == 4);
  EXPECT(ds->spec().shape()[1] == 5);
  EXPECT(ds->spec().shape()[2] == 6);
  EXPECT(ds->spec().shapef()[0] == 6);
  EXPECT(ds->spec().shapef()[1] == 5);
  EXPECT(ds->spec().shapef()[2] == 4);

  EXPECT(ds->spec().strides()[0] == 6 * 5);
  EXPECT(ds->spec().strides()[1] == 6);
  EXPECT(ds->spec().strides()[2] == 1);

  EXPECT(ds->spec().hasDefaultLayout());

  delete ds;
}

CASE("test_spec_layout") {
  Array* ds = Array::create<double>(make_shape(4,5,6), make_layout(0,1,2));
  EXPECT(ds->spec().rank() == 3);
  EXPECT(ds->spec().size() == 4 * 5 * 6);
  EXPECT(ds->spec().shape()[0] == 4);
  EXPECT(ds->spec().shape()[1] == 5);
  EXPECT(ds->spec().shape()[2] == 6);
  EXPECT(ds->spec().shapef()[0] == 6);
  EXPECT(ds->spec().shapef()[1] == 5);
  EXPECT(ds->spec().shapef()[2] == 4);
  EXPECT(ds->spec().strides()[0] == 6 * 5);
  EXPECT(ds->spec().strides()[1] == 6);
  EXPECT(ds->spec().strides()[2] == 1);
  EXPECT(ds->spec().hasDefaultLayout());
  EXPECT(ds->spec().layout()[0] == 0);
  EXPECT(ds->spec().layout()[1] == 1);
  EXPECT(ds->spec().layout()[2] == 2);

  delete ds;
}

CASE("test_spec_layout_rev") {
  Array* ds = Array::create<double>(make_shape(4,5,6),make_layout(2,1,0));
  EXPECT(ds->spec().rank() == 3);
  EXPECT(ds->spec().size() == 4 * 5 * 6);
  EXPECT(ds->spec().shape()[0] == 4);
  EXPECT(ds->spec().shape()[1] == 5);
  EXPECT(ds->spec().shape()[2] == 6);
  EXPECT(ds->spec().shapef()[0] == 4);
  EXPECT(ds->spec().shapef()[1] == 5);
  EXPECT(ds->spec().shapef()[2] == 6);
  EXPECT(ds->spec().strides()[0] == 1);
  EXPECT(ds->spec().strides()[1] == 4);
  EXPECT(ds->spec().strides()[2] == 4 * 5);
  EXPECT(!ds->spec().hasDefaultLayout());
  EXPECT(ds->spec().layout()[0] == 2);
  EXPECT(ds->spec().layout()[1] == 1);
  EXPECT(ds->spec().layout()[2] == 0);

  delete ds;


  EXPECT_THROWS_AS( Array::create<double>(make_shape(4,5,6,2),make_layout(0,1,3,2)), eckit::BadParameter );
}

CASE("test_resize_throw") {
  Array* ds = Array::create<double>(32, 5, 33);

  EXPECT_NO_THROW(ds->resize(32, 5, 33));
  EXPECT_THROWS_AS(ds->resize(32, 4, 33), eckit::BadParameter);
  EXPECT_THROWS_AS(ds->resize(32, 5, 32), eckit::BadParameter);
  EXPECT_THROWS_AS(ds->resize(32, 5, 33, 4), eckit::BadParameter);

  delete ds;
}

CASE("test_resize") {
  {
    Array* ds = Array::create<double>(0);
    EXPECT(ds->size() == 0);
    ds->resize(0);
    delete ds;
  }

  {
    Array* ds = Array::create<double>(7, 5, 8);
    {
      array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);
      hv(3, 3, 3) = 4.5;
      hv(6, 4, 7) = 7.5;
    }
    ds->resize(32, 5, 33);
    array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);

    EXPECT(ds->spec().shape()[0] == 32);
    EXPECT(ds->spec().shape()[1] == 5);
    EXPECT(ds->spec().shape()[2] == 33);

    EXPECT(ds->spec().rank() == 3);
    EXPECT(ds->spec().size() == 32 * 5 * 33);

    EXPECT(hv(3, 3, 3) == 4.5);
    EXPECT(hv(6, 4, 7) == 7.5);

    delete ds;
  }

  {
    Array* ds = Array::create<int>(3, 2);
    {
      array::ArrayView<int, 2> hv = make_host_view<int, 2>(*ds);
      hv(2, 1) = 4;
      hv(1, 1) = 7;
    }
    ds->resize(6, 2);
    array::ArrayView<int, 2> hv = make_host_view<int, 2>(*ds);

    EXPECT(ds->spec().shape()[0] == 6);
    EXPECT(ds->spec().shape()[1] == 2);

    EXPECT(ds->spec().rank() == 2);
    EXPECT(ds->spec().size() == 6 * 2);

    EXPECT(hv(2, 1) == 4);
    EXPECT(hv(1, 1) == 7);

    delete ds;
  }
  // test the resize with wrap
  {
    int vals[6] = {3, 4, 6, 7, 5, 4};

    Array* ds = Array::wrap<int>(vals, array::ArrayShape{3, 2});
    {
      array::ArrayView<int, 2> hv = make_host_view<int, 2>(*ds);
      hv(2, 1) = 4;
      hv(1, 1) = 7;
    }
    ds->resize(6, 2);
    array::ArrayView<int, 2> hv = make_host_view<int, 2>(*ds);

    EXPECT(ds->spec().shape()[0] == 6);
    EXPECT(ds->spec().shape()[1] == 2);

    EXPECT(ds->spec().rank() == 2);
    EXPECT(ds->spec().size() == 6 * 2);

    EXPECT(hv(2, 1) == 4);
    EXPECT(hv(1, 1) == 7);

    delete ds;
  }
}

CASE("test_resize_shape") {
  Array* ds = Array::create<double>(7, 5, 8);
  {
    array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);
    hv(3, 3, 3) = 4.5;
    hv(6, 4, 7) = 7.5;
  }
  ds->resize(ArrayShape{32, 5, 33});

  array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);
  EXPECT(ds->spec().shape()[0] == 32);
  EXPECT(ds->spec().shape()[1] == 5);
  EXPECT(ds->spec().shape()[2] == 33);

  EXPECT(ds->spec().rank() == 3);
  EXPECT(ds->spec().size() == 32 * 5 * 33);

  EXPECT(hv(3, 3, 3) == 4.5);
  EXPECT(hv(6, 4, 7) == 7.5);

  delete ds;
}

CASE("test_insert") {
  Array* ds = Array::create<double>(7, 5, 8);

  array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);
  hv(1, 3, 3) = 1.5;
  hv(2, 3, 3) = 2.5;
  hv(3, 3, 3) = 3.5;
  hv(6, 4, 7) = 6.5;

  ds->insert(3, 2);

  EXPECT(ds->spec().shape()[0] == 9);
  EXPECT(ds->spec().shape()[1] == 5);
  EXPECT(ds->spec().shape()[2] == 8);

  EXPECT(ds->spec().rank() == 3);
  EXPECT(ds->spec().size() == 9 * 5 * 8);

  array::ArrayView<double, 3> hv2 = make_host_view<double, 3>(*ds);

  // currently we have no mechanism to invalidate the old views after an insertion into the Array
  // The original gt data store is deleted and replaced, but the former ArrayView keeps a pointer to it
  // wihtout noticing it has been deleted
  EXPECT(hv.valid() == true);
  EXPECT(hv2.valid() == true);

  EXPECT(hv2(1, 3, 3) == 1.5);
  EXPECT(hv2(2, 3, 3) == 2.5);
  EXPECT(hv2(5, 3, 3) == 3.5);
  EXPECT(hv2(8, 4, 7) == 6.5);

  delete ds;
}

CASE("test_insert_throw") {
  Array* ds = Array::create<double>(7, 5, 8);

  EXPECT_THROWS_AS(ds->insert(8, 2), eckit::BadParameter);
}

CASE("test_wrap_storage") {
  {
    Array* ds = Array::create<double>(4, 5, 6);

    array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);

    hv(2, 3, 3) = 2.5;

    Array* ds_ext = Array::wrap<double>(hv.data(), ds->spec());

    array::ArrayView<double, 3> hv_ext = make_host_view<double, 3>(*ds_ext);

    EXPECT(hv_ext(2, 3, 3) == 2.5);

    delete ds;
    delete ds_ext;
  }
  {
    Array* ds = Array::create<double>(4, 5, 6);

    array::ArrayView<double, 3> hv = make_host_view<double, 3>(*ds);

    hv(2, 3, 3) = 2.5;

    ArrayShape shape{4, 5, 6};
    Array* ds_ext = Array::wrap<double>(hv.data(), shape);

    array::ArrayView<double, 3> hv_ext = make_host_view<double, 3>(*ds_ext);

    EXPECT(hv_ext(2, 3, 3) == 2.5);

    delete ds;
    delete ds_ext;
  }
}

CASE("test_storageview") {
  Array* ds = Array::create<double>(2ul, 3ul, 4ul);
  auto hv = make_host_view<double, 3>(*ds);

  EXPECT(hv.size() == 2 * 3 * 4);

  auto sv = make_storageview<double>(*ds);

  EXPECT(sv.size() == 2 * 3 * 4);

  delete ds;
}

CASE("test_assign") {
  Array* ds = Array::create<double>(2ul, 3ul, 4ul);
  auto hv = make_host_view<double, 3>(*ds);

  hv.assign(2.5);

  EXPECT(hv(1, 2, 3) == 2.5);

  auto lv = hv.at(1);
  lv.assign(5.0);

  EXPECT(hv(0, 2, 3) == 2.5);
  EXPECT(hv(1, 2, 3) == 5.0);
  EXPECT(lv(2, 3) == 5.0);

  auto sv = make_storageview<double>(*ds);
  sv.assign(0.);

  EXPECT(hv(0, 2, 3) == 0.);
  EXPECT(hv(1, 2, 3) == 0.);
  EXPECT(lv(2, 3) == 0.);

  delete ds;
}

CASE("test_ArrayT") {
  {
    ArrayT<double> ds(2, 3, 4);

    EXPECT(ds.size() == 2 * 3 * 4);
    EXPECT(ds.stride(0) == 3 * 4);
    EXPECT(ds.stride(1) == 4);
    EXPECT(ds.stride(2) == 1);
    EXPECT(ds.shape(0) == 2);
    EXPECT(ds.shape(1) == 3);
    EXPECT(ds.shape(2) == 4);
  }

  {
    ArrayT<double> ds(make_shape(2, 3, 4));

    EXPECT(ds.size() == 2 * 3 * 4);
    EXPECT(ds.stride(0) == 3 * 4);
    EXPECT(ds.stride(1) == 4);
    EXPECT(ds.stride(2) == 1);
    EXPECT(ds.shape(0) == 2);
    EXPECT(ds.shape(1) == 3);
    EXPECT(ds.shape(2) == 4);
  }

  {
    ArrayT<double> ds(ArraySpec(make_shape(2, 3, 4)));

    EXPECT(ds.size() == 2 * 3 * 4);
    EXPECT(ds.stride(0) == 3 * 4);
    EXPECT(ds.stride(1) == 4);
    EXPECT(ds.stride(2) == 1);
    EXPECT(ds.shape(0) == 2);
    EXPECT(ds.shape(1) == 3);
    EXPECT(ds.shape(2) == 4);
  }
}

//-----------------------------------------------------------------------------

}  // namespace test
}  // namespace atlas


int main(int argc, char **argv) {
    atlas::test::AtlasTestEnvironment env( argc, argv );
    return run_tests ( argc, argv, false );
}