#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Adder/adder.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include <openssl/sha.h>

#include "cpp-learnConfig.h"

using namespace std;

int emptyGLFWWindow()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main(int argc, char *argv[])
{
    // Version example
    cout << "Running " << argv[0] << " Version " << cpp_learn_VERSION_MAJOR << "." << cpp_learn_VERSION_MINOR << "\n";

    // SHA256 example
    // cout << sha256("1234567890_1") << endl;
    // cout << sha256("1234567890_2") << endl;
    // cout << sha256("1234567890_3") << endl;
    // cout << sha256("1234567890_4") << endl;

    // GLFW example
    // emptyGLFWWindow();
    return 0;
}
