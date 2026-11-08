#include <stdio.h>
#include "counter.h"

static int count = 0;

static int clamp(int v){
	if(v > 1000) return 1000;
	return v; 
}

void counter_inc(void){
	count = clamp(count + 1);
}

int counter_get(void){
	return count;
}
