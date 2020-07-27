/*
** EPITECH PROJECT, 2020
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"
#include "catchEvent.hpp"
#include "Bomb.hpp"
#include "bombermanManager.hpp"
#include <memory>

Player::Player(BManager *manager, key_binding_t keyBinding, irr::u8 ID, bool isBot)
{
    this->_ID = ID;
    this->_key_binding = keyBinding;
    this->_isBot = isBot;
    switch (ID) {
        case 0:
            this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
                "../assets/Mesh/PlayersTextures/PlayerBasic/PlayerOne.b3d"));
            this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture(
                "../assets/Mesh/PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
            break;
        case 1:
            this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
                "../assets/Mesh/PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
            this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture(
                "../assets/Mesh/PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
            break;
        case 2:
            this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
                "../assets/Mesh/PlayersTextures/PlayerGreen/PlayerThree.b3d"));
            this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture(
                "../assets/Mesh/PlayersTextures/PlayerGreen/PlayerColorSetThree.png"));
            break;
        case 3:
            this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
                "../assets/Mesh/PlayersTextures/PlayerYellow/PlayerFour.b3d"));
            this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture(
                "../assets/Mesh/PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
            break;
        default:
            this->_mesh = manager->getsmgr()->addAnimatedMeshSceneNode(manager->getsmgr()->getMesh(
                "../assets/Mesh/PlayersTextures/PlayerBasic/PlayerOne.b3d"));
            this->_mesh->setMaterialTexture(0, manager->getdriver()->getTexture(
                "../assets/Mesh/PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
            break;
    }
    this->iddlePlayer();
    this->_prevMoveTime = -1;
    this->_statistics.speed = 1;
    this->_statistics.bombRange = 2;
    this->_statistics.bombNumber = 1;
    this->_statistics.life = 3;
    this->_statistics.wallPass = false;
    this->_objectType = PLAYER;
}

Player::~Player()
{

}

map_pos_t Player::getMapPos(std::shared_ptr<Map> map)
{
    map_pos_t result;
    irr::core::vector3df playerPos = this->_mesh->getTransformedBoundingBox().getCenter();
    irr::core::vector3df tmpBlockPos;

    result.x = 0;
    result.z = 0;
    for (irr::s32 indexZ = 0; indexZ < map->getMapZ(); indexZ++) {
        for (irr::s32 indexX = 0; indexX < map->getMapX(); indexX++) {
            tmpBlockPos = map->getBlockPosition(indexZ, indexX);
            if (playerPos.X > tmpBlockPos.X && playerPos.X < tmpBlockPos.X + BLOCK_SIZE &&
                playerPos.Z > tmpBlockPos.Z && playerPos.Z < tmpBlockPos.Z + BLOCK_SIZE) {
                result.z = indexZ;
                result.x = indexX + 1;
                return (result);
            }
        }
    }
    return (result);
}

irr::scene::IAnimatedMeshSceneNode *Player::getPlayerMesh(void)
{
    return (this->_mesh);
}

bool Player::update()
{
    if (this->_is_running) {
        if (this->_moving_state_change && this->_mesh->getFrameNr() < 1 || this->_mesh->getFrameNr() > 81) {
            this->_mesh->setFrameLoop(1, 81);
            this->_mesh->setAnimationSpeed(100);
            this->_moving_state_change = 0;
        }
    }
    else {
        if (this->_moving_state_change && this->_mesh->getFrameNr() < 91 || this->_mesh->getFrameNr() > 131) {
            this->_mesh->setFrameLoop(91, 131);
            this->_mesh->setAnimationSpeed(20);
            this->_moving_state_change = 0;
        }
    }
    return (0);
}

void Player::draw()
{
    this->_mesh->setPosition(this->_nextPosition);
}

/* START ALGO IA */
#define SCI32(x) (static_cast<irr::s32>(x))

irr::f32 floor_block(irr::f32 x)
{
    return (x - (SCI32(x * 100) % SCI32(BLOCK_SIZE * 100)) / 100);
}

irr::core::vector3df get_block_from_pos(irr::core::vector3df playerPos, std::shared_ptr<Map> map)
{
    playerPos.X = round(floor_block((playerPos.X - map->getMapOffX())) / BLOCK_SIZE);
    playerPos.Z = round(floor_block((playerPos.Z - map->getMapOffZ())) / BLOCK_SIZE);
    return (playerPos);
}

irr::f32 fake_dist_between_player(irr::core::vector3df p1, irr::core::vector3df p2)
{
    return (static_cast<irr::f32>(abs(p1.X - p2.X) + abs(p1.Z - p2.Z)));
}

void dichotomic_insert(std::vector<irr::core::vector3df> queue, irr::core::vector3df pos, irr::core::vector3df target)
{
    irr::s32 s = 0;
    irr::s32 e = queue.size() - 1;
    if (e == -1) {
        queue.push_back(pos);
        return ;
    }
    irr::s32 p = (s + e) / 2;
    irr::f32 d2 = fake_dist_between_player(pos, target);
    irr::f32 d1 = fake_dist_between_player(queue[e], target);

    while (s <= e)
    {
        p = (s + e) / 2;
        d1 = fake_dist_between_player(queue[p], target);
        if (d1 < d2)
            s += 1;
        else if (d1 > d2)
            e -= 1;
        else 
            break;
    }
    if (d1 <= d2)
        queue.insert(queue.begin() + p, pos);
    else
        queue.insert(queue.begin() + p + 1, pos);
}

irr::s32 is_valid_block(Block block, bool inDangerZone)
{
    return ((block.getBlockType() == NONE || block.getBlockType() == BREAKABLE)); // && (inDangerZone || !block->isDangerous()));
}

irr::core::vector3df initV3D(irr::f32 x, irr::f32 y, irr::f32 z)
{
    irr::core::vector3df ret;

    ret.X = x;
    ret.Y = y;
    ret.Z = z;
    return (ret);
}

irr::core::vector3df Player::getBotNodePath(BManager *manager, std::shared_ptr<Map> map, irr::u8 playerID)
{
    // manager->getBombs()[0]->getBombRange(); // <- pour les bombes

    // OLD
    /**
	 * faire la map en 2d avec la pos des ennemis et des bombes
	 * 
	 * algo : bfs qui tient compte des obstacles pour trouver l'ennemi le plus proche (si pas d'ennemi, bfs qui ne tient pas compte des obstacles)
	 * 
	 * bfs de l'ennemi pour trouver la case safe la plus proche
	 * 
	 * combiner les 2 bfs (avec un bfs en plus si besoin)
	**/

    // NEW
    /**
	 * faire la map en 2d avec la pos des ennemis et des bombes
	 * 
	 * algo : trouver l'ennemi le plus proche en ignorant les obstacle
	 * 
	 * bfs de l'ennemi pour trouver la case safe la plus proche
	 * 
	 * combiner les 2 bfs (avec un bfs en plus si besoin)
	**/

// trouver l'ennemi le plus proche du player

    map_pos_t playerPosTmp = this->getMapPos(map);
    irr::core::vector3df playerPos = irr::core::vector3df(playerPosTmp.x, this->getPos().Y, playerPosTmp.z);

    Player *closestEnemyPlayer; 
    irr::core::vector3df closestEnemy;

    // printf("playerID: %d\n", playerID);
    // printf("myBlock -> X = |%d| Z = |%d|\n", (int)playerPos.X, (int)playerPos.Z);
    for (irr::s32 i = 0, dist = -1, tmp_dist; i < manager->getplayer().size(); i++) {
        if (i == playerID)
            continue ;
        tmp_dist = fake_dist_between_player(this->getPos(), manager->getplayer()[i]->getPos());
        if (dist == -1 || dist > tmp_dist) {
            dist = tmp_dist;
            // closestEnemy = manager->getplayer()[i]->getPos();
            closestEnemyPlayer = manager->getplayer()[i];
        }
    }
    if (!closestEnemyPlayer)
        return (initV3D(-1, -1, -1));
    playerPosTmp = closestEnemyPlayer->getMapPos(map);
    closestEnemy = initV3D(playerPosTmp.x, closestEnemyPlayer->getPos().Y, playerPosTmp.z);

    // printf("closestEnemy -> X = |%d| Z = |%d|\n", (int)closestEnemy.X, (int)closestEnemy.Z);
/*
** trouver le block valide le plus proche de l'ennemi
*/
    std::vector<irr::core::vector3df> queue = {};
    //bool visited[map->getMapZ()][map->getMapX()];
    bool visited[30][40];

    for (irr::s32 i = 0; i < map->getMapZ(); i++)
        for (irr::s32 j = 0; j < map->getMapX(); j++)
            visited[i][j] = 0;

    visited[SCI32(closestEnemy.Z)][SCI32(closestEnemy.X)] = 1;

    irr::core::vector3df tmp = closestEnemy;
    irr::core::vector3df closestValidBlock = initV3D(-1, -1, -1);

    queue.push_back(closestEnemy);
    while (queue.size()) {
        // printf("queue.size %d\n", queue.size());
        tmp = queue[0];
        queue.erase(queue.begin());
        for (irr::s32 offz = -1, run = 1; offz <= 1 && run; offz++)
            for (irr::s32 offx = -1, x, z; offx <= 1; offx++) {
                if (!offx && !offz)
                    continue ;
                x = SCI32(tmp.X + offx);
                z = SCI32(tmp.Z + offz);

                if (x < map->getMapX() && x >= 0 &&
                    z < map->getMapZ() && z >= 0 &&
                    map->getMap()[z][x]->getBlockType() != UNBREAKABLE &&
                    !visited[z][x]) {
                    
                    if (map->getMap()[z][x]->getBlockType() == NONE) { // && !map->getMap()[z][x]->isDangerous())
                        closestValidBlock = initV3D(x, tmp.Y, z);
                        // printf("\n");
                        run = 0;
                        break ;
                    }
                    // printf("BLOCK SEARCHING added to queue X = |%d| Z = |%d|\n", int(x), int(z));
                    dichotomic_insert(queue, initV3D(x, tmp.Y, z), playerPos);
                    visited[z][x] = 1;
                }
            }
    }
    if (closestValidBlock.X == -1) {
        // printf("pas trouver de block le plus proche de l'ennemi");
        return (initV3D(-1, -1, -1));
    }
    // printf("closestValidBlock %d %d\n", int(closestValidBlock.X), int(closestValidBlock.Z));

    if (playerPos.X == closestValidBlock.X && closestValidBlock.Z == playerPos.Z)
        return (this->getPos());
/*
** trouver le chemin le plus court vers le block valide le plus proche de l'ennemi
*/
    //irr::core::vector3df parents[map->getMapZ()][map->getMapX()];
    irr::core::vector3df parents[30][40];
    bool inDangerZone = 1;

    for (irr::s32 i = 0; i < map->getMapZ(); i++)
        for (irr::s32 j = 0; j < map->getMapX(); j++) {
            visited[i][j] = 0;
            parents[i][j] = initV3D(-1, -1, -1);
        }
    queue.clear();
    visited[SCI32(playerPos.Z)][SCI32(playerPos.X)] = 1;

    queue.push_back(playerPos);
    while (queue.size()) {
        tmp = queue[0];
        queue.erase(queue.begin());
        for (irr::s32 offz = -1; offz <= 1; offz++)
            for (irr::s32 offx = -1, x, z; offx <= 1; offx++) {
                if (!offx && !offz)
                    continue ;
                x = SCI32(tmp.X + offx);
                z = SCI32(tmp.Z + offz);

                if (x < map->getMapX() && x >= 0 &&
                    z < map->getMapZ() && z >= 0 &&
                    is_valid_block(*map->getMap()[z][x], inDangerZone) &&
                    !visited[z][x]) {
                    if (x == closestValidBlock.X && z == closestValidBlock.Z) {
                        irr::core::vector3df current = initV3D(x, tmp.Y, z);
                        // printf("LE CHEMIN:\n        %d %d\n", int(current.Z), int(current.X));
                        while (parents[irr::s32(tmp.Z)][irr::s32(tmp.X)].X != -1) {
                            current = tmp;
                            // printf("        %d %d\n", int(tmp.Z), int(tmp.X));
                            tmp = parents[irr::s32(tmp.Z)][irr::s32(tmp.X)];
                        }
                        if (map->getMap()[irr::s32(current.Z)][irr::s32(current.X)]->getBlockType() == BREAKABLE)
                            return (this->getPos());
                        // printf("ret %d %d\n", irr::s32(current.Z), irr::s32(current.X));
                        return (initV3D(current.X * BLOCK_SIZE, current.Y, current.Z * BLOCK_SIZE));
                    }
                    // inDangerZone = (inDangerZone && map->getMap()[z][x]->isDangerous()); // faire la fonction isDangerous()
                    // printf("PATHFINDING added to queue X = |%d| Z = |%d|\n", int(x), int(z));
                    queue.push_back(initV3D(x, tmp.Y, z));
                    visited[z][x] = 1;
                    parents[z][x] = tmp;
                }
            }
    }
    // printf("pas trouver de chemin");
    return (initV3D(-1, -1, -1));
}

/* END ALGO IA */
bool Player::movement(BManager *manager, std::shared_ptr<Map> map, irr::u8 playerID)
{
    bool is_posing_bomb = false;
    const irr::u32 timeNow = manager->getdevice()->getTimer()->getTime();
    // sleep(10);
    // const irr::f32 frameDeltaTime = (irr::f32)(timeNow - this->_prevMoveTime - 10000) / 1000.f;
    const irr::f32 frameDeltaTime = (irr::f32)(timeNow - this->_prevMoveTime) / 1000.f;
    this->_nextPosition = this->getPos();
    irr::u8 botMove = 0;

    if (this->_prevMoveTime <= 0) {
        this->_prevMoveTime = timeNow;
        return (is_posing_bomb);
    }
    this->_prevMoveTime = timeNow;
    if (this->_isBot) {
        irr::core::vector3df nodePath = this->getBotNodePath(manager, map, playerID);
        // printf("%f %f %f\n", nodePath.X, nodePath.Y, nodePath.Z);
        if (nodePath.X != -1 && nodePath.Y != -1 && nodePath.Z != -1) {
            if (nodePath == this->getPos())
                botMove = BOMB;
            else if (abs(nodePath.X - abs(this->_nextPosition.X)) > abs(this->_nextPosition.Z - abs(this->_nextPosition.Z)))
                botMove = (nodePath.X < this->_nextPosition.X) ? LEFT : RIGHT;
            else
                botMove = (nodePath.Z < this->_nextPosition.Z) ? BACK : FRONT;
        }
        else
            botMove = IDDLE;
    }
    if (botMove == FRONT || (!botMove && manager->getCatchEvent()->keyIsPressed(this->_key_binding.front))) {
        this->_nextPosition.Z += PLAYER_SPEED * frameDeltaTime;
        this->_mesh->setRotation(irr::core::vector3df(0, 180, 0));
        this->runPlayer();
    }
    else if (botMove == BACK || (!botMove && manager->getCatchEvent()->keyIsPressed(this->_key_binding.back))) {
            this->_nextPosition.Z -= PLAYER_SPEED * frameDeltaTime;
        this->_mesh->setRotation(irr::core::vector3df(0, 0, 0));
        this->runPlayer();
    }
    else if (botMove == LEFT || (!botMove && manager->getCatchEvent()->keyIsPressed(this->_key_binding.left))) {
            this->_nextPosition.X -= PLAYER_SPEED * frameDeltaTime;
        this->_mesh->setRotation(irr::core::vector3df(0, 90, 0));
        this->runPlayer();
    }
    else if (botMove == RIGHT || (!botMove && manager->getCatchEvent()->keyIsPressed(this->_key_binding.right))) {
            this->_nextPosition.X += PLAYER_SPEED * frameDeltaTime;
        this->_mesh->setRotation(irr::core::vector3df(0, -90, 0));
        this->runPlayer();
    }
    else if ((!botMove && manager->getCatchEvent()->keyIsPressed(this->_key_binding.bomb))) {
        is_posing_bomb = true;
    }
    else {
        this->iddlePlayer();
    }
    return (is_posing_bomb);
}

void Player::runPlayer()
{
    if (!this->_is_running) {
        this->_is_running = true;
        this->_moving_state_change = true;
    }
}

void Player::iddlePlayer()
{
    if (this->_is_running) {
        this->_is_running = false;
        this->_moving_state_change = true;
    }
}