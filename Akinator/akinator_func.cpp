#include "akinator.h"

const int LT_BUT_POSITION = 265;
const int LB_BUT_POSITION = 550;

const int X_BUT_SIZE = 250;
const int Y_BUT_SIZE = 100;

#pragma warning(disable : 4996)

void print_all_elements(tree_element* tmp, FILE* dump)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if(tmp->get_right())
	{
		print_all_elements(tmp->get_right(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp, tmp->get_right());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
	}
	if (tmp->get_left())
	{
		print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp, tmp->get_left());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
	}


    if((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
		fprintf(dump, "\"%p\" [label = \"<f0> value = [%.*s]|{<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp->get_left(), tmp->get_prev(), tmp->get_right());
	else
		if(tmp->get_prev() == nullptr)
			fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());
		else 
			fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());


    return;

}

void print_all_elements_beauty(tree_element* tmp, FILE* dump)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if (tmp->get_right())
	{
		print_all_elements_beauty(tmp->get_right(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp, tmp->get_right());
	}
	if (tmp->get_left())
	{
		print_all_elements_beauty(tmp->get_left(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp, tmp->get_left());
	}

	if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
		fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data());
	else
		if(tmp->get_prev() == nullptr)
			fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data());
		else
			fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data());
	return;
}

long size_of_file(FILE *user_code)
{
	assert(user_code);

	fseek(user_code, 0, SEEK_END);
	long file_length = ftell(user_code);
	fseek(user_code, 0, SEEK_SET);

	file_length++;

	return file_length;
}

using namespace sf;
void graphic_play()
{
	// ������������� 8-� ������� �����������
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	bool DRAW_BUTTON = true;
	bool NEED_MENU = false;
	bool REGIME_1 = true;

	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(800, 939), "Akinator", Style::Default, settings);


	// ������� ���������� ��������
	Texture texture;

	texture.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/backgraund.jpg");

	// ������� ������ � ������������� ��� ���� ��������
	Sprite sprite(texture);

	// ������������� ��� ���� - �������
	sprite.setColor(Color::Green);

	// ������� ������������� �������� 
	RectangleShape rectangle(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	rectangle.move(LT_BUT_POSITION, LB_BUT_POSITION);

	// ������������� ��� ����
	rectangle.setFillColor(Color(175, 180, 240));

	// ������� ������������� �������� 
	//RectangleShape rectangle2(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));


	Font font;
	font.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/CyrilicOld.TTF");

	Text text("", font, 50);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	text.setString("������");
	text.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10);

	Text exit_but("", font, 50);
	exit_but.setColor(Color::Magenta);
	exit_but.setStyle(Text::Bold);

	exit_but.setString("�����");
	exit_but.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10 + Y_BUT_SIZE + 10);


	Text regime1("", font, 50);
	regime1.setColor(Color::Blue);
	regime1.setStyle(Text::Bold);

	regime1.setString("��������");
	regime1.setPosition(120, 350);


	Text yes_text("��", font, 50);
	yes_text.setColor(Color::Green);
	yes_text.setStyle(Text::Bold);

	//	yes_text.setString("��");
	yes_text.setPosition(180, 450);

	Text no_text("���", font, 50);
	no_text.setColor(Color::Red);
	no_text.setStyle(Text::Bold);

	//	yes_text.setString("��");
	no_text.setPosition(170 + X_BUT_SIZE + 100, 450);


	RectangleShape yes_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	yes_rect.move(100, 440);

	// ������������� ��� ����
	yes_rect.setFillColor(Color(175, 180, 240));


	RectangleShape no_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	no_rect.move(100 + X_BUT_SIZE + 100, 440);

	// ������������� ��� ����
	no_rect.setFillColor(Color(175, 180, 240));


	RectangleShape reg1_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	reg1_rect.move(100, 340);

	// ������������� ��� ����
	reg1_rect.setFillColor(Color(175, 180, 240));

	RectangleShape exit_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	exit_rect.move(LT_BUT_POSITION, LB_BUT_POSITION + Y_BUT_SIZE + 10);

	// ������������� ��� ����
	exit_rect.setFillColor(Color(175, 180, 240));


	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{

		// �������� ���������� ������� ����� ������������ ���� ������ ����������
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x;
		int y = pos.y;

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{

			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();

			// ����������, ���� �� ������ ������ ����?
			if (event.type == Event::MouseButtonPressed)
			{
				// ���� ���� ������ ����� ������ ����, �� ��������� ������
				if (event.key.code == Mouse::Left)
				{
					//printf("x = %d,y = %d\n LT_BUT_POSITION = %d, LB_BUT_POSITION = %d\n", x, y, LT_BUT_POSITION, LB_BUT_POSITION);
					if (DRAW_BUTTON)
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
						{
							if ((LB_BUT_POSITION <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE))
							{
								//printf("ok\n");
								text.setColor(Color::Green);
								window.draw(text);

								DRAW_BUTTON = false;
								NEED_MENU = true;

								text.setColor(Color::Black);
								text.setString("�������� ����� ����:");

								text.move(-170, -330);

								// ���������� ��� � ������ �����
								rectangle.move(-170, -330);

								// ������������� ��� ����
								rectangle.setSize(sf::Vector2f(600, 100));
								rectangle.setFillColor(Color(175, 180, 240));
							}
							else if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
								window.close();
						}
					}
					else
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
						{
							if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
								window.close();
						}
						else if ((100 <= x) && (x <= 100 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_1 = true;
								text.setString("���?");
							}
						}
					}

				}
			}

		}
		// ��������� ����� ���� - �����
		window.clear(Color::White);


		// ��������� ����
		window.draw(sprite);

		// ��������� ������ play
		window.draw(rectangle);

		if (DRAW_BUTTON)
			window.draw(text);
		else if (NEED_MENU)
		{
			window.draw(text);

			window.draw(reg1_rect);
			window.draw(regime1);

		}
		else if (REGIME_1)
		{
			window.draw(text);

			window.draw(yes_rect);
			window.draw(no_rect);

			window.draw(yes_text);
			window.draw(no_text);

		}

		// EXIT BUTTON
		window.draw(exit_rect);
		window.draw(exit_but);


		// ��������� ����
		window.display();
	}
}