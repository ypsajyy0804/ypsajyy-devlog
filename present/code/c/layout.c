#include <stdio.h>

struct Emp {
    char   name[12];
    int    age;
    double salary;
    char   grade;
};

int main(){
	struct Emp e;

	printf("sizeof = %zu\n", sizeof(e));
	printf("name = %td\n", (char*)&e.name - (char*)&e);
	printf("age = %td\n", (char*)&e.age - (char*)&e);
	printf("salary = %td\n", (char*)&e.salary - (char*)&e);
	printf("grade = %td\n", &e.grade - (char*)&e);

	return 0;
}
