#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side {LEFT,RIGHT,NONE};//where is the player/branch -> left or right
side branchPositions[NUM_BRANCHES];



int main()
{
	VideoMode vm(1920, 1080);//video mode object
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);//open window
	Texture textureBackground;//create a texture to hold a graphic on GPU
	textureBackground.loadFromFile("graphics/background.png");//load agraphic into texture
	Sprite  spriteBackground;//create a sprite
	spriteBackground.setTexture(textureBackground);//attach the texture to sprite
	spriteBackground.setPosition(0, 0);//set the spriteBG to cover screen

	Texture textureTree;//making a tree sprite
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	bool isCloud1Active = false;
	bool isCloud2Active = false;
	bool isCloud3Active = false;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Clock clock;//var to control time
	bool paused = true;

	//time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400, timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1980 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	int score = 0;//Draw some text
	Text messageText;
	Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	//prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int i = 0;i < NUM_BRANCHES;i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}


	while (window.isOpen())
	{
		//score++;//test
		//Handle player's input
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) 
		{
			paused = false;
			//reset time and score
			score = 0; timeRemaining = 6.0f;
		}

		if (!paused)
		{
			//update scene
			Time dt = clock.restart();
			timeRemaining -= dt.asSeconds();//timeBar related
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f)
			{
				paused = true;
				messageText.setString("Out of time!!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}
			
			//Setup the bee
			if (!beeActive)
			{
				srand((unsigned int)time(0));
				beeSpeed = (rand() % 200) + 200;
				srand((unsigned int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			//Move the bee
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y
				);
				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}
			if (!isCloud1Active)
			{
				srand((unsigned int)time(0)*10);
				cloud1Speed = (rand() % 200);
				srand((unsigned int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200,height);
				isCloud1Active = true;

			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x + cloud1Speed * dt.asSeconds(),
					spriteCloud1.getPosition().y
				);
				if (spriteCloud1.getPosition().x > 1920)
				{
					isCloud1Active = false;
				}
			}
			// Cloud 2 
			if (!isCloud2Active)
			{ 
				// How fast is the cloud 
				srand((int)time(0) * 20); cloud2Speed = (rand() % 200); 
				// How high is the cloud 
				srand((int)time(0) * 20); 
				float height = (rand() % 300) - 150; 
				spriteCloud2.setPosition(-200, height); isCloud2Active = true;
			} 
			else
			{
				spriteCloud2.setPosition( spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y); 
				// Has the cloud reached the right hand edge of the screen? 
				if (spriteCloud2.getPosition().x > 1920)
				{ 
					// Set it up ready to be a whole new cloud next frame 
					isCloud2Active = false; 
				} 
			} 
			if (!isCloud3Active) 
			{
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150; 
				spriteCloud3.setPosition(-200, height); 
				isCloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition( spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y); 
				if (spriteCloud3.getPosition().x > 1920)
				{
					isCloud3Active = false;
				}
			}

			//update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//update the branch sprites
			for (int i = 0;i < NUM_BRANCHES;i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(3000, height);//hide branch
				}
			}

		}//EndIf(!paused)

		//draw scene

		//clear everything from last frame
		window.clear();

		window.draw(spriteBackground);//draw game scene
		window.draw(spriteCloud1);//
		window.draw(spriteCloud2);//
		window.draw(spriteCloud3);//
		for (int i = 0;i < NUM_BRANCHES;i++) { window.draw(branches[i]); }
		window.draw(spriteTree);//
		window.draw(spriteBee);//

		window.draw(scoreText);//draw the score
		window.draw(timeBar);//draw the timebar
		if (paused)
		{
			window.draw(messageText);//draw our message
		}
		window.display();//show everithing wejust drew //flipping double buffering

		
	}
	return 0;
}

void updateBranches(int seed)
{
	for (int j = NUM_BRANCHES-1;j > 0;j--) {//
		branchPositions[j] = branchPositions[j - 1];
	}
	srand((unsigned int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;

	}
}