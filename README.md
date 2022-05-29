# Femto
> Everybody writes a screen editor. It's easy to do and makes them feel important.   
> \- Rob Pike

You have heard of [micro](https://github.com/zyedidia/micro), [nano](https://savannah.gnu.org/git/?group=nano), and [pico](https://en.wikipedia.org/wiki/Pico_(text_editor)), so now it is time for femto.

femto is a lightweight modal terminal-based text editor. It is based on ncurses with vim-like keybindings.

## Features
- Vim-like keybindings
- Normal, Visual, and Insert modes
- Basic Markdown syntax highlighting
- Common editor features such as undo/redo, line numbers, scrolling, …
- Fast `find all`, `find and replace`

## Installation

- The only dependency is ncurses.
 ####  Arch
   ```shell
   sudo pacman -S ncurses
   ```
 ####  RHEL/Fedora
   ```shell
   sudo dnf install ncurses-devel
   ```
 ####   Debian
   ```shell
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```
- Clone, compile, and run.
 ```shell
 git clone https://github.com/Elkhdiwy/Femto.git
 cd Femto
 mkdir obj
 make
 ./femto
 ```
- Enjoy.


## Todo
- [ ] cpp syntax highlighting
- [ ] support regex
- [ ] string automata

 ## Team Members
- [@mh084449](https://github.com/mh084449) 
- [@mazzensaadd](https://github.com/mazzensaadd)  
- [@Omar-Yasser](https://github.com/Omar-Yasser)  
- [@Silverhorse7](https://github.com/Silverhorse7)  
- [@Elkhdiwy](https://github.com/Elkhdiwy)  
- [@SalmaAlassal](https://github.com/SalmaAlassal)  
- [@tenafrangelos](https://github.com/tenafrangelos)  
