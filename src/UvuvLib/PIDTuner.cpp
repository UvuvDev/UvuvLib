#include "UvuvLib/PIDTuner.h"
#include "Definitions.h"
#include "Math.h"
#include "Motor.h"
#include <functional>

    
UvuvGeneralPIDTuner::UvuvGeneralPIDTuner() {

}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotor* uvuvMotorPtr) {
    uvuvMotor = uvuvMotorPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::UvuvMotor;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotorGroup* uvuvMotorGroupPtr) {
    uvuvMotorGroup = uvuvMotorGroupPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::UvuvMotorGroup;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::Motor* prosMotorPtr, Gearing gearingArg) {
    prosMotor = prosMotorPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::ProsMotor;
    gearing = gearingArg;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::MotorGroup* prosMotorGroupPtr, Gearing gearingArg) {
    prosMotorGroup = prosMotorGroupPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::ProsMotorGroup;
    gearing = gearingArg;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::~UvuvGeneralPIDTuner() {
    delete filter;
    delete graph;
}


std::vector<float> UvuvGeneralPIDTuner::generatePIDValues() {

    bool continueTuning = true;

    while (continueTuning) {

        // Do sin(1) or something like that, then do an integral

        float voltage = 0;
        float rpm = 0;

        // UNFINISHED PLS FINISH TWTWTWTWTWTWTWTW

        switch(motorAPI) {
            case E_MotorAPI::UvuvMotor:
                voltage = uvuvMotor->getVoltage();
                rpm = uvuvMotor->getRPM();
                break;
            case E_MotorAPI::UvuvMotorGroup:
                break;
            case E_MotorAPI::ProsMotor:
                voltage = prosMotor->get_voltage();
                rpm = getRPM(prosMotor, gearing);
                break;
            case E_MotorAPI::ProsMotorGroup:
                voltage = averageNumbers(prosMotorGroup->get_actual_velocities());
                break;

        }


        /*======= kP =======*/

        kP = .01; // Starting kP

        pidController->kP = kP;

        /* For calculating amplitude */
        /* ------------------------- */

        float lowestValue = graph->getGraphDataPoints()->at(graphName)[0]; 
        float highestValue = graph->getGraphDataPoints()->at(graphName)[0];

        std::pair<float*, float*> amplitude = {&lowestValue, &highestValue};
        
        /* For calculating period */
        /* ---------------------- */

        int sortaRandomIndex = 18; // Kinda random but whatever

        int SRIvalue = 0;

        int period = 0;

        /* ---------------------- */

        int verticalShift = NAN;

        int horizontalShift = NAN;

        /* ---------------------- */

        pros::delay(waitTimeBetweenUpdate * 1000); // Wait so motor can catch up

        for (int i = 0; i > graph->getGraphDataPoints()->at(graphName).size(); i++) {
        
            // Set amplitude values
        
            if (graph->getGraphDataPoints()->at(graphName)[i] < lowestValue) {
                lowestValue = graph->getGraphDataPoints()->at(graphName)[i];
            }  

            if (graph->getGraphDataPoints()->at(graphName)[i] > highestValue) {
                highestValue = graph->getGraphDataPoints()->at(graphName)[i];
            }  

            // Get period values and stuff like that

            if (i == sortaRandomIndex) {
                SRIvalue = graph->getGraphDataPoints()->at(graphName)[i];
            }

            if (graph->getGraphDataPoints()->at(graphName)[i] - 10 > SRIvalue &&
                graph->getGraphDataPoints()->at(graphName)[i] + 10 < SRIvalue )
            {
                period = (i - sortaRandomIndex) * waitTimeBetweenUpdate;
            }



        }

        // Get vertical shift by averaging the Y value of the graph

        verticalShift = averageNumbers(graph->getGraphDataPoints()->at(graphName));
        
        horizontalShift = NAN;

        // Now everything's in place and we have all the necessary variables to make a sin graph

        

        for (int i = 0; i > graph->getGraphDataPoints()->at(graphName).size(); i++) {
        
            deviationVector.emplace_back( abs(graph->getGraphDataPoints()->at(graphName)[i] -
            sinGraph(i, (amplitude.second - amplitude.first), period, 
                verticalShift, horizontalShift)   ));


        }

        
        deviationLevel = averageNumbers(deviationVector);
        
        if (deviationLevel < 5) {
            continueTuning = false;
        }

        else {
                        
            if (deviationLevel > lastDeviationLevel) { // If its retuning made it better
                if( static_cast<float>(deviationLevel) / lastDeviationLevel > .95) { // Get if its 
                    kP *= 1.2;
                }
                if( static_cast<float>(deviationLevel) / lastDeviationLevel < .95) { // Get if its 
                    kP *= 2;
                }

            }

            else { // If changing kP made it worse
                if( static_cast<float>(lastDeviationLevel) / deviationLevel > .95) { // Get if its 
                    kP /= 1.2;
                }
                if( static_cast<float>(lastDeviationLevel) / deviationLevel < .95) { // Get if its 
                    kP /= 2;
                }
            }
           

            
        }

        lastDeviationLevel = deviationLevel;

        deviationVector.clear();

        
    }
    




    continueTuning = true;

    while (continueTuning) {
        
        pidController->kD = kD;

        int verticalShift = NAN;

        int horizontalShift = NAN;


        /* For calculating amplitude */
        /* ------------------------- */

        float lowestValue = graph->getGraphDataPoints()->at(graphName)[0]; 
        float highestValue = graph->getGraphDataPoints()->at(graphName)[0];

        std::pair<float*, float*> amplitude = {&lowestValue, &highestValue};
        
        /* ------------------------- */


        for (int i = 0; i > graph->getGraphDataPoints()->at(graphName).size(); i++) {
        
            // Set amplitude values
        
            if (graph->getGraphDataPoints()->at(graphName)[i] < lowestValue) {
                lowestValue = graph->getGraphDataPoints()->at(graphName)[i];
            }  

            if (graph->getGraphDataPoints()->at(graphName)[i] > highestValue) {
                highestValue = graph->getGraphDataPoints()->at(graphName)[i];
            }  


        }

        verticalShift = averageNumbers(graph->getGraphDataPoints()->at(graphName));
        
        for (int i = 0; i > graph->getGraphDataPoints()->at(graphName).size(); i++) {
        
            deviationVector.emplace_back( abs(graph->getGraphDataPoints()->at(graphName)[i] -
            verticalShift ));

        }

        int deviationLevel = averageNumbers(deviationVector);

        if (deviationLevel < 2) {
            continueTuning = false;
        }


        deviationVector.clear();

    }





    continueTuning = false;

    while (continueTuning) {




        
    }



    return {kP, kI, kD};

}





UvuvPIDFFTuner::UvuvPIDFFTuner(DesiredPIDType type, PIDController* untunedPIDFFController) {

}

  
std::vector<float> UvuvPIDFFTunergeneratePIDValues() {

}

