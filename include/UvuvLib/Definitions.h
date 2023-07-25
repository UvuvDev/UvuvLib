#pragma once

#define pi 3.14159265

typedef enum {

    G_DIRECT = 6,
    G_BLUE = 1,
    G_SPEED = 1,
    G_GREEN = 1,
    G_MEDIUM = 1,
    G_RED = 1,
    G_TORQUE = 1,
    G_257_RPM = 3/8,
    G_343_RPM = 4/7,
    G_350_RPM = 7/4



} Gearing;

typedef enum {

    E_CLOCKWISE = 1,
    E_NORMAL_ROTATION = 1,
    E_COUNTER_CLOCKWISE = 2,
    E_REVERSED_ROTATION = 2
    
} motorRotation;

typedef enum {

    E_ALLIANCE_RED = 0,
    E_ALLIANCE_BLUE = 1

} Alliance;

typedef enum {
    
    E_ARCADE_DRIVE = 0,
    E_TANK_DRIVE = 1,
    
} ControlScheme;

class BotDimensions {
public:

    float length;
    float width;
    float height;

    BotDimensions(float lengthArg, float widthArg, float heightArg): 
        length(lengthArg), width(widthArg), height(heightArg) {};

};
