# jrl_acc

**jrl_acc** is an ACS script compiler, for use in tandem with [ZDoom](http://zdoom.org/News) and [Hexen](http://doom.wikia.com/wiki/Hexen).

It is based on the original [acc](https://github.com/rheit/acc) repository,
but is redesigned in C++ using [JUCE](https://github.com/julianstorer/JUCE) for a modern approach to its code.

# Build Status

| [Travis-CI](https://travis-ci.org/) |
| :-------: |
| [![Build Status](https://travis-ci.org/jrlanglois/jrl_acc.svg?branch=master)](https://travis-ci.org/jrlanglois/jrl_acc) |

# Licensing
http://opensource.org/licenses/lgpl-3.0.html

# Get Started

* In the same folder:
  * Clone [JUCE](https://github.com/julianstorer/JUCE).
  * Clone [jrl_acc](https://github.com/jrlanglois/jrl_acc).
* Open up a **jrl_acc** project that is supported on your platform.
* Compile the project.
* Run the project, if you want to run the GUI version.

# New Features
* Can be compiled on Windows, MacOSX and Linux.
* Supports the following IDEs/compilers:
  * VS2015
  * VS2013
  * VS2012
  * VS2010
  * VS2008
  * VS2005
  * Xcode (OSX)
  * Linux Makefile
  * Code::Blocks (Windows)
  * Code::Blocks (Linux)
* Unity build module that can be easily brought into any existing JUCE project.
* Lightning fast compile times.
* Code editor.
  * Code tokeniser and syntax highlighter.
  * Internal CLI for continuous development in one swift workflow

# Contribution Guidelines
Suggestions, improvements and pull requests are welcome!

But do ensure that they adhere to the following guidelines:
* Search previous suggestions before making a new one, as yours may be a duplicate.
* Make an individual pull request for _*each*_ suggestion.
* Make sure your text editor is set to remove all trailing whitespace.
* Absolutely _*no tabs*_. Use 4 spaces.
* Code changes must follow JUCE's [coding standard](http://www.juce.com/learn/coding-standards).
* Keep descriptions short, simple and understandable.
* Start the description with a capital and end with a full stop/period.
* Check your spelling and grammar, and follow UK English spelling (e.g.: "colour", "specialisation").
