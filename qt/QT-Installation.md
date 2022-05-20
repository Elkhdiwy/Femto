## Install Qt Creator

- Install build essential, if you don't already have it installed. This is a package that will allow users to install and use c ++ tools:

  `sudo apt update; sudo apt install build-essential`

- Install Qt Creator package that contains the UI and command line tools for creating and running the Qt project:
 
  `sudo apt install qtcreator`

- Install Qt 5 to be used as the default version of Qt Creator:

  `sudo apt install qt5-default`

- The following command will create a file with the name of **makefile** in the project directory:

   `qmake femto-QT.pro`

- Use `make` to compile the **Makefile**:
 
  `make`

  As long as there are no errors in the project, this command should create an executable program in the working directory.

- To launch the executable file: 

  `./femto-QT`
