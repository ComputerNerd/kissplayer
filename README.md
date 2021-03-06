**Development has ceased a long time ago, but now I decided to archive this project. I would like thank everyone involved with the project.**

-----

<img style="display: block; margin-left: auto; margin-right: auto;" width="547" height="87" src="https://user-images.githubusercontent.com/34600369/40232414-917452a4-5a96-11e8-9960-b358e99b0cd6.png">  

<br/>

### A Simple and Lightweight Music Player [![Build Status](https://travis-ci.org/andreldm/kissplayer.svg?branch=master)](https://travis-ci.org/andreldm/kissplayer)

![kissplayer](https://user-images.githubusercontent.com/599565/40580686-fe25937a-6119-11e8-82b3-01aded94b3e1.png)

Cross-platform and open-source Music Player designed to be simple and lightweight.
If you want a player full of features, most of them you don't use, exaggerated eye-candy and a memory hog, take a look around , there are lots. However if you want a different player that doesn't distract you or wastes your time, KISS Player can be a great alternative.

As of now, it's alpha, usable, but lacks some minor features and needs more polishing. Suggestions and contributions are welcome.

Note: The name has nothing to do with the metal band or the act of kissing. It's an acronym for "Keep it simple, stupid" principle.

#### Download

- **Windows** - [download](https://github.com/andreldm/kissplayer/releases) the lastest release and extract.
- **Arch Linux** - an [AUR package](https://aur.archlinux.org/packages/kissplayer/) is available: `yay -S kissplayer`

#### Usage

- First you should have your songs on one or more directories.
- Open KISS Player, click the menu button(with 3 lines) and select the option Settings.
- Add your directory(ies) and close the settings window.
- On main window menu select the option Synchronize Library.
- Now you can play your songs which are available on the left panel.
- You can also drag and drop files on main window.

#### How to build

[Check the project's wiki for instructions](https://github.com/andreldm/kissplayer/wiki/Building%20from%20source)

#### Translation
If you'd like to contribute and see KISS Player in your native language, please head over [Transifex](https://www.transifex.com/kissplayer/kissplayer).

#### Change the language
On Windows, there is an option for this under settings.<br/>
On Linux, check the current locale with the command: `locale`<br/>
Check [Arch's wiki](https://wiki.archlinux.org/index.php/Locale#Setting_the_locale) for instructions on how to manage locales.

For CJK languages under Linux, due FLTK limitations, it is necessary to pass as argument the name of a font that supports CJK characters, i.e. `./kissplayer -f Code2000`.

#### Copyright
    KISS Player
    Copyright (C) 2012-2018 by André Miranda

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
