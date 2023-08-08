# UvuvLib

UvuvLib is a library intended to just do everything humanely possible to get you to where you need to go.

This library includes several other libraries (no need to install), such sa Fido, Graphy, and others in the future. 
All will be linked below for due credit. Some I leave plain as is like Fido, others like Graphy I build off of to 
make better and more useful.

https://github.com/jazonshou/Graphy

https://github.com/FidoProject/Fido

This description is updated for Version 0.01, the second beta release of UvuvLib, now with Pure Pursuit!.

Current functionality of UvuvLib is the following:

1. Custom Motors/Motorgroups
2. A Pre-Built Drivetrain class
3. An Input Reader to track your controller inputs and save them to an SD Card
4. A Pre-Built lift class
5. A Pre-Built Flywheel class
6. PID
7. Lightweight Field class for easier tracking of Auton progress 
8. Custom Controller Software
9. Extra Math Functions
10. Logger class for logging variables, and a Poller for reading from the SD Card
11. Auton Maker found here: https://github.com/7121B/AutonMakerV2
12. Graphing using Graphy as a core
13. Machine Learning capabilities using Fido 
14. (IN ALPHA) Pure Pursuit
15. Vision Sensor simulation application using Jupyter Notebook and OpenCV, letting you test code while seeing what's happening. 

Many of these will have bugs as I haven't been able to test most of the code on an actual bot.

Current timeline is as follows:

1. Skills Simulator, to be able to practice your driving skills runs
2. Filters, including a Kalman Filter
3. The UvuvCompass, which will use Kalman Filtering for the most accurate position tracking possible
4. A full on PID Tuner that will tune PIDs for you
5. Improving the Graphing Tool functionality and taking it to the limit

I may throw in LED control and some other things at some point, but I don't really know how far UvuvLib will go. The 5 listed are the current goals for code, and hopefully I can do it with help from the community as well.

Contributors:

Lucas - 7121A

Beta Testers:

Aidan - 70761S


## Installation

To install the library, put the uvuvlib zip file into your project directory and run this in the terminal:

**pros conduct fetch uvuvLib@[version].zip**

For any questions about installation, read this website below first and if that doesn't help, join our Discord server.

https://pros.cs.purdue.edu/v5/cli/conductor.html?highlight=template

https://discord.gg/E6HsRSQd

## VSS / Jupyter Notebook

You're gonna find the Notebook inside the main folder, the .ipynb file. Installing should be really easy, just make sure you have stuff like Python already installed. Once everythings ready, run **jupyter notebook** in your command prompt of choice inside the directory where the Notebooks stored, and it should be really easy from there. There's key controls on the screen, which will let you wipe out signatures, save up to 7 signatures, pause the output, and obviously close the app.

NOTE: This is a you-code thing, the only thing that comes with the app is some example code. It's just an API with a display. 