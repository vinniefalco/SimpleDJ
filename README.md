# AppletJUCE

This is a collection of cross platform applications and audio plugins that
demonstrate various concepts. Every project is completely self contained,
there are almost no external dependencies (except for the Steinberg SDKs, see
below).

The projects use [JUCE][1], an all-encompassing C++ class library for
developing cross-platform software. Full  sources for JUCE are included in this
repository, no additional downloads are required. The sources come from
[JUCEAmalgam][2], making it easy to add to your own project.

## Contributions

If you would like to contribute your own example programs or plugins, feel free
to fork the repository, add a new directory containing your sources, and then
submit a pull request! I ask that you make sure that your project uses the
provided amalgamated JUCE sources, this way the repository will always be self
contained to make it easy for students and beginning programmers to use. Make
sure that every file in your contribution is marked with a copyright and the
full text of the [MIT License][4] (see the HelloWorld project files for
an example).

## Steinberg SDKs (VST plugins and ASIO devices)

Unfortunately, the Steinberg SDKs' onerous licensing terms prevent
redistribution of their header files required to build a VST plugin. This is
fundamentally incompatible with almost all Open Source licenses: **you can't
create self-contained source code to make a VST plugin or use an ASIO device**.

The VST and ASIO SDKs can be obtained by for free by filling out a form and
agreeing to the licensing terms, on the [Steinberg Developer Portal][3].

If you would like to express your support for publishing Steinberg SDKs under
and Open Source-compatible license, please email Steinberg directly at
[info@steinberg.de][6]

## License

Copyright 2012 [Vinnie Falco][5].<br>
Unless otherwise specified, files are provided under the terms of the
[MIT License][4]<br>
JUCE is licensed separately, visit [Raw Material Software][1] for details,
or view the corresponding source files.<br>
Some portions of AppletJUCE are copyright by their respective owners, see the
corresponding source files for details.

[1]: http://www.rawmaterialsoftware.com/juce.php "JUCE"
[2]: https://github.com/vinniefalco/JUCEAmalgam "JUCEAmalgam"
[3]: http://www.steinberg.net/en/company/developer.html "Steinberg Developer"
[4]: http://www.opensource.org/licenses/MIT
[5]: http://vinniefalco.com "Vinnie Falco's Home Page"
[6]: mailto:info@steinberg.de "Steinberg email"
