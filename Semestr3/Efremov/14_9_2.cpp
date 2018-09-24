#include<iostream>
#include<cstdio>

using namespace std;

class tring{
private:
	char *str;
	int len;
	int len_now;

public:
	void append (char c) {
		len_now++;
		str[len_now] = c;
		if (len_now >= len) {
			str = (char *)realloc(str, len * 2);
			len *= 2;// to do: fix me
		}
	}

	void init(int size){
		len = size;
		str = (char *)malloc(size);
		len_now = 0;
	}

	void freee(){
		free(str);
	}

};

int main (){
	tring str; 
	str.init(100);
	char c = 1;
	while (c != '\n') {
		c = getchar();
		cout << c;
		str.append(c);
	}

	str.freee();

	return 0;
}