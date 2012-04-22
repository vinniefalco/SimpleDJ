/*
========================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
========================================================================
*/

// strings of help and about..

#ifndef __HELPANDABOUT_H_
#define __HELPANDABOUT_H_

#include "../JuceLibraryCode/JuceHeader.h"

//======================================================================
namespace HelpAndAbout
{
	const String getHelpString()
    {
        String s = TRANS("Get help: ");
        s << "  [?]\n" <<
            TRANS("Real-time Prompts: ") << "  [H]\n" <<
            TRANS("Switch languge: ") << "  [L]\n" <<
            TRANS("Show About info: ") << "  [A]";

        return s;
    }
    //=================================================================
    const String getAboutString()
    {
        String s = "Swing Tic-Tac-Toe\n\n";

        s << TRANS("Author: SwingCoder") << "\n\n" <<
            TRANS("Copyright (C) 2012");

        return s;
    }
    //=================================================================
}

#endif  // __HELPANDABOUT_H_