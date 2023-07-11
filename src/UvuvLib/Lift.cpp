#include "UvuvLib/Lift.h"


PTO* pto;
UvuvMotorGroup* liftMotors;
PIDFFController* pidController;

bool keepInPlace = true;

UvuvBasicLift::UvuvBasicLift() {
    // Nothing here lol
}   

UvuvBasicLift::UvuvBasicLift(UvuvMotorGroup* liftMotorsArg, PIDFFController* pidFFControllerArg, PTO* ptoArg) {

    liftMotors = liftMotorsArg;
    pidController = pidFFControllerArg;

    pto = ptoArg;

}

void UvuvBasicLift::rotateLiftTo(float degrees) {

    pidController->step(liftMotors->getAverageEncoderPositions(), degrees);

}

void UvuvBasicLift::setPTO(bool state) {

    if (pto != nullptr) {

        if (state) {
            pto->engagePTO();
        }
        else {
            pto->disengagePTO();
        }
        
    }


}







UvuvAdvancedLift::UvuvAdvancedLift(UvuvMotorGroup* liftMotorsArg, PIDFFController* pidFFControllerArg, float inchesFromGround,
    float minimumHeightArg, float maximumHeightArg) {

    liftMotors = liftMotorsArg;

    pidController = pidFFControllerArg;

    minimumHeight = minimumHeightArg;

    maximumHeight = maximumHeightArg;


}

UvuvAdvancedLift::UvuvAdvancedLift(std::vector<std::pair<int, motorRotation>> motorParameters, 
        PIDFFController* pidFFControllerArg, float defaultInchesFromGround, float minimumHeightArg, float maximumHeightArg) {

    liftMotors = new UvuvMotorGroup(motorParameters);

    pidController = pidFFControllerArg;

    minimumHeight = minimumHeightArg;

    maximumHeight = maximumHeightArg;

}

void UvuvAdvancedLift::moveToMaxHeight() {
    pidController->step(liftMotors->getAverageEncoderPositions(), maximumHeight);
}

void UvuvAdvancedLift::moveToMinimumHeight() {
    pidController->step(liftMotors->getAverageEncoderPositions(), minimumHeight);
}

void UvuvAdvancedLift::moveToHeight(float inchesFromGround) {
    if (inchesFromGround > minimumHeight && inchesFromGround < maximumHeight) {
        pidController->step(liftMotors->getAverageEncoderPositions(), inchesFromGround);
    }
    else {
        std::cout << "ERROR: Height out of bounds.";
    }
    

}

int UvuvAdvancedLift::getGamepiecesBeingHeld() {
    return gamepiecesHeld;
}

void UvuvAdvancedLift::grabGamepiece(int count) {
    gamepiecesHeld+=count;
}   

void UvuvAdvancedLift::dropGamepiece(int count) {
    gamepiecesHeld-=count;
}