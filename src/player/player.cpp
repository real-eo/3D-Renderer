#include "src/player/player.h"


Player::Player()                                            : pos({0, 0, 0})    { camera = Camera(&pos, Vec3(0, 0, 0)); }
Player::Player(const Vec3& offset)                          : pos({0, 0, 0})    { camera = Camera(&pos, offset); }
Player::Player(const Vec3& position)                        : pos(position)     { camera = Camera(&pos, Vec3(0, 0, 0)); }
Player::Player(const Vec3& position, const Vec3& offset)    : pos(position)     { camera = Camera(&pos, offset); }

Player::~Player() {}
