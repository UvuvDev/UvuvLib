#include "pros/adi.hpp"

class PTO {
private:

    int smartPort; // Port of the PTO mech. 22 = ADI ports, otherwise, 3 wire extender
    char ADIport; // Port letter of the PTO mech. "A", "B", "C", "D", etc

public:

    /**
     * @brief Construct a new PTO object
     * @param smartPortArg 22 if using the ADI ports. Otherwise, this will be assumed to have a 3 wire extender.
     * @param ADIportArg Uses either ADI ports or a 3 wire extender, depending on the smart port. Input the port letter ("A", "B", "C", "D", etc)
     */
    PTO(int smartPortArg, char ADIportArg);

    /**
     * @brief Checks if the PTO is engaged or not on the selected port.
     * 
     * @return true 
     * @return false 
     */
    bool isPTOEngaged();

    /**
     * @brief Engages the PTO on the selected port.
     * 
     */
    void engagePTO();

    /**
     * @brief Disengages the PTO on the selected port.
     * 
     */
    void disengagePTO();

    /**
     * @brief Toggles the PTO on the selected port.
     * 
     */
    void togglePTO(int smartPort, char ADIport = 0);

    

};