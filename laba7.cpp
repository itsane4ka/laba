#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <time.h>
#include <array>
#include <random>
#include <iomanip>
#include <sstream>
#include <thread>
#include <algorithm>
#include <functional>
#include <windows.h>
#include <ShellApi.h>

using namespace sf;

const int size = 120;

std::string operators[] = {
	// c++
 "if", "else", "switch", "case", "default", "break",  // 6
 "continue", "try", "goto", "catch", "const", "int", "long", "float", "double", "bool", // 16
 "for", "while", "array", "void", "include", "cmath", "cash", "programming", "pow", // 24
 "sizeof", "sqrt", "enum", "delete", "cmath", // 30
	// python
 "python", "print", "type", "int", "float", "class", "bool", "elif", "while", "input",
 "True", "const", "def", "range", "raise", "exeption", "except", "next", "list", "exit",
 "cmp", "import", "return", "if", "match", "zip", "remove", "insert", "nums", "plot" //60
	// javascript
 "alert", "forEach", "eval", "uneval", "isNan", "isFinite", "parseFloat", "parseInt",
 "decodeURI", "decodeURIComponent", "encodeURI", "escape", "unescape", "object", "function",
 "boolean", "symbol", "error", "EvalError", "TypeError", "RangeError", "number", "math", "string",
 "date", "RegExp", "Array", "Map", "Set", "WeakMap", "ArrayBuffer", // 90
	// html
 "html", "head", "body", "title", "bgcolor", "link", "u", "pre", "vlink", "h1", "b", "i", "em",
 "tt", "cite", "font", "blockquote", "ol", "li", "div align", "img","td", "tr", "table", "frameset",
 "form", "select", "textarea", "type", "strong" // 120
};

enum eLanguage {
	c_lang, py_lang, js_lang, html_lang
} language;

int getRandomOperator(enum eLanguage language)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int flag = 0;
	switch (language)
	{
	case c_lang:
		flag = gen() % 30;
		break;
	case py_lang:
		flag = gen() % 30 + 30;
		break;
	case js_lang:
		flag = gen() % 30 + 60;
		break;
	case html_lang:
		flag = gen() % 30 + 90;
		break;
	}
	return flag;
}

int FileWork(int words_score)
{
	// trying to get something from the file
	std::string buff;
	std::ifstream fin("record.txt");

	if (!fin.is_open())
	{
		std::cout << "Файл не может быть открыт!\n";
		return 0;
	}
	else
	{
		fin >> buff;
		if (buff == "")
			return words_score;
		else
		{
			int n = atoi(buff.c_str());
			if (words_score > n)
			{
				// getting new rec to the file
				std::string str_record = std::to_string(words_score);
				std::ofstream fout("record.txt");
				fout << words_score;
				fout.close();
				return words_score;
			}
			else
				return n;
		}
	}
}

void GetDataToFile(std::string username, std::string password)
{
	std::ofstream fout("data.txt");
	fout << username << "\n" << password;
	fout.close();
}

bool registration(std::fstream& fin)
{
	bool registrated = false;

	RenderWindow windowreg(VideoMode(700, 200), "IT-stamina");

	// figures angles sharpness 
	ContextSettings settings;
	settings.antialiasingLevel = 10;

	// top text output (about IT-stamina project)
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		exit(0);

	Texture back;
	back.loadFromFile("C:\\programming\\IT-stamina pro\\IT-stamina pro\\registration.png");

	Sprite background_s;
	background_s.setTexture(back);
	
	// username and password fields
	RectangleShape rectangle1(Vector2f(176.f, 30.f));
	rectangle1.move(242, 86);
	rectangle1.setFillColor(Color(175, 180, 240));

	RectangleShape rectangle2(Vector2f(176.f, 30.f));
	rectangle2.move(242, 148);
	rectangle2.setFillColor(Color(175, 180, 240));

	RectangleShape rectangle0(Vector2f(150.f, 33.f));
	rectangle0.move(260, 15);
	rectangle0.setFillColor(Color(175, 180, 240));

	// vertex line coursor (behind the cycle)
	Vertex line_without_thickness1[] =
	{
		Vertex(Vector2f(247.f, 91.f)),
		Vertex(Vector2f(247.f, 111.f))
	};
	line_without_thickness1->color = Color::White;

	Vertex line_without_thickness2[] =
	{
		Vertex(Vector2f(247.f, 152.f)),
		Vertex(Vector2f(247.f, 173.f))
	};
	line_without_thickness2->color = Color::White;

	// timing
	long long timing = 0;
	auto begin_timing = std::chrono::steady_clock::now();
	bool get_username = 0, get_password = 0;
	std::string username, password, trash, letter_entered, last_entered;
	int counter1 = 0, counter2 = 0;
	bool first_username_letter = false;
	bool first_password_letter = false;
	bool delete_once = true;

	// username text
	Text username_text;
	username_text.setFont(font);
	username_text.setString(username);
	username_text.setCharacterSize(20);
	username_text.setFillColor(Color::White);
	username_text.move(245, 86);

	// password text
	Text password_text;
	password_text.setFont(font);
	password_text.setString(username);
	password_text.setCharacterSize(20);
	password_text.setFillColor(Color::White);
	password_text.move(245, 150);

	while (windowreg.isOpen())
	{
		Event event;
		while (windowreg.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				registrated = false;
				return registrated;
			}

			if (event.type == Event::Resized)
			{
				std::cout << "trying to resize window" << std::endl;
				windowreg.setSize(Vector2u(700, 200));
			}
		}
		windowreg.clear(Color::White);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (rectangle1.getGlobalBounds().contains(windowreg.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
			{
				std:: cout << "got username" << std::endl;
				get_username = true;
				get_password = false;
				Sleep(500);
			}
			else if (rectangle2.getGlobalBounds().contains(windowreg.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
			{
				std::cout << "got password" << std::endl;
				get_password = true;
				get_username = false;
				Sleep(500);
			}
			else if (rectangle0.getGlobalBounds().contains(windowreg.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
			{
				if (username.size() > 4 && password.size() > 4)
				{
					GetDataToFile(username, password);
					Sleep(500);
					return true;
				}
			}
			else
			{
				get_password = false;
				get_username = false;
			}
		}

		// entering the username
		if (get_username)
		{
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode > 48)
				{
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					letter_entered = static_cast<char>(event.text.unicode);
					if (username.size() > 9)
						std::cout << "MISTAKE" << std::endl;
					else
					{
						if (letter_entered != last_entered)
						{
							counter1++;
							username += static_cast<char>(event.text.unicode);
							username_text.setString(username);
						}
					}
					last_entered = letter_entered;
					delete_once = true;
				}
				if (event.text.unicode == 8 && delete_once)
				{
					delete_once = false;
					std::cout << "deleting symbol" << std::endl;
					username.erase(username.size() - 1);
					username_text.setString(username);
				}
			}
		}

		// entering the password
		if (get_password)
		{
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode > 48)
				{
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					letter_entered = static_cast<char>(event.text.unicode);
					if (password.size() > 9)
						std::cout << "MISTAKE" << std::endl;
					else
					{
						if (letter_entered != last_entered)
						{
							counter1++;
							password += static_cast<char>(event.text.unicode);
							password_text.setString(password);
						}
					}
					last_entered = letter_entered;
					delete_once = true;
				}
				if (event.text.unicode == 8 && delete_once)
				{
					delete_once = false;
					std::cout << "deleting symbol" << std::endl;
					password.erase(password.size() - 1);
					password_text.setString(password);
				}
			}
		}

		// getting coursor
		auto end_timing = std::chrono::steady_clock::now();
		auto elapsed_ms_timing = std::chrono::duration_cast<std::chrono::milliseconds>(end_timing - begin_timing);
		timing = (float)elapsed_ms_timing.count() / 1000;
		std::cout << timing << std::endl;
		if (timing == 60)
			timing -= 59;

		// drawing
		windowreg.draw(background_s);
		if (timing % 2 == 0 && get_username && username.size() < 1)
			windowreg.draw(line_without_thickness1, 2, Lines);
		if (timing % 2 == 0 && get_password && password.size() < 1)
			windowreg.draw(line_without_thickness2, 2, Lines);
		windowreg.draw(username_text);  
		windowreg.draw(password_text);
		windowreg.display();
	}
}

int stamina()
{
	// obsiously, gendering the window function
	RenderWindow window(VideoMode(700, 200), "IT-stamina");

	// figures angles sharpness 
	ContextSettings settings;
	settings.antialiasingLevel = 10;

	// top text output (about IT-stamina project)
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		exit(0);
	Text text1;
	text1.setFont(font);
	text1.setString("This is IT-stamina! Train your code-typing skills with us and make your \nown records!");
	text1.setCharacterSize(22);
	text1.setFillColor(Color(0, 0, 0));
	text1.move(26, 25);

	// top text 
	Text choose_language;
	choose_language.setFont(font);
	choose_language.setString("Choose your programming language!");
	choose_language.setCharacterSize(30);
	choose_language.setFillColor(Color(255, 255, 255));
	choose_language.move(145, 15);
	choose_language.setOutlineThickness(1.f);
	choose_language.setOutlineColor(Color::Black);

	// c++
	Text c;
	c.setFont(font);
	c.setString("c++");
	c.setCharacterSize(30);
	c.setFillColor(Color(255, 255, 255));
	c.move(110, 65);
	c.setOutlineThickness(1.f);
	c.setOutlineColor(Color::Black);

	// rectangle c++
	RectangleShape rectanglec;
	rectanglec.setSize(Vector2f(70.f, 32.f));
	rectanglec.setOutlineThickness(2.f);
	rectanglec.setOutlineColor(Color::Black);
	rectanglec.setPosition(Vector2f(80.f, 70.f));

	// next button
	Texture next;
	next.loadFromFile("C:\\programming\\IT-stamina pro\\IT-stamina pro\\next.png");

	Sprite next_s;
	next_s.setTexture(next);
	next_s.setPosition(600, 145);

	// circle c
	CircleShape circleс(7.f);
	circleс.setFillColor(Color(255, 255, 255));
	circleс.setOutlineThickness(2.f);
	circleс.setOutlineColor(Color(0, 0, 0));
	circleс.move(85, 80);

	// circle c_choosed
	CircleShape circleс_choosed(5.f);
	circleс_choosed.setFillColor(Color(50, 50, 50));
	circleс_choosed.move(87, 82);

	// python
	Text py;
	py.setFont(font);
	py.setString("python");
	py.setCharacterSize(30);
	py.setFillColor(Color(255, 255, 255));
	py.move(110, 130);
	py.setOutlineThickness(1.f);
	py.setOutlineColor(Color::Black);

	// rectangle py
	RectangleShape rectanglepy;
	rectanglepy.setSize(Vector2f(115.f, 30.f));
	rectanglepy.setOutlineThickness(2.f);
	rectanglepy.setOutlineColor(Color::Black);
	rectanglepy.setPosition(Vector2f(80.f, 133.f));

	// circle py
	CircleShape circlepy(7.f);
	circlepy.setFillColor(Color(255, 255, 255));
	circlepy.setOutlineThickness(2.f);
	circlepy.setOutlineColor(Color(0, 0, 0));
	circlepy.move(85, 145);

	// circle py_choosed
	CircleShape circlepy_choosed(5.f);
	circlepy_choosed.setFillColor(Color(50, 50, 50));
	circlepy_choosed.move(87, 147);

	// java script
	Text js;
	js.setFont(font);
	js.setString("JavaScript");
	js.setCharacterSize(30);
	js.setFillColor(Color(255, 255, 255));
	js.move(520, 65);
	js.setOutlineThickness(1.f);
	js.setOutlineColor(Color::Black);

	//rectangle js
	RectangleShape rectanglejs;
	rectanglejs.setSize(Vector2f(155.f, 32.f));
	rectanglejs.setOutlineThickness(2.f);
	rectanglejs.setOutlineColor(Color::Black);
	rectanglejs.setPosition(Vector2f(490.f, 65.f));

	// circle js
	CircleShape circlejs(7.f);
	circlejs.setFillColor(Color(255, 255, 255));
	circlejs.setOutlineThickness(2.f);
	circlejs.setOutlineColor(Color(0, 0, 0));
	circlejs.move(495, 80);

	// circle js_choosed
	CircleShape circlejs_choosed(5.f);
	circlejs_choosed.setFillColor(Color(50, 50, 50));
	circlejs_choosed.move(497, 82);

	// html
	Text html;
	html.setFont(font);
	html.setString("HTML 5.0");
	html.setCharacterSize(30);
	html.setFillColor(Color(255, 255, 255));
	html.move(530, 130);
	html.setOutlineThickness(1.f);
	html.setOutlineColor(Color::Black);

	//rectangle html
	RectangleShape rectanglehtml;
	rectanglehtml.setSize(Vector2f(143.f, 32.f));
	rectanglehtml.setOutlineThickness(2.f);
	rectanglehtml.setOutlineColor(Color::Black);
	rectanglehtml.setPosition(Vector2f(490.f, 130.f));

	// circle html
	CircleShape circlehtml(7.f);
	circlehtml.setFillColor(Color(255, 255, 255));
	circlehtml.setOutlineThickness(2.f);
	circlehtml.setOutlineColor(Color(0, 0, 0));
	circlehtml.move(495, 145);

	// circle html_choosed
	CircleShape circlehtml_choosed(5.f);
	circlehtml_choosed.setFillColor(Color(50, 50, 50));
	circlehtml_choosed.move(497, 147);

	// timing bottom text
	Text maintime;
	maintime.setFont(font);
	maintime.setString("Timing: 60");
	maintime.setCharacterSize(22);
	maintime.setFillColor(Color(0, 0, 0));
	maintime.move(545, 160);

	// score bottom text
	int words_score = 0;
	Text score;
	score.setFont(font);
	score.setString("Score: 0");
	score.setCharacterSize(22);
	score.setFillColor(Color(0, 0, 0));
	score.move(27, 160);

	// help bottom text
	Text help;
	help.setFont(font);
	help.setString("Help?");
	help.setCharacterSize(24);
	help.setFillColor(Color(0, 0, 0));
	help.move(310, 160);
	help.setStyle(Text::Underlined);

	// rectangle help
	RectangleShape rectanglehelp;
	rectanglehelp.setSize(Vector2f(56.f, 24.f));
	rectanglehelp.setOutlineThickness(2.f);
	rectanglehelp.setOutlineColor(Color::Black);
	rectanglehelp.setPosition(Vector2f(307.f, 165.f));

	// score bottom text
	Text result;
	result.setFont(font);
	result.setString("Score: ");
	result.setCharacterSize(40);
	result.setFillColor(Color(247, 168, 24));
	result.setOutlineColor(Color::Black);
	result.setOutlineThickness(1.f);
	result.move(50, 20);

	// speed bottom text
	Text speed;
	speed.setFont(font);
	speed.setString("Speed: ");
	speed.setCharacterSize(40);
	speed.setFillColor(Color(247, 168, 24));
	speed.setOutlineColor(Color::Black);
	speed.setOutlineThickness(1.f);
	speed.move(50, 70);

	// mistakes bottom text
	Text mistakestxt;
	mistakestxt.setFont(font);
	mistakestxt.setString("Mistakes: ");
	mistakestxt.setCharacterSize(40);
	mistakestxt.setFillColor(Color(247, 168, 24));
	mistakestxt.setOutlineColor(Color::Black);
	mistakestxt.setOutlineThickness(1.f);
	mistakestxt.move(50, 120);

	// record bottom text
	Text recordtxt;
	recordtxt.setFont(font);
	recordtxt.setString("Your record: \n");
	recordtxt.setCharacterSize(40);
	recordtxt.setFillColor(Color(247, 168, 24));
	recordtxt.setOutlineColor(Color::Black);
	recordtxt.setOutlineThickness(1.f);
	recordtxt.move(460, 40);

	// game timing (real amount)
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	int leftTime = 10; // main start timing 
	int timing = 60;

	// rectangle render
	ConvexShape convex;
	window.draw(convex);
	RectangleShape rectangle(Vector2f(650.f, 50.f));
	rectangle.move(25, 100);
	rectangle.setFillColor(Color(255, 255, 255));
	rectangle.setOutlineThickness(2.f);
	rectangle.setOutlineColor(Color(209, 224, 255));

	// getting text from the app INPUT
	std::string letter_entered;
	std::string last_enterd = "stop";

	// creating texture
	Texture mainpic;
	mainpic.loadFromFile("C:\\programming\\IT-stamina pro\\IT-stamina pro\\choose.png");
	Sprite sprite(mainpic);

	// important variables
	bool same_elements = false;
	bool choosen = false;
	bool first_time = true;
	bool choosenreal = false;
	int AmountSymbols = 0;
	int startTime = 0;
	int GeneralSymbols = 0;
	int mistakes_per = 0;
	bool once_read = false;

	// main opening text from the app OUTPUT
	Text operatorstxt;
	operatorstxt.setFont(font);
	int AmountOperators = 3;
	std::string strwords;
	int flag = 0;

	// getting the first word black
	Text firstwordtxt;
	firstwordtxt.setFont(font);
	std::string firstword = "";

	//main cycle
	while (window.isOpen())
	{
		// game exit
		Event event;
		while (window.pollEvent(event))
		{
			// closing
			if (event.type == Event::Closed)
				window.close();
			
			// getting fixed size
			if (event.type == Event::Resized)
			{
				std::cout << "trying to resize window" << std::endl;
				window.setSize(Vector2u(700, 200));
			}

			// help
			rectanglehelp.setOutlineColor(Color::Black);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (rectanglehelp.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					rectanglehelp.setOutlineColor(Color::Red);
					ShellExecuteW(0, 0, L"https://itstamina.netlify.app", NULL, NULL, SW_SHOW);
				}
			}
		}

		if (!choosen)
		{
			// c++
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (rectanglec.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglec.setOutlineColor(Color::Red);
					c.setFillColor(Color(201, 201, 201));
					c.setStyle(Text::Underlined);
					language = c_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglepy.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglepy.setOutlineColor(Color::Red);
					py.setFillColor(Color(211, 211, 211));
					py.setStyle(Text::Underlined);
					language = py_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglejs.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglejs.setOutlineColor(Color::Red);
					js.setFillColor(Color(201, 201, 201));
					js.setStyle(Text::Underlined);
					language = js_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglehtml.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglehtml.setOutlineColor(Color::Red);
					html.setFillColor(Color(201, 201, 201));
					html.setStyle(Text::Underlined);
					language = html_lang;
					choosen = true;
					Sleep(500);
				}
			}
		}
		else if (choosen)
		{
			// getting time before beginnig
			if (first_time)
				startTime = gameTimeClock.getElapsedTime().asSeconds();
			if (first_time)
			{
				for (size_t i = 0; i < 4; i++)
				{
					flag = getRandomOperator(language);
					std::cout << operators[flag] << " " << flag << std::endl;
					strwords = strwords + operators[flag] + ' ';
					if (i == 0)
						firstword = operators[flag] + ' ';
				}
				operatorstxt.setString(strwords);
				operatorstxt.setCharacterSize(30);
				operatorstxt.setFillColor(Color(70, 70, 70));
				operatorstxt.move(40, 104);
				first_time = false;

				firstwordtxt.setString(firstword);
				firstwordtxt.setCharacterSize(30);
				firstwordtxt.setFillColor(Color(0, 0, 0));
				firstwordtxt.move(40, 104);
			}

			// getting text + check if it is a letter/number + main func
			window.setKeyRepeatEnabled(false);
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << " !! " << last_enterd << std::endl;
					letter_entered = static_cast<char>(event.text.unicode);

					// back gray text
					if (letter_entered != last_enterd && strwords[0] == letter_entered)
					{
						if (same_elements)
						{
							strwords.insert(strwords.begin() + 1, strwords[0]);
							firstword.insert(firstword.begin() + 1, firstword[0]);
						}
						same_elements = false;

						if (strwords[0] == strwords[1])
							same_elements = true;

						// deleting the entered symbol
						strwords.erase(strwords.begin());
						operatorstxt.setString(strwords);

						// deleting the first word 
						firstword.erase(firstword.begin());
						firstwordtxt.setString(firstword);

						std::cout << ".................." << std::endl;
						std::cout << "letter_entered " << letter_entered << std::endl;
						std::cout << "last_enterd " << last_enterd << std::endl;
						std::cout << "string " << strwords << std::endl;
						std::cout << ".................." << std::endl;

						// increasing the amount of symbols
						if (timing > 0)
						{
							AmountSymbols++;
							std::cout << "Amount symbols:  " << AmountSymbols << std::endl;
						}

						if (strwords[1] == ' ')
						{
							// adding new word if the last is done
							strwords = strwords + operators[getRandomOperator(language)] + ' ';
							operatorstxt.setString(strwords);
							words_score++;

							// making new word black
							for (int i = 2; i < strwords.size(); i++)
							{
								if (strwords[i] == ' ')
									break;
								else
									firstword = firstword + strwords[i];
							}
							firstword += ' ';
						}

						if (!same_elements)
							last_enterd = letter_entered;
						else
						{
							last_enterd = "trash";
							//strwords.insert(strwords.begin()+1, strwords[0]);
							same_elements = false;
						}
						once_read = true;
					}
					else if (letter_entered != last_enterd && strwords[0] != letter_entered && once_read)
					{
						GeneralSymbols++;
						once_read = false;
					}
				}
			}

			// getting correct time
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			timing = leftTime - gameTime + startTime;

			//convetring int to string and adding real timing
			std::string s1 = std::to_string(timing);
			maintime.setString("Timing: " + s1);

			//convetring int to string and adding real score / speed / mistakes
			std::string s2 = std::to_string(words_score);
			std::string s3 = std::to_string(AmountSymbols);
			score.setString("Score: " + s2);
			result.setString("Score: " + s2 + " op-s");
			speed.setString("Speed: " + s3 + " s/min");

			// view all text + pic output
			window.clear(Color(222, 202, 245, 0));
		}

		// vertex line coursor (behind the cycle)
		Vertex line_without_thickness[] =
		{
			Vertex(Vector2f(36.f, 110.f)),
			Vertex(Vector2f(36.f, 145.f))
		};
		line_without_thickness->color = Color::Black;

		if (!choosenreal)
		{
			// first window
			window.draw(sprite);
			window.draw(choose_language);
			// window.draw(rectanglec);
			window.draw(c);
			window.draw(circleс);
			// window.draw(rectanglepy);
			window.draw(py);
			window.draw(circlepy);
			// window.draw(rectanglejs);
			window.draw(js);
			window.draw(circlejs);
			// window.draw(rectanglehtml);
			window.draw(html);
			window.draw(circlehtml);

			window.draw(rectanglehelp);
			window.draw(help);

			if (choosen)
			{
				std::cout << "CHOICE MADE" << std::endl;
				std::cout << language << std::endl;
				switch (language)
				{
				case 0:
					std::cout << "looser" << std::endl;
					window.draw(circleс_choosed);
					break;
				case 1:
					window.draw(circlepy_choosed);
					break;
				case 2:
					window.draw(circlejs_choosed);
					break;

				case 3:
					window.draw(circlehtml_choosed);
					break;
				}
				window.display();
				Sleep(300);
			}
			else
				window.display();
		}
		else
		{
			if (timing > 0)
			{
				// second main window
				window.draw(rectangle);
				window.draw(rectanglehelp);
				if (timing % 2 == 0)
					window.draw(line_without_thickness, 2, Lines);
				window.draw(text1);
				window.draw(maintime);
				window.draw(operatorstxt);
				window.draw(firstwordtxt);
				window.draw(score);
				window.draw(help);
			}
			else
			{
				int a;
				if (AmountSymbols != 0)
					a = (int)GeneralSymbols * 100 / AmountSymbols;
				else
					a = 0;
				a = a - a / 100;
				std::string s5 = std::to_string(a);
				mistakestxt.setString("Mistakes: " + s5 + "%");

				//file
				int record_int = FileWork(words_score);
				std::string record_str = std::to_string(record_int);
				recordtxt.setString("Your record: \n\t\t\t   " + record_str);

				// getting
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (next_s.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
						break;
				}

				//third result window
				window.draw(sprite);
				window.draw(result);
				window.draw(speed);
				window.draw(recordtxt);
				window.draw(mistakestxt);

				// also draw help
				window.draw(next_s);
				window.draw(rectanglehelp);
				window.draw(help);

				return words_score;
			}
			window.display();
			if (timing < 0)
				Sleep(1000);
		}
		choosenreal = choosen;
	}
}

void racing(int res)
{
	system("cls");
	std::cout << "LOL " << res << std::endl;
}

int main()
{
	setlocale(LC_ALL, "rus");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool registrated = false;

	// checking file
	std::fstream fin;
	fin.open("data.txt", std::ios::in);
	if (!fin.is_open())
	{
		std::cout << "Can't open the file :D" << std::endl;
		registrated = registration(fin);
	}
	else
	{
		long file_size;
		fin.seekg(0, std::ios::end);
		file_size = fin.tellg();
		if (file_size == 0)
		{
			std::cout << "The file is empty :D" << std::endl;
			registrated = registration(fin);
		}
	}
	fin.close();

	if (registrated)
	{
		// getting to main file
		int res = stamina();
		racing(res);
	}

	system("Pause");
	return 0;
}
