#include<iostream>
#include<thread>
#include<chrono>
using std::cin;
using std::cout;
using std::endl;
using namespace std::literals::chrono_literals;

bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);
	}
}
void Minus()
{
	while (!finish)
	{
		cout << "- ";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	setlocale(LC_ALL, "");
	int a(5);
	std::thread thread_plus(Plus);
	std::thread t_minus(Minus);
	cin.get();	//Функция
	finish = true;
	if(thread_plus.joinable())thread_plus.join();
	if(t_minus.joinable())t_minus.join();
}