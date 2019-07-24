#include "array.h"
#include "../vertex.h"

#include "../utils.h"

#include "memory.h"
#include "../engine.h"


int init_array(Array * array, size_t element_bytes_size, int count){
    if(array->initialized != true){
       
    }else{
        LOG("Array already initialized\n");
        return -1;
    }  
    array->count = 0;
    array->data = allocate_stack_memory_alignmed(element_bytes_size * count,16);
    array->actual_bytes_size = 0;
    array->element_bytes_size = element_bytes_size;
    array->bytes_capacity = element_bytes_size * count;
    array->initialized = true;
    array->element_capacity = count;
    return 0;
}

void add_to_array(Array* array, void* element){
    if(array->initialized == false){
        LOG("Array not initialized\n");
        raise(SIGINT);
        return;
    }
    if(array->count == 0){
        array->actual_bytes_size += array->element_bytes_size;
        memcpy(array->data,element,array->element_bytes_size);
        array->count++;
        return;
    }
    if(array->bytes_capacity < array->actual_bytes_size + array->element_bytes_size){
        LOG("Array need reallocation\n");//TODO: reallocation engine memory
        raise(SIGINT);
    }
    size_t offset = array->actual_bytes_size;
    array->count++;
    array->actual_bytes_size += array->element_bytes_size;
    
    memcpy(array->data+(offset),element,array->element_bytes_size);
}

void *get_from_array(Array* array,int index){
    if(array->count == 0){
        LOG("Array is empty\n");
        return NULL;
    }
    if(array->initialized == false){
        LOG("Array not initialized\n");
        raise(SIGINT);
        return NULL;
    }
    size_t offset = array->element_bytes_size;
    if(index == 0)
        return &array->data[0];
    if(index > array->count){
        LOG("Element out of range, array count: %i\n",array->count);
        return NULL;
    }         
    return &array->data[0] + (index*offset);
}

void clean_array(Array* array){
    array->count = 0;    
    array->actual_bytes_size = 0;
}
