#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class Audio
{
private:
	Music menuMusic;
	SoundBuffer pelletBuffer, superPelletBuffer, ghostBuffer, extraLifeBuffer, deathBuffer, fruitBuffer;
	Sound pellets, superPellets, ghosts, extraLife, death, fruit;

public:
	Audio();
	void playMenuMusic();
	void playPelletSound();
	void playSuperPelletSound();
	void playGhostSound();
	void playExtraLifeSound();
	void playDeathSound();
	void playFruitSound();
};

