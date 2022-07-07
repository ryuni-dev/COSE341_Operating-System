#include <stdio.h>
#include <stdlib.h>

#define EMPTY_FRAME -1

int* generate_ref_arr(size_t sz, size_t page_max);
void opt(int* ref_arr, size_t ref_arr_sz, size_t frame_sz);

int _contains(int* arr, size_t sz, int target);
int _get_distance(int* ref_arr, size_t sz, int curr_idx, int target);

// Driver code
int main(void) {
    int ref[] = {2,6,9,2,4,2,1,7,3,0,5,2,1,2,9,5,7,3,8,5  };
    //int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int sz = sizeof(ref) / sizeof(int);
    opt(ref, sz, 3);
    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
    
    // TODO ::
    //   Generate Refernece String
    for(int i = 0; i < sz; i++){
        ref_arr[i] = rand() % (page_max + 1);
    }

    return ref_arr;
}

void opt(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    int i, j, is_fault;
    int page_faults = 0, target = 0;
    int dist = -1;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = EMPTY_FRAME;

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
                for (j=0; j<frame_sz; j++) {
                    int tmp_dist = _get_distance(ref_arr, ref_arr_sz, i, frames[j]);
                    if (tmp_dist > dist) {
                        target = j;
                        dist = tmp_dist;
                    }
                }
            }
            
            frames[target] = ref_arr[i];
            page_faults++;
            dist = -1;
        }

        // Printing current states of frames
        printf("%d | ", ref_arr[i]);
        for(j=0; j<frame_sz; j++) {
            if (frames[j] == -1) printf(". ");
            else printf("%d ", frames[j]);
        }
        if (is_fault == -1) printf("(fault)");
        printf("\n");
    }


    printf("\ntotal of page fault : %d \n", page_faults);
    // Releasing memory
    free(frames);
}

int _contains(int* arr, size_t sz, int target) {
    int i = 0;
    for (i=0; i<sz; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int _get_distance(int* ref_arr, size_t sz, int curr_idx, int target) {
    int i;
    for (i=curr_idx; i<sz; i++) {
        if (ref_arr[i] == target) return i - curr_idx;
    }
    return sz + 1;
}