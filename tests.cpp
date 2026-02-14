#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "code.h"
#include <iostream>
#include <sstream>

TEST_CASE("testing the printImage() function.", "[20 points]") {
    {
    INFO("This test checks the printImage() function.");
        std::vector<std::vector<int>> input_image{
            {10,  20,  30,  40,  50,  60,  70,  80,  90,  100},
            {10,  20,  30,  40,  50,  60,  70,  80,  90,  100},
            {10,  20,  30,  40,  50,  60,  70,  80,  90,  100},
            {10,  20,  30,  40,  50,  60,  70,  80,  90,  100},
            {10,  20,  30,  40,  50,  60,  70,  80,  90,  100}
        };
        
        // Redirect cout to our stringstream buffer
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::stringstream out;
        std::cout.rdbuf(out.rdbuf());
        printImage(input_image);
        // Restore the original buffer so further cout calls are normal
        std::cout.rdbuf(coutBuf);

        std::string expected_output_1 =
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\t\n";

        std::string expected_output_2 =
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\n"
        "10\t20\t30\t40\t50\t60\t70\t80\t90\t100\n";

        CHECK(((out.str() == expected_output_1) || (out.str() == expected_output_2)));
    }
}


// UNCOMMENT TEST CASES AS YOU IMPLEMENT FUNCTIONS


TEST_CASE("testing the applyKernel() function boundaries.", "[10 points]") {

    {
    INFO("This test checks the boundaries of the return of applyKernel() function.");
        std::vector<std::vector<int>> input_image{
            {100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
            {100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
            {100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
            {100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
            {100, 100, 100, 100, 100, 100, 100, 100, 100, 100}
        };

        std::vector<std::vector<int>> output_image = applyKernel(input_image);

        REQUIRE(output_image[0][0] == 0); // Check top-left corner
        REQUIRE(output_image[0][9] == 0); // Check top-right corner
        REQUIRE(output_image[4][0] == 0); // Check bottom-left corner
        REQUIRE(output_image[4][9] == 0); // Check bottom-right corner
        REQUIRE(output_image[2][4] == 0); // Check center pixel
    }
}

TEST_CASE("testing the applyKernel() function on vertical edge.", "[10 points]") {
    
    {
    INFO("This test checks the applyKernel() function for an image with a vertical edge.");

        std::vector<std::vector<int>> input_image{
            {50,  50,  50,  50,  50,  200,  200,  200,  200,  200},
            {50,  50,  50,  50,  50,  200,  200,  200,  200,  200},
            {50,  50,  50,  50,  50,  200,  200,  200,  200,  200},
            {50,  50,  50,  50,  50,  200,  200,  200,  200,  200},
            {50,  50,  50,  50,  50,  200,  200,  200,  200,  200}
        };

        std::vector<std::vector<int>> output_image = applyKernel(input_image);
    
        REQUIRE(output_image[2][4] == -450);  // Check left of vertical edge
        REQUIRE(output_image[2][5] == 450);   // Check right of vertical edge
        REQUIRE(output_image[2][3] == 0);     // Check non-edge region
    }
} 


TEST_CASE("testing the applyKernel() function on slanting edge.", "[10 points]") {
    {
    INFO("This test checks the applyKernel() function for an image with a slanting edge.");

        std::vector<std::vector<int>> input_image{
            {200,  50,  50,  50,  50},
            {50,  200,  50,  50,  50},
            {50,  50,  200,  50,  50},
            {50,  50,  50,  200,  50},
            {50,  50,  50,  50,  200}
        };

        std::vector<std::vector<int>> output_image = applyKernel(input_image);

        REQUIRE(output_image[2][2] == 900);
        REQUIRE(output_image[1][1] == 900);
        REQUIRE(output_image[3][3] == 900);
        REQUIRE(output_image[0][3] == 0);
    }
}




TEST_CASE("testing the applyKernel() function on an image smaller than the kernel.", "[10 points]") {
    {
    INFO("This test checks the applyKernel() function on an image smaller than the kernel.");

        std::vector<std::vector<int>> small_image{
            {150, 250},
            {50, 100}
        };

        std::vector<std::vector<int>> output_image = applyKernel(small_image);

        // Check that the output image has the same dimensions as the input image
        // Handle out of bounds error
        REQUIRE(output_image.size() == small_image.size());
        REQUIRE(output_image[0].size() == small_image[0].size());
    }
}

TEST_CASE("testing the minMaxNormalization() function.", "[10 points]") {
    {
    INFO("This test checks the minMaxNormalization() function.");

        std::vector<std::vector<int>> image{
            {-255, -200, -150, -100, -50,  0,   50,  100, 150, 200},
            {-200, -150, -100, -50,   0,   50,  100, 150, 200, 250},
            {-150, -100, -50,   0,    50,  100, 150, 200, 250, 300},
            {-100, -50,   0,    50,   100, 150, 200, 250, 300, 350},
            {-50,   0,    50,   100,  150, 200, 250, 300, 350, 400}
        };

        minMaxNormalization(image);

        REQUIRE(image[0][0] == 0);    // Check top-left corner
        REQUIRE(image[0][9] == 177);  // Check top-right corner
        REQUIRE(image[4][0] == 79);   // Check bottom-left corner
        REQUIRE(image[4][9] == 255);  // Check bottom-right corner
    }
}

TEST_CASE("testing the minMaxNormalization() function for for out of range values.", "[10 points]") {
    {
    INFO("This test checks out of range values in the minMaxNormalization() function.");

        std::vector<std::vector<int>> image{
            {100, 200, 300, 400, 500},
            {50, 150, 250, 350, 450},
            {175, 275, 375, 475, 575},
            {0, 100, 200, 300, 400},
            {50, 150, 250, 350, 450}
        };

        minMaxNormalization(image);

        // Check that the output image has values within the [0, 255] range
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                REQUIRE(image[i][j] >= 0);
                REQUIRE(image[i][j] <= 255);
            }
        }
    }
}

TEST_CASE("testing the minMaxNormalization() function on an already normalized image", "[10 points]") {
    {
    INFO("This test checks the minMaxNormalization() function make changes to a normalized image.");
    
        std::vector<std::vector<int>> image{
            {0,  25,  50,  75, 100},
            {125, 150, 175, 200, 225},
            {50,  75, 100, 125, 150},
            {175, 200, 225, 250, 255},
            {0,   50, 100, 150, 200}
        };

        std::vector<std::vector<int>> orig_image = image;
        minMaxNormalization(image); // should not normalize an already normalized image.
        REQUIRE(orig_image == image);
    }
}

TEST_CASE("testing the minMaxNormalization() function on negative pixels", "[10 points]") {
    {
    INFO("This test checks minMaxNormalization() function with negative values.");
        std::vector<std::vector<int>> image{
            {-200,  -50,  -50,  -50,  -50},
            {-50,  -200,  -50,  -50,  -50},
            {-50,  -50,  -200,  -50,  -50},
            {-50,  -50,  -50,  -200,  -50},
            {-50,  -50,  -50,  -50,  -200}
        };

        minMaxNormalization(image);

        REQUIRE(image[2][2] == 0);
        REQUIRE(image[1][1] == 0);
        REQUIRE(image[3][3] == 0);
    }
}