#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY_FRAME -1

int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, size_t page_max);

int _contains(int* arr, size_t sz, int target);

// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;
    
    int ref_arr_sz = atoi(argv[1]);
    int page_max = atoi(argv[2]);
    int frame_sz = atoi(argv[3]);

    //int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int* ref = generate_ref_arr(ref_arr_sz, page_max);
    int page_faults = lru(ref, ref_arr_sz, frame_sz, page_max);
    printf("%d\n", page_faults);
    free(ref);

    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
    
    // TODO :: Generate Random Refernece String
    srand(time(NULL));
    for(int i = 0; i < sz; i++){
        ref_arr[i] = rand() % (page_max + 1);
    }
    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, size_t page_max) {
    int i, j;
    int page_faults = 0, frame_target = 0, is_fault = 0, target = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO
    // Initializing accessed reference bits table
    int page_size = page_max + 1;
    int* bits = (int*) malloc(sizeof(int) * page_size);
    for (i=0; i<page_size; i++) bits[i] = 0b00000000;

    // Iterating reference string
    for (i=0; i<ref_arr_sz; i++) {
        is_fault = _contains(frames, frame_sz, ref_arr[i]);
        for(int j = 0; j < page_size; j++) bits[j] = bits[j] >> 1;
        bits[ref_arr[i]] |= 0b10000000;

        // Miss (page fault occurred)
        if (is_fault == -1) {
            page_faults++;
            if(frame_target < frame_sz){
                frames[frame_target++] = ref_arr[i];
            }
            else{
                int min_target = frames[0];
                for(int j = 1; j < frame_sz; j++){
                    if(bits[min_target] > bits[frames[j]]){
                        min_target = frames[j];
                    }
                }
                target = _contains(frames, frame_sz, min_target);
                frames[target] = ref_arr[i];
            }
        }

        // Printing current states of frames
        printf("%d | ", ref_arr[i]);
        for(j=0; j<frame_sz; j++) {
            if (frames[j] == EMPTY_FRAME) printf(". ");
            else printf("%d ", frames[j]);
        }
        if (is_fault == -1) printf("(fault)");
        printf("\n");
    }

    // Releasing memory
    free(frames);
    free(bits);

    return page_faults;
}

int _contains(int* arr, size_t sz, int target) {
    int i = 0;
    for (i=0; i<sz; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}