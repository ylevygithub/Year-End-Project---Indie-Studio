
#include "audio.hpp"

int TakeItem(std::shared_ptr<sound_t> sound)
{
    if (!sound->takeItemBuffer.loadFromFile("../assets/wav/TakeItem.wav"))
        return (-1);
    sound->takeItem.setBuffer(sound->takeItemBuffer);
    sound->takeItem.play();
    return (0);
}
int BombExplosion(std::shared_ptr<sound_t> sound)
{
    if (!sound->bombExplosionBuffer.loadFromFile("../assets/wav/BombExplosion.wav"))
    	return (-1);
    sound->bombExplosion.setBuffer(sound->bombExplosionBuffer);
    sound->bombExplosion.play();
    return (0);
}
int PlayerWalking(std::shared_ptr<sound_t> sound)
{
    if (!sound->playerWalkingBuffer.loadFromFile("../assets/wav/PlayerWalking.wav"))
    	return (-1);
    sound->playerWalking.setBuffer(sound->playerWalkingBuffer);
    sound->playerWalking.play();
    return (0);
}
int BombUp(std::shared_ptr<sound_t> sound)
{
    if (!sound->bombUpBuffer.loadFromFile("../assets/wav/BombUp.wav"))
    	return (-1);
    sound->bombUp.setBuffer(sound->bombUpBuffer);
    sound->bombUp.play();
    return (0);
}
int SpeedUp(std::shared_ptr<sound_t> sound)
{
    if (!sound->speedUpBuffer.loadFromFile("../assets/wav/SpeedUp.wav"))
    	return (-1);
    sound->speedUp.setBuffer(sound->speedUpBuffer);
    sound->speedUp.play();
    return (0);
}
int WallPass(std::shared_ptr<sound_t> sound)
{
    if (!sound->wallPassBuffer.loadFromFile("../assets/wav/WallPass.wav"))
    	return (-1);
    sound->wallPass.setBuffer(sound->wallPassBuffer);
    sound->wallPass.play();
    return (0);
}
