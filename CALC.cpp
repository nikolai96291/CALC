#include "fltkopt.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Text_Display.H>
#include <iostream>
#include <sstream>

using namespace std;

enum GL_state { PLUS, MULTI, SUBTR, DIV, RESULT };
GL_state state = RESULT;
GL_state state1 = RESULT;
int kk = 0;
double a = 0, b;
bool ch = false, point = false;

string double_to_string(double n)
{
	if (n > -0.00001 && n < 0.00001)
		n = 0;
	stringstream s;
	s << n;
	return s.str();
}
double string_to_double(string s)
{
	double c;
	c = atoi(s.c_str());
	double k;
	string s_double;
	bool n = false;
	for (string::iterator i = s.begin(); i != s.end(); i++)
	{
		if (n)
			s_double = s_double + *i;
		if (*i == '.')
			n = true;
	}
	int len = s_double.length();
	k = atoi(s_double.c_str());
	for (int i = 0; i < len; i++)
		k = k / 10;
	c = c + k;
	return c;
}
void Choise_states(Fl_Input* input)
{
	string inp = input->value();
	switch (state)
	{
	case PLUS:
		a = a + string_to_double(inp);
		input->value(double_to_string(a).c_str());
		break;
	case SUBTR:
		a = a - string_to_double(inp);
		input->value(double_to_string(a).c_str());
		break;
	case RESULT:
		a = string_to_double(inp);
		break;
	case MULTI:
		a = a * string_to_double(inp);
		input->value(double_to_string(a).c_str());
		break;
	case DIV:
		if (-0.001 < string_to_double(inp) && string_to_double(inp) < 0.001)
		{
			if (kk == 0)
				input->value("I CAN'T DO THIS");
			if (kk == 1)
				input->value("I SAID, THAT I CAN'T");
			if (kk == 2)
				input->value("OH... COME ON");
			if (kk > 2)
				input->value("JUST CLOSE ME");
			kk++;
		}
		else
		{
			a = a / string_to_double(inp);
			input->value(double_to_string(a).c_str());
		}
		break;
	default:
		break;
	}
}
void Use_states(string but_s, Fl_Input* input)
{
	char but = but_s[0];
	switch (but)
	{
	case '+':
		state1 = PLUS;
		ch = true;
		break;
	case '-':
		state1 = SUBTR;
		ch = true;
		break;
	case '*':
		state1 = MULTI;
		ch = true;
		break;
	case '/':
		state1 = DIV;
		ch = true;
		break;
	case '=':
		Choise_states(input);
		a = 0;
		state = RESULT;
		ch = true;
		break;
	case 'C':
		input->value('\0');
		a = 0;
		state = RESULT;
		state1 = RESULT;
		break;
	default:
		switch (state1)
		{
		case PLUS:
		{
			if (ch == true)
			{
				Choise_states(input);
				state = PLUS;
				input->value('\0');
				ch = false;
				point = false;
			}
			if (but != '.' || point == false)
			{
				string inp = input->value();
				inp = inp + but;
				input->value(inp.c_str());
				if (but == '.')
					point = true;
			}
		}
		break;
		case SUBTR:
		{
			if (ch == true)
			{
				Choise_states(input);
				state = SUBTR;
				input->value('\0');
				ch = false;
				point = false;
			}
			if (but != '.' || point == false)
			{
				string inp = input->value();
				inp = inp + but;
				input->value(inp.c_str());
				if (but == '.')
					point = true;
			}
		}
		break;
		case MULTI:
		{
			if (ch == true)
			{
				Choise_states(input);
				state = MULTI;
				input->value('\0');
				ch = false;
				point = false;
			}
			if (but != '.' || point == false)
			{
				string inp = input->value();
				inp = inp + but;
				input->value(inp.c_str());
				if (but == '.')
					point = true;
			}
		}
		break;
		case DIV:
		{
			if (ch == true)
			{
				Choise_states(input);
				state = DIV;
				input->value('\0');
				ch = false;
				point = false;
			}
			if (but != '.' || point == false)
			{
				string inp = input->value();
				inp = inp + but;
				input->value(inp.c_str());
				if (but == '.')
					point = true;
			}
		}
		break;
		default:
		{
			if (but != '.' || point == false)
			{
				string inp = input->value();
				inp = inp + but;
				input->value(inp.c_str());
				if (but == '.')
					point = true;
			}
		}
		break;
		}
	}
}
void Button_C(Fl_Widget* b, void* data)
{
	Fl_Input* input = (Fl_Input*)data;
	Fl_Button* bt = (Fl_Button*)b;
	string but = bt->label();

	Use_states(but, input);
}

int main()
{
	Fl_Window win(330, 420, "Rainbow");
	win.begin();
	Fl_Input inp(160, 50, 120, 30);
	Fl_Button bt1(10, 100, 300, 300, "C");
	bt1.color(5);
	bt1.color2(6);
	bt1.callback(Button_C, &inp);
	//bt1.callback(Button_Func, 0);
	for (int i = 0; i < 10; i++)
	{
		char* c = new char[2];
		c[0] = '0' + i;
		c[1] = '\0';
		Fl_Button* bt = new Fl_Button(10 + i * 30, 10, 30, 30, c);
		bt->callback(Button_C, &inp);
	}
	Fl_Button sum(10, 50, 30, 30, "+");
	sum.callback(Button_C, &inp);
	Fl_Button sum1(40, 50, 30, 30, "-");
	sum1.callback(Button_C, &inp);
	Fl_Button mult(70, 50, 30, 30, "*");
	mult.callback(Button_C, &inp);
	Fl_Button mult1(100, 50, 30, 30, "/");
	mult1.callback(Button_C, &inp);
	Fl_Button c(130, 50, 30, 30, "=");
	c.callback(Button_C, &inp);
	Fl_Button point(280, 50, 30, 30, ".");
	point.callback(Button_C, &inp);
	win.end();
	win.show();
	return Fl::run();
}
