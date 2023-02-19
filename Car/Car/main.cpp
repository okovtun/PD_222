#include<iostream>
#include<conio.h>
#include<thread>
#include<Windows.h>
using namespace std;
using namespace std::literals::chrono_literals;

//#define MIN_TANK_VOLUME 20
//#define MAX_TANK_VOLUME 80
//# показывает, что дальше идет директива
//Директива - это указание компилятору на выполнение некоторых действий,
//Например, директива #include (включить в состав, подключить) указывает компилятору на то, что к нашему исходному файлу нужно подключить другой файл.
//Директива #define (определить) создает макоопределение (макрос) типа ИМЯ ЗНАЧЕНИЕ,
//и везде где компилятор видет имя макроса вставляет значение макроса.

#define Enter	13
#define Escape	27

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
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
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
	double get_consumption_per_second(int speed)
	{
		if (speed > 200) consumption_per_second = CONSUMPTION * 3e-5 * 10;
		else if (speed > 140)consumption_per_second = CONSUMPTION * 3e-5*8.33333;
		else if (speed > 100)consumption_per_second = CONSUMPTION * 3e-5*6.66666;
		else if (speed > 60)consumption_per_second = CONSUMPTION * 3e-5*4.66666;
		else if (speed > 0)consumption_per_second = CONSUMPTION * 3e-5*6.66666;
		else consumption_per_second = CONSUMPTION * 3e-5;
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

class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	static const int MAX_SPEED_LOW_LIMIT = 90;
	static const int MAX_SPEED_HIGH_LIMIT = 390;
	int speed;
	const int MAX_SPEED;
	struct Control
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
	}threads;
public:
	Car(int volume, int consumption, int max_speed = 250) :tank(volume), engine(consumption),
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed > MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed
		)
	{
		driver_inside = false;
		speed = 0;
		cout << "Your car is ready, press Enter to get in" << endl;
	}
	~Car()
	{
		cout << "Car is over" << endl;
	}

	//			Methods:
	void get_in()
	{
		driver_inside = true;
		threads.panel_thread = std::thread(&Car::panel, this);	//Запускаем метод panel() в потоке panel_thread
	}
	void get_out()
	{
		driver_inside = false;
		if (threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "You are out of your car" << endl;
	}
	void start_engine()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_edle, this);
		}
	}
	void stop_engine()
	{
		if (driver_inside)
		{
			engine.stop();
			if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();
		}
	}
	void accellerate()
	{
		if (engine.started() && speed < MAX_SPEED)
		{
			speed += 10;
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			std::this_thread::sleep_for(1s);
		}
		if (!threads.free_wheeling_thread.joinable())
			threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
	}
	void slow_down()
	{
		if (speed > 0)
		{
			speed -= 10;
			if (speed <= 0) speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void control()
	{
		char key = 0;
		do
		{
			key = 0;
			if (_kbhit())key = _getch();
			switch (key)
			{
			case 'W':case 'w':accellerate();	break;
			case 'S':case 's':slow_down();		break;
			case Enter: driver_inside ? get_out() : get_in(); break;
			case 'I':case 'i':	//Ignition - зажигание
				engine.started() ? stop_engine() : start_engine();
				break;
			case 'F':case'f':
				if (driver_inside)cout << "Надо выйти их машины" << endl;
				else
				{
					double amount;
					cout << "Введите объем топлива: "; cin >> amount;
					tank.fill(amount);
				}
			case Escape:
				stop_engine();
				get_out();
			}
			if (tank.get_fuel_level() == 0)stop_engine();
			if (speed <= 0)speed = 0;
			if (speed == 0 && threads.free_wheeling_thread.joinable())threads.free_wheeling_thread.join();
		} while (key != Escape);
	}
	void engine_edle()
	{
		//Холостой ход двигателя
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second(speed)))
		{
			std::this_thread::sleep_for(1s);
		}
	}
	void free_wheeling()
	{
		while (--speed > 0)
		{
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void panel()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//Получаем обработчик окна консоли
		while (driver_inside)
		{
			system("CLS");
			for (int i = 0; i < MAX_SPEED / 3; i++)
			{
				if (i > 50)SetConsoleTextAttribute(hConsole, 0x0E);
				if (i > 66)SetConsoleTextAttribute(hConsole, 0x0C);
				cout << (i <= speed / 3 ? "|" : ".");
				SetConsoleTextAttribute(hConsole, 0x7);
			}
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << endl;
			cout << "Speed: " << speed << " km/h\n";
			cout << "Fuel level:\t" << tank.get_fuel_level() << " liters\t";
			if (tank.get_fuel_level() < 5)
			{
				SetConsoleTextAttribute(hConsole, 0xCF);	//0xCF:'C'- красный фон, 'F'- белые буквы.
				cout << "LOW FUEL";
				SetConsoleTextAttribute(hConsole, 0x07);	//0xCF:'0'- черный фон, '7'- серые буквы.
			}
			cout << endl;
			cout << "Consumption per second: " << engine.get_consumption_per_second(speed) << " liters.\n";
			cout << "Engine " << (engine.started() ? "started" : "stopped") << "\n";
			std::this_thread::sleep_for(1s);
		}
	}

	void info()const
	{
		tank.info();
		engine.info();
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

	Car bmw(80, 10);
	bmw.info();

	bmw.control();
}