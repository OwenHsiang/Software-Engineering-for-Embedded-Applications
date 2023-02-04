#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <math.h>

/* private functions *********************************************************/
DynamicArray *arrVec[9999];
int LastIndex = 0;
int TotalCount = 0;

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    arrVec[LastIndex+1] = da;
    LastIndex++;
    TotalCount++;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    for(int i=0; i<LastIndex; ++i) {
        if(arrVec[i] == da) {
            arrVec[i] = NULL;
            break;
        }
    }
    TotalCount--;
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

/* HW3 starts from here **********************************************************/

double DynamicArray_min ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double min = DBL_MAX;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (da->buffer[da, index_to_offset(da, i)]<min) {
            min = da->buffer[da, index_to_offset(da, i)];
        }
    }
    return min;
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double max = DBL_MIN;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (da->buffer[da, index_to_offset(da, i)] > max) {
            max = da->buffer[da, index_to_offset(da, i)];
        }
    }
    return max;    
}

double DynamicArray_mean ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum = sum + da->buffer[da, index_to_offset(da, i)];
    }
    return (sum / DynamicArray_size(da));
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    int size = DynamicArray_size(da);
    int median = floor((double)size / 2);
    if (size % 2 == 0){
        return (da->buffer[da->origin + median - 1] + da->buffer[da->origin + median]) / 2.0;
    }
    else{
        return da->buffer[da->origin + median];
    }
}

double DynamicArray_sum ( const DynamicArray * da ) {
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum = sum + da->buffer[da, index_to_offset(da, i)];
    }
    return sum;
}

double DynamicArray_last ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return DynamicArray_get(da, DynamicArray_size(da) - 1);
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return DynamicArray_get(da, 0);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray* nd = DynamicArray_new();
    nd->capacity = da->capacity;
    nd->end = da->end;
    nd->origin = da->origin;
    nd->buffer = (double* )calloc(nd->capacity, sizeof(double));
    for (int i = 0; i<DynamicArray_size(da); i++) {
        DynamicArray_set(nd, i, da->buffer[index_to_offset(da,i)]);
    }
    return nd;
}

DynamicArray * DynamicArray_range ( double a, double b, double step) {
    DynamicArray* nd = DynamicArray_new();
    assert((b > a && step > 0) || (b < a && step < 0));
    if (b > a && step > 0) {
        for (int i = 0; a <= b; a = a + step, i = i + 1) {
            DynamicArray_set(nd, i, a);
        }
    } else if (b < a && step < 0) {
        for (int i = 0; a >= b; a = a + step, i = i + 1) {
            DynamicArray_set(nd, i, a);
        }
    } 
    return nd;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    assert(a != NULL && a->buffer != NULL);
    assert(b != NULL && b->buffer != NULL);

    DynamicArray *nd = DynamicArray_new();

    for(int i=0; i<DynamicArray_size(a); ++i) {
        double val = DynamicArray_get(a, i);
        DynamicArray_push(nd, val);
    }

    for(int i=0; i<DynamicArray_size(b); ++i) {
        double val = DynamicArray_get(b, i);
        DynamicArray_push(nd, val);
    }
    return nd;
}

DynamicArray * DynamicArray_take(const DynamicArray * da, int a) {
    DynamicArray * nd = DynamicArray_new();
    if (a > 0) {
        int i = 0;
        for (; i < a && i < DynamicArray_size(da); i++) {
            DynamicArray_set(nd, i, DynamicArray_get(da, i));
        }
        while (i < a) {
            DynamicArray_set(nd, i, 0);
            i++;
        }
    } else if (a < 0) {
        int count = 0;
        a = -a;
        for (int i = DynamicArray_size(da) - 1; i >= 0 && count < a; i--) {
            DynamicArray_push_front(nd, DynamicArray_get(da, i));
            count++;
        }
        while (count < a) {
            DynamicArray_push_front(nd, 0);
            count++;
        }
    }
    return nd;
}

int DynamicArray_num_arrays() {
    return TotalCount;
}

int DynamicArray_destroy_all() {
    for(int i=0; i<=LastIndex; ++i)
        if(arrVec[i] != NULL)
            DynamicArray_destroy(arrVec[i]);
    LastIndex = 0;
    TotalCount = 0;
    return 0;
}

int DynamicArray_is_valid(const DynamicArray * da) {
    if(da == NULL || da->buffer == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}
