#include<iostream>
#include<cstdio>

using namespace std;

struct tring{
	char *str;
	int len;
	int len_now;
};

void append (struct tring *str, char c) {
	str->len_now++;
	str->str[str->len_now] = c;
	if (str->len_now >= str->len) {
		str->str = (char *)realloc(str->str, str->len * 2);
		str->len *= 2;// to do: fix me
	}
}

void init(struct tring * str, int size){
	str->len = 10;
	str->len_now = 0;
}

void freee(struct tring *str){
	free(str->str);
}

int main (){
	struct tring str; 
	str.str = (char *)calloc(1, sizeof(char));
	init(&str, 100);
	char c = 1;
	while (c != '\n') {
		c = getchar();
		cout << c;
		append(&str, c);
	}

	cout << str.str << endl;

	freee(&str);

	return 0;
}