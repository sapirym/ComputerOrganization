//
// Sapir Yamin
// 316251818

#include <stdio.h>
#include <string.h>

int compareSignWin(char byte[], char source[], char prev[], char next[], int flag);
int compareSignUnixMac(char *byte, char *source, char *prev, int flag);
void fromUnixMac(char sourceFile[], char destFile[], char *flagSource, char *flagDest, int flag, char *win);
void mission2And3(char sourceFile[], char destFile[], char flagSource[], char flagDest[], int flag);
int checkFlagOs(char* sourceFile);
int checkFlagSwap(char* sourceFile);
void setBytes(char bytes[],int flagUnix);
void setSigns(char flag[],char returnSign[], char returnSignFromWin[]);
void fromWin(char* sourceFile, char* destFile, char* srcMachine,char *destMachine,int flag, char *win);

//run ex2
int main(int argc, char *argv[] ) {
    //if it is mission 1
    if(argc == 3){
        //check if the files are correct
        if(strstr(argv[1],".")&&strstr(argv[2],".")) {
            char returnSign[2];
            returnSign[0] = '\000';
            returnSign[1] = '\000';
            fromUnixMac(argv[1], argv[2], NULL, NULL, 1, returnSign);
        }
        //mission 2
    } else if(argc == 5){
        if(strstr(argv[1],".")&&strstr(argv[2],".")) {
            if (checkFlagOs(argv[3]) && checkFlagOs(argv[4])) {
                mission2And3(argv[1], argv[2], argv[3], argv[4], 1);
            }
        }
        //mission 3+2:
    } else if(argc==6) {
        if (strstr(argv[1], ".") && strstr(argv[2], ".")) {
            //check if the rights flags are in place.
            if (checkFlagOs(argv[3]) && checkFlagOs(argv[4]) && checkFlagSwap(argv[5])) {
                if (strcmp(argv[5], "-swap") == 0) {
                    mission2And3(argv[1], argv[2], argv[3], argv[4], -1);
                } else {
                    mission2And3(argv[1], argv[2], argv[3], argv[4], 1);
                }
            }
        }
    }
    return 0;
}

/**
 * check if the flag :if swap or keep are at the command line args.
 */
int checkFlagSwap(char* sourceFile){
    if(strcmp(sourceFile,"-swap")==0){
        return 1;
    } else if(strcmp(sourceFile,"-keep")==0){
        return 1;
    }
    return  0 ;
}

/**
 * check if the flags of the OS are at the command line.
 */
int checkFlagOs(char* sourceFile){
    if(strcmp(sourceFile,"-unix")==0){
        return 1;
    } else if(strcmp(sourceFile,"-win")==0){
        return 1;
    } else if(strcmp(sourceFile,"-mac")==0){
        return 1;
    }
    return  0 ;
}
/**
 * swap between the bytes anf write them in the file.
 * @param destMachine - the OS of the dest file.
 * @param indexNull  - the null byte.
 * @param indexVal  - the byte with the value.
 * @param copyFile - the file that it writes on.
 */
void writeSwap(char destMachine[],int indexNull,int indexVal,FILE*copyFile){
    char first[1],second[1];
    first[0] = destMachine[indexNull];
    second[0] = destMachine[indexVal];
    fwrite(first, 1, 1, copyFile);
    fwrite(second, 1, 1, copyFile);
}
/**convert from win file to mac \ unix \ win files.
 * @param sourceFile - the source file from the command line.
 * @param destFile - the dest file from the command line.
 * @param srcMachine - the source OS from the command line.
 * @param destMachine - the dest file from the command line.
 * @param flag - flag if we want to swap
 * @param secondByteWin - the second byte of the sign of win.
 */
void fromWin(char* sourceFile, char* destFile, char* srcMachine,char *destMachine,int flag, char *secondByteWin) {
    char byte[2] ,prev[2], first[1],second[1];
    FILE *fileRead;
    FILE*copyFile;
    fileRead = fopen(sourceFile, "rb");
    copyFile = fopen(destFile, "wb");
    if (copyFile == NULL){
        fclose(fileRead);
        return;
    }
    prev[0] = '\000';
    prev[1] = '\000';
    int swapFlag = 0, firstLoop = 0, indexVal = 0, indexNull= 1;
    // if the file is not null
    if (fileRead != NULL) {
        //write the correct byte
        while (fread(byte, sizeof(byte), 1, fileRead)) {
            if(byte[1]==srcMachine[0]&&byte[0]==srcMachine[1]){
                swapFlag =1;
                indexNull=0;
                indexVal=1;
            }
            //if it is mission 2
            if (srcMachine != NULL && destMachine != NULL) {
                //check if prev is initialized
                if (compareSignWin(byte, srcMachine, prev, secondByteWin, swapFlag)) {
                    //if it is mission 2
                    if(flag ==1) {
                        if(swapFlag){
                            writeSwap(destMachine, indexVal,indexNull, copyFile);
                        } else {
                            fwrite(destMachine, sizeof(byte), 1, copyFile);
                        }
                        //if it is mission we need to swap
                    } else{
                        if(prev[indexVal] == '\r'&& byte[indexVal]=='\n') {
                            writeSwap(destMachine,indexNull,indexVal,copyFile);
                        } else{
                            writeSwap(byte,indexNull,indexVal,copyFile);
                        }
                    }
                    // if it is not the sign to replace
                } else {
                    // if we dont need to swap
                    if(flag==1) {
                        if(byte[indexVal]!='\r') {
                            fwrite(byte, sizeof(byte), 1, copyFile);
                        }
                    } else {
                        // if we need to swap
                        if(byte[indexVal]!='\r') {
                            char swap[2];
                            if (!swapFlag) {
                                writeSwap(byte,indexNull, indexVal,copyFile);
                            } else {
                                first[0] = byte[0];
                                second[0] = byte[1];
                                fwrite(second, 1, 1, copyFile);
                                fwrite(first, 1, 1, copyFile);
                            }
                        } if(byte[indexVal]!='\n' && prev[indexVal] == '\r'){
                            writeSwap(prev, indexNull,indexVal, copyFile);
                            writeSwap(byte, indexNull,indexVal, copyFile);
                        }
                    }
                }
                prev[0]= byte[0];
                prev[1] = byte[1];
            }
                // if it is mission 1
            else {
                if(flag==1) {
                    fwrite(byte, sizeof(byte), 1, copyFile);
                    //if it is mission 2 with swap
                } else if(flag==-1){
                    writeSwap(byte,indexNull, indexVal,copyFile);
                }
            }
            //if it is mission 3
        }
        fclose(fileRead);
        fclose(copyFile);
    }
}
/**convert from unix\mac file to mac \ unix \ win files.
 * @param sourceFile - the source file from the command line.
 * @param destFile - the dest file from the command line.
 * @param srcMachine - the source OS from the command line.
 * @param destMachine - the dest file from the command line.
 * @param flag - flag if we want to swap
 * @param secondByteWin - the second byte of the sign of win.
 */
void fromUnixMac(char *sourceFile, char *destFile, char *srcMachine, char *destMachine, int flag, char *secondByteWin) {
    char byte[2] ,prev[2], first[1],second[1];
    FILE *fileRead,*copyFile;
    fileRead = fopen(sourceFile, "rb");
    copyFile = fopen(destFile, "wb");
    if (copyFile == NULL){
        fclose(fileRead);
        return;
    }
    prev[0] = '\000';
    prev[1] = '\000';
    int swapFlag=0, firstloop=0, indexvalue=0, indexNull = 1;
    // if the file is not null
    if (fileRead != NULL) {
        //write the correct byte
        while (fread(byte, sizeof(byte), 1, fileRead)) {
            //if it is mission 2
            if (srcMachine != NULL && destMachine != NULL) {
                // if the file is already swaped
                if(byte[1] == srcMachine[0] && byte[0]==srcMachine[1]){
                    swapFlag = 1;
                    indexNull=0;
                    indexvalue=1;
                }
                //check if prev is initialized
                if (compareSignUnixMac(byte, srcMachine, prev, swapFlag)) {
                    //if it is mission 2
                    if(flag ==1) {
                        //if the file is swap already
                        if(swapFlag){
                            writeSwap(destMachine, 1,0,copyFile);
                        } else {
                            fwrite(destMachine, sizeof(byte), 1, copyFile);
                        }
                        if(swapFlag&&secondByteWin[0] != '\000'){
                            writeSwap(secondByteWin, 1,0,copyFile);
                        }else  if((!swapFlag)&&secondByteWin[0] != '\000'){
                            fwrite(secondByteWin, sizeof(byte), 1, copyFile);
                        }
                        //if it is mission we need to swap
                    } else {
                        writeSwap(destMachine, indexNull,indexvalue,copyFile);
                        if (secondByteWin[0] != '\000') {
                            writeSwap(secondByteWin, indexNull,indexvalue,copyFile);
                        }

                    }
                    // if it is not the sign to replace
                } else {
                    // if we dont need to swap
                    if(flag==1) {
                        fwrite(byte, sizeof(byte), 1, copyFile);
                    } else {
                        char swap[2];
                        swap[indexNull] = byte[indexvalue];
                        swap[indexvalue] = byte[indexNull];
                        fwrite(swap,sizeof(byte),1,copyFile);
                    }
                }
                strcpy(prev,byte);
            }
                // if it is mission 1
            else {
                if(flag==1) {
                    fwrite(byte, sizeof(byte), 1, copyFile);
                    //if it is mission 2 with swap
                } else if(flag==-1){
                        writeSwap(byte, indexNull,indexvalue,copyFile);
                }
            }
        }
        fclose(fileRead);
        fclose(copyFile);
    }
}

/**
 * compare between 2 Os's, when the first is win.
 * @param byte - the current byte.
 * @param source - the source file Sign.
 * @param prev - the prev byte.
 * @param sourceNext - if it is win the it is \n.
 * @param swapFlag - is we nees to swap the bytes.
 * @return int- if their equal - return 1, else: 0.
 */
int compareSignWin(char *byte, char *source, char *prev, char *sourceNext, int swapFlag){
    if(!swapFlag) {
        if (sourceNext[0] != '\000') {
            if (prev[0] == source[0] && byte[0] == sourceNext[0]) {
                return 1;
            } else {
                return 0;
            }
        } else if (byte[0] == source[0] || byte[1] == source[0]) {
            return 1;
        }
    } else{
        if (sourceNext[0] != '\000') {
            if (prev[1] == source[0] && byte[1] == sourceNext[0]) {
                return 1;
            } else {
                return 0;
            }
        }else if ((byte[1] == source[1] || byte[0] == source[1])) {
            return 1;
        }
    }
    //if they are not equal
    return 0;
}
/**
 * compare between 2 Os's, when the they are not win.
 * @param byte - the current byte.
 * @param source - the source file Sign.
 * @param prev - the prev byte.
 * @param swapFlag - is we nees to swap the bytes.
 * @return int- if their equal - return 1, else: 0.
 */
int compareSignUnixMac(char *byte, char *source, char *prev, int swapFlag){
    if(!swapFlag) {
        if(strcmp(byte,source)==0){
        //if (byte[0] == source[0] || byte[1] == source[0]) {
            return 1;
        }
    } else {
        if (byte[1] == source[0] || byte[0] == source[0]) {
            return 1;
        }
    }
    //if they are not eaqual
    return 0;
}
/**
 * set the signs of each OS,then send it to the right function.
 * @param sourceFile - source file
 * @param destFile - dest file.
 * @param flagSource - the flag of the source.
 * @param flagDest - the flag of the dest.
 * @param flag - swap flag.
 */
void mission2And3(char *sourceFile, char *destFile, char *flagSource, char *flagDest, int flag){
    char returnSignWin[2],returnSignFromWin[2];
    char srcSign[2], destSign[2], returnSign[2];
    returnSignWin[0] = '\000';
    returnSignWin[1] = '\000';
    returnSignFromWin[0] = '\000';
    returnSignFromWin[1] = '\000';
    if(strcmp(flagSource, flagDest)==0){
        fromUnixMac(sourceFile, destFile, flagSource, flagDest, flag, NULL);
    } else{
        setSigns(flagSource,returnSign, returnSignFromWin);
        strcpy(srcSign, returnSign);
        setSigns(flagDest,returnSign, returnSignWin);
        strcpy(destSign, returnSign);
        if(strcmp(flagSource, "-win")==0){
            fromWin(sourceFile,destFile, srcSign, destSign,flag, returnSignFromWin);
        } else {
            fromUnixMac(sourceFile, destFile, srcSign, destSign, flag, returnSignWin);
        }
    }
}
/**
 * set the value of the byte
 * @param bytes - the current byte
 * @param flagUnix - if it is unix OS.
 */
void setBytes(char bytes[],int flagUnix){
    char valueByte = '\r';
    if (flagUnix == 1){
        valueByte = '\n';
    }
    bytes[0] = valueByte;
    bytes[1] = '\000';
}
/**
 * set all of the signs for the Os
 * @param flag - OS flag
 * @param returnSign - the first 2 bytes.
 * @param returnSignFromWin - is it win - then it is \n.
 */
void setSigns(char flag[],char returnSign[], char returnSignFromWin[]){
    if(strcmp(flag, "-unix")==0){
        setBytes(returnSign,1);
    } else if(strcmp(flag, "-mac")==0){
        setBytes(returnSign,0);
    } else if(strcmp(flag, "-win")==0){
        setBytes(returnSign,0);
        setBytes(returnSignFromWin,1);
    }
}