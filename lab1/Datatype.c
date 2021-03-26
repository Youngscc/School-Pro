# include <stdio.h>

struct sample_struct {
	char a;
	int b;
} struct_sample;

union sample_union {
	int a;
	char b;
} union_sample;

enum sample_enum {
	sun=1,mon,tue,wen,thu,fri,sat
} enum_sample;

void show_byte(unsigned char* start,int len){
	int i;
	for (i=0; i<len; ++i) printf("%.2X ",start[i]);
	puts("");
}

void print_short(short a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[short]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%d\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_int(int a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[int]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%d\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_long(long long a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[long long]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%lld\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_float(float a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[float]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%f\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_double(double a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[double]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%lf\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_char(char a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[char]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%c\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_struct(struct sample_struct a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[struct]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\ta=%c b=%d\n", a.a, a.b);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_union(union sample_union a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[union]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\ta=%d b=%c\n", a.a, a.b);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_enum(enum sample_enum a, char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[enum]:\n");
	printf("var name:\t%s\n", name);
	printf("var value:\t%d\n", a);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(a));
	puts("------------------******------------------");
}

void print_main(char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[main]:\n");
	printf("var name:\t%s\n", name);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(addr));
	puts("------------------******------------------");
}

void print_printf(char *name, void *addr) {
	puts("------------------******------------------");
	puts("datatype[printf]:\n");
	printf("var name:\t%s\n", name);
	printf("var addr:\t%p\n", addr);
	printf("var byte:\t");
	show_byte((unsigned char*)addr, sizeof(addr));
	puts("------------------******------------------");
}

int main(){
	short varshort = 30;
	int varint = 1190200122;
	long long varlong = 11111111111111LL;
	float varfloat = 20001019.00;
	double vardouble = 20001029.00;
	char varchar = '?';
	struct_sample.a = '!', struct_sample.b = 2;
	union_sample.a = 1, union_sample.b = '$';
	enum_sample =wen;
	print_short(varshort,"varshort",&varshort);
	print_int(varint,"varint",&varint);
	print_long(varlong,"varlong",&varlong);
	print_float(varfloat,"varfloat",&varfloat);
	print_double(vardouble,"vardouble",&vardouble);
	print_char(varchar,"varchar",&varchar);
	print_struct(struct_sample,"struct_sample",&struct_sample);
	print_union(union_sample,"union_sample",&union_sample);
	print_enum(enum_sample,"enum_sample",&enum_sample);
	print_main("main",&main);
	print_printf("printf",&printf);
	return 0;
} 
