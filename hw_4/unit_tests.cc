#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "complex.h"
#include "typed_array.h"
#include "gtest/gtest.h"

namespace {

    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(TypedArray, Construction) {
        TypedArray<int> b;
        b.set(0, 1);
        b.set(10, 2);
        b.set(100, 3);
        EXPECT_EQ(b.get(0), 1);
        EXPECT_EQ(b.get(10), 2);
        EXPECT_EQ(b.get(100), 3);
    }

    TEST(TypedArray, Push) {
        TypedArray<double> b;
        b.push(1.1);
        b.push(2.2);
        b.push(3.3);
        EXPECT_EQ(b.get(0), 1.1);
        EXPECT_EQ(b.get(1), 2.2);
        EXPECT_EQ(b.get(2), 3.3);
    }

    TEST(TypedArray, Pop) {
        TypedArray<char> b;
        EXPECT_THROW(b.pop(), std::range_error);
        b.push('q');
        b.push('w');
        b.push('e');
        
        EXPECT_EQ(b.size(), 3);
        char c1 = b.pop();
        EXPECT_EQ(c1, 'e');

        EXPECT_EQ(b.size(), 2);
        char c2 = b.pop();
        EXPECT_EQ(c2, 'w');

        EXPECT_EQ(b.size(), 1);
        char c3 = b.pop();
        EXPECT_EQ(c3, 'q');

        EXPECT_THROW(b.pop(), std::range_error);
    }

    TEST(TypedArray, PushFront) {
        TypedArray<int> b;
        b.push(1);
        b.push(2);
        b.push_front(3);
        b.push_front(4);
        
        EXPECT_EQ(b.get(0), 4);
        EXPECT_EQ(b.get(1), 3);
        EXPECT_EQ(b.get(2), 1);
        EXPECT_EQ(b.get(3), 2);
    }

    TEST(TypedArray, PopFront) {
        TypedArray<int *> b;
        EXPECT_THROW(b.pop_front(), std::range_error);
        
        b.push(new int(1));
        b.push(new int(2));
        b.push(new int(3));
        
        EXPECT_EQ(b.size(), 3);
        int *p1 = b.pop_front();
        EXPECT_EQ(*p1, 1);

        EXPECT_EQ(b.size(), 2);
        int *p2 = b.pop_front();
        EXPECT_EQ(*p2, 2);

        EXPECT_EQ(b.size(), 1);
        int *p3 = b.pop();
        EXPECT_EQ(*p3, 3);

        EXPECT_THROW(b.pop_front(), std::range_error);
        
        delete p1, p2, p3;
    }

    TEST(TypedArray, Concat) {
        TypedArray<int> b;
        b.push(1);
        b.push(2);
        b.push(3);
        
        TypedArray<int> c;
        c.push(4);
        c.push(5);

        TypedArray<int> d = b.concat(c);

        EXPECT_EQ(d.size(), 5);
        EXPECT_EQ(d.get(0), 1);
        EXPECT_EQ(d.get(1), 2);
        EXPECT_EQ(d.get(2), 3);
        EXPECT_EQ(d.get(3), 4);
        EXPECT_EQ(d.get(4), 5);

        EXPECT_EQ(b.size(), 3);
        EXPECT_EQ(b.get(0), 1);
        EXPECT_EQ(b.get(1), 2);
        EXPECT_EQ(b.get(2), 3);      

        EXPECT_EQ(c.size(), 2);
        EXPECT_EQ(c.get(0), 4);
        EXPECT_EQ(c.get(1), 5);  
    }

    TEST(TypedArray, Reverse) {
        TypedArray<int> b;
        b.push(1);
        b.push(2);
        b.push(3);
        b.push(4);
        b.push(5);
        
        b = b.reverse();

        EXPECT_EQ(b.get(0), 5);
        EXPECT_EQ(b.get(1), 4);
        EXPECT_EQ(b.get(2), 3);
        EXPECT_EQ(b.get(3), 2);
        EXPECT_EQ(b.get(4), 1);
    }

    TEST(TypedArray, Plus) {
        TypedArray<int> b;
        b.push(1);
        b.push(2);
        b.push(3);
        
        TypedArray<int> c;
        c.push(4);
        c.push(5);
        c.push(6);

        TypedArray<int> d = b + c;

        EXPECT_EQ(d.size(), 6);
        EXPECT_EQ(d.get(0), 1);
        EXPECT_EQ(d.get(1), 2);
        EXPECT_EQ(d.get(2), 3);
        EXPECT_EQ(d.get(3), 4);
        EXPECT_EQ(d.get(4), 5);
        EXPECT_EQ(d.get(5), 6);

        EXPECT_EQ(b.size(), 3);
        EXPECT_EQ(b.get(0), 1);
        EXPECT_EQ(b.get(1), 2);
        EXPECT_EQ(b.get(2), 3);      

        EXPECT_EQ(c.size(), 3);
        EXPECT_EQ(c.get(0), 4);
        EXPECT_EQ(c.get(1), 5);
        EXPECT_EQ(c.get(2), 6);   
    }

    TEST(ComplexClass, Equal) {
        Complex a(1.0, 2.0);
        Complex b(1.0, 2.0);

        EXPECT_EQ(a, b);
    }

    TEST(ComplexClass, Conjugate) {
        Complex a(1.0, 2.0);
        Complex b(1.0, -2.0);
        EXPECT_EQ(a, b.conjugate());
    }

    TEST(ComplexClass, Multiply) {
        Complex a(1.0, 2.0);
        Complex b(3.0, 4.0);
        EXPECT_EQ(a*b, Complex(-5, 10));
    }

    TEST(ComplexClass, Add) {
        Complex a(1.0, 2.0);
        Complex b(3.0, 4.0);
        EXPECT_EQ(a+b, Complex(4, 6));
    }
}