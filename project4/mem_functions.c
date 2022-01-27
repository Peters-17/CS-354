#include "mem.h"
extern BLOCK_HEADER* first_header;

int Is_Free(BLOCK_HEADER* pointer) {
	return !(pointer->size_alloc & 1);
}

void Set_Free(BLOCK_HEADER* pointer) {
	pointer -> size_alloc = pointer -> size_alloc & -2;
}

void Set_Allocated(BLOCK_HEADER* pointer) {
	pointer -> size_alloc =  (pointer->size_alloc | 1);
}

BLOCK_HEADER* Get_Next_Header(BLOCK_HEADER* pointer) {
	BLOCK_HEADER* newPointer;
	//check the input pointer is null
	if(pointer == NULL){
		return NULL;
	}
	//check whether this block is allocated
	if(Is_Free(pointer)){
		newPointer = (BLOCK_HEADER*)((unsigned long)pointer + (pointer -> size_alloc));
	}
	else{
		newPointer = (BLOCK_HEADER*)((unsigned long)pointer + (pointer -> size_alloc - 1));
	}
    	return newPointer;
}

void Set_Payload(BLOCK_HEADER* pointer) {
    pointer -> payload = pointer -> size_alloc - sizeof(BLOCK_HEADER);
}

// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size) {
    int totalSize = 0;
    if((size + sizeof(BLOCK_HEADER)) % 16 == 0){
		totalSize = size + sizeof(BLOCK_HEADER);
    }
    else{
		totalSize = ((size + sizeof(BLOCK_HEADER)) + 16)/ 16 * 16;
		}
		BLOCK_HEADER* ptr = first_header;
		BLOCK_HEADER* searchStart = ptr;
    // locate first available block
    while (!Is_Free(ptr) || (ptr->size_alloc >>2 << 2 < totalSize)) {
			//check whether reach the end of memory
		if(ptr -> size_alloc == 1){
			ptr = first_header;
			if(searchStart == first_header){
				return NULL;//search end, no empty space
			}
			continue;
		}
		int stepLength = (ptr -> size_alloc) >> 2 << 2;//to delete the alloc label
		if(stepLength == 0){
			return NULL;//check whether stepLength is 0
		}
		ptr = Get_Next_Header(ptr);
			//check if ptr is null or search end, no empty space
		if (ptr == NULL || ptr == searchStart) {
			return NULL;
		}
	}

    // allocate memory and split block if applicable
    if (ptr -> size_alloc >= totalSize + 16) {
        BLOCK_HEADER* next_header =(BLOCK_HEADER *) ((unsigned long)ptr + totalSize);
		//set next_header's size and set payload of next_header	
		next_header->size_alloc = ptr -> size_alloc - totalSize;
		Set_Payload(next_header);
		ptr -> size_alloc = totalSize;
			//set allocated for this ptr block
		Set_Allocated(ptr);
			ptr -> payload = size;
		} 
	else { 
		//set allocated fpr this ptr block
		Set_Allocated(ptr);
		ptr -> payload = size;
    }
    return (BLOCK_HEADER*)((unsigned long)ptr + sizeof(BLOCK_HEADER));
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr) {
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    if (ptr == NULL) {
		return -1;
    }
    if (!(((BLOCK_HEADER*)ptr - 1) -> size_alloc & 1)) {
	    return -1; // ptr is already freed
    }
    // get header before ptr
    BLOCK_HEADER* tempPtr = first_header;
    BLOCK_HEADER* prev_header = NULL;
    BLOCK_HEADER* NEXT_header = NULL;
    
    //iterate all memory block
    while (Get_Next_Header(tempPtr) != NULL) {
	//if find the next header of tempPtr is bigger than ptr, then break
        if (Get_Next_Header(tempPtr) > (BLOCK_HEADER*)ptr) {
            break;
        }
	//increament for temp block
        tempPtr = Get_Next_Header(tempPtr);
    }
    if(Is_Free(tempPtr)){
	    return -1;
    }
    //ptr is a void type pointer with 1 setpLength
    //tempPtr is a BLOCK_HEADER pointer with 8 stepLength
	//check if ptr is not the next pointer of tempPtr in memory
    if(ptr != tempPtr + 1){
	    return -1;
    }
    Set_Free(tempPtr);
	tempPtr -> payload = tempPtr -> size_alloc - 8;
    //initialize NEXT_header and immediate coalescing
    NEXT_header = Get_Next_Header(tempPtr);
    if (Is_Free(NEXT_header)) {
        tempPtr -> size_alloc += (NEXT_header -> size_alloc);
        Set_Payload(tempPtr);
    } else {
        Set_Free(tempPtr);
    }

    //initialize prev_header and immediate coalescing
    prev_header = first_header;
    if (tempPtr != first_header) {
        while (Get_Next_Header(prev_header) != tempPtr) {
            prev_header = Get_Next_Header(prev_header);
        }
        if (Is_Free(prev_header)) {
            prev_header -> size_alloc += tempPtr -> size_alloc;
            Set_Payload(prev_header);
        }
    }
    return 0;
}





