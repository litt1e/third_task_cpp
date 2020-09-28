#include <iostream>
#include <string>
using namespace std;

class Time
{
public:
	int hours;
	int minutes;
	friend bool operator> (const Time& t1, const Time& t2);
	friend bool operator< (const Time& t1, const Time& t2);
	friend bool operator== (const Time& t1, const Time& t2);
	Time(int h, int m)
	{
		hours = ((h <= 23) && (h >= 0)) ? h : fmin(23, fmax(0, h));
		minutes = ((m <= 59) && (m >= 0)) ? m : fmin(59, fmax(0, m));
	};
	void AddHours(int h)
	{
		if ((hours + h) / 24 >= 1)
		{
			hours = (hours + h) - (hours + h) * 24;
		}
		else
		{
			hours += h;
		}
	};
	void AddMinutes(int m)
	{
		if (((minutes + m) / 60.0) >= 1)
		{
			minutes += m;
			hours += minutes / 60;
			minutes -= (minutes / 60) * 60;
		}
		else
		{
			minutes += m;
		}
	};
	void add_time(int h, int m)
	{
		AddMinutes(m);
		AddHours(h);
	};
};

bool operator> (const Time &t1, const Time &t2)
{
	bool result = false;
	if (t1.hours > t2.hours)
	{
		result = true;
	}
	else if ((t1.hours == t2.hours) && (t1.minutes > t2.minutes))
	{
		result = true;
	}
	return result;
}

bool operator< (const Time& t1, const Time& t2)
{
	bool result = false;
	if (t1.hours < t2.hours)
	{
		result = true;
	}
	else if ((t1.hours == t2.hours) && (t1.minutes < t2.minutes))
	{
		result = true;
	}
	return result;
}

bool operator== (const Time& t1, const Time& t2)
{
	return ((t1.hours == t2.hours) && (t1.minutes == t2.minutes));
}

Time add_lesson_time(Time time)
{
	time.add_time(1, 20);
	return time;
}

Time add_break_time(Time time, bool isWeekday)
{
	if (isWeekday)
	{
		time.AddMinutes(15);
	}
	else
	{
		time.AddMinutes(10);
	}
	return time;
}

string get_current_lesson(Time time, bool isWeekdway)
{
	int lesson = 0;
	string result = "";
	bool isLesson = true;
	for (Time beginning = Time(8, 0); beginning < time; lesson++)
	{
		beginning = add_lesson_time(beginning);
		bool a = beginning < time;
		if (beginning < time)
		{
			beginning = add_break_time(beginning, isWeekdway);
			isLesson = beginning > time ? false : true;
			lesson = beginning == time ? lesson + 1 : lesson;
		}
		if (lesson > 6)
		{
			break;
		}
	}
	if (lesson > 6)
	{
		result = "Пары закончились";
	}
	else if (!isLesson)
	{
		result = "Сейчас идёт перемена.";
	}
	else if (Time(8, 0) > time)
	{
		result = "Пары еще не начались";
	}
	else
	{
		result = "Сейчас идет " + to_string(lesson);
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "russian");
	int usual_days[4] = {1,2,3,5};
	while (true)
	{
		cout << "Чтобы узнать, какая сейчас идет пара, выберите день недели и введите время. Для выхода " << endl;
		int day, hours, minutes;
		while (true)
		{
			cout << "1) Понедельник\n2) Вторник\n3) Среда\n4) Четверг\n5) Пятница\n6) Суббота\n7) Воскресенье\nВыберите день недели(введите число от 1 до 7):" << endl;
			cin >> day;
			if ((day <= 7) && (day >= 1))
			{
				break;
			}
			else
			{
				cout << "Выбрано неверное число" << endl;
				continue;
			}
		}

		while (true)
		{
			cout << "Введите час(от 0 до 23)" << endl;
			cin >> hours;
			if ((hours >= 0) && (hours <= 23))
			{
				break;
			}
			else
			{
				cout << "Введенное число не соответствует диапозону от 0 до 23" << endl;
				continue;
			}
		}

		while (true)
		{
			cout << "Введите минуты(от 0 до 59)" << endl;
			cin >> minutes;
			if ((minutes >= 0) && (minutes <= 59))
			{
				break;
			}
			else
			{
				cout << "Введенное число не соответствует диапозону от 0 до 59" << endl;
				continue;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (day == usual_days[i])
			{
				day = -2;
				break;
			}
		}
		switch (day)
		{
			case (-2):
			{
				cout << get_current_lesson(Time(hours, minutes), true) << endl;
				break;
			}
			case (4):
			{
				cout << "Сегодня физ-ра" << endl;
				break;
			}
			case (6):
			{
				cout << get_current_lesson(Time(hours, minutes), false) << endl;
				break;
			}
			case (7):
			{
				cout << "Сегодня выходной" << endl;
				break;
			}
		}
		cout << "\n\n\n____________________\n\n";
	}
}


