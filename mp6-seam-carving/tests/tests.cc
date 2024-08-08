//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                  MP : Seam Carver  : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "image_ppm.hpp"
#include "pixel.hpp"
#include "seam_carver.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("Video Example Vertical Seam", "vid_vertical") {
  /*  TESTING LOCALLY
    std::ifstream infile(
        "/Users/apt/cs128/cs128env/src/mp-seam-carving-AdamTKoy/images/"
        "image.ppm");
  */

  std::ifstream infile("images/image.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();

  SeamCarver carver(image);

  int* test = carver.GetVerticalSeam();

  REQUIRE(test[0] == 3);
  REQUIRE(test[1] == 4);
  REQUIRE(test[2] == 4);
  REQUIRE(test[3] == 4);
  REQUIRE(test[4] == 4);
}

TEST_CASE("Video Example Horizontal Seam", "vid_horizontal") {
  /*  TESTING LOCALLY
    std::ifstream infile(
        "/Users/apt/cs128/cs128env/src/mp-seam-carving-AdamTKoy/images/"
        "image.ppm");
  */

  std::ifstream infile("images/image.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();

  SeamCarver carver(image);

  int* test = carver.GetHorizontalSeam();

  REQUIRE(test[0] == 3);
  REQUIRE(test[1] == 4);
  REQUIRE(test[2] == 4);
  REQUIRE(test[3] == 4);
  REQUIRE(test[4] == 4);
}

TEST_CASE("Populate Image Object", "new_img_obj") {
  int w = 4, h = 3;
  ImagePPM test;
  test.PopulateObject(w, h, 20);

  REQUIRE(test.GetWidth() == 4);
  REQUIRE(test.GetHeight() == 3);

  Pixel p = {4, 2, 1};

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      test.SetPixel(p, row, col);
    }
  }

  REQUIRE(test.GetPixel(1, 0) == p);
  REQUIRE(test.GetPixel(1, 1) == p);
  REQUIRE(test.GetPixel(1, 2) == p);
  REQUIRE(test.GetPixel(1, 3) == p);

  REQUIRE(test.GetPixel(2, 0) == p);
  REQUIRE(test.GetPixel(2, 1) == p);
  REQUIRE(test.GetPixel(2, 2) == p);
  REQUIRE(test.GetPixel(2, 3) == p);
}

TEST_CASE("Video Example Remove Vertical Seam", "vid_remove_vertical") {
  /*  RUNNING LOCALLY:
    std::ifstream infile(
        "/Users/apt/cs128/cs128env/src/mp-seam-carving-AdamTKoy/images/"
        "image.ppm");
  */
  std::ifstream infile("images/image.ppm");

  ImagePPM image;
  infile >> image;
  infile.close();

  SeamCarver carver(image);

  // first seam to remove: {3, 4, 4, 4, 4}
  carver.RemoveVerticalSeam();

  ImagePPM test = carver.GetImage();

  Pixel p = {0, 0, 0};
  Pixel p1 = {2, 1, 1};

  REQUIRE(test.GetPixel(0, 3) == p);
  REQUIRE(test.GetPixel(3, 2) == p1);
  REQUIRE(test.GetWidth() == 4);
}

/*
TEST_CASE("Video Example PPM After Carve", "vid_ppm_after_carve") {
  //RUNNING LOCALLY:
    std::ifstream infile(
        "/Users/apt/cs128/cs128env/src/mp-seam-carving-AdamTKoy/images/"
        "image.ppm");

    std::ifstream infile("images/image.ppm");

    ImagePPM image;
    infile >> image;
    infile.close();

    SeamCarver carver(image);

    // first seam to remove: {3, 4, 4, 4, 4}
    carver.RemoveVerticalSeam();

    ImagePPM test = carver.GetImage();

    std::cout << test;

    REQUIRE(true == true);
}
*/