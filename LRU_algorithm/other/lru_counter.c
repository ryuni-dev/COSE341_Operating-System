#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define EMPTY_FRAME -1

int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz);

int _contains(int* arr, size_t sz, int target);
int _max(int* arr, size_t sz);
int _min(int* arr, size_t sz);

// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;

    int ref_arr_sz = atoi(argv[1]);
    int page_max = atoi(argv[2]);
    int frame_sz = atoi(argv[3]);

    int ref[] = {0,1,2,3,4,4,3,2,1,0,0,1,2,3,4,4,3,2,1,0 };
   //int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int sz = sizeof(ref) / sizeof(int);
    int page_faults = lru(ref, sz, frame_sz);
    //printf("%d\n", page_faults);

    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
    
    // TODO ::
    //   Generate Referenece String
    for(int i = 0; i < sz; i++){
        ref_arr[i] = rand() % (page_max + 1);
    }

    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    int i, j, is_fault, target;
    int page_faults = 0;
    int curr_time = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = EMPTY_FRAME;

    // Initializing accessed times table
    int page_max = _max(ref_arr, ref_arr_sz) + 1;
    int* atimes = (int*) malloc(sizeof(int) * page_max);
    for (i=0; i<page_max; i++) atimes[i] = -1;

    // Iterating reference string
    for (i=0; i<ref_arr_sz; i++) {
        is_fault = _contains(frames, frame_sz, ref_arr[i]);

        // Miss (page fault occurred)
        if (is_fault == -1) {
            int empty_idx = _contains(frames, frame_sz, EMPTY_FRAME);

            // Checking for empty frame slots
            if (empty_idx != EMPTY_FRAME) {
                target = empty_idx;
            }
            else {
                int target_atime = INT_MAX;
                for (j=0; j<frame_sz; j++) {
                    if (atimes[frames[j]] < target_atime && atimes[frames[j]] >= 0) {
                        target = j;
                        target_atime = atimes[frames[j]];
                    }
                }
            }

            frames[target] = ref_arr[i];
            page_faults++;
        }

        atimes[ref_arr[i]] = curr_time++;

        printf("%d | ", ref_arr[i]);
        for(j=0; j<frame_sz; j++) {
            if (frames[j] == -1) printf(". ");
            else printf("%d ", frames[j]);
        }
        if (is_fault == -1) printf("(fault)");
        printf("\n");
        
    }

    printf("\ntotal of page fault : %d \n", page_faults);

    free(atimes);
    free(frames);

    return page_faults;
}

int _contains(int* arr, size_t sz, int target) {
    int i = 0;
    for (i=0; i<sz; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int _max(int* arr, size_t sz) {
    int i;
    int max = INT_MIN;

    for (i=0; i<sz; i++) {
        if (arr[i] > max) max = arr[i];
    }

    return max;
}

int _min(int* arr, size_t sz) {
    int i;
    int min = INT_MAX;

    for (i=0; i<sz; i++) {
        if (arr[i] < min) min = arr[i];
    }

    return min;
}