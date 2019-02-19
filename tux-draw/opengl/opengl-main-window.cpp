#include <iostream>
#include "./common/OpenGLWindow.h"

int main()
{
    const std::string& windowTitle = "001.) Creating OpenGL4 Window - Tutorial by Michal Bubnar (www.mbsoftworks.sk)";
    int majorVersion = 4;
    int minorVersion = 1;
    bool showFullscreen = false;

    OpenGLWindow window;
    if (!window.createOpenGLWindow(windowTitle, majorVersion, minorVersion, showFullscreen))
    {
        printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
        return 1;
    }

    window.runApp();
    if (window.hasErrorOccured())
    {
        std::cout << std::endl << std::endl << "Program could not start because of the above errors! Press ENTER to quit..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}