#pragma once
#include "Vector3.h"

/**
 * @file GameScene.cpp
 * @brief ゲームシーンで使う定数
 * @author カネコ_リョウタ
 */

//開始時
static const Vector3 START_EYE = { -1.0f, 0.5f, 490.0f };
static const Vector3 START_PLAYER = { 0.0f, 0.5f, 495.0f };
static const Vector3 ROTATE_FRONT = { 0.0f,90.0f,0.0f };
static const Vector3 ROTATE_BACK = { 0.0f,270.0f,0.0f };
static const float FADE_LIMIT = 1820.0f;
static const Vector3 FADE_DOWN = { 0.0f,80.0f,0.0f };
static const float ALPHA_MAX = 1.0f;
static const Vector3 ENEMY_SCALE = { 0.6f,0.6f,0.6f };
static const float ROTATE_MAX = 1.0f;

//--MAIN--//
static const float SHAKE_MAX = 1.0f;
static const float SHAKE_MIN = -1.0f;
static const float BOSS_RADIUS = 50.0f;
static const float ENEMY_RADIUS = 30.0f;
static const float ROTATE_CURSOR_MAX = 0.01f;
static const float ROTATE_CURSOR_MIN = 0.002f;
static const float ADD_ROTATE_CURSOR = 0.0005f;
static const Vector3 START_SCENE_EYEMOVE = { 0.0f, 0.0f, 0.05f };

//--BOSS--//
static const Vector3 BOSS_START_EYE = { -40, 55, -150 };
static const float SUB_PLAYER_ALPHA = 0.025f;
static const int BOSS_START_MAX = 40;
static const Vector3 BOSS_CAMERA_FORCUS = { 0.0f,0.05f,0.5f };
static const Vector3 BOSS_POP_CAMERA = { -80, 55, -300 };
static const Vector3 BOSS_POP_MOVE = { 0.75f, 0.0f, 0.25f };
static const Vector3 BOSS_SCENE_CAMERA = { 0, 53, -80 };
static const Vector3 BOSS_SCENE_PPOS = { 0, 50, -100 };
static const int BOSS_TIME = 75;
static const float BOSS_RAIL_CHECKPOINT = 3.0f;
static const float SUB_FADE = 0.1f;
static const Vector3 TO_CLEAR_CAMERA = { 0, 65, -120 };
static const Vector3 BOSS_SCENE_TARGET = { 0, 52, -200 };
static const Vector3 BOSS_FIGHT_EYE = { 0, 60, -95 };
static const Vector3 BOSS_FIGHT_TARGET = { 0, 52, -200 };
static const Vector3 BOSS_FIGHT_PPOSITION = { 0, 50, -100 };

//--CONTINUE--//
static const int DEAD_TIME = 100;
static const int GAME_TIME_MAX = 150;
static const float ADD_FADE = 0.05f;

//--PAUSE--//
static const int GAME_TIME_RESET = 75;

//--CLEAR--//
static const int CLEARTIME_ONE = 3;
static const int CLEARTIME_TWO = 53;
static const int CLEARTIME_THREE = 56;
static const int CLEARTIME_FOUR = 116;
static const int CLEARTIME_FIVE = 119;
static const int CLEARTIME_SIX = 179;
static const int CLEARTIME_SEVEN = 229;
static const int CLEARTIME_EIGHT = 264;

static const int PARTICLENUM = 35;
static const int PARTICLENUM_ONE = 3;
static const int PARTICLENUM_TWO = 6;
static const int PARTICLENUM_THREE = 9;

static const int FADENUM_ONE = 20;
static const int FADENUM_TWO = 45;

static const Vector3 CLOAR_CAMERA_MOVE = { 0.0f,-0.5f,0.0f };
static const Vector3 CLEAR_CAMERA_POS_ONE = { -30, 65, -120 };
static const Vector3 CLEAR_CAMERA_POS_TWO = { 30, 65, -120 };
static const Vector3 CLEAR_CAMERA_POS_THREE = { 0, 75, -120 };
static const Vector3 CLEAR_PLAYER_POS = { 3.8f, 49.0f, -128.0f };
static const Vector3 RED_FIRE = { -40,30,0 };
static const Vector3 GREEN_FIRE = { 0,30,0 };
static const Vector3 BLUE_FIRE = { 40,30,0 };
static const float PARTICLE_POS = -1.0f;
static const float BOSS_PARTICLE_VEL = 4.0f;
static const int BOSS_PARTICLE_NUM = 20;
static const float BOSS_PARTICLE_SCALE = 18.0f;
static const float FIRE_PARTICLE_VEL = 1.0f;
static const int FIRE_PARTICLE_NUM = 30;
static const float FIRE_PARTICLE_SCALE = 3.0f;

//--その他--//
static const float PI = 3.141592f;
static const float DEGREES = 180.0f;
static const float PROJECTION_ANGLE = 45.0f;
static const float PROJECTION_DISTANCE = 0.05f;
static const float PROJECTION_NEAR = 0.1f;
static const float PROJECTION_FAR = 200.0f;
static const float INITIAL_SCALE = 64.0f;