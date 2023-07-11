# UvuvLib

UvuvLib is a library intended to just do everything humanely possible to get you to where you need to go.

This library includes several other libraries (no need to install), such sa Fido, Graphy, and others in the future. 
All will be linked below for due credit. Some I leave plain as is like Fido, others like Graphy I build off of to 
make better and more useful.

https://github.com/jazonshou/Graphy

https://github.com/FidoProject/Fido

This description is updated for Version 0.00, the first Beta release of UvuvLib.

Current functionality of UvuvLib is the following:

Custom Motors/Motorgroups
A Pre-Built Drivetrain class
An Input Reader to track your controller inputs and save them to an SD Card
A Pre-Built lift class
A Pre-Built Flywheel class
PID
Lightweight Field class for easier tracking of Auton progress 
Custom Controller Software
Extra Math Functions
Logger class for logging variables, and a Poller for reading from the SD Card
Auton Maker found here: https://github.com/7121B/AutonMakerV2
Graphing using Graphy as a core
Machine Learning capabilities using Fido 

Many of these will have bugs as I haven't been able to test most of the code on an actual bot.

Current timeline is as follows:

1. Pure Pursuit 
2. Skills Simulator, to be able to practice your driving skills runs
3. Vision Sensor simulation application using Jupyter Notebook and OpenCV, letting you test code while seeing what's happening
4. Filters, including a Kalman Filter
5. The UvuvCompass, which will use Kalman Filtering for the most accurate position tracking possible
6. A full on PID Tuner that will tune PIDs for you
7. Improving the Graphing Tool functionality and taking it to the limit

I may throw in LED control and some other things at some point, but I don't really know how far UvuvLib will go. The 7 listed are the current goals for code, and hopefully I can do it with help from the community as well.

Contributors:

Lucas - 7121A

Beta Testers:

Aidan - 70761S

Can't wait to get this thing working.

