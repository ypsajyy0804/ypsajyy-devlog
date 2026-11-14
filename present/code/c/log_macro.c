#include <stdio.h>

#define LOG(msg) printf("[%s:%d] %s\n", __FILE__, __LINE__, msg)

int main(){
#ifdef DEBUG
	LOG("start");
	LOG("big");
	LOG("done");
#endif

	return 0;
}
