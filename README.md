Pyromania
=========

*Archived code of my attempt to make a POCO and Irrlicht based Bomberman clone, 2011-2013*

Read more about it on my [blog](http://blog.squareys.de/tag/pyromania/).

This code currently only contains the 3D version of the client, which I only posted
[on facebook](https://www.facebook.com/Squareys/photos/a.194342153966540.47777.177219555678800/570479649686120/)
about (once).
The 2D and 3D client both share game and net code. Should I find the 2D client code, I will of course add it
to this repository.

**Note:** I created this in my early days of programming and I didn't touch a line of code since, do not infer
any qualities about my current code from it.

# Building

*It may not compile.*

I honestly don't know. Back then I was using [MinGW](http://mingw.org/), judging from some exectuables
the standard 32 bit version (I later switched to MinGW64).

You will notice the folders contain a set of Eclipse CDT ".project" files. You can hopefully just import
them into an Eclipse CDT and go with it.

As far as I can tell, you'll need to build "Pyromania Gamelogic" first, which builds a static library used
by both the client and server.

## Dependencies

Some old version from 2011/2012 (;P) of the following libraries:

 - Irrlicht
 - POCO
 - Maybe SDL2 (I am unsure why I had that "SDL Test" project there)

# Maps

I created the maps using [Tiled](https://www.mapeditor.org/). To convert the resulting ".dat" file to
a set of .map files, you will need to compile and use "PyromaniaMapConverter".


# Running

You will need to start the server first, then the client, obviously ;)

# Licence

The code of this project is licensed under the MIT/Expat license:

~~~
Copyright © 2011-2018 Jonathan Hale <squareys@googlemail.com>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
~~~
