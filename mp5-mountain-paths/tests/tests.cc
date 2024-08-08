// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("ElevationDataset Object", "[elev_dat_obj]") {
  ElevationDataset e1(
      "/home/vagrant/src/mp-mountain-paths-AdamTKoy/example-data/ex_input_data/"
      "all-tie-row1-2w-3h.dat",
      2,
      3);

  REQUIRE(e1.Height() == 3);
  REQUIRE(e1.Width() == 2);
  REQUIRE(e1.MaxEle() == 10);
  REQUIRE(e1.MinEle() == 7);
  REQUIRE(e1.DatumAt(0, 0) == 9);
  REQUIRE(e1.DatumAt(0, 1) == 10);
  REQUIRE(e1.DatumAt(1, 0) == 8);
  REQUIRE(e1.DatumAt(1, 1) == 10);
  REQUIRE(e1.DatumAt(2, 0) == 7);
  REQUIRE(e1.DatumAt(2, 1) == 10);
}

TEST_CASE("Basic PPM", "[ppm_basic]") {
  ElevationDataset e1(
      "/home/vagrant/src/mp-mountain-paths-AdamTKoy/example-data/ex_input_data/"
      "map-input-w480-h480.dat",
      480,
      480);
  GrayscaleImage gsi1(e1);

  gsi1.ToPpm("/home/vagrant/src/mp-mountain-paths-AdamTKoy/bin/output.ppm");

  REQUIRE(gsi1.Height() == 480);
  REQUIRE(gsi1.Width() == 480);
}

TEST_CASE("PathImage 480 480 PPM", "[path_image_480_ppm]") {
  ElevationDataset e1(
      "/home/vagrant/src/mp-mountain-paths-AdamTKoy/example-data/ex_input_data/"
      "map-input-w480-h480.dat",
      480,
      480);
  GrayscaleImage gsi1(e1);

  PathImage p1(gsi1, e1);

  p1.ToPpm("/home/vagrant/src/mp-mountain-paths-AdamTKoy/bin/output1.ppm");

  REQUIRE(p1.Height() == 480);
  REQUIRE(p1.Width() == 480);
}

TEST_CASE("PathImage 480 840 PPM", "[path_image_844_ppm]") {
  ElevationDataset e1(
      "/home/vagrant/src/mp-mountain-paths-AdamTKoy/example-data/ex_input_data/"
      "map-input-w844-h480.dat",
      844,
      480);
  GrayscaleImage gsi(e1);

  PathImage p(gsi, e1);

  p.ToPpm("/home/vagrant/src/mp-mountain-paths-AdamTKoy/bin/output844.ppm");

  REQUIRE(p.Height() == 480);
  REQUIRE(p.Width() == 844);
}

/*
TEST_CASE("More Data Than Rows", "[invalid_dim_too_few_rows]") {
  REQUIRE_THROWS_AS(
      ElevationDataset e1("/home/vagrant/src/mp-mountain-paths-AdamTKoy/"
                          "example-data/ex_input_data/"
                          "map-input-invalid-dim.dat",
                          51,
                          55),
      std::runtime_error);
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////