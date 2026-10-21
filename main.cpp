#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>
#include <glad/glad.h>
//#include <GLFW/glfw3.h> // Include GLFW/GL headers (optional, but harmless since GLAD is used)
//#include <array.hpp>
#include <array.hpp>
#include <linked_list.hpp>
#include <matrix.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "OpenGL Triangle"
#define VERTEX_COUNT 3
#define SCALE_FACTOR 2.0

// --- Shader Source Code (GLSL) ---
const char* vertexShaderSource = R"(
#version 300 es
layout (location = 0) in vec3 aPos;    // Vertex Position (NDC: -1.0 to 1.0)
layout (location = 1) in vec3 aColor;  // Vertex Color

uniform mat4 model;

out vec3 vColor; // Passed to the fragment shader

void main()
{
    gl_Position = model * vec4(aPos, 1.0);
    vColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 300 es
precision mediump float;

in vec3 vColor;  // Interpolated color from the vertex shader

out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";
// --- End Shader Source Code ---

// Helper function to compile and check shaders
GLuint compileShader(GLenum type, const char* source) {
    // This call is now safe, as GLAD has initialized the glCreateShader pointer
    GLuint shader = glCreateShader(type); 
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED of type " << type << "\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

// Helper function to link shaders into a program
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return program;
}

Array<float, 6 * VERTEX_COUNT> vertices = 
{
	// Position X, Y, Z     // Color R, G, B
    SCALE_FACTOR * 0.0f,  SCALE_FACTOR * 0.5f, SCALE_FACTOR * 0.0f, 1.0f, 0.0f, 0.0f, 
    SCALE_FACTOR * -0.433f, SCALE_FACTOR * -0.25f, SCALE_FACTOR * 0.0f, 0.0f, 1.0f, 0.0f, 
    SCALE_FACTOR * 0.433f, SCALE_FACTOR * -0.25f, SCALE_FACTOR * 0.0f, 0.0f, 0.0f, 1.0f  
};

int main(int argc, char* argv[]) 
{
    // 1. Initialize SDL 
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Setup OpenGL Attributes 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Request GL 3.3 core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // 3. Create Window 
    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL 
    );
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 4. Create OpenGL Context 
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        std::cerr << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 5. GLAD Initialization 
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        return -1;
    }
    
    // Get the size of the drawable area (in pixels)
    int width, height;
    // We use SDL_GetWindowSizeInPixels to get the correct dimensions for OpenGL's glViewport
    SDL_GetWindowSizeInPixels(window, &width, &height); 

    // Set the OpenGL viewport based on the retrieved window dimensions
    glViewport(0, 0, width, height);

    SDL_GL_SetSwapInterval(1); // Enable VSync
    
    // 6. OpenGL Calls (Shaders are now safe to compile)
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 7. Setup VBO and VAO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * VERTEX_COUNT * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind (best practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
	
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	if (modelLoc == -1) 
	{
		std::cerr << "model uniform not found\n";
	}
	
	Uint64 prevCounter = SDL_GetPerformanceCounter();
	double freq = (double)SDL_GetPerformanceFrequency();
	double totalTime = 0.0;
	
    // --- Main Loop ---
    bool running = true;
    while (running)
    {
		Uint64 currentCounter = SDL_GetPerformanceCounter();
		double deltaTime = (double)(currentCounter - prevCounter) / freq;
		prevCounter = currentCounter;
		totalTime += deltaTime;
        // 8. Event Handling
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_EVENT_QUIT || (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_ESCAPE))
                running = false;
        }

        // 9. Rendering (Direct OpenGL)
        // Clear the screen (black background)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		float angle = fmodf((float)totalTime, 2.0f * 3.14159265f);
		float c = cosf(angle);
		float s = sinf(angle);
		Array<float,16> model = 
		{
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

        // Draw the triangle
        glUseProgram(shaderProgram);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3); 
        glBindVertexArray(0); // Unbind VAO

        // Swap buffers to display the rendered image 
        SDL_GL_SwapWindow(window);
    }

    // 10. Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    SDL_GL_DestroyContext(context); 
    SDL_DestroyWindow(window);
    SDL_Quit();
	
    return 0;
}