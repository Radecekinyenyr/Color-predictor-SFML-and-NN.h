#include <SFML/Graphics.hpp>
#include "Collision/Collision.h"
#include <math.h> // atan2
#include <iostream>
#include <Windows.h>
#include "Randomer.h"
#include "NN.h"

Randomer random{ 0, 255 };
float r, g, b;
NeuralNetwork* nn = new NeuralNetwork(3, 3, 2);
std::string which;
const short SCREEN_WIDTH = 900;
const short SCREEN_HEIGHT = 500;


void pickColor()
{
    r = random();
    g = random();
    b = random();
}

std::vector<float> trainColor(float r1, float g1, float b1)
{
    if (r1 + g1 + b1 > 300)
    {
        
        return { 1, 0 };
    }
    else return { 0, 1 };
}
std::string colorPredictor(float r, float g, float b)
{
    std::vector<float> inputs = { r / 255, g / 255, b / 255 };
    std::vector<float> outputs;
    std::vector<double> out;

    outputs = nn->feedForward(inputs, 3);
    out = softMax(outputs, 2, true);
    std::cout << out[0] << std::endl;
    std::cout << out[1] << std::endl;
    std::cout << outputs[0] << std::endl;
    std::cout << outputs[1] << std::endl;
    std::cout << r + g + b << std::endl;

    if (outputs[0] > outputs[1])
    {
        return "Black";
    }
    else {
        return "White";
    }

}

void trainFunc()
{
    for (auto i = 0; i < 10000; ++i)
    {
        pickColor();
        std::vector<float> inputs = {r / 255, g / 255, b / 255};
        std::vector<float> targets = trainColor(r, g, b);
        nn->train(inputs, 3, targets, 2);

    }
}

int main(void)
{
    
    nn->setActivationFunction(sigmoidFunction, dSigmoidFunction);

    std::vector<float> targets;
    
    sf::CircleShape shape;
    shape.setRadius(40);
    shape.setOrigin(20, 20);

    sf::Vector2i mousePosition;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Color predictor");
    sf::Text whiteText;
    sf::Text blackText;
    sf::Font fonts;


    if (!fonts.loadFromFile("font/American Captain.ttf"))
        throw("Nemohu otevrit font!!");

    whiteText.setFont(fonts);
    whiteText.setString("White");
    whiteText.setCharacterSize(75);
    whiteText.setFillColor(sf::Color::White);
    whiteText.setStyle(sf::Text::Bold);
    whiteText.setOrigin(50, 50);
    whiteText.setPosition(200, 250);

   
    blackText.setFont(fonts);
    blackText.setString("Black");
    blackText.setCharacterSize(75);
    blackText.setFillColor(sf::Color::Black);
    blackText.setStyle(sf::Text::Bold);
    blackText.setOrigin(50, 50);
    blackText.setPosition(650, 250);

    trainFunc();
    
    pickColor();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
     //   mousePosition = sf::Mouse::getPosition();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            pickColor();
            which = colorPredictor(r, g, b);
            Sleep(200);

        }
        
        

        window.clear(sf::Color(r, g, b));

        window.draw(whiteText);
        window.draw(blackText);

        if (which == "White")
        {
            shape.setFillColor(sf::Color::White);
            shape.setPosition(200, 350);
            
        }
        else {    
            shape.setFillColor(sf::Color::Black);
            shape.setPosition(650, 350);
        }
        window.draw(shape);
        window.display();
    }

    delete nn;
    return 0;
}
