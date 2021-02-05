#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
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

/*class Enemy2
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
		this->Shape.setPosition(rand()%windowsize.x - this->Shape.getGlobalBounds().width, rand()%200 -this->Shape.getGlobalBounds().height);

	}

	~Enemy2(){}

};*/



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
	//Player
	CircleShape player(50.f);
	player.setFillColor(Color::White);
	player.setPointCount(3);
	player.setOrigin(50.f, 50.f);
    player.setPosition(950, 750) ;
	int Hp =12 ;

    Texture ship ;
    ship.loadFromFile("ship.png");
    player.setTexture(&ship);
	int shoottimer = 15 ;

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

	/*Vector2f enemyCenter;
	Vector2f destination;
	Vector2f enemyaimDir;
	Vector2f enemyaimDirNorm;*/



	//enemy	
	Texture ent ;
	ent.loadFromFile("enemyve.png");
	std::vector<Enemy> enemies;
	std::vector<Enemy2> enemiestype2;
	int enemyspowntimer1 = 0 , enemyspowntimer2=0 ;
	//int enemyshoottimer = 10 ;



	//limit line
	RectangleShape line(Vector2f(window.getSize().x, 10.f));
	line.setFillColor(Color::Red);
	line.setPosition(Vector2f(0.f, 550.f));


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			 if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();
		}

		//Update
		//Vectors
		playerCenter = Vector2f(player.getPosition());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		player.setRotation(deg + 90);
     
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
		
			
		window.clear();
		window.draw(player);
		for (size_t i = 0; i < bullets.size(); i++)		
			window.draw(bullets[i].shape);

		if(shoottimer < 15)
			shoottimer++ ;

		//Shooting
		if (Mouse::isButtonPressed(Mouse::Left) && shoottimer>= 15)
		{
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;
			bullets.push_back(Bullet(b1));
			shoottimer=0 ;
		}

		
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
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);
						break;
					}
				}

				for (size_t k = 0; k < enemiestype2.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemiestype2[k].Shape.getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						enemiestype2.erase(enemiestype2.begin() + k);
						break;
					}
				}
			}				
		}

		



		//enemy 
			//spown1
		if(enemyspowntimer1 < 100)
		++enemyspowntimer1 ;



		if(enemyspowntimer1 >= 100)
		{
			enemies.push_back(Enemy(&ent , window.getSize())); 
			enemyspowntimer1 = 0 ;			
		}
			//moving
		for (size_t i = 0; i < enemies.size(); i++)
		{	
			
			if(enemies[i].Shape.getPosition().x >= window.getSize().x -50)
			{
				enemies[i].speedx *= -1.2;
				//every time it will be faster than befor
				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+100 ) ;
			}
			if(enemies[i].Shape.getPosition().x <= 0)
			{
				enemies[i].speedx *= -1.2;
				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+100 );
			}
	
			enemies[i].Shape.move(Vector2f(enemies[i].speedx, enemies[i].speedy)) ;

			if (enemies[i].Shape.getPosition().y<= -enemies[i].Shape.getGlobalBounds().height )
			{
				enemies.erase(enemies.begin()+i);
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
									
			window.draw(enemies[i].Shape);

		}




			//spown2
		if(enemyspowntimer2 < 700)
		++enemyspowntimer2 ;

		//	if(enemyshoottimer < 10)
			//enemyshoottimer++ ;
		if(enemyspowntimer2 >= 700)
		{
			enemiestype2.push_back(Enemy2(&ent , window.getSize())); 
			enemyspowntimer2 = 0 ;
			
		}
			//moving
		for (size_t i = 0; i < enemiestype2.size(); i++)
		{	
					
	
			enemiestype2[i].Shape.move(Vector2f(0.f, 5.f)) ;

			if (enemiestype2[i].Shape.getPosition().y<= -enemiestype2[i].Shape.getGlobalBounds().height )
			{
				enemiestype2.erase(enemiestype2.begin()+i);
				break ;
			}

			/*if(enemies[i].Shape.getPosition().y>=550)
			{
				enemies.erase(enemies.begin()+i);
				--Hp;
				break;
				
			}
			//enemyCenter = Vector2f(player.getPosition());
			destination = Vector2f(enemiestype2[i].Shape.getPosition().x, window.getSize().y);
			enemyCenter = Vector2f(enemiestype2[i].Shape.getPosition());
			enemyaimDir = destination - enemyCenter;
			enemyaimDirNorm.x = enemyaimDir.x / sqrt(pow(enemyaimDir.x, 2) + pow(enemyaimDir.y, 2));
        	enemyaimDirNorm.y = enemyaimDir.y / sqrt(pow(enemyaimDir.x, 2) + pow(enemyaimDir.y, 2));
			
			if ( enemyshoottimer>= 10)
			{
			enmbul.shape.setPosition(Vector2f(enemiestype2[i].Shape.getPosition()));
			enmbul.currVelocity = enemyaimDirNorm * enmbul.maxSpeed;
			enemybullets.push_back(Bullet(enmbul));
			enemyshoottimer=0 ;
			}

			for (size_t i = 0; i < bullets.size(); i++)
			{	
			//move
			enemybullets[i].shape.move(enemybullets[i].currVelocity);
			}

			for (size_t i = 0; i < enemybullets.size(); i++)		
			window.draw(enemybullets[i].shape);*/

			if (enemiestype2[i].Shape.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				enemiestype2.erase(enemiestype2.begin()+i);
				Hp -=5;
				break;
			}
									
			window.draw(enemiestype2[i].Shape);

		}

		window.draw(line);
		window.display();
	}
	return 0;
}