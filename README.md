This program only works with SDL 2 attached to it. If you want to run it, you will have to set that up. Here are some good intructions that I found that will help with that. It explains it far better than I ever could:

Setting up SDL 2 on Visual Studio 2019 Community Edition
Last Updated: Sep 17th, 2022: [Click Here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)

Setting up SDL 2 on Linux
Last Updated: Sep 17th, 2022: [Click Here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php)

Setting up SDL 2 on Mac OS X Sonoma
Last Updated: Jan 7th, 2024: [Click Here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)

***You also have to download SDL2_Image and SDL2_ttf (image and true type fonts). Combine the includes and libs folders from these inside of the regualr SDL include and libs folders. Contrastly, you could just add each of the libs and includes in the project separately if you prefer***

[Click here for the releases of SDL2 image](https://github.com/libsdl-org/SDL_image/releases)
[Click here for the releases of SDL2 ttf](https://github.com/libsdl-org/SDL_ttf/releases)

If you managed to get it working, just compile and run the main function, there are no errors as of this commit but there may be linker or other 
errors if you didn't configure SDL2 properly. When you get it working, a GUI will pop up, just click the play button that shows up in the GUI and the game scene will appear. Pay attention to the text at the top of the window, it will tell you what to do in each phase of the game.

This is just an experimental program, I'm currently creating a 2D game engine where I will be making a full scale version of this. It will also be a card counting simulator. Feel free to take this code and use it as a template for simple GUIs or just to get familiar with basic SDL2 functions. There is extensive commentary within the code that will explain everything as you read it. Start at Game.h and follow the comments.
