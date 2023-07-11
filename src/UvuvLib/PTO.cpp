
#include "PTO.h"
#include "pros/ext_adi.h"

PTO::PTO(int smartPortArg, char ADIportArg) {

}

    
bool PTO::isPTOEngaged() {

    if (smartPort == 22) {
        return pros::c::adi_digital_read(ADIport);
    }

    else {
        return pros::c::ext_adi_digital_read(smartPort, ADIport);
    }

}

   
void PTO::engagePTO() {

    if (smartPort == 22) {
        pros::c::adi_digital_write(ADIport, 1);
    }

    else {
        pros::c::ext_adi_digital_write(smartPort, ADIport, 1);
    }

}

   
void PTO::disengagePTO() {

    if (smartPort == 22) {
        pros::c::adi_digital_write(ADIport, 0);
    }

    else {
        pros::c::ext_adi_digital_write(smartPort, ADIport, 0);
    }

}

    
void PTO::togglePTO() {
    
    if (isPTOEngaged()) {
        disengagePTO();
    }
    
    else {
        engagePTO();
    }

}

    

