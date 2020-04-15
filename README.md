# Sherlock-and-Jack (2015)
PC Game 
Language: C++
IDE & Engine: Visual Studio, custom engine (SGE).

# Prerequisites:
Microsoft DirectX SDK (June 2010)

# Instruction:
## Gameplay:
"Sherlock & Jack" is a 2D PVP chasing game. The game requires minimum two players to play, and maximum is three. The player who plays Sherlock needs to catch Jack. The player who plays Jack should avoid to be caught with invisibility cloak. The third players will control John to help Sherlock catch Jack. Sherlock and John should use their abilities well so that they can catch Jack as soon as possible.

## Controls:
### Sherlock:
	Movement: W, A, S, D
	Ability: Left Shift Button
### Jack:
	Movement: Arrow Keys
### John:
	Movement: I, J, K, L
	Ability: Space Button

## Characters' Abilities:
### Sherlock:
	Speed: 4 (7 when activate his ability)
	Taxi (Active): Sherlock can call a taxi to increase his speed
	Duration: 2s
	Cooldown: 5s
### Jack:
	Speed: 5
	Invisibility (Passive): Jack can be invisible.
	Duration: 2s
	Cooldown: 1s
### John:
	Speed: 3
	Roadblocks (Active): John can place roadblocks to block players' movement.
	Quantity: 25
	Cooldown: 1s.

# About Sherlock & Jack:
Sherlock & Jack uses SGE game engine which is provided by The Art Institute of Vancouver and created by Peter Chan and modified by Cam McRae and Jinfeng Liu. The textures and sounds used in the game are downloaded from google.com.

### Responsibilities
* Designed and implemented the UI and game state system.
* Designed and implemented multiple characters with different abilities.
* Created a random level generator.
* Implemented animation for characters, and added BGM for the game.

### What I created: 
Almost everything under "JefferyGame" project.

## Contributors:
- Professor: Peter Chan
- Jinfeng (Jeffery) Liu <liujinfeng1209@gmail.com>

