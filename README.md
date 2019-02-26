# leap-max-opengl
cycling74 max plugin for Leap Motion controller

implementing opengl4 view to be able to test leap motion not only with the max patch.


# TODO

there are still lots to do... 

currently what I have is a code to draw the hands detected from leap motion with OpenGL 3. 
i'd like to convert it to OpenGL4, add proper camera and colors.

Started implementing OpenGL4 but still lots to do.

after that I need to decide what type of events I'd like to fetch from the LeapSDK 
to be used in the max patch and implement fetching them.

 only after all of this is complete I'll start working on the max patch itself.


# thanks 

### https://github.com/nok/leap-motion-processing
their project allowed me to properly understand how to fetch
hand information properly in order to draw it.
ported some of it's code to c++. thanks! :)

### http://www.mbsoftworks.sk/tutorials/opengl4/

a very good OpenGL4 tutorial. allowed me to get started quickly.

### https://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c

learned there how to draw a sphere