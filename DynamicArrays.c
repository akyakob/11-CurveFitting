#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "DynamicArrays.h"

void CreateDArray(DArray *DArrayHead, unsigned int InitialSize){
DArrayHead->Capacity = InitialSize;
DArrayHead->EntriesUsed = 0;
DArrayHead->Payload = (Data *)malloc(sizeof(Data) * DArrayHead->Capacity);
if(DArrayHead->Payload == NULL) {
	fprintf(stderr, "error to stderr");
	exit(1);
}
}

unsigned int PushToDArray(DArray *DArrayHead, Data *Payload){
if(DArrayHead->Capacity <= DArrayHead->EntriesUsed) {
	DArrayHead->Capacity = DArrayHead->Capacity + GROWTH_AMOUNT;
	DArrayHead->Payload = realloc(DArrayHead->Payload, DArrayHead->Capacity * sizeof(Data));
}
if(DArrayHead->Payload == NULL){
	fprintf(stderr,"error to stderr");
	exit(1);
}
memcpy(&(DArrayHead->Payload[DArrayHead->EntriesUsed]),Payload,sizeof(Data) );
DArrayHead->EntriesUsed = DArrayHead->EntriesUsed + 1;
return DArrayHead->EntriesUsed - 1;
}

void DestroyDArray(DArray *DArrayHead){
DArrayHead->Capacity = 0;
DArrayHead->EntriesUsed = 0;
free(DArrayHead->Payload);
DArrayHead->Payload = NULL;
}
#if 0
Data *SearchDArray(DArray *DArrayHead , char *String){
for(int i=0; i < DArrayHead->EntriesUsed; i++) {
   if(strncmp(DArrayHead->Payload[i].String, String, MAX_STR_LEN) == 0) {
   return(&(DArrayHead->Payload[i]));
   }
 }  
return(NULL);
}
#endif
