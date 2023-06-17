#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.h"
#include "PromotionDialog.h"
#include "Cursor.h"
#include "Consts.h"
#include "GFigure.h"
#include "PossibleMove.h"
#include "../Game.h"

void game(sf::RenderWindow& window, Cursor& cursor)
{
    // Setup logic
    Game game;

    // Object Initialization
    sf::Event event;

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
    Position from;
    Position to;
    while (true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            break;

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
                    if (!gfigures[i].isTaken() && gfigures[i].contains(cursor.getPosition()))
                    {
                        cursor.setMovingFigure(true);
                        gfigures[i].setPickedUp(true);
                        cursor.setMovingFigureID(i);
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

            cursor.update(window);

        }

        window.display();
    }
}
void menu(sf::RenderWindow& window, Cursor& cursor)
{
    sf::Event event;

    while (true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {

            window.close();
            std::cout << "[INFO]: Window closed.\n";
            break;

        }
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

    game(window, cursor);

    return EXIT_SUCCESS;
}