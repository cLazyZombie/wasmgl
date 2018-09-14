#include "stdafx.h"
#include "main.h"
#include "Renderer/Renderer.h"

// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;                       \n"
    "attribute vec3 color;                          \n"
    "varying vec3 vColor;                           \n"
    "void main()                                    \n"
    "{                                              \n"
    "  gl_Position = vec4(position.xyz, 1.0);       \n"
    "  vColor = color;                              \n"
    "}                                              \n";

const GLchar* fragmentSource =
    "precision mediump float;                       \n"
    "varying vec3 vColor;                           \n"
    "void main()                                    \n"
    "{                                              \n"
    "  gl_FragColor = vec4(vColor, 1.0);           \n"
    "}                                              \n";

std::function<void()> loop;
void main_loop() { loop(); }

int main() {
    #ifdef DEBUG
	printf("------------------------------------------\n");
    #endif

     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

     if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // SDL_Window *window;
    // SDL_CreateWindowAndRenderer(640, 480, 0, &window, nullptr);

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // test
    VoxerEngine::Renderer::Info info;
    info.Width = 640;
    info.Height = 480;

    VoxerEngine::Renderer* r = new VoxerEngine::Renderer(info);
    
    // // Create a Vertex Buffer Object and copy the vertex data to it
    // GLuint vbo;
    // glGenBuffers(1, &vbo);

    // GLfloat vertices[] = {
    //     -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 
    //     0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 
    //     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f };

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // index buffer
    // GLuint ibo;
    // glGenBuffers(1, &ibo);
    // GLshort indices[] = {0, 1, 2, 0, 2, 3};
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // Create and compile the vertex shader
    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // glCompileShader(vertexShader);

    // // Create and compile the fragment shader
    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    // glCompileShader(fragmentShader);

    // // Link the vertex and fragment shader into a shader program
    // GLuint shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);
    // glUseProgram(shaderProgram);

    // // Specify the layout of the vertex data
    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glEnableVertexAttribArray(posAttrib);
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    // GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    // glEnableVertexAttribArray(colorAttrib);
    // glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid *)(2 * sizeof(GLfloat)));

    loop = [&]
    {
        // // Clear the screen
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);

        SDL_RenderPresent(renderer);
        //SDL_GL_SwapWindow(window);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return EXIT_SUCCESS;
}