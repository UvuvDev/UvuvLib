#include "Uvuvlib/AcornTracking.h"
#include "pros/vision.h"
#include "pros/vision.hpp"

AcornTracker::AcornTracker(pros::Vision* visionSensorArg, pros::GPS* gpsSensorArg, pros::vision_signature AcornSigArg) {
    visionSensor = visionSensorArg;
    gpsSensor = gpsSensorArg;
    AcornSig = AcornSigArg;
}

AcornTracker::AcornTracker(pros::Vision* visionSensorArg, okapi::ThreeEncoderOdometry* threeEOdomArg, pros::vision_signature AcornSigArg) {
    visionSensor = visionSensorArg;
    threeEOdom = threeEOdomArg;
    AcornSig = AcornSigArg;
}

AcornTracker::AcornTracker(pros::Vision* visionSensorArg, okapi::TwoEncoderOdometry* twoEOdomArg, pros::vision_signature AcornSigArg) {
    visionSensor = visionSensorArg;
    twoEOdom = twoEOdomArg;
    AcornSig = AcornSigArg;
}

AcornTracker::AcornTracker(pros::Vision* visionSensorArg, okapi::OdomChassisController* odomChassisArg, pros::vision_signature AcornSigArg) {
    visionSensor = visionSensorArg;
    odomChassis = odomChassisArg;
    AcornSig = AcornSigArg;
}

AcornTracker::~AcornTracker() {
    delete visionSensor;
    delete gpsSensor;
    delete threeEOdom;
    delete twoEOdom;
    delete odomChassis;
}

void AcornTracker::setPositionTracking(pros::GPS* gpsSensorArg) {
    gpsSensor = gpsSensorArg;
}

void AcornTracker::setPositionTracking(okapi::ThreeEncoderOdometry* threeEOdomArg) {
    threeEOdom = threeEOdomArg;
}

void AcornTracker::setPositionTracking(okapi::TwoEncoderOdometry* twoEOdomArg) {
    twoEOdom = twoEOdomArg;
}

void AcornTracker::setPositionTracking(okapi::OdomChassisController* odomChassisArg) {
    odomChassis = odomChassisArg;
}

void AcornTracker::setVisionSensor(pros::Vision* visionSensorArg) {
    visionSensor = visionSensorArg;
}

void AcornTracker::setAcornSignature(pros::vision_signature AcornSigArg) {
    AcornSig = AcornSigArg;
}

void AcornTracker::setAcornDistanceToHeightValues(std::vector<std::pair<float, float>>* acornDistanceToHeightArg) {
    for (auto i = acornDistanceToHeightArg->begin(); i != acornDistanceToHeightArg->end(); i++) {
        acornDistanceToHeight.push_back(*i);

    }
}

void AcornTracker::setTheta(float thetaArg) {
    theta = thetaArg;
}

std::vector<std::pair<float, float>> AcornTracker::getAcornDistanceToHeightValues() {
    return acornDistanceToHeight;
}

float AcornTracker::getLeftmostAcornDistance() {

    pros::vision_object acorns = visionSensor->get_by_sig(0, AcornSig.id);

    float trackedAcornRadius = acorns.height / 2.0;

    float x1 = acornDistanceToHeight[0].first;
    float x2 = acornDistanceToHeight[1].second;
    float y1 = acornDistanceToHeight[0].first;
    float y2 = acornDistanceToHeight[1].second;

    for (int i = 0; i > acornDistanceToHeight.size(); i++) {
    
        // If in range of acorn radius, do linear interp. between the 2 tuples.
        if (trackedAcornRadius > acornDistanceToHeight[i-1].first && 
            trackedAcornRadius < acornDistanceToHeight[i].first) {
            x1 = acornDistanceToHeight[i-1].first;
            y1 = acornDistanceToHeight[i-1].second;
            x2 = acornDistanceToHeight[i].first;
            y2 = acornDistanceToHeight[i].second;
        }
        // If it takes up the whole screen, set the distance to 0.
        if (trackedAcornRadius == VISION_FOV_HEIGHT / 2.0) {
            x1 = VISION_FOV_WIDTH;
            y1 = 0;
            x2 = VISION_FOV_WIDTH;
            y2 = 0;                  
        }

    }
    // Linear Interpolation: y1 + [(x-x1) * (y2-y1)]/ (x2-x1)
    return y1 + ((trackedAcornRadius-x1) * (y2-y1))/ (x2-x1);


}

