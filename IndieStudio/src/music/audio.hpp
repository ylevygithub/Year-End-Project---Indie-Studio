
#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_

#include <SFML/Audio.hpp>
#include <memory>

struct music_s
{
    sf::Music menu;
    sf::Music ingame;
    sf::Music gameover;
    sf::Music intro;
};
typedef struct music_s music_t;

struct sound_s
{
    sf::SoundBuffer takeItemBuffer;
    sf::Sound takeItem;
    sf::SoundBuffer bombExplosionBuffer;
    sf::Sound bombExplosion;
    sf::SoundBuffer playerWalkingBuffer;
    sf::Sound playerWalking;
    sf::SoundBuffer bombUpBuffer;
    sf::Sound bombUp;
    sf::SoundBuffer speedUpBuffer;
    sf::Sound speedUp;
    sf::SoundBuffer wallPassBuffer;
    sf::Sound wallPass;
};
typedef struct sound_s sound_t;

/************music.cpp***********/
int MenuMusic(std::shared_ptr<music_t>);
int InGameMusic(std::shared_ptr<music_t>);
int GameOver(std::shared_ptr<music_t>);
void StopMusic(sf::Music);
int introMusic(std::shared_ptr<music_t> music);
bool isIntroPlay(std::shared_ptr<music_t> music);
void playIntro(std::shared_ptr<music_t> music);

/************sound.cpp***********/
int TakeItem(std::shared_ptr<sound_t>);
int BombExplosion(std::shared_ptr<sound_t>);
int PlayerWalking(std::shared_ptr<sound_t>);
int BombUp(std::shared_ptr<sound_t>);
int SpeedUp(std::shared_ptr<sound_t>);
int WallPass(std::shared_ptr<sound_t>);

#endif
