Name: Jinfeng Liu (Jeffery)

Accomplished:
1. I made a game based on "HellowAnimation" project.
2. Find source images on the Internet.
3. Cut and resized images.
4. Created the 2D tile map with source images.
5. Changed character's textures and animation. Changed "Mario" to my character (Jack).
6. Modified the movements. Deleted the gravity and allow players to move left, right, up and down.
7. Added second character (Sherlock) along with textures, animation, and movement.
8. Created keys for each players' movement.
9. Created "Counter.h" and "Counter.cpp" files for counting the time.
10. Added "Invisible" ability for thief "Jack".
11. Added "Call a Taxi" ability for first cop "Sherlock".
12. Modified "map.h" and "map.cpp" files to add "MovementCost".
13. Added title page, three different background music, new button with new textures.
14. Added game instructions on title page (Modified SGE file).
15. Added third character (John) in the game.
16. Added "Roadblock" ability for second cop "John".
17. Tested "Roadblock" ability and delay it to activate. 
18. Added three more "gamestates" for three different end page.
19. Added three different end page.
20. Added buttons and function to ask if players want a new game in end page.
21. Added game time to count down.
22. Added collision in the game (Modified SGE file).
23. Added "game time", "Call a Taxi cooldown time" and "Roadblock counter" in gameplay page.
24. Tested the game and tested each ability.
25. Changed the game time, abilities' time and roadblock's number.

Problems (when):
1. Adding "Counter.h" and "Counter.cpp" for counting time.
2. Adding "MovementCost".
3. Adding "Game instructions" on title page. I want to show different messages when player click the different buttons.
4. Fixing the "Roadblock" bug.
5. Adding "collision" in the game.

I will do next:
1. Let my friends to play the game and collect the feedback from them, both on game instructions and gameplay.
2. Make it works on everyone's PC. Fix "Missing MSCVP120D.dll".
3. Add treasures and different items let players to collect (Bombs, keys).
4. Add keys, doors and ships for thief escaping.
5. Add dead (catching) animation.
6. Add more or random maps.



Game Instructions:

Game Name: Sherlock & Jack (PVP)
Jack Sparrow came to Hogwarts and he stole lots of magic stuff from this School of Witchcraft and Wizardry. One day, he stole the invisibility cloak from Harry Potter! So, Albus Dumbledore invited Sherlock Holmes and Dr. John Watson to Hogwarts and helped him to catch Jack Sparrow.  

Gameplay:
"Sherlock & Jack" is a 2D PVP chasing game. The game requires minimum two players to play, and maximum is three. The player who plays Sherlock needs to catch Jack. The player who plays Jack should avoid to be caught with invisibility cloak. The third players will control John to help Sherlock catch Jack. Sherlock and John should use their abilities well so that they can catch Jack as soon as possible.

Controls:
Sherlock:
	Movement: W, A, S, D
	Ability: Left Shift Button
Jack:
	Movement: Arrow Keys
John:
	Movement: I, J, K, L
	Ability: Space Button

Characters' Abilities:
Sherlock:
	Speed: 4 (7 when activate his ability)
	Taxi (Active): Sherlock can call a taxi to increase his speed
	Duration: 2s
	Cooldown: 5s
Jack:
	Speed: 5
	Invisibility (Passive): Jack can be invisible.
	Duration: 2s
	Cooldown: 1s
John:
	Speed: 3
	Roadblocks (Active): John can place roadblocks to block players' movement.
	Quantity: 25
	Cooldown: 1s.

About Sherlock & Jack:
Sherlock & Jack uses SGE game engine which is provided by The Art Institute of Vancouver and created by Peter Chan and modified by Cam McRae and Jinfeng Liu. The textures and sounds used in the game are downloaded from the internet.
