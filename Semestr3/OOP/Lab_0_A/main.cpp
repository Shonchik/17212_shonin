#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace std; // Чтобы не писать std::cout можно просто написать эту функцию и мы сможем писать просто cout. 

	cout <<  "Hello world!" << "\n";
	
	cout << Module1::getMyName() << "\n";
	cout << Module2::getMyName2() << "\n";
	cout << Module3::getMyName3() << "\n";

	using namespace Module1;
	cout << getMyName() << "\n"; // (A)------John
	cout << Module2::getMyName2() << "\n";

	using namespace Module2; // (B)
	cout << getMyName2() << "\n"; // COMPILATION ERROR (C) Мы получается делаем 2 функции которые называются одинаково
	                              // и при вызове getMyName() он не знает к какому модулю обращаться. Для устранения 
						          // этой проблемы мы можем переименовать эту функцию в одном из модулей.

	using Module2::getMyName2;
	cout << getMyName2() << "\n"; // (D)------James

	using namespace Module3;
	cout << getMyName3() << "\n";

	using Module3::getMyName3;
	cout << getMyName3() << "\n";

}
