#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(1000, 500), "Running!");

	Texture f;
	f.loadFromFile("Paint/fon.png");
	Sprite fon(f);

	Texture e;
	e.loadFromFile("Paint/earth.png");
	Sprite earth[3];
	for (int i = 0; i < 3; i++) 
	{
		earth[i].setTexture(e);
		earth[i].setScale(1, 0.25);
		earth[i].setPosition(0, 150 + 150 * i);
	}

	Texture m;
	m.loadFromFile("Paint/man.png");
	Sprite man(m);
	man.setScale(0.8, 0.8);
	man.setTextureRect(IntRect(0, 0, 80, 130));
	float y = 200, frame = 0, py = 0, dy = 0, speed = 0.5;
	bool up = false, down = false, anim = true;

	Texture t;
	t.loadFromFile("Paint/text.png");
	Sprite text(t);
	text.setPosition(300, 50);
	float fx = 0;
	int game = 0;

	Texture b;
	b.loadFromFile("Paint/block.png");
	Sprite block[2];
	int bx[2], by[2], bty[2];
	for (int i = 0; i < 2; i++) 
	{
		block[i].setTexture(b);

		bx[i] = rand() % 3 + 1;
		by[i] = rand() % 2 + 1;
		bty[i] = rand() % 3 + 1;
		block[i].setTextureRect(IntRect(100 * (bx[i] - 1), 100 * (by[i] - 1), 100, 100));
		block[i].setPosition(1000 + 500 * i, 50 + 150 * (bty[i] - 1));
	}

	Texture go;
	go.loadFromFile("Paint/gameover.png");
	Sprite gameover(go);
	gameover.setPosition(400, 50);

	Texture sc;
	sc.loadFromFile("Paint/score.png");
	Sprite score[5];
	float fs[5];
	for (int i = 0; i < 5; i++) 
	{
		score[i].setTexture(sc);
		score[i].setTextureRect(IntRect(0, 0, 44, 55));
		score[i].setPosition(50 * i, 5);
		fs[i] = 0;
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					if (game == 0)
						game = 1;

			if (game == 1)
				if (event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Up) 
					{
						dy = -150;

						up = true;
					}
					else if (event.key.code == Keyboard::Down) 
					{
						dy = 150;

						down = true;
					}
		}

		if (game == 0) 
		{
			frame += 0.001;
			if (frame > 4)
				frame -= 4;
			man.setTextureRect(IntRect(80 * int(frame), 0, 80, 130));
		}
		else if (game == 1) 
		{
			if (py != dy) 
			{
				if (dy > 0) 
				{
					py = speed;
					dy = dy - speed;
				}
				if (dy < 0) 
				{
					py = -speed;
					dy = dy + speed;
				}

				y += py;

				anim = false;
			}

			else 
			{
				up = false;
				down = false;

				anim = true;
			}

			if (y < 55)
				y = 55;
			else if (y > 355)
				y = 355;

			if (anim) 
			{
				frame += 0.01;
				if (frame > 6)
					frame -= 6;
				switch (int(frame))
				{
				case 0:
					man.setTextureRect(IntRect(0, 135, 80, 130));
					break;
				case 1:
					man.setTextureRect(IntRect(80, 135, 90, 130));
					break;
				case 2:
					man.setTextureRect(IntRect(172, 135, 100, 130));
					break;
				case 3:
					man.setTextureRect(IntRect(0, 270, 88, 130));
					break;
				case 4:
					man.setTextureRect(IntRect(88, 270, 88, 130));
					break;
				case 5:
					man.setTextureRect(IntRect(172, 270, 90, 130));
					break;
				}
			}

			else 
			{
				if (up)
					man.setTextureRect(IntRect(0, 400, 80, 150));
				if (down)
					man.setTextureRect(IntRect(82, 400, 100, 150));
			}

			Vector2f eh[3];
			for (int i = 0; i < 3; i++) 
			{
				earth[i].move(-0.4, 0);

				eh[i] = earth[i].getPosition();
				if (eh[i].x < -800)
					earth[i].setPosition(0, 150 + 150 * i);
			}

			Vector2f bk[2];
			for (int i = 0; i < 2; i++) 
			{
				block[i].move(-0.4, 0);

				bk[i] = block[i].getPosition();
				if (bk[i].x < -100) 
				{
					bx[i] = rand() % 3 + 1;
					by[i] = rand() % 2 + 1;
					bty[i] = rand() % 3 + 1;
					block[i].setTextureRect(IntRect(100 * (bx[i] - 1), 100 * (by[i] - 1), 100, 100));
					block[i].setPosition(1000 + 500 * i, 50 + 150 * (bty[i] - 1));
				}

				if (man.getGlobalBounds().intersects(block[i].getGlobalBounds()))
					game = 2;
			}

			fs[4] += 0.01;
			if (fs[4] > 10) 
			{
				fs[4] -= 10;
				fs[3]++;
				if (fs[3] > 9) 
				{
					fs[3] -= 10;
					fs[2]++;
					if (fs[2] > 9) 
					{
						fs[2] -= 10;
						fs[1]++;
						if (fs[1] > 9) 
						{
							fs[1] -= 10;
							fs[0]++;
							if (fs[0] > 9)
								fs[0] -= 10;
							score[0].setTextureRect(IntRect(44 * int(fs[0]), 0, 44, 55));
						}
						score[1].setTextureRect(IntRect(44 * int(fs[1]), 0, 44, 55));
					}
					score[2].setTextureRect(IntRect(44 * int(fs[2]), 0, 44, 55));
				}
				score[3].setTextureRect(IntRect(44 * int(fs[3]), 0, 44, 55));
			}
			score[4].setTextureRect(IntRect(44 * int(fs[4]), 0, 44, 55));
		}

		else if (game == 2)
			man.setTextureRect(IntRect(190, 400, 100, 150));

		window.clear(Color::White);
		window.draw(fon);

		for (int i = 0; i < 3; i++)
			window.draw(earth[i]);

		man.setPosition(100, y);
		window.draw(man);

		if (game == 0) 
		{
			fx += 0.005;
			if (fx > 5)
				fx -= 5;
			if (fx < 3)
				window.draw(text);
		}

		for (int i = 0; i < 2; i++)
			window.draw(block[i]);

		if (game == 2)
			window.draw(gameover);

		for (int i = 0; i < 5; i++)
			window.draw(score[i]);

		window.display();
	}

	return 0;
}