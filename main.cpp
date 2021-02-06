#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>




using namespace sf;

class Enemy
{
public:
	int hp;
	int hpmax ;
	Sprite  Shape ;
	float speedx =7;
	float speedy =0;

	Enemy(Texture *texture , Vector2u windowsize )
	{
		this-> hpmax = rand()%3 + 1;
		this->hp = this->hpmax ;
		this->Shape.setTexture(*texture);
		this->Shape.setScale(0.15f, 0.15f);
		this->Shape.setPosition(rand()%windowsize.x - this->Shape.getGlobalBounds().width, rand()%200 -this->Shape.getGlobalBounds().height);

	}

	~Enemy(){}

};

class Enemy2
{
public:
	int hp;
	int hpmax ;
	Sprite  Shape ;
	float speedx =7;
	float speedy =0;

	Enemy2(Texture *texture , Vector2u windowsize )
	{
		this-> hpmax = rand()%3 + 1;
		this->hp = this->hpmax ;
		this->Shape.setTexture(*texture);
		this->Shape.setScale(0.15f, 0.15f);
		this->Shape.setPosition(rand()%windowsize.x , rand()%200 -this->Shape.getGlobalBounds().height);

	}

	~Enemy2(){}

};

class heart
{
public :
	Sprite Shape ;
	float speedx=0;
	float speedy=0;
	heart(Texture *texture2 , Vector2u windowsize )
	{
	
		this->Shape.setTexture(*texture2);
		this->Shape.setScale(0.05f, 0.05f);
		this->Shape.setPosition(rand()%windowsize.x + this->Shape.getGlobalBounds().width, 0);

	}
	~heart(){}

};

class rocket
{
public :
	Sprite Shape ;
	float speedx=0;
	float speedy=0;
	rocket(Texture *texture2 , Vector2u windowsize )
	{
	
		this->Shape.setTexture(*texture2);
		this->Shape.setScale(0.1f, 0.1f);
		this->Shape.setPosition(rand()%windowsize.x + this->Shape.getGlobalBounds().width, 0);

	}
	~rocket(){}

};


class Bullet
{
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

int main()
{
	srand(time(NULL));

	RenderWindow window(sf::VideoMode(1000, 800), "space invades",  sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize );
    window.setMouseCursorVisible(true);
    window.setFramerateLimit(60);
	
	
	Texture backtexture ;
	backtexture.loadFromFile("space.png");

	Sprite backsprite ;
	backsprite.setTexture(backtexture);
	backsprite.setPosition(0, 0);
	
	SoundBuffer shootbuffer ;
	shootbuffer.loadFromFile("playerShootSound.wav");
	Sound shooting ;
	shooting.setBuffer(shootbuffer);


	SoundBuffer dethbuffer ;
	dethbuffer.loadFromFile("enemyHit.wav");
	Sound deth ;
	deth.setBuffer(dethbuffer);


	SoundBuffer gobuffer ;
	gobuffer.loadFromFile("playerDeathSound.wav");
	Sound go ;
	go.setBuffer(dethbuffer);

	Music backgroudmu ;
	backgroudmu.openFromFile("backgroundMusic.ogg");
	backgroudmu.play();

	
	
	
	
	//Player
	CircleShape player(50.f);
	player.setFillColor(Color::White);
	player.setPointCount(3);
	player.setOrigin(50.f, 50.f);
    player.setPosition(950, 750) ;
	int Hp =12 ;
	int xp =0 ;
	int maxxp =0 ;

	Font font;
				if (!font.loadFromFile("TheBrown.otf"))
				{
					std::cout << "Load Failed";
				}
	
	
	Text hptxt;
	hptxt.setFont(font);
	hptxt.setCharacterSize(20);
	hptxt.setFillColor(Color::White);
	hptxt.setPosition(50 , 30);
	hptxt.setStyle(Text::Bold);

	Text erhptxt;
	erhptxt.setFont(font);
	erhptxt.setCharacterSize(20);
	erhptxt.setFillColor(Color::White);
	erhptxt.setPosition(50 , 70);
	erhptxt.setStyle(Text::Bold);

	Text xpt;
	xpt.setFont(font);
	xpt.setCharacterSize(20);
	xpt.setFillColor(Color::Yellow);
	xpt.setPosition(50 , 750);
	xpt.setStyle(Text::Bold);

	Text xpmaxt;
	xpmaxt.setFont(font);
	xpmaxt.setCharacterSize(20);
	xpmaxt.setFillColor(Color::Blue);
	xpmaxt.setPosition(150 , 750);
	xpmaxt.setStyle(Text::Bold);

	Text reload;
	reload.setFont(font);
	reload.setCharacterSize(50);
	reload.setFillColor(Color::Yellow);
	reload.setPosition(200 , 500);
	reload.setStyle(Text::Bold);



	RectangleShape health(Vector2f(Hp*20, 7)) ;
	health.setFillColor(Color::White );
	health.setPosition(50, 50);


	int earthhp=10 ;
	RectangleShape earthhealth(Vector2f(earthhp*20, 7)) ;
	earthhealth.setFillColor(Color::Green );
	earthhealth.setPosition(50, 100);
	


    Texture ship ;
    ship.loadFromFile("ship.png");
    player.setTexture(&ship);
	int shoottimer = 30 ;

	//Bullets
	Bullet b1;
	Bullet enmbul ;
	std::vector<Bullet> bullets;
	std::vector<Bullet> enemybullets;

	
	//Vectors
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;


	//enemy	
	Texture ent ;
	ent.loadFromFile("enemyve.png");
	std::vector<Enemy> enemies;
	std::vector<Enemy2> enemiestype2;
	int enemyspowntimer1 = 0 , enemyspowntimer2=0 ;

	Text ehptxt;
	ehptxt.setFont(font);
	ehptxt.setCharacterSize(15);
	ehptxt.setFillColor(Color::Red);

	Text ehptxt1;
	ehptxt1.setFont(font);
	ehptxt1.setCharacterSize(15);
	ehptxt1.setFillColor(Color::Red);

	Text limit;
	limit.setFont(font);
	limit.setCharacterSize(15);
	limit.setFillColor(Color::Red);
	limit.setPosition(10 , 520);

// level up
	Text level;
	level.setFont(font);
	level.setCharacterSize(15);
	level.setFillColor(Color::Red);
	level.setPosition(500 , 30);
	level.setStyle(Text::Bold);



	//heart 
	Texture life;
	life.loadFromFile("Heart.png");
	std::vector<heart> hearts;
	int he = 0;

	//rocket
	Texture bomb;
	bomb.loadFromFile("rocket.png");
	std::vector<rocket> rockets;
	int re = 0;


	//limit line
	RectangleShape line(Vector2f(window.getSize().x, 10.f));
	line.setFillColor(Color::Red);
	line.setPosition(Vector2f(0.f, 550.f));

	//level up
	int shoottime =15 ;
	int enemytime = 100 ;
	int lno = 1;

	int v ;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			 if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();
		}
		window.clear();
		window.draw(backsprite);
		if(Hp>0 && earthhp>0)
		{ v=1;
		health.setSize(Vector2f(Hp*20, 10)) ;
		earthhealth.setSize(Vector2f(earthhp*20, 10));

//.......................................................level up................................
	if(xp>700)
	{
		lno =5 ;
		shoottime = 8 ;
		enemytime = 60 ;
	}
	else if(xp>500)
	{	
		lno =4 ;
		shoottime = 8 ;
		enemytime = 70 ;
	}	
	else if (xp>250)
	{	
		lno =3 ;
		shoottime = 9 ;
		enemytime = 80 ;	
	}
	else if (xp>150)
	{	
		lno =2 ;
		shoottime = 12 ;
		enemytime = 90 ;	
	}
	

//..............................................................Update diraction....................
		//Vectors
		playerCenter = Vector2f(player.getPosition());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		player.setRotation(deg + 90);
     
//.............................................................moving control...........................
		//Player
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.move(0.f, -10.f);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.move(0.f, 10.f);
			
			//dont go out :))
		
		if(player.getPosition().x <= 0)
		{	
			player.setPosition(window.getSize().x , player.getPosition().y) ;
			
		}
		else if(player.getPosition().x >= window.getSize().x)
		{
			//player.setPosition(window.getSize().x - player.getLocalBounds().width, player.getPosition().y) ;
			player.setPosition(0.f, player.getPosition().y) ;
		}
		else if (player.getPosition().y >= window.getSize().y)
		{
			player.setPosition(player.getPosition().x, window.getSize().y -10);
		}
		else if (player.getPosition().y <= 600)
		{
			player.setPosition(player.getPosition().x, 610.f);
		}
		
//.........................................................shoot handeling..................................................			
		
		window.draw(player);
		for (size_t i = 0; i < bullets.size(); i++)		
			window.draw(bullets[i].shape);
		
		
		//Shooting
		if(shoottimer < shoottime)
			shoottimer++ ;
		
		if (Mouse::isButtonPressed(Mouse::Left) && shoottimer>= shoottime)
		{	shooting.play();
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;
			bullets.push_back(Bullet(b1));
			shoottimer=0 ;
		}

//...........................................................shooting & colision & bullet movment control ..........................		
		for (size_t i = 0; i < bullets.size(); i++)
		{	
			//move
			bullets[i].shape.move(bullets[i].currVelocity);

			//Out of bounds
			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
				{
					bullets.erase(bullets.begin() + i);
					break ;					
				}
				
			//colision
			else
			{
				//Enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].Shape.getGlobalBounds()))
					{	
						--enemies[k].hp;
						bullets.erase(bullets.begin() + i);
						if(enemies[k].hp<=1)
						{
							enemies.erase(enemies.begin() + k);
							deth.play();
							xp += 10 ;
						}	
						break;
					}
				}

				for (size_t k = 0; k < enemiestype2.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemiestype2[k].Shape.getGlobalBounds()))
					{	
						--enemiestype2[k].hp;
						bullets.erase(bullets.begin() + i);
						if(enemiestype2[k].hp<=1)
						{
							enemiestype2.erase(enemiestype2.begin() + k);
							xp += 10 ;
						}						
						break;
					}
				}
			}				
		}

		

//..................................................................enemy type 1......................................

		//enemy 
			//spown1
		if(enemyspowntimer1 < enemytime)
		++enemyspowntimer1 ;



		if(enemyspowntimer1 >= enemytime)
		{
			enemies.push_back(Enemy(&ent , window.getSize())); 
			enemyspowntimer1 = 0 ;			
		}
			//moving
		for (size_t i = 0; i < enemies.size(); i++)
		{	
			
			if(enemies[i].Shape.getPosition().x >= window.getSize().x -50)
			{
				enemies[i].speedx *= -1.3;
				//every time it will be faster than befor
				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+100 ) ;
			}
			if(enemies[i].Shape.getPosition().x <= 0)
			{
				enemies[i].speedx *= -1.3;
				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+100 );
			}
	
			enemies[i].Shape.move(Vector2f(enemies[i].speedx, enemies[i].speedy)) ;

			if (enemies[i].Shape.getPosition().y>= window.getSize().y - enemies[i].Shape.getGlobalBounds().height )
			{
				enemies.erase(enemies.begin()+i);
				--earthhp;
				break ;
			}

			/*if(enemies[i].Shape.getPosition().y>=550)
			{
				enemies.erase(enemies.begin()+i);
				--Hp;
				break;
				
			}*/
		
			if (enemies[i].Shape.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				enemies.erase(enemies.begin()+i);
				Hp -=5;
				break;
			}
			ehptxt1.setString(std::to_string(enemies[i].hp)+"/"+std::to_string(enemies[i].hpmax))	;
			ehptxt1.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y - ehptxt1.getGlobalBounds().height);
			window.draw(ehptxt1);						
			window.draw(enemies[i].Shape);

		}



//.......................................................................enemy type 2..............................
			//spown2
		if(enemyspowntimer2 < enemytime)
		++enemyspowntimer2 ;

		//	if(enemyshoottimer < 10)
			//enemyshoottimer++ ;
		if(enemyspowntimer2 >= enemytime)
		{
			enemiestype2.push_back(Enemy2(&ent , window.getSize())); 
			enemyspowntimer2 = 0 ;
			
		}
			//moving
		for (size_t i = 0; i < enemiestype2.size(); i++)
		{	
					
	
			enemiestype2[i].Shape.move(Vector2f(0.f, 5.f)) ;

			if (enemiestype2[i].Shape.getPosition().y>= window.getSize().y  -enemiestype2[i].Shape.getGlobalBounds().height )
			{
				enemiestype2.erase(enemiestype2.begin()+i);
				--earthhp;
				break ;
			}

			/*if(enemies[i].Shape.getPosition().y>=550)
			{
				enemies.erase(enemies.begin()+i);
				--Hp;
				break;
				
			}*/
			

			if (enemiestype2[i].Shape.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				enemiestype2.erase(enemiestype2.begin()+i);
				Hp-=3;
				break;
			}

			ehptxt.setString(std::to_string(enemiestype2[i].hp)+"/"+std::to_string(enemiestype2[i].hpmax))	;
			ehptxt.setPosition(enemiestype2[i].Shape.getPosition().x, enemiestype2[i].Shape.getPosition().y - ehptxt.getGlobalBounds().height);
			window.draw(ehptxt);			
			window.draw(enemiestype2[i].Shape);

		}

//........................................................... extra ............................

		//heart

		if(he < 600)
		++he ;

		if(he >= 600)
		{
			hearts.push_back(heart(&life , window.getSize())); 
			he = 0 ;
			
		}
			//moving
		for (size_t i = 0; i < hearts.size(); i++)
		{							
			hearts[i].Shape.move(Vector2f(0.f, 5.f)) ;

			if (hearts[i].Shape.getPosition().y<= -hearts[i].Shape.getGlobalBounds().height )
			{
				hearts.erase(hearts.begin()+i);
				break ;
			}		

			if (hearts[i].Shape.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				hearts.erase(hearts.begin()+i);
				if(Hp!=12)
				++Hp;
				break;
			}									
			window.draw(hearts[i].Shape);
		}

		//rocket

		if(re < 400)
		++re ;

		if(re >= 400)
		{
			rockets.push_back(rocket(&bomb , window.getSize())); 
			re = 0 ;
			
		}
			//moving
		for (size_t i = 0; i < hearts.size(); i++)
		{							
			rockets[i].Shape.move(Vector2f(0.f, 7.f)) ;

			if (rockets[i].Shape.getPosition().y<= -rockets[i].Shape.getGlobalBounds().height )
			{
				rockets.erase(rockets.begin()+i);
				break ;
			}		

			if (rockets[i].Shape.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				rockets.erase(rockets.begin()+i);
				--Hp;
				break;
			}									
			window.draw(rockets[i].Shape);
		}

//......................................................game over & drawing................................................

		}
		//game over
		if (Hp<=0 || earthhp<=0)
		{	
			if(v==1)
			{
				go.play();
				v=0 ;
			}
			Text text;
				Font font;
				if (!font.loadFromFile("game_over.ttf"))
				{
					std::cout << "Load Failed";
				}
				text.setFont(font);
				text.setString("Game Over");
				reload.setString("press Enter to continu");
				text.setCharacterSize(300);
				text.setFillColor(Color::Red);
				text.setStyle(Text::Bold | Text::Underlined);
				text.setPosition(200, 100);
				text.setOutlineColor(Color::Yellow);

				//window.clear();
				//Draw the text
				window.draw(text);
				window.draw(reload);
				//Display the text to the window
				//window.display();
				if(Keyboard::isKeyPressed(Keyboard::Enter))
				{
					xp=0;
					Hp =12 ;
					lno =1 ;
					earthhp =10 ;

					for (size_t k = 0; k < enemiestype2.size(); k++)
					{
						enemiestype2.erase(enemiestype2.begin() + k);
					}
					for (size_t k = 0; k < enemies.size(); k++)
					{
						enemies.erase(enemies.begin() + k);
					}


				}

				
				//sleep(seconds(10));
				//window.close();


		}
		
		

	level.setString("level : "+std::to_string(lno))	;
	limit.setString("movment limit")	;
	hptxt.setString("ship health : "+std::to_string(Hp)+" / 12")	;
	erhptxt.setString("earth resistance : "+std::to_string(earthhp)+" / 10")	;
	xpt.setString("score : "+std::to_string(xp))	;
	if(xp>=maxxp)
	{
		maxxp=xp ;
	}
	xpmaxt.setString("high score : "+std::to_string(maxxp))	;
		
		window.draw(limit);
		window.draw(xpmaxt);
		window.draw(level);
		window.draw(xpt);
		window.draw(hptxt);
		window.draw(erhptxt);
		window.draw(earthhealth);
		window.draw(health);
		window.draw(line);
		window.display();
	}
	return 0;
}