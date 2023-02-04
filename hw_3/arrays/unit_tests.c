#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         
// Mathematical operations
    TEST(DynamicArray, min) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -100);    
        DynamicArray_set(da, 1, 50);  
        DynamicArray_set(da, 2, 0);  
        DynamicArray_set(da, 3, 50);  
        DynamicArray_set(da, 4, 100);      
        ASSERT_EQ(DynamicArray_min(da),-100);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, max) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -100);    
        DynamicArray_set(da, 1, 50);  
        DynamicArray_set(da, 2, 0);  
        DynamicArray_set(da, 3, 50);  
        DynamicArray_set(da, 4, 100);      
        ASSERT_EQ(DynamicArray_max(da),100);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, mean) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 50);  
        DynamicArray_set(da, 1, 100);      
        ASSERT_EQ(DynamicArray_mean(da),75); 
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, median) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -100);    
        DynamicArray_set(da, 1, 50);  
        DynamicArray_set(da, 2, 0);  
        DynamicArray_set(da, 3, 50);  
        DynamicArray_set(da, 4, 100);      
        ASSERT_EQ(DynamicArray_median(da),0);  
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, sum) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -100);    
        DynamicArray_set(da, 1, 50);       
        ASSERT_EQ(DynamicArray_sum(da),-50);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, lastAndFirst) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 100);    
        DynamicArray_set(da, 1, 1); 
        ASSERT_EQ(DynamicArray_last(da),1); 
        ASSERT_EQ(DynamicArray_first(da),100); 
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, copy) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 0, 10);    
        DynamicArray_set(da, 1, 9); 
        DynamicArray_set(da, 2, 8);  
        DynamicArray_set(da, 3, 7);      
        DynamicArray_set(da, 4, 6);

        DynamicArray * c = DynamicArray_copy(da);
        ASSERT_EQ(DynamicArray_size(c),5);
        ASSERT_EQ(DynamicArray_get(c, 0),10);
        ASSERT_EQ(DynamicArray_get(c, 1),9);
        ASSERT_EQ(DynamicArray_get(c, 2),8);
        ASSERT_EQ(DynamicArray_get(c, 3),7);
        ASSERT_EQ(DynamicArray_get(c, 4),6);
        DynamicArray_destroy(da);
        DynamicArray_destroy(c);
    }

    TEST(DynamicArray, Range) {
        double a = 100.0;
        double b = 200.0;
        double step = 50;
        DynamicArray * da = DynamicArray_range(a, b, step);

        ASSERT_EQ(DynamicArray_get(da, 0), 100.0);
        ASSERT_EQ(DynamicArray_get(da, 1), 150.0);
        ASSERT_EQ(DynamicArray_get(da, 2), 200.0);
        
        DynamicArray_destroy(da);
    }

    TEST(DynamnicArray,concat) {
        DynamicArray * a = DynamicArray_range(0, 0.4, 0.1);
        DynamicArray * b = DynamicArray_range(0.5, 1, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b); 
        ASSERT_NEAR(DynamicArray_get(c,0), 0.0000, 0.1); 
        ASSERT_NEAR(DynamicArray_get(c,1), 0.1000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,2), 0.2000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,3), 0.3000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,4), 0.4000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,5), 0.5000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,6), 0.6000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,7), 0.7000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,8), 0.8000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,9), 0.9000, 0.1);
        ASSERT_NEAR(DynamicArray_get(c,10), 1.0000, 0.1);
        DynamicArray_destroy(c);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 2);  
        DynamicArray * c = DynamicArray_take(a, -2); 
        DynamicArray * d = DynamicArray_take(a, 7);  

        ASSERT_EQ(DynamicArray_get(b, 0), 1);
        ASSERT_EQ(DynamicArray_get(b, 1), 2);

        ASSERT_EQ(DynamicArray_get(c, 0), 4);
        ASSERT_EQ(DynamicArray_get(c, 1), 5);

        ASSERT_EQ(DynamicArray_get(d, 0), 1);
        ASSERT_EQ(DynamicArray_get(d, 1), 2);
        ASSERT_EQ(DynamicArray_get(d, 2), 3);
        ASSERT_EQ(DynamicArray_get(d, 3), 4);
        ASSERT_EQ(DynamicArray_get(d, 4), 5);
        ASSERT_EQ(DynamicArray_get(d, 5), 0);
        ASSERT_EQ(DynamicArray_get(d, 6), 0);

        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
    }

    TEST(DynamicArray, DestroyAll) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);
    }
}