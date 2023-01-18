#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, test1) {
        Complex c1 = (Complex) { 1, 2 };
        Complex c2 = (Complex) { 3, 4 };
        
        EXPECT_EQ(add(c1,c2).real, 4);
        EXPECT_EQ(add(c1,c2).im, 6);
        
        EXPECT_EQ(negate(c1).real, -1);
        EXPECT_EQ(negate(c1).im, -2);

        EXPECT_EQ(negate(c2).real, -3);
        EXPECT_EQ(negate(c2).im, -4);
        
        EXPECT_EQ(multiply(c1,c2).real, -5);
        EXPECT_EQ(multiply(c1,c2).im, 10);
        
        EXPECT_TRUE((magnitude(c1) >= 2.2360) && (2.2361 >= magnitude(c1)));
        EXPECT_TRUE((magnitude(c2) == 5));
    }

    TEST(Complex, test2) {
        Complex c1 = (Complex) { -10, 12 };
        Complex c2 = (Complex) { 4, -8 };
        
        EXPECT_EQ(add(c1,c2).real, -6);
        EXPECT_EQ(add(c1,c2).im, 4);
        
        EXPECT_EQ(negate(c1).real, 10);
        EXPECT_EQ(negate(c1).im, -12);

        EXPECT_EQ(negate(c2).real, -4);
        EXPECT_EQ(negate(c2).im, 8);
        
        EXPECT_EQ(multiply(c1,c2).real, 56);
        EXPECT_EQ(multiply(c1,c2).im, 128);
        
        EXPECT_TRUE((magnitude(c1) >= 15.6204) && (15.6205 >= magnitude(c1)));
        EXPECT_TRUE((magnitude(c2) >= 8.9442) && (8.9443 >= magnitude(c2)));
    }
    
    TEST(Complex, test3) {
        Complex c1 = (Complex) { 0, 1 };
        Complex c2 = (Complex) { 1, 0 };
        
        EXPECT_EQ(add(c1,c2).real, 1);
        EXPECT_EQ(add(c1,c2).im, 1);
        
        EXPECT_EQ(negate(c1).real, 0);
        EXPECT_EQ(negate(c1).im, -1);

        EXPECT_EQ(negate(c2).real, -1);
        EXPECT_EQ(negate(c2).im, 0);
        
        EXPECT_EQ(multiply(c1,c2).real, 0);
        EXPECT_EQ(multiply(c1,c2).im, 1);
        
        EXPECT_TRUE((magnitude(c1) == 1.0000));
        EXPECT_TRUE((magnitude(c2) == 1.0000));
    }
}