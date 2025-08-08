#ifndef _BYTEARRAY_H
#define _BYTEARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* data;
    size_t size;
    
} ByteArray;


ByteArray* createByteArray();
int freeByteArray(ByteArray* array) ;
int appendToByteArray(ByteArray* array, const void* data, size_t size) ;
int removeFromByteArray(ByteArray* array, size_t startPoint, size_t length);
void showMessage(ByteArray* message);

#endif