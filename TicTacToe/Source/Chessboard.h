/*
========================================================================================
Tic Tac Toe

Author: SwingCoder
Email: SwingCoder2@gmail.com
Github: https://github.com/SwingCoder

License: MIT License, Copyright (c) 2012 by SwingCoder
========================================================================================
*/

// chessboard component.

#ifndef __CHESSBOARD_H_
#define __CHESSBOARD_H_

#include "SoundPlayer.h"

class BaseComp;
//========================================================================================
class Chessboard  : public Component, public Timer
{
public:
    Chessboard (BaseComp* _baseComp);
    ~Chessboard();

    enum SoundName { LOST = 0x001, REMOVE, START, WIN, TIE };
    static int stepNumbers;

    void paint (Graphics& g);
    void resized();
    void mouseDown(const MouseEvent& e);

    void timerCallback();

    const String getInfo() const;
    void setFirst(const bool isFirst);    

    void playSound(SoundName soundName);

    void setTimeout(const int t) 
    { 
        timeSet = t; 
        resetThinkTime();
    }

    const int getTimeout() const
    {
        return timeSet;
    }

    void setSteps(const int steps) 
    { 
        stepSet = steps;
    }

    const int getSteps() const
    {
        return stepSet;
    }

    void resetThinkTime() 
    { 
        thinkTime = Time::getMillisecondCounter(); 
    }

private:
    //========================================================================================
    // nested class. the chesspiece have 3 properties: 
    // value, is or not human's chesspiece, is or not first (will remove after next step).
    // usage: (1) create object.  (2) set value and props
    class ChessPiece : public Component
    {
    public:
        ChessPiece(bool isHuman) : human(isHuman), value(0), first(false)  
        {
            sound.play(new MemoryInputStream
                (BinaryData::human_mp3, BinaryData::human_mp3Size, false));
        }
        //======================================================================================
        ~ChessPiece()   
        {
        }
        //======================================================================================
        void paint(Graphics& g)
        {
            g.setColour(human ? Colours::deeppink : Colours::burlywood);

            g.setFont(float(jmin(getWidth(), getHeight()) / 1.5), 
                first ? Font::underlined : Font::plain);

            String s(human ? "X" : "O");

            g.drawText(s, 0, 0, getWidth(), getHeight(), Justification::centred, false);
        }
        //======================================================================================
        void resized()
        { 
            repaint(); 
        }
        //======================================================================================
        // If received a mouse-click event, to prove that this grid has a chess piece.
        void mouseDown(const MouseEvent&)
        {
            sound.play(new MemoryInputStream
                (BinaryData::cpter_mp3, BinaryData::cpter_mp3Size, false));

            AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                TRANS("Emm"), TRANS("Here already have one."));
        }
        //======================================================================================
        void setValue(const int hasThisValue)
        { 
            value = hasThisValue; 
        }        

        const int getValue() const 
        {
            return value;
        }

        const bool isHuman() const 
        {
            return human;
        }

        void setFirst(const bool isFirst = false) 
        { 
            first = isFirst;
        }

    private:
        int value;
        bool human; 
        bool first;

        SoundPlayer sound;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChessPiece)
    };  // nested class ChessPiece end..

    //=========================================================================================

private:

    void humanPlay(Point<int> clickedPos);
    void cptPlay();
    void addAndShow(const int thisValue, bool isHuman);
    void winOrNot();

    int howManyChess(bool hasHuman);
    int sumOfHowMany(int howmany, bool hasHuman);

    bool alreadyHave(int thisValue);
    void removeFisrt();
    void removeAll();

    // core function..
    int getRandomValue();
    int getBestChessOfOne(int thisValue);
    int getBestChessOfTwo(int thisValue);

    // timeout and limit steps..
    void limitsTolose(bool isTimeOut);

    //========================================================================================
    BaseComp* baseComp;

    // 2 data structures..
    OwnedArray<ChessPiece> chess;
    OwnedArray< Rectangle<int> > checker;

    int chessSize;
    bool humanTurn;

    int humanWins, cptWins, humanTime, timeSet, stepSet;
    uint32 thinkTime;  

    ComponentAnimator animator, animator2;
    SoundPlayer soundPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chessboard)
};

#endif  // __CHESSBOARD_H_
