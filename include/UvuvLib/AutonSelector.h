


enum class E_Selected_Auton {
    leftSideRed1 = 1,
    leftSideRed2,
    leftSideBlue1, 
    leftSideBlue2,
    rightSideRed1,
    rightSideRed2,
    rightSideBlue1, 
    rightSideBlue2,

};

class AutonSelector {
private:

    E_Selected_Auton selectedAuton;

public:

    AutonSelector();

    ~AutonSelector();

    E_Selected_Auton getAuton();

};