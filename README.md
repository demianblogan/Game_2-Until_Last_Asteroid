[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.ua.md)

# Brief description of the game
This is my first game for my portfolio. Its genre is "Shoot 'Em Up". In this game, you control a spaceship and shoot at enemies, including asteroids and other ships. You have multiple lives, earn points, and complete levels.

![1](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3b0eb5bc-6564-49be-a4cb-a588289da779)

## **Game controls:**<br />
Arrow up    -> Move forward<br />
Arrow left  -> Rotate left<br />
Arrow right -> Rotate right<br />
Arrow down  -> Jump to hyper scape (jump to random position)<br />
Space       -> Shoot<br />
Escape      -> Close the game<br />

## **How to play?**<br />
When you launch the game, you'll see the text "Press any key to start". It's a pause menu. Every time you die - you'll see this window. If you want to close the game anytime - just press the Escape key. The game has an infinite number of levels. Every level contains some number of asteroids and saucers. To complete a level, you must destroy them all and wait until all your bullets are disappeared. (Every bullet disappears after 5 seconds). The game has its score. You get points for every destroyed asteroid or saucer. If you gain another 1000 points - you'll get an extra life. At the beginning of the game, you have 3 lives. You lose one life when an asteroid, enemy saucer, or its bullets touch you. If you lose all your lives - the game will restart. The game's world has no boundaries, so if you flew out of the world's one side - you'll appear on its other side.

## **Who are the enemies?**<br />
1. Big asteroid - small speed, floats in a random direction. When destroyed, splits into several medium asteroids, and you get +20 points.<br />
2. Medium asteroid - medium speed, floats in a random direction. When destroyed, splits into several small asteroids, and you get +60 points.<br />
3. Small asteroid -  high speed, floats in a random direction, and you get +100 points.<br />
4. Saucer kamikaze - moves quickly towards you. When destroyed, you'll get +200 points.<br />
5. Big saucer -  moves quickly towards you, shoots you. When destroyed, you'll get +50 points.<br />

## **How to create and build this project in Visual Studio?**<br />
NOTE: I need to have installed Visual Studio 2022, which supports C++20 standard. Google how to do it.<br />

1. Download this repository as a .zip file and extract it.<br />
![2](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/97026464-e1ae-4787-820d-d5aeabf59556)

2. Create an empty C++ project in Visual Studio.<br />
![3](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/ba48864e-86ff-421e-8f27-5be65d026eda)

3. Open the project's folder in File Explorer and move all files from the archive into it.<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/a061ec73-8441-4bed-ab4b-b5b9e8afce44)

4. To make all those files visible in your project, click the button "Show all files" in Solution Explorer.<br />
![4](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/21533c25-f96e-4e53-bbb8-40ffdc63f1c3)

5. Select all files in Solution Explorer, press RMB, and click "Include In Project" (some files in inner folders might not be included, so you can include them individually).<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/e99f90ad-0c66-4e97-ba13-0b715ba0a52a)

6. We need to link the SFML library to the project and change the C++ standard to C++20. So go to the project's properties.<br />
![5](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/bf9e841d-9119-49db-a0cf-107d75c39767)

7. Select "All Configurations" and "All Platforms".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/32a7b835-c44a-4807-88ef-f1aff00f1456)

8. In "Configuration Properties" go to the tab "General", find "C++ Language Standard" and select "ISO C++20 Standard (/std:c++20".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/30d7c9f7-aefa-44aa-b352-f6d993872c4e)

9. SFML library consists of three parts: .h/.cpp files (folder "include"), .lib files (folder "lib"), and .dll files. Let's link the "include" folder first. Go to the "C/C++" tab, find "Additional Include Directories", press the arrow on its right, and click "<Edit...>".<br />
![8](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/79cb8d11-aabb-40e5-897f-ddbf3fe087c1)

10. In the new window double-click on the empty line, type "$(ProjectDir)SFML\include", and press "OK" at the bottom of the window.<br />
![9](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/4257e884-5b7f-41da-b223-804560326285)

11. You need to do the same with .lib files: go to the tab "Linker", find "Additional Library Directories", press the arrow on its right, and click "<Edit...>".<br />
![10](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3ada0b06-2495-444c-ba47-03de46a538f5)

12. Do the same as you did in item #10, but now write "$(ProjectDir)SFML\lib".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/a0488d5d-414c-4050-9a61-9f9ae3860f52)

13. Almost done. We only need to add .dll files to our project. Save your changes by clicking the "Apply" button at the bottom of the project's properties, change the configuration to "Debug", go to "Linker" -> "Input" tab, find "Additional Dependencies", click the arrow on its right, and click "<Edit...>".<br />
![11](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/d6be1795-e5a9-49c4-b285-0bf18b07ed25)

14. In the popup window write the next lines:<br />
sfml-system-d.lib<br />
sfml-window-d.lib<br />
sfml-audio-d.lib<br />
sfml-graphics-d.lib<br />
sfml-network-d.lib<br />
and press "Ok" button.<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/58e2669e-8805-4624-b2a5-aaf502f12297)

15. Press "Apply", switch configuration to "Release" and do the same things, but write the next lines:<br />
sfml-system.lib<br />
sfml-window.lib<br />
sfml-audio.lib<br />
sfml-graphics.lib<br />
sfml-network.lib<br />
and press "Ok" button.<br />
![12](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3f3f6dd1-6dae-46f0-8f26-6a9c873685c7)

16. That's it! Press "Apply", and now SFML is linked to your project.

17. To compile & launch the game, press "Ctrl + F5".
