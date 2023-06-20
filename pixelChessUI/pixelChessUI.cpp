#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

#include "Board.h"
#include "PromotionDialog.h"
#include "Cursor.h"
#include "GClock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "Checkbox.h"
#include "Consts.h"
#include "GFigure.h"
#include "PossibleMove.h"
#include "../GameHistory.h"
#include "../Game.h"
#include "Button.h"
#include "ResultPrompt.h"

enum class ProgramVariation
{
    NewGame,
    LoadGame,
    Menu,
    Exit,
};

ProgramVariation game(sf::RenderWindow& window, Cursor& cursor)
{
    // Setup logic
    Game game;

    // Object Initialization
    sf::Event event;
    GClock gclock(Timestamp(0, 10, 0), Timestamp(0, 10, 0));
    gclock.setActiveColor(game.isWhiteTurn());

    Board board(BOARD_SIZE, sf::Vector2i({ ((SCREEN_WIDTH - BOARD_SIZE) / 2),(SCREEN_HEIGHT - BOARD_SIZE) / 2 }));

    PromotionDialog promotionDialog(game.isWhiteTurn(), false);

    std::vector<GFigure> gfigures;
    for (std::shared_ptr<Piece> figure : game.getArrangementAsVector())
        gfigures.push_back(GFigure(figure.get(), board.positions));

    if (game.isWhiteTurn())
        cursor.setWhiteColor();
    else
        cursor.setBlackColor();

    //variables for loop
    std::vector<Position> validMoves;
    std::vector<PossibleMove> possibleMoves;

    char promotionVariant;
    bool promotion = false;
    bool exitLoop = false;
    Position from;
    Position to;
    ResultPrompt* resPromptWhite = ResultPrompt::getInstance(sf::Vector2f(SCREEN_WIDTH/2.0, (SCREEN_HEIGHT/2.0)-30), sf::Vector2f(300, 100), 1);
    ResultPrompt* resPromptBlack = ResultPrompt::getBlackInstance();
    Button returnToMenu("Main menu", sf::Vector2f(SCREEN_WIDTH/2.F, (SCREEN_HEIGHT/2.F)+60.0), sf::Vector2f(300, 40));
    while (!exitLoop)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            return ProgramVariation::Exit;
        }
        else
        {

            board.draw(window);

            promotionVariant = promotionDialog.update(cursor);
            if (promotionVariant != 'E')
            {
                game.move(from, to, promotionVariant);
                gfigures[cursor.getMovingFigureID()] = GFigure(game.getArrangement()[to.y][to.x].get(), board.positions);
                promotionDialog.hide();

                if (game.isWhiteTurn())
                    cursor.setWhiteColor();
                else
                    cursor.setBlackColor();
            }

            promotionDialog.draw(window);
            //draw moving figure
            if (cursor.isClicked() && cursor.isMovingFigure())
            {
                gfigures[cursor.getMovingFigureID()].setPosition(cursor.getPosition());
            }
            else if (cursor.isClicked())
            {
                for (int i = 0; i < gfigures.size(); i++)
                {
                    if (!gfigures[i].isTaken() && gfigures[i].contains(cursor.getPosition()) && gfigures[i].getColor() == game.isWhiteTurn())
                    {
                        cursor.setMovingFigure(true);
                        gfigures[i].setPickedUp(true);
                        cursor.setMovingFigureID(i);
                        gclock.start();
                    }
                }
            }
            else if (!cursor.isClicked() && cursor.isMovingFigure())
            {
                GFigure* figure = &gfigures[cursor.getMovingFigureID()];
                for (int i = 0; i < possibleMoves.size(); i++)
                {
                    if (possibleMoves[i].contains(cursor.getPosition()))
                    {
                        to = possibleMoves[i].getBoardPos();
                        from = figure->getBoardPos();

                        if (game.isPromotion(from, to))
                        {
                            promotion = true;
                            promotionDialog.setActiveColor(game.isWhiteTurn());
                            promotionDialog.show();
                            figure->setPosition(board.positions[to.x][to.y]);
                            //gfigures[cursor.getMovingFigureID()] = GFigure(game.getArrangement()[to.y][to.x].get(), board.positions);
                            //figure = &gfigures[cursor.getMovingFigureID()];
                        }
                        else
                        {
                            if (!game.move(from, to))
                                throw new std::exception("ERROR: Incorrect move occured!");
                            figure->resetPosition(board.positions);

                        }

                        game.debug();
                        break;
                    }
                }

                if (game.isWhiteTurn())
                    cursor.setWhiteColor();
                else
                    cursor.setBlackColor();

                gclock.setActiveColor(game.isWhiteTurn());
                figure->setPickedUp(false);
                cursor.setMovingFigure(false);
                possibleMoves.clear();
            }

            //draw standing figures
            for (int i = 0; i < gfigures.size(); i++)
            {
                GFigure* figure = &gfigures[i];
                if (!figure->isPickedUp() && !figure->isTaken())
                {
                    figure->resetPosition(board.positions);
                    figure->draw(window);
                }
            }

            //draw possible moves
            if (cursor.isMovingFigure() && possibleMoves.empty())
            {
                validMoves = gfigures[cursor.getMovingFigureID()].getValidMoves();
                for (int i = 0; i < validMoves.size(); i++)
                {
                    PossibleMove pm(Position(validMoves[i].x, validMoves[i].y), board.positions[validMoves[i].x][7 - validMoves[i].y]);
                    possibleMoves.push_back(pm);
                }
            }

            for (int i = 0; i < possibleMoves.size(); i++)
            {
                possibleMoves[i].draw(window);
            }

            //draw picked up figure
            if (cursor.isMovingFigure())
                gfigures[cursor.getMovingFigureID()].draw(window);

            if (game.isGameOver())
            {
                if (game.gameResult())
                    resPromptWhite->draw(window);
                else
                    resPromptBlack->draw(window);

                exitLoop = returnToMenu.update(cursor);
                returnToMenu.draw(window);
                
            }
            else
                gclock.update();
            
            gclock.draw(window);

            cursor.update(window);

        }

        window.display();
    }
    return ProgramVariation::Menu;
}
ProgramVariation menu(sf::RenderWindow& window, Cursor& cursor)
{
    sf::Event event;

    sf::Text programName;
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    programName.setFont(font);
    programName.setString("Pixel Chess");
    programName.setCharacterSize(100);

    sf::Vector2f center = sf::Vector2f(programName.getGlobalBounds().width / 2.f, programName.getGlobalBounds().height / 2.f);
    sf::Vector2f rounded = sf::Vector2f{ std::round(center.x), std::round(center.y) };
    programName.setOrigin(rounded);

    programName.setPosition(SCREEN_WIDTH/2.F, (SCREEN_HEIGHT/2.F)-300);

    Button newGameButton("New Game", sf::Vector2f(SCREEN_WIDTH / 2.F, (SCREEN_HEIGHT / 2.F) - 80.0), sf::Vector2f(400, 40));
    Button loadGameButton("Load Game", sf::Vector2f(SCREEN_WIDTH / 2.F, (SCREEN_HEIGHT / 2.F) - 20.0), sf::Vector2f(400, 40));
    Button exitButton("Exit to desktop", sf::Vector2f(SCREEN_WIDTH / 2.F, (SCREEN_HEIGHT / 2.F) + 40.0), sf::Vector2f(400, 40));
    while (true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            return ProgramVariation::Exit;

        }
        window.draw(programName);

        if (newGameButton.update(cursor))
            return ProgramVariation::NewGame;

        if(loadGameButton.update(cursor))
            return ProgramVariation::LoadGame;
            

        if (exitButton.update(cursor))
            return ProgramVariation::Exit;

        newGameButton.draw(window);
        loadGameButton.draw(window);
        exitButton.draw(window);

        cursor.update(window);
        window.display();
    }
}
std::pair<ProgramVariation, Settings> newGame(sf::RenderWindow& window, Cursor& cursor)
{
    sf::Event event;
    TextInput gameName(36, "game name", sf::Vector2f((SCREEN_WIDTH/2.f)-400, 100), sf::Vector2f(800, 40));

    TimeInput whiteTime(sf::Vector2f((SCREEN_WIDTH / 2.f), 200), sf::Vector2f(300, 40));
    TimeInput blackTime(sf::Vector2f((SCREEN_WIDTH / 2.f), 250), sf::Vector2f(300, 40));
    Checkbox allowUndo(sf::Vector2f((SCREEN_WIDTH / 2.f), 350), sf::Vector2f(40, 40));
    Button startGameButton("start Game", sf::Vector2f((SCREEN_WIDTH / 2.F)+ 225, 500), sf::Vector2f(350, 40));
    Button returnButton("return", sf::Vector2f((SCREEN_WIDTH / 2.F) - 225, 500), sf::Vector2f(350, 40));

    sf::Font font;
    font.loadFromFile(FONT_PATH);
    sf::Text timeInputDesc1("white time:", font);
    sf::Text timeInputDesc2("black time:", font);
    sf::Text allowUndoDesc("allow undo:", font);

    timeInputDesc1.setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f)-300, 200));
    timeInputDesc2.setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f)-300, 250));
    allowUndoDesc.setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f)-300, 350));
    while (true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            return std::pair<ProgramVariation, Settings>(ProgramVariation::Exit, Settings());

        }
        window.draw(timeInputDesc1);
        window.draw(timeInputDesc2);
        window.draw(allowUndoDesc);

        gameName.update(cursor, event);
        gameName.draw(window);

        whiteTime.update(cursor, event);
        whiteTime.draw(window);

        blackTime.update(cursor, event);
        blackTime.draw(window);

        allowUndo.update(cursor);
        allowUndo.draw(window);

        if (startGameButton.update(cursor))
        {
            bool settingsOk = true;
            if (gameName.getValue().empty() || GameHistory::gameExists(gameName.getValue()))
            {
                gameName.setRed();
                settingsOk = false;
            }

            if (!(whiteTime.isValueCorrect() && blackTime.isValueCorrect()))
                settingsOk = false;

            if (settingsOk == true)
                return std::pair<ProgramVariation, Settings>(ProgramVariation::NewGame, Settings(whiteTime.getValue(), blackTime.getValue(), 1, allowUndo.getValue(), gameName.getValue()));
        }
        startGameButton.draw(window);

        if(returnButton.update(cursor))
            return std::pair<ProgramVariation, Settings>(ProgramVariation::Menu, Settings());
        returnButton.draw(window);

        cursor.update(window);
        window.display();
    }
}
std::pair<ProgramVariation, std::string> loadGame(sf::RenderWindow& window, Cursor& cursor)
{
    std::vector<std::string> games = GameHistory::getAvailibleGames();
    std::vector<sf::Vector2f> positions;
    for (int i = 0; i < 800; i += 100)
        positions.push_back(sf::Vector2f((SCREEN_WIDTH / 2.F) - 50, 100+i));
    sf::Event event;

    Button scrollDown("v", sf::Vector2f((SCREEN_WIDTH / 2.F) + 300, 500), sf::Vector2f(40, 40));
    Button scrollUp("v", sf::Vector2f((SCREEN_WIDTH / 2.F) + 300, 100), sf::Vector2f(40, 40));
    scrollUp.flip_text();
    Button returnButton("return", sf::Vector2f((SCREEN_WIDTH / 2.F), 700), sf::Vector2f(650, 40));

    int posOnList = 0;
    int listLength = 5;
    while (true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            return std::pair<ProgramVariation, std::string>(ProgramVariation::Exit, "");

        }
        for (int i = posOnList; i < posOnList + listLength && i < games.size(); i++)
        {
            Button option(std::to_string(i+1) + ": " + games[i], positions[i-posOnList], sf::Vector2f(500, 40));
            option.update(cursor);
            option.draw(window);
        }

        if (scrollUp.update(cursor) && posOnList>0)
        {
            posOnList--;
        }
        scrollUp.draw(window);

        if (scrollDown.update(cursor) && posOnList+listLength < games.size())
        {
            posOnList++;
        }
        scrollDown.draw(window);

        if (returnButton.update(cursor))
            return std::pair<ProgramVariation, std::string>(ProgramVariation::Menu, "");
        returnButton.draw(window);

        cursor.update(window);
        window.display();
    }
}
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chess", sf::Style::Fullscreen);
    window.setFramerateLimit(FRAME_RATE_LIMIT);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    // Cursor
    Cursor cursor;

    // Icon Setup
    sf::Image icon;
    if (!(icon.loadFromFile(WINDOW_ICON_PATH)))
    {
        std::cout << "[WARNING]: Image not found: " << WINDOW_ICON_PATH << '\n';
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    ProgramVariation pv;
    std::pair<ProgramVariation, Settings> newGameRes;
    std::pair<ProgramVariation, std::string> loadGameRes;
    while (true)
    {
        pv = menu(window, cursor);
        if (pv == ProgramVariation::Exit)
            return EXIT_SUCCESS;
        else if (pv == ProgramVariation::NewGame)
        {
            newGameRes = newGame(window, cursor);
            if (newGameRes.first == ProgramVariation::Exit)
                return EXIT_SUCCESS;
            else if (newGameRes.first == ProgramVariation::Menu)
                continue;
        }
        else if (pv == ProgramVariation::LoadGame)
        {
            loadGameRes = loadGame(window, cursor);
            if (loadGameRes.first == ProgramVariation::Exit)
                return EXIT_SUCCESS;
            else if (loadGameRes.first == ProgramVariation::Menu)
                continue;
        }


        pv = game(window, cursor);
        if (pv == ProgramVariation::Exit)
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}