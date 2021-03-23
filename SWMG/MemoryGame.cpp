#include "MemoryGame.h"
#include <iostream>



MemoryGame::MemoryGame()
{
}

MemoryGame::~MemoryGame()
{
}

sf::String MemoryGame::EnterPlayerName(sf::RenderWindow* window, int playerNo)
{
	sf::String buffer;
	sf::Font font;
	if (!font.loadFromFile("resources/STARWARS.ttf"))
	{
		// error...
	}

	std::string textStr;
	sf::Text text, character;
	text.setFont(font);
	int counter = 0;

	buffer.clear();

	window->clear(sf::Color::White);

	
	text.setString("Enter " + std::to_string(playerNo) + ". player name:");
	text.setCharacterSize(50);
	text.setColor(sf::Color::Black);
	text.setPosition(600, 400);
	window->draw(text);
	window->display();

	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case::sf::Event::EventType::Closed:
				window->close();
				break;
			case sf::Event::EventType::TextEntered:

				if (event.text.unicode < 127 && event.text.unicode > 31)
				buffer += event.text.unicode;
				
				break;
				
			case sf::Event::EventType::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Return)
				{
					return buffer;
				}
				break;
			default:
				break;
			}
			
		}
	}
	window->display();
	return buffer;
}

int MemoryGame::Start()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800,600), "Star Wars Memory Game", sf::Style::Titlebar | sf::Style::Close);


	int choice = 0;
	noOfPlayers = 0, level = 0, cardCounter = 0, boardW = 0, boardH = 0;

	sf::Music music;
	music.openFromFile("resources/Imperial_March.ogx");
	music.setLoop(true);
	music.play();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				GameOver();
			}
		}
		window->clear(sf::Color::White);

		if(!choice) choice = DrawMenu(window, "MainMenu", 3);
		
		switch (choice)
		{
		case 1: GameSetup(window); break;
		case 2: break;
		case 3: window->close(); break;
		default: break;
		}

		if (level && noOfPlayers)
		{
			window->close();
			music.stop();
			Play();
		}
		
		window->display();
	}
	return EXIT_SUCCESS;
}

int MemoryGame::DrawMenu(sf::RenderWindow* window, std::string menuType, int noOfMenuItems)
{
	int choice = 0;

	AssetManager manager;

	sf::Vector2u size;
	std::vector<sf::Sprite*> menuItem;


	size = window->getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	sf::Sprite* menuName = new sf::Sprite(AssetManager::GetTexture("resources/" + menuType + "Caption.png"));
	menuName->setPosition(sf::Vector2f((width / 2) - menuName->getLocalBounds().width / 2, 50));
	window->draw(*menuName);

	for (int i = 0; i < noOfMenuItems; ++i)
	{
		menuItem.push_back(new sf::Sprite(AssetManager::GetTexture("resources/" + menuType + "Button" + std::to_string(i) + ".png")));
		menuItem[i]->setPosition(sf::Vector2f((width / 2) - menuItem[i]->getLocalBounds().width / 2, 200 + 100*i));
		window->draw(*menuItem[i]);
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		for (int i = 0; i < noOfMenuItems; ++i)
			if (menuItem[i]->getGlobalBounds().contains(mousePosF)) choice = i + 1;
	}
	Delay(.08);
	return choice;
}

void MemoryGame::GameSetup(sf::RenderWindow* window)
{
	if (!level) level = DrawMenu(window, "LevelMenu", 3);
	if (!noOfPlayers && level) noOfPlayers = DrawMenu(window, "PlayersMenu", 4);
}



int MemoryGame::Play()
{
	
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode().getDesktopMode(), "Star Wars Memory Game", sf::Style::Titlebar | sf::Style::Close);

	float scale;
	scale = window->getSize().y / 1200.;
	cardDimension = CARD_DIM * scale;
	//sf::VideoMode().getDesktopMode()
	
	AssetManager manager;

	int choice = 0;
	flipCardFlag = FALSE, flopCardFlag = FALSE;
	gameOver = FALSE;
	noOfCardsSelect = 0;
	activePlayer = 0;

	sf::Music music;
	music.openFromFile("resources/star-wars-theme-song.ogg");
	music.setLoop(true);
	music.setVolume(50);
	music.play();


	BoardSetup();
	PlayersSetup(window);
	SoundSetup();


	window->clear();
	DrawBoard(window);

		while (window->isOpen())
		{
			while (!gameOver)
			{
			
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
					GameOver();
					music.stop();
				}
			}

			window->clear(sf::Color::White);

			if (noOfCardsSelect == 0) firstCard = SelectCard(window);
			else if (noOfCardsSelect == 1) secondCard = SelectCard(window);

			if (flipCardFlag && noOfCardsSelect == 1) FlipCard(window, firstCard);
			else
				if (flipCardFlag && noOfCardsSelect == 2)
				{
					FlipCard(window, secondCard);
					if (!checkPair(firstCard, secondCard))
					{
						flopCardFlag = TRUE;
						Delay(.5);
						FlipCard(window, secondCard);
						FlipCard(window, firstCard);
						flopCardFlag = FALSE;
					}
					Delay(.3);
					noOfCardsSelect = 0;
				}
				
			DrawBoard(window);

			}
			window->close();
			DrawResults();
		}
	return EXIT_SUCCESS;
}

void MemoryGame::BoardSetup()
{
	
	switch (level)
	{
	case 1: boardW = 5; boardH = 4; break;
	case 2: boardW = 6; boardH = 5; break;
	case 3: boardW = 7; boardH = 6; break;
	default: break;
	}

	for (int i = 0; i < (boardW*boardH) / 2; ++i)
	{
		board.push_back(new Card(i, new sf::Sprite(AssetManager::GetTexture("resources/" + std::to_string(i) + ".png")),
									new sf::Sprite(AssetManager::GetTexture("resources/card-back.png"))));
		board.push_back(new Card(i, new sf::Sprite(AssetManager::GetTexture("resources/" + std::to_string(i) + ".png")),
									new sf::Sprite(AssetManager::GetTexture("resources/card-back.png"))));
	}
	
	Card* temp;
	int CardPos;
	srand(time(NULL));
	for (int i = 0; i < 100; ++i)
	{
		CardPos = rand() % (boardW*boardH);
		temp = board[CardPos];
		board.erase(board.begin() + CardPos);
		board.push_back(temp);
	}

}

void MemoryGame::PlayersSetup(sf::RenderWindow* window)
{
	sf::String playerName;

	for (int i = 0; i < noOfPlayers; ++i)
	{
		players.push_back(new Player(i, new sf::Sprite(AssetManager::GetTexture("resources/player" + std::to_string(i) + ".png"))));
		//players[i]->SetPlayerName(EnterPlayerName(window, i + 1));
		switch (i)
		{
		case 0: players[i]->SetPlayerPos(window->getSize().x / 2, window->getSize().y - (window->getSize().y - cardDimension * boardH) / 4); break;
		case 1: players[i]->SetPlayerPos((window->getSize().x - cardDimension * boardW) / 4, window->getSize().y / 2); break;
		case 2: players[i]->SetPlayerPos(window->getSize().x / 2, (window->getSize().y - cardDimension * boardH) / 4); break;
		case 3: players[i]->SetPlayerPos(window->getSize().x - (window->getSize().x - cardDimension * boardW) / 4, window->getSize().y / 2); break;
		};
	}
}

void MemoryGame::SoundSetup()
{
	flipSound = sf::Sound(AssetManager::GetSoundBuffer("resources/light-saber-on.wav"));
	flopSound = sf::Sound(AssetManager::GetSoundBuffer("resources/light-saber-off.wav"));
	pairSound = sf::Sound(AssetManager::GetSoundBuffer("resources/forcestrong.wav"));
}

void MemoryGame::DrawBoard(sf::RenderWindow* window)
{

	int counter = 0;
	sf::Texture texture;
	sf::Sprite sprite;

	window->clear(sf::Color::White);
	
	
	texture.loadFromFile("resources/star-wars-logo.png");
	sprite.setTexture(texture);
	sprite.setPosition(75*scale, 75*scale);
	sprite.scale(1.f * scale, 1.f * scale);
	window->draw(sprite);


	for (int i = 0; i < boardH; ++i)
		for (int j = 0; j < boardW; ++j)
		{
			if (board[counter] != nullptr)
				board[counter]->DrawCard(window, board[counter]->GetCardNo(), j, i, boardW, boardH, board[counter]->GetCardSelect());
			++counter;
		}
	DrawPlayers(window);

	

	window->display();
}


void MemoryGame::DrawPlayers(sf::RenderWindow* window)
{
	
	for (int i = 0; i < noOfPlayers; ++i)
	{

		for (int i = 0; i < noOfPlayers; ++i)
			players[i]->DrawPlayer(window, activePlayer);
	}
}

void MemoryGame::DrawResults()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Star Wars Memory Game", sf::Style::Titlebar | sf::Style::Close);

	int maxScore = 0;
	Player* temp;

		for (int i = 0; i < noOfPlayers; i++)
		 for (int j = i+1; j < noOfPlayers; j++)
			if (players[i]->GetScore() < players[j]->GetScore())
			{
				temp = players[i];
				players[i] = players[j];
				players[j] = temp;
			}

	maxScore = players[0]->GetScore();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				GameOver();
			}

			window->clear(sf::Color::White);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window->close();
				GameOver();
				Start();
			}

			sf::Font font;
			if (!font.loadFromFile("resources/STARWARS.ttf"))
			{
				// error...
			}

			std::string textStr;
			sf::Text text;
			text.setFont(font);
			text.setColor(sf::Color::Black);

			text.setString("Results");
			text.setCharacterSize(50);
			text.setPosition(200, 60);
			window->draw(text);

			for (int i = 0; i < noOfPlayers; ++i)
			{
				textStr = "";
				textStr = players[i]->GetPlayerName() + " " + std::to_string(players[i]->GetPlayerNo()+1) + "  Score: " + std::to_string(players[i]->GetScore());
				if (players[i]->GetScore() == maxScore) textStr = textStr + "  WINNER";
				text.setString(textStr);
				text.setCharacterSize(30);
				text.setPosition(200, 200 + i * 75);
				window->draw(text);
			}

			text.setString("Press mouse button to continue...");
			text.setCharacterSize(15);
			text.setPosition(200, 530);
			window->draw(text);

			window->display();
		}
	}
}

int MemoryGame::SelectCard(sf::RenderWindow* window)
{
	int choice = 0;
	sf::Vector2i mousePosition;

	float scale;
	scale = window->getSize().y / 1200.;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// get card position in board
		 mousePosition = sf::Mouse::getPosition(*window);
		 if ((mousePosition.x > (window->getSize().x - cardDimension * boardW) / 2 && mousePosition.x < (window->getSize().x - cardDimension * boardW) / 2 + cardDimension * boardW &&
			 mousePosition.y >(window->getSize().y - cardDimension * boardH) / 2 && mousePosition.y < (window->getSize().y - cardDimension * boardH) / 2 + cardDimension * boardH))
		 choice = (((mousePosition.y - ((window->getSize().y - cardDimension * boardH) / 2)) / cardDimension) * boardW) + ((mousePosition.x - ((window->getSize().x - cardDimension * boardW) / 2)) / cardDimension) + 1;
	}

	if (choice && board[choice - 1] != nullptr && !board[choice - 1]->GetCardSelect())
	{
		board[choice - 1]->SetCardSelect(TRUE); 
		flipCardFlag = TRUE;
		++noOfCardsSelect;
	}
	else choice = 0;
	return choice - 1;
}

bool MemoryGame::checkPair(int first, int second)
{
	bool checkPair = FALSE;
	board[first]->SetCardSelect(FALSE);
	board[second]->SetCardSelect(FALSE);

	if (board[first]->GetCardNo() == board[second]->GetCardNo())
	{
		board[first] = board[second] = nullptr;
		players[activePlayer]->SetScore(1);
		cardCounter = cardCounter+2;
		checkPair = TRUE;
		
		pairSound.play();
	}
	else
	{
		if (activePlayer < noOfPlayers - 1) ++activePlayer;
		else activePlayer = 0;
	}
	
	if (cardCounter == boardW*boardH) gameOver = TRUE;
	Delay(.5);

	return checkPair;
}

void MemoryGame::FlipCard(sf::RenderWindow* window, int field)
{
	std::string imageName;
	sf::Texture frontTexture, backTexture, texture;
	sf::Sprite blankSprite;

	float scale;
	scale = window->getSize().y / 1200.;
	cardDimension = CARD_DIM*scale;

	if (!flopCardFlag) flipSound.play();
	else flopSound.play();

	texture.loadFromFile("resources/blank105.png");
	blankSprite.setTexture(texture);
	blankSprite.setOrigin(sf::Vector2f(blankSprite.getLocalBounds().width, blankSprite.getLocalBounds().height) / 2.f);
	blankSprite.setPosition(sf::Vector2f((window->getSize().x - cardDimension * boardW) / 2 + cardDimension * (field % boardW) + cardDimension / 2, (window->getSize().y - cardDimension * boardH) / 2 + cardDimension * (field / boardW) + cardDimension / 2));
	blankSprite.scale(scale, scale);

	imageName = "resources/" + std::to_string(board[field]->GetCardNo()) + ".png";

	if (flopCardFlag)
	{
		backTexture.loadFromFile(imageName);
		frontTexture.loadFromFile("resources/card-back-flip.png");
	}
	else
	{
		backTexture.loadFromFile("resources/card-back.png");
		frontTexture.loadFromFile(imageName);
	}

	sw::Sprite3d sprite(backTexture, frontTexture);

	//if (flopCardFlag) sprite.setTextureRect(sf::IntRect(cardDimension, 0, -cardDimension, cardDimension));

	sprite.scale(scale, scale);
	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height) / 2.f);
	sprite.setPosition(sf::Vector2f((window->getSize().x - cardDimension * boardW) / 2 + cardDimension * (field % boardW) + cardDimension / 2,
		(window->getSize().y - cardDimension * boardH) / 2 + cardDimension * (field / boardW) + cardDimension / 2));
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() <= .25)
	{
		sprite.setRotation({ clock.getElapsedTime().asSeconds() * 0.0f, clock.getElapsedTime().asSeconds() * 720.0f, clock.getElapsedTime().asSeconds() * 0.0f });
		window->clear();

		DrawBoard(window);
		window->draw(blankSprite);
		window->draw(sprite);
		window->display();
	}

	flipCardFlag = FALSE;
}


void MemoryGame::Delay(float time)
{
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() <= time) {}
}

void MemoryGame::GameOver()
{
	for (int i = 0; i < noOfPlayers; ++i)
		delete players[i];
	for (int i = 0; i < boardW*boardH; ++i)
		delete board[i];
	players.empty();
	board.empty();
}
