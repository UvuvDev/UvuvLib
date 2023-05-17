#pragma once

typedef enum {

    G_DIRECT = 600*6,
    G_BLUE = 600*1,
    G_SPEED = 600*1,
    G_GREEN = 200*1,
    G_MEDIUM = 200*1,
    G_RED = 100*1,
    G_TORQUE = 100*1,
    G_257_RPM = 600 * 3/8



} Gearing;

typedef enum {

    E_CLOCKWISE = 1,
    E_NORMAL_ROTATION = 1,
    E_COUNTER_CLOCKWISE = 2,
    E_REVERSED_ROTATION = 2
    
} motorRotation;