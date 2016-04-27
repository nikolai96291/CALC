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

enum GL_state { PLUS, MULTI, SUBTR, DIV, RESULT};
GL_state state = RESULT;
float a, b;
bool ch=false;

string int_to_string(int n)
{
	stringstream s;
	s << n;
	return s.str();
}
int string_to_int(string s)
{
	return(atoi(s.c_str()));
}
void Choise_states(Fl_Input* input)
{
	string inp = input->value();
	switch (state)
	{
	case PLUS:
		a = a + string_to_int(inp);
		input->value(int_to_string(a).c_str());
		break;
	case SUBTR:
		a = a - string_to_int(inp);
		input->value(int_to_string(a).c_str());
		break;
	case RESULT:
		a = string_to_int(inp);
		break;
	case MULTI:
		a = a * string_to_int(inp);
		input->value(int_to_string(a).c_str());
		break;
	case DIV:
		a = a / string_to_int(inp);
		input->value(int_to_string(a).c_str());
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
		Choise_states(input);
		state = PLUS;
		ch = true;
		break;
	case '-':
		Choise_states(input);
		state = SUBTR;
		ch = true;
		break;
	case '*':
		Choise_states(input);
		state = MULTI;
		ch = true;
		break;
	case '/':
		Choise_states(input);
		state = DIV;
		ch = true;
		break;
	case '=':
		Choise_states(input);
		state = RESULT;
		break;
	case 'C':
		input->value('\0');
		a = 0;
		break;
	default:
		if ( ch==true)
		{
			input->value('\0');
			ch = false;
		}
		string inp = input->value();
		inp = inp + but;
		input->value(inp.c_str());
		break;

	}
}
void Button_C(Fl_Widget* b, void* data)
{
	Fl_Input* input = (Fl_Input*)data;
	Fl_Button* bt = (Fl_Button*)b;
	string but = bt->label();
	
	Use_states(but,input);
}

int main()
{
	Fl_Window win(330, 420, "Rainbow");
	win.begin();
	Fl_Input inp(160, 50, 120, 30);
	Fl_Button bt1(10, 100, 300, 300, "C");
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
