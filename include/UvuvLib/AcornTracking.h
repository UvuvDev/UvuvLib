#include "main.h"
#include "okapi/api.hpp"
#include "okapi/api/chassis/controller/odomChassisController.hpp"
#include "okapi/api/odometry/threeEncoderOdometry.hpp"
#include "Uvuvlib/ShapesAndCoords.h"
#include "pros/vision.h"

class AcornTracker {
private:

protected:

    pros::Vision* visionSensor = nullptr;

    pros::GPS* gpsSensor = nullptr;
    okapi::ThreeEncoderOdometry* threeEOdom = nullptr;
    okapi::TwoEncoderOdometry* twoEOdom = nullptr;
    okapi::OdomChassisController* odomChassis = nullptr;

    pros::vision_signature AcornSig = pros::Vision::signature_from_utility(1, 0, 0, 0, 0, 0, 0, 3.000, 0);
    
    std::vector<std::pair<float, float>> acornDistanceToHeight;

    float theta;

public:
    
    // Constructors

    /**
     * Argument 1: Vision Sensor. Needed for robot to see acorns. Must be facing straight ahead (for now).
     * Argument 2: Whatever Position Tracking you want. GPS sensor and Okapi Odometry Tracking are supported. 
     * Argument 3: The vision signature for the acorns. Has to be tuned properly.
     */

    AcornTracker(pros::Vision* visionSensorArg, pros::GPS* gpsSensorArg, pros::vision_signature AcornSigArg);

    AcornTracker(pros::Vision* visionSensorArg, okapi::ThreeEncoderOdometry* threeEOdomArg, pros::vision_signature AcornSigArg);

    AcornTracker(pros::Vision* visionSensorArg, okapi::TwoEncoderOdometry* twoEOdomArg, pros::vision_signature AcornSigArg);

    AcornTracker(pros::Vision* visionSensorArg, okapi::OdomChassisController* odomChassisArg, pros::vision_signature AcornSigArg);

    ~AcornTracker();

    // Sets the position tracking to a new method. WARNING: Will overwrite any previous position 
    // tracking method.

    void setPositionTracking(pros::GPS* gpsSensorArg);

    void setPositionTracking(okapi::ThreeEncoderOdometry* threeEOdomArg);

    void setPositionTracking(okapi::TwoEncoderOdometry* twoEOdomArg);

    void setPositionTracking(okapi::OdomChassisController* odomChassisArg);

    /**
     * @brief Sets the Vision Sensor object to a different sensor. 
     * 
     * @param visionSensorArg 
     */
    void setVisionSensor(pros::Vision* visionSensorArg);

    /**
     * @brief Changes the Acorn Signature object
     * 
     * @param AcornSigArg 
     */
    void setAcornSignature(pros::vision_signature AcornSigArg);

    /**
     * @brief Set the distance to height ratios on all acorn distances. The more measurements you can get, 
     * the more accurate the tracking will be. After 5 feet, distance practically stops being accurate. 
     * Inputted as an std::pair<float, float>, where the first float is the distance in inches, and the second
     * is the read height of the acorn from the vision sensor size Y function.
     * @param acornDistanceToHeightArg 
     */
    void setAcornDistanceToHeightValues(std::vector<std::pair<float, float>>* acornDistanceToHeightArg);

    void setTheta(float thetaArg);

    std::vector<std::pair<float, float>> getAcornDistanceToHeightValues();

    float getLeftmostAcornDistance(); // Gives the predicted distance of the acorn farthest to the left

    float getRightmostAcornDistance(); // Gives the predicted distance of the acorn farthest to the right


};