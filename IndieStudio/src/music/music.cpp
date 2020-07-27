
#include "audio.hpp"

int MenuMusic(std::shared_ptr<music_t> music)
{
    if (!music->menu.openFromFile("../assets/ogg/menu.ogg"))
    	return (-1);
    music->menu.play();
    music->menu.setLoop(true);
    return (0);
}

int InGameMusic(std::shared_ptr<music_t> music)
{
    if (!music->ingame.openFromFile("../assets/ogg/ingame.ogg"))
	    return (-1);
    music->ingame.play();
    music->ingame.setLoop(true);
    return (0);
}

int GameOver(std::shared_ptr<music_t> music)
{
    if (!music->gameover.openFromFile("../assets/ogg/GameOver.ogg"))
        return (-1);
    music->gameover.play();
    return (0);
}

bool isIntroPlay(std::shared_ptr<music_t> music)
{
    if (music->intro.getStatus() == sf::Sound::Status::Stopped)
        return (false);
    else
        return (true);
}

void playIntro(std::shared_ptr<music_t> music)
{
    music->intro.play();
}

int introMusic(std::shared_ptr<music_t> music)
{
    if (!music->intro.openFromFile("../assets/ogg/indihub.ogg"))
        return (-1);
    return (0);
}

void StopMusic(sf::Music music)
{
    music.stop();
}
