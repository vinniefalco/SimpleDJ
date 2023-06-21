# SimpleDJ

## Important Fork Notes

This should be considered a reference codebase for understanding the lengths
mid-era C++ developers had to go through prior to the arrival of modern C++.
(C++'11 and onward). Read the following JUCE forum posts before using this
codebase (i.e. VFLib usage) for study:

http://www.juce.com/forum/topic/vflib-significant-defects-found

https://forum.juce.com/t/vflib-vs-beast/11428

That said, https://forum.juce.com/t/vflib-vs-beast/11428/22 should be a 
testament to the robustness of the code, and therefore the value of it for study.

## Overview

SimpleDJ is a stand-alone application for Windows, Mac OS, and GNU/Linux
systems with X-Windows. It supports decoding, playback, and mixing of up
to four audio files simultaneously. This program was written to demonstrate
"best practices" for building robust concurrent audio applications.

## Dependencies

SimpleDJ has no external dependencies. Nothing outside of the repository
is required to build the application. It uses these libraries, which are
open source and included in the repository (in the Extern directory)

### VFLib

VFLib is a source code collection of individual modules containing
functionality for a variety of applications, with an emphasis on building
concurrent systems.

### JUCE

JUCE (Jules' Utility Class Extensions) is an all-encompassing C++ class
library for developing cross-platform software. It contains pretty much
everything you're likely to need to create most applications, and is
particularly well-suited for building highly-customised GUIs, and for
handling graphics and sound.

## License

Copyright 2012 [Vinnie Falco][1] <[e-mail][2]>.<br>
Unless otherwise specified, files are provided under the terms of the
[MIT License][3]<br>
JUCE is licensed separately, visit [Raw Material Software][4] for details,
or view the corresponding source files.<br>
Some portions of AppletJUCE are copyright by their respective owners, see the
corresponding source files for details.

[1]: http://vinniefalco.com "Vinnie Falco's Home Page"
[2]: mailto:vinnie.falco@gmail.com "Vinnie Falco's Email"
[3]: http://www.opensource.org/licenses/MIT
[4]: http://www.rawmaterialsoftware.com/juce.php "JUCE"
