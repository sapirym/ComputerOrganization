/**
 * Sapir Yamin
 * 316251818
 */

#include <stdio.h>
#include "ex1.h"

/*
 * the function check if the version in the computer is big or little endian.
 * first, we will define int =1, it's the easiest number that we can check.
 * then, we will take the first byte in the int by casting to char,
 * int is compose from 4 bytes, and we want to check the first byte:
 * if it is 1, then it is true - the machine with a version of Little endian.
 * if it is not 1, then it is false - the machine with a version of Big endian.
 *
 * */
int is_little_endian(){
    long int i=1;
    //go to the address of i, then cast it to char *.
    // that's how we can get the first byte.
    char* x  = (char*)&i;
    //if the value of x is 1 - then it is little endian.
    if(*x){
        return 1;
    }
    return 0;
}

/*
 * the function merge the bytes of the first, with the byte of
 * the second.
 * first we will check if the machine with a version of big or little endian.
 * if true - we will take the first bytes.
 * else - we will take the last bytes.
 * */
unsigned long merge_bytes(unsigned long x, unsigned long int y){
    long endOfy;
    long startOfX;
    //check if the it is little or big endian.
    if(is_little_endian()) {
        //get the last byte of y, by "and" operator.
        endOfy = y&(0x00000000000000FF);
        //reset the last byte of x, by "and" operator.
        startOfX = x & (0xFFFFFFFFFFFFFF00);
        //if it is big endian:
    } else {
        //get the first byte from the end.
        endOfy = y&(0xFF00000000000000);
        //reset the first byte from the end.
        startOfX = x&(0x00FFFFFFFFFFFFFF);
    }
    //get the merge value by "or" operator.
    return endOfy|startOfX;
}
/*
 * the function merge the byte i of the last with the rest of the bytes of the first.
 * if it is little endian - then go to the first byte (by casting to char),
 * if it is big endian - then we go to the last byte (by casting to char
 * and move the pointer to the and).
 * */
unsigned long put_byte(unsigned long x, unsigned char b, int i){
    //check if it is little or big endian.
    if(is_little_endian()) {
        //get the first byte by casting to char.
        unsigned char *g = (char *) &x;
        //move the pointer i steps and set the byte i to b.
        *(g + i) = b;
        //return the new value of x.
        return x;
        //if it is big endian:
    } else{
        //get the first byte by casting to char.
        unsigned char *g = (char *) &x;
        //move the pointer 7-i steps and set the byte i to b.
        *(g + (7- i)) = b;
        //return the new value of x.
        return x;
    }
}
