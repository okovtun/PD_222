#include<iostream>
#include<conio.h>
using namespace std;

//#define MIN_TANK_VOLUME 20
//#define MAX_TANK_VOLUME 80
//# показывает, что дальше идет директива
//Директива - это указание компилятору на выполнение некоторых действий,
//Например, директива #include (включить в состав, подключить) указывает компилятору на то, что к нашему исходному файлу нужно подключить другой файл.
//Директива #define (определить) создает макоопределение (макрос) типа ИМЯ ЗНАЧЕНИЕ,
//и везде где компилятор видет имя макроса вставляет значение макроса.

class Tank
{
	static const int MIN_TANK_VOLUME = 20;
	static const int MAX_TANK_VOLUME = 80;

	const int VOLUME;	//объем бака
	double fuel_level;	//уровень топлива
public:
	int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
		true;
	}
	Tank(int volume) :VOLUME
	(
		volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
		volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
		volume
	)
	{
		//this->VOLUME = volume;
		this->fuel_level = 0;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tank()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void fill(double amount)
	{
		if (amount < 0)return;
		if (fuel_level + amount > VOLUME)fuel_level = VOLUME;
		else fuel_level += amount;
	}
	void info()const
	{
		cout << "Volume:    " << VOLUME << endl;
		cout << "Fuel level:" << fuel_level << endl;
	}
};

class Engine
{
	static const int MIN_ENGINE_CONSUMPTION = 3;
	static const int MAX_ENGINE_CONSUMPTION = 30;

	const double CONSUMPTION;
	double consumption_per_second;
	bool is_started;
public:
	double get_CONSUMPTION()const
	{
		return this->CONSUMPTION;
	}
	double get_consumption_per_second()const
	{
		return this->consumption_per_second;
	}
	Engine(int consumption) :CONSUMPTION
	(
		consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
		consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
		consumption
	)
	{
		consumption_per_second = CONSUMPTION * 3e-5;	//3*10^-5
		is_started = false;
		cout << "EConstructor:\t" << this << endl;
	}
	~Engine()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}

	void info()const
	{
		cout << "Consumption per 100 km:  " << CONSUMPTION << " liters\n";
		cout << "Consumption per 1 second:" << consumption_per_second << " liters\n";
	}
};

//#define TANK_CHECK
//Некоторым макросам дают только имя, и не дают никакого значения,
//такие макросы используются с директивами условной компиляции #ifdef ... #endif
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#if defined TANK_CHECK
	//Если определено TANK_CHECK, то нижеследующий код до директивы #endif будет виден компилятору.
	Tank tank(40);
	tank.info();
	do
	{
		int fuel;
		cout << "Введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (_getch() != 27);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK


}