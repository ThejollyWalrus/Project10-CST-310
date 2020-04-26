# Project10-CST-310
Mason Hamilton
4/26/20
Read Me
To run this project, you will need a decent computer with at least 8GB off installed RAM.
Then you will need to have some version of Linux installed on your computer either a VM (virtual Machine) or dual boot.
After you will need to install all the glut libraries as well as the C++ ones.
Once all this is done you will need to copy and paste my code file into your Linux text editor and 
run the file in the program with all the correct libraries. The correct way to run the program is show in the project document. 
Also, to find my code it will be in a separate document labeled code. All you need to do is copy and paste into the correct location.
To run this program, you will have to enter the following in the command line: 
g++ Project10.cpp -o num10 -lGL -lGLU -lGLUT -lSOIL
./num10
Keystroke	Action
Right Arrow	Slide camera 1 unit in the positive X direction
Left Arrow	Slide camera 1 unit in the negative X direction
Up Arrow	Slide camera 1 unit in the positive Y direction
Down Arrow	Slide camera 1 unit in the negative Y direction
Shift Up Arrow	Slide camera 1 unit in the positive Z ("in") direction
Shift Down Arrow	Slide camera 1 unit in the negative Z ("out") direction
Control Down Arrow	Change camera pitch by 2 degrees
Control Up Arrow	Change camera pitch by -2 degrees
Control Right Arrow	Change camera yaw by 2 degrees
Control Left Arrow	Change camera yaw by -2 degrees
<	Change camera roll by 2 degrees
>	Change camera roll by -2 degrees
r	Reset to the default position and orientation

