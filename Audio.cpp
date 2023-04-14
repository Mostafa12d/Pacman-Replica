#include "Audio.h"

Audio::Audio()
{
	// loading the sound effect
	menuMusic.openFromFile("menu music.wav");
	pelletBuffer.loadFromFile("eating pellets.wav");
	superPelletBuffer.loadFromFile("power pellet.wav");
	ghostBuffer.loadFromFile("eat ghost.wav");
	extraLifeBuffer.loadFromFile("extra life.wav");
	deathBuffer.loadFromFile("death.wav");
	fruitBuffer.loadFromFile("eat fruit.wav");
	// setting the sound 
	pellets.setBuffer(pelletBuffer);
	superPellets.setBuffer(superPelletBuffer);
	ghosts.setBuffer(ghostBuffer);
	extraLife.setBuffer(extraLifeBuffer);
	death.setBuffer(deathBuffer);
	fruit.setBuffer(fruitBuffer);
}
void Audio::playMenuMusic()
{
	menuMusic.play();
}

void Audio::playPelletSound()
{
	pellets.play();
}
void Audio::playSuperPelletSound()
{
	superPellets.play();
}
void Audio::playGhostSound()
{
	ghosts.play();
}
void Audio::playExtraLifeSound()
{
	extraLife.play();
}
void Audio::playDeathSound()
{
	death.play();
}
void Audio::playFruitSound()
{
	fruit.play();
}
