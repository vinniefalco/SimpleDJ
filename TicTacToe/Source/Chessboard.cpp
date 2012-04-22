/*
==========================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================
*/

// chessboard component contain by baseComp.

/*
    most only can have 6 chess pieces on the chessboard,
    auto remove the first one if more than 6.
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComp.h"
#include "Chessboard.h"

// init static data member.
int Chessboard::stepNumbers = 0;

//==========================================================================
Chessboard::Chessboard (BaseComp* _baseComp) : baseComp(_baseComp), 
    chessSize(0), 
    humanTurn(true), 
    humanWins(0), 
    cptWins(0), 
    humanTime(0), 
    timeSet(0), 
    stepSet(0), 
    thinkTime(Time::getMillisecondCounter())
{
    playSound(START);

    // init checkers..
    for (int i = 0; i < 9; ++i)
    {
        checker.add(new Rectangle<int>());
    } 

    startTimer(200);
}
//==========================================================================
Chessboard::~Chessboard()
{
}
//==========================================================================
// draw chessboard...
void Chessboard::paint (Graphics& g)
{
    g.setColour(Colours::lightskyblue);
    
    // draw frame.
    g.drawRect(0, 0, getWidth(), getHeight(), 2);

    // draw "#"..
    float gap = float(getWidth() / 3) - 1.0f;

    g.drawLine(0.0f, gap, float(getWidth()), gap, 2.0f);
    g.drawLine(0.0f, gap * 2.0f, float(getWidth()), gap * 2.0f, 2.0f);
    g.drawLine(gap, 0.0f, gap, float(getHeight()), 2.0f);
    g.drawLine(gap * 2.0f, 0.0f, gap * 2.0f, float(getHeight()), 2.0f);
}
//==========================================================================
// ensure that this component is a square and resized each chess piece...
void Chessboard::resized()
{
    int size = jmin(getWidth(), getHeight());
    setSize(size, size);

    chessSize = getWidth() / 3;

    // every checker get size..
    for (int i = 0, index = 0, y = 0; i < 3; ++i)
    {        
        for (int j = 0, x = 0; j < 3; ++j)
        {
            checker[index]->setBounds(x, y, chessSize, chessSize);
            ++index;
            x += chessSize;
        }
        y += chessSize;
    }

    // resized each chess piece..
    for (int i = 0; i < chess.size(); ++i)
    {
        int thisValue = chess[i]->getValue();
        int posX = 0, posY = 0;

        if (4 == thisValue)      { posX = posY = 0;}
        else if (9 == thisValue) { posX = chessSize;     posY = 0;}
        else if (2 == thisValue) { posX = chessSize * 2; posY = 0;}
        else if (3 == thisValue) { posX = 0;             posY = chessSize;}
        else if (5 == thisValue) { posX = chessSize;     posY = chessSize;}
        else if (7 == thisValue) { posX = chessSize * 2; posY = chessSize;}
        else if (8 == thisValue) { posX = 0;             posY = chessSize * 2;}
        else if (1 == thisValue) { posX = chessSize;     posY = chessSize * 2;}
        else if (6 == thisValue) { posX = chessSize * 2; posY = chessSize * 2;}

        chess[i]->setBounds(posX, posY, chessSize, chessSize);
    }
}
//==========================================================================
// human dwon chess piece.
void Chessboard::mouseDown(const MouseEvent& e)
{
    if (!animator.isAnimating())
    {
        humanPlay(e.getPosition());        
    }
}
//===========================================================================
void Chessboard::timerCallback()
{
    // if timeout, game lose.
    if (timeSet != 0)
    {
        uint32 tempTime = Time::getMillisecondCounter();
        humanTime = int((tempTime - thinkTime) / 1000);

        if (humanTime > timeSet)
        {
            limitsTolose(true);
        } 
    }    

    // To prevent the disappearance of 2 chess pieces at same time (computer too fast)
    if (!animator.isAnimating())
    {
        cptPlay();          
    }  

    baseComp->setInfo();

    winOrNot();

    // steps limits to tie..
    if (stepNumbers >= stepSet && stepSet != 0)
    {
        limitsTolose(false);
    }
}
//===========================================================================
// return info strings...
const String Chessboard::getInfo() const
{
    String s = String(humanWins) + " : " + String(cptWins);
    s += '\t' + TRANS("Steps: ") + String(Chessboard::stepNumbers);
    
    if (0 != timeSet)
    {
        s += " \t";
        s += (humanTime < 10 ? TRANS("Timing:  0") : TRANS("Timing:  ")) 
            + String(humanTime);
    } 
        
    return s;
}
//===========================================================================
void Chessboard::humanPlay(Point<int> clickedPos)
{ 
    if (!humanTurn)  { return; }    

    int index = 0, value = 0;

    // Judgment click in which grid.
    for (int i = 0; i < 9; ++i)
    {
        if (checker[i]->contains(clickedPos))
        {
            index = i;
            break;
        }
    }

    // According to the index to determine the corresponding value...
         if (0 == index) {value = 4;}
    else if (1 == index) {value = 9;}
    else if (2 == index) {value = 2;}
    else if (3 == index) {value = 3;}
    else if (4 == index) {value = 5;}
    else if (5 == index) {value = 7;}
    else if (6 == index) {value = 8;}
    else if (7 == index) {value = 1;}
    else if (8 == index) {value = 6;}

    addAndShow(value, true);
    ++stepNumbers;
    humanTurn = false;
}
//==================================================================================
// According to the value to determine its location (starting point)
void Chessboard::addAndShow(const int thisValue, bool isHuman)
{
    int posX = 0, posY = 0;

         if (4 == thisValue) { posX = posY = 0;}
    else if (9 == thisValue) { posX = chessSize;     posY = 0;}
    else if (2 == thisValue) { posX = chessSize * 2; posY = 0;}
    else if (3 == thisValue) { posX = 0;             posY = chessSize;}
    else if (5 == thisValue) { posX = chessSize;     posY = chessSize;}
    else if (7 == thisValue) { posX = chessSize * 2; posY = chessSize;}
    else if (8 == thisValue) { posX = 0;             posY = chessSize * 2;}
    else if (1 == thisValue) { posX = chessSize;     posY = chessSize * 2;}
    else if (6 == thisValue) { posX = chessSize * 2; posY = chessSize * 2;}

    // the element add to array. set its value..
    chess.add(new ChessPiece(isHuman));
    chess.getLast()->setValue(thisValue);

    // display on chessboard..
    addAndMakeVisible(chess.getLast());    
    chess.getLast()->setBounds(posX, posY, chessSize, chessSize);        

    removeFisrt();
    resetThinkTime(); 
}
//==================================================================================
void Chessboard::cptPlay()
{    
    if (humanTurn || animator.isAnimating())  { return; }    
    
    // 4 kinds of responses: to win, defensive, offensive, random

    /*   cptr     human         
          0         1       -->defensive
          1         1       -->offensive
          1         2       -->defensive, else random
          2         2       -->(to win, defensive, offensive), else random
          2         3       -->(to win, defensive, offensive), else random
          3         3       -->to win, else random

          all other responses  -->random
    */
    int value = getRandomValue();

    if (0 == howManyChess(false) && 1 == howManyChess(true))
        value = getBestChessOfOne(sumOfHowMany(1, true));

    else if (1 == howManyChess(false) && 1 == howManyChess(true))
        value = getBestChessOfOne(sumOfHowMany(1, false));      
    
    else if (1 == howManyChess(false) && 2 == howManyChess(true))
        value = getBestChessOfTwo(sumOfHowMany(2, true)); 
    
    else if (2 == howManyChess(false) && 2 == howManyChess(true))
    {
        value = getBestChessOfTwo(sumOfHowMany(2, false)); 

        if (15 != value + sumOfHowMany(2, false))
            value = getBestChessOfTwo(sumOfHowMany(2, true));
    }
    
    else if (2 == howManyChess(false) && 3 == howManyChess(true))
    {
        value = getBestChessOfTwo(sumOfHowMany(2, false));
        
        if (15 != value + sumOfHowMany(2, false))
            value = getBestChessOfTwo(sumOfHowMany(2, true));
    }

    else if (3 == howManyChess(false) && 3 == howManyChess(true))
    {
        value = getBestChessOfTwo(sumOfHowMany(2, false));

        if (15 != value + sumOfHowMany(2, false))
            value = getBestChessOfTwo(sumOfHowMany(2, true));
    }

    else
        value = getBestChessOfTwo(sumOfHowMany(2, true));
    
    addAndShow(value, false);
    ++stepNumbers;
    humanTurn = true;
}
//==================================================================================
void Chessboard::winOrNot()
{
    if (howManyChess(true) + howManyChess(false) < 5) { return; }
 
    // human win..
    if (3 == howManyChess(true) && 15 == sumOfHowMany(3, true))
    {
        playSound(WIN);
        animator.cancelAllAnimations(true);    

        AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
            TRANS("congrats!"), 
            TRANS("You won!!"));

        removeAll(); 
        ++humanWins;          
    } 
    // computer win..
    else if (3 == howManyChess(false) && 15 == sumOfHowMany(3, false))
    {
        playSound(LOST);
        animator.cancelAllAnimations(true);

        AlertWindow::showMessageBox(AlertWindow::InfoIcon, 
            TRANS("HiaHia..."), 
            TRANS("I won!!"));

        removeAll();
        ++cptWins;   
    }    
}
//==================================================================================
 // Calculate the current human or computer each have how many chess pieces.
int Chessboard::howManyChess(bool hasHuman)
{
    int howMany = 0;

    for (int i = 0; i < chess.size(); ++i)
    {
        if (hasHuman && chess[i]->isHuman())
            ++howMany;
        
        if (!hasHuman && !chess[i]->isHuman())
            ++howMany;
    }

    return howMany;
}
//==================================================================================
// sum the value of lastest N chess pieces of human or computer.
int Chessboard::sumOfHowMany(int howmany, bool hasHuman)
{
    int sum = 0;

    for (int i = chess.size() - 1; i >= 0 && howmany > 0; --i)
    {
        if (hasHuman && chess[i]->isHuman())
        {
            sum += chess[i]->getValue();
             --howmany;
        }

        if (!hasHuman && !chess[i]->isHuman())
        {
            sum += chess[i]->getValue();
             --howmany;
        }
    }
    return sum;
}
//=================================================================================
// Randomly chosen a value, do not repeat existing.
int Chessboard::getRandomValue()
{
    int rValue = Random::getSystemRandom().nextInt (9) + 1;
    
    while (alreadyHave(rValue))
        rValue = Random::getSystemRandom().nextInt (9) + 1;

    return rValue;
}
//===================================================================================
// when 1 chess piece on chessborad (human or computer)...
int Chessboard::getBestChessOfOne(int thisValue)
{
    int defendValue = 0;

    if (1 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 8;
            if (alreadyHave(defendValue)) {
                defendValue = 6;
                if (alreadyHave(defendValue)) {
                    defendValue = 9;
                    if (alreadyHave(defendValue))
                        defendValue = getRandomValue();
                } } } }
    else if (2 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 9;
            if (alreadyHave(defendValue)) {
                defendValue = 7;
                if (alreadyHave(defendValue)) {
                    defendValue = 6;
                    if (alreadyHave(defendValue)) {
                        defendValue = 4;
                         if (alreadyHave(defendValue)) {
                             defendValue = 8;
                             if (alreadyHave(defendValue))
                                 defendValue = getRandomValue();
                         } } } } } }    
    else if (3 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 4;
            if (alreadyHave(defendValue)) {
                defendValue = 8;
                if (alreadyHave(defendValue)) {
                    defendValue = 7;
                    if (alreadyHave(defendValue))
                        defendValue = getRandomValue();
                } } } }    
    else if (4 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 9;
            if (alreadyHave(defendValue)) {
                defendValue = 3;
                if (alreadyHave(defendValue)) {
                    defendValue = 2;
                    if (alreadyHave(defendValue)) {
                        defendValue = 8;
                        if (alreadyHave(defendValue)) {
                            defendValue = 6;
                            if (alreadyHave(defendValue))
                                defendValue = getRandomValue();
                        } } } } } }  

    else if (5 == thisValue) 
        defendValue = getRandomValue();

    else if (6 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 7;
            if (alreadyHave(defendValue)) {
                defendValue = 1;
                if (alreadyHave(defendValue)) {
                    defendValue = 2;
                    if (alreadyHave(defendValue)) {
                        defendValue = 8;
                        if (alreadyHave(defendValue)) {
                            defendValue = 4;
                            if (alreadyHave(defendValue))
                                defendValue = getRandomValue();
                        } } } } } }
    else if (7 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 2;
            if (alreadyHave(defendValue)) {
                defendValue = 6;
                if (alreadyHave(defendValue)) {
                    defendValue = 3;
                    if (alreadyHave(defendValue))
                        defendValue = getRandomValue();
                } } } }
    else if (8 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 3;
            if (alreadyHave(defendValue)) {
                defendValue = 1;
                if (alreadyHave(defendValue)) {
                    defendValue = 4;
                    if (alreadyHave(defendValue)) {
                        defendValue = 6;
                        if (alreadyHave(defendValue)) {
                            defendValue = 2;
                            if (alreadyHave(defendValue))
                                defendValue = getRandomValue();
                        } } } } } }
    else if (9 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) {
            defendValue = 2;
            if (alreadyHave(defendValue)) {
                defendValue = 4;
                if (alreadyHave(defendValue)) {
                    defendValue = 1;
                    if (alreadyHave(defendValue))
                        defendValue = getRandomValue();
                } } } }

    else if (10 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue))
            defendValue = getRandomValue();
    }
    else if (11 == thisValue) {
        defendValue = 4;
        if (alreadyHave(defendValue))
            defendValue = getRandomValue();
    }
    else if (12 == thisValue) {
        defendValue = 3;
        if (alreadyHave(defendValue))
            defendValue = getRandomValue();
    }
    else if (13 == thisValue) {
        defendValue = 2;
        if (alreadyHave(defendValue))
            defendValue = getRandomValue();
    }
    else if (14 == thisValue) {
        defendValue = 1;
        if (alreadyHave(defendValue))
            defendValue = getRandomValue();
    }

    else
    {
        defendValue = getRandomValue();
    }

    return defendValue;
}
//===================================================================================
int Chessboard::getBestChessOfTwo(int thisValue)
{
    int defendValue = getRandomValue();

    if (6 == thisValue) {
        defendValue = 9;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    } 
    else if (7 == thisValue) {
        defendValue = 8;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (8 == thisValue) {
        defendValue = 7;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (9 == thisValue) {
        defendValue = 6;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (10 == thisValue) {
        defendValue = 5;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (11 == thisValue) {
        defendValue = 4;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (12 == thisValue) {
        defendValue = 3;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (13 == thisValue) {
        defendValue = 2;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }
    else if (14 == thisValue) {
        defendValue = 1;
        if (alreadyHave(defendValue)) 
            defendValue = getBestChessOfOne(defendValue);
    }

    return defendValue;
}
//====================================================================================
// Determine this value whether in the array.
bool Chessboard::alreadyHave(int thisValue)
{
    for (int i  = 0; i < chess.size(); ++i)
        if (thisValue == chess[i]->getValue())
            return true;
    
    return false;
}
//====================================================================================
// more than 6, automatically removes the earliest.
void Chessboard::removeFisrt()
{
    if (chess.size() > 6)
    {
        playSound(REMOVE);

        // animation remove..
        animator.animateComponent(chess[0], 
            Rectangle<int>(getWidth(), 0, 0, 0), 0.45f, 600, true, 1.0, 0.0);          

        chess.remove(0, true);   
    }

    // show or don't show hint (first has underline).
    setFirst(baseComp->getHintState());
}
//=====================================================================================
// call this function after every win and lose, then to start a new round...
void Chessboard::removeAll()
{
    playSound(START);

    for (int i =0; i < chess.size(); ++i)
        animator2.animateComponent(chess[i], 
            Rectangle<int>(0, getHeight(), 0, 0), 0.45f, 800, true, 1.0, 0.0);

    chess.clear(true);
    stepNumbers = 0;
    resetThinkTime();    
}
//=====================================================================================
// timeout or reached limit steps...
void Chessboard::limitsTolose(bool isTimeOut)
{
    animator.cancelAllAnimations(true);
    playSound(isTimeOut ? LOST : TIE);

    String s = isTimeOut ? 
        TRANS("Timeout!  You lose!") : TRANS("Step Limits! We tie!");

    AlertWindow::showMessageBox(AlertWindow::InfoIcon, TRANS("Sorry..."), s);

    if (isTimeOut)
        ++cptWins;

    removeAll();    
}
//=====================================================================================
// show or don't show hint (first has underline).
void Chessboard::setFirst(const bool isFirst)
{
    for (int i = 0; i < 2 && i < chess.size(); ++i)
    {
        chess[i]->setFirst(isFirst ? true : false);
        chess[i]->repaint();
    }
}
//=====================================================================================
void Chessboard::playSound(SoundName soundName)
{
    MemoryInputStream* audioStream = nullptr;

    switch (soundName)
    {
    case LOST: 
        audioStream = new MemoryInputStream
            (BinaryData::lost_mp3, BinaryData::lost_mp3Size, false);
        break;

    case REMOVE:
        audioStream = new MemoryInputStream
            (BinaryData::remove_mp3, BinaryData::remove_mp3Size, false);
        break;

    case START:
        audioStream = new MemoryInputStream
            (BinaryData::start_mp3, BinaryData::start_mp3Size, false);
        break;

    case WIN:
        audioStream = new MemoryInputStream
            (BinaryData::win_mp3, BinaryData::win_mp3Size, false);
        break;

    case TIE:
        audioStream = new MemoryInputStream
            (BinaryData::cpter_mp3, BinaryData::cpter_mp3Size, false);
        break;

    default:
        break;
    }

    soundPlayer.play(audioStream);
}