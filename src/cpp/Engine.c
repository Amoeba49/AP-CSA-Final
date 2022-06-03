//#define DEBUG_ENABLED

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "model.h"
#include "matrix.h"
#include "vector.h"
#include "Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void glfw_initialization();
Matrix look_at(Vector *eye, Vector *center, Vector *up);

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
float cameraSpeed = 5.0f;
float mouseSpeed = 0.075f;

float deltaTime;
float lastTime;

Matrix projection;
Matrix view;
Matrix model;
Matrix rotation;
Matrix scale;
Matrix translate;
Vector position;
Vector direction;
Vector right;
Vector up;
Vector center;
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;

int main() {
	glfw_initialization();

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);
	glfwSetCursorPosCallback(window, mouse_cursor_callback);



    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    struct Shader shader;
    shader_load(&shader, "C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\shaders\\vertex.glsl", "C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\shaders\\frag.glsl");

	struct Model kirby_model;
	model_load(&kirby_model, "C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\resources\\models\\kirby_blender.obj");

	struct Model cube_model;
	model_load(&cube_model, "C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\resources\\models\\mountain.obj");

	glEnable(GL_CULL_FACE);

    // load and create a texture
    // -------------------------
    unsigned int kirby_texture;
    // kirby texture
    // ---------
    glGenTextures(1, &kirby_texture);
    glBindTexture(GL_TEXTURE_2D, kirby_texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\resources\\textures\\kirby.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("%s", stbi_failure_reason());
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);

	// load and create a texture
    // -------------------------
	unsigned int cube_texture;
	// kirby texture
	// ---------
	glGenTextures(1, &cube_texture);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
	data = stbi_load("C:\\Users\\andru\\IdeaProjects\\GameEngine\\src\\cpp\\resources\\textures\\GroundForest003_COL_VAR1_3K.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("%s", stbi_failure_reason());
		printf("Failed to load texture\n");
	}
	stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader_use(&shader); // don't forget to activate/use the shader before setting uniformss
    shader_set_int(&shader, "kirby_texture", 0);
	shader_set_int(&shader, "cube_texture", 1);

    unsigned int frameCount = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		

        // render container
        shader_use(&shader);

        float currentTime = (float) glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = (float) glfwGetTime();

        shader_set_float(&shader, "time", currentTime);

        vector_set(&direction, 0, (float)cos(verticalAngle) * sin(horizontalAngle));
        vector_set(&direction, 1, (float)sin(verticalAngle));
        vector_set(&direction, 2, (float)cos(verticalAngle) * cos(horizontalAngle));

        vector_set(&right, 0, sin(horizontalAngle - (3.14f / 2.0f)));
        vector_set(&right, 2, cos(horizontalAngle - (3.14f / 2.0f)));

        vector_normalize(&direction);
        vector_normalize(&right);

        up = *vector_cross(&right, &direction);
        center = *vector_add(&position, &direction);
        view = look_at(&position, &center, &up);

		shader_set_mat4x4(&shader, "view", GL_FALSE, &view);
		shader_set_mat4x4(&shader, "projection", GL_FALSE, &projection);

		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cube_texture);

			rotation = *matrix_rotate(0.0f, -3.14f / 2.0f, 0.0f);
			scale = *matrix_scale(10.0f, 10.0f, 10.0f);
			translate = *matrix_translate(-20.0f, -1.0f, 0.0f);

			Matrix temp;
			matrix_create(&temp, 4, 4, COL_MAJOR);

			temp = *matrix_matrix_mul(&translate, &rotation);
			model = *matrix_matrix_mul(&temp, &scale);

			shader_set_mat4x4(&shader, "model", GL_FALSE, &model);

			glBindVertexArray(cube_model.VAO);
			glDrawElements(GL_TRIANGLES, cube_model.faceCount * 3, GL_UNSIGNED_INT, 0);
		}

		{
			// bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, kirby_texture);

			rotation = *matrix_rotate(0.0f, ((frameCount * 0.01) + 0.523599f), 0.0f);
			scale = *matrix_scale(1.0f, 1.0f, 1.0f);
			translate = *matrix_translate(0.0f, -0.5f, -5.0f);

			Matrix temp;
			matrix_create(&temp, 4, 4, COL_MAJOR);

			temp = *matrix_matrix_mul(&translate, &rotation);
			model = *matrix_matrix_mul(&temp, &scale);

			shader_set_mat4x4(&shader, "model", GL_FALSE, &model);

			glBindVertexArray(kirby_model.VAO);
			glDrawElements(GL_TRIANGLES, kirby_model.faceCount * 3, GL_UNSIGNED_INT, 0);
		}


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        frameCount++;
    }

    return 0;
}

void glfw_initialization() {
	vector_create(&position, 3, ((float[]){0, 0, 0}));
	vector_create(&direction, 3, ((float[]){0, 0, 0}));
	vector_create(&right, 3, ((float[]){0, 0, 0}));
	vector_create(&up, 3, ((float[]){0, 0, 0}));

	vector_set(&direction, 0, (float)cos(verticalAngle) * sin(horizontalAngle));
	vector_set(&direction, 1, (float)sin(verticalAngle));
	vector_set(&direction, 2, (float)cos(verticalAngle) * cos(horizontalAngle));

	vector_normalize(&direction);

	vector_set(&right, 0, sin(horizontalAngle - (3.14f / 2.0f)));
	vector_set(&right, 2, cos(horizontalAngle - (3.14f / 2.0f)));
	vector_normalize(&right);

	up = *vector_cross(&right, &direction);

	// Projection matrix setup
	float radians = 3.1415f / 180.0f;
	float aspect = 4.0f / 3.0f;
	float fov = 90.0f;
	float farClip = 100.0f;
	float nearClip = 1.0f;
	float tanHalf = (float)tan(0.5 * (fov * radians));
	matrix_create(&projection, 4, 4, COL_MAJOR);

	matrix_set(&projection, 0, 0, 1 / (aspect * tanHalf));
	matrix_set(&projection, 1, 1, 1 / tanHalf);
	matrix_set(&projection, 2, 2, farClip / (nearClip - farClip));
	matrix_set(&projection, 2, 3, -1.0f);
	matrix_set(&projection, 3, 2, -(farClip * nearClip) / (farClip - nearClip));

	// Model matrix initialization
	matrix_create(&model, 4, 4, COL_MAJOR);
	matrix_create(&rotation, 4, 4, COL_MAJOR);
	matrix_create(&scale, 4, 4, COL_MAJOR);
	matrix_create(&translate, 4, 4, COL_MAJOR);

	vector_create(&center, 3, ((float[]){0, 0, 0}));
	center = *vector_add(&position, &direction);

	view = look_at(&position, &center, &up);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    Vector temp;
    vector_create(&temp, 3, ((float []){0, 0, 0}));

    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS){
        vector_set(&position, 0, 0);
        vector_set(&position, 1, 0);
        vector_set(&position, 2, 0);
        horizontalAngle = 3.14f;
        verticalAngle = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        cameraSpeed = 10.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
        cameraSpeed = 5.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        temp = *vector_scalar_mul(&direction, deltaTime * cameraSpeed);
        position = *vector_add(&position, &temp);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        temp = *vector_scalar_mul(&right, deltaTime * cameraSpeed);
        position = *vector_sub(&position, &temp);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        temp = *vector_scalar_mul(&direction, deltaTime * cameraSpeed);
        position = *vector_sub(&position, &temp);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        temp = *vector_scalar_mul(&right, deltaTime * cameraSpeed);
        position = *vector_add(&position, &temp);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        temp = *vector_scalar_mul(&up, deltaTime * cameraSpeed);
        position = *vector_sub(&position, &temp);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        temp = *vector_scalar_mul(&up, deltaTime * cameraSpeed);
        position = *vector_add(&position, &temp);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_cursor_callback( GLFWwindow * window, double xpos, double ypos) {
    horizontalAngle += mouseSpeed * deltaTime * (float)(SCR_WIDTH/2 - xpos);
    verticalAngle   += mouseSpeed * deltaTime * (float)(SCR_HEIGHT/2 - ypos);

    if(verticalAngle > 1.552f)
        verticalAngle = 1.552f;
    if(verticalAngle < -1.552f)
        verticalAngle = -1.552f;

    vector_set(&direction, 0, (float)cos(verticalAngle) * sin(horizontalAngle));
    vector_set(&direction, 1, (float)sin(verticalAngle));
    vector_set(&direction, 2, (float)cos(verticalAngle) * cos(horizontalAngle));
}

Matrix look_at(Vector *eye, Vector *center, Vector *upVec) {
    Matrix view;
    Vector fVec;
    Vector sVec;
    Vector uVec;

    matrix_create(&view, 4, 4, ROW_MAJOR);

    fVec = *vector_sub(center, eye);
    vector_normalize(&fVec);

    sVec = *vector_cross(&fVec, upVec);
    vector_normalize(&sVec);

    uVec = *vector_cross(&sVec, &fVec);

    matrix_set(&view, 0, 0, vector_get(&sVec, 0));
    matrix_set(&view, 1, 0, vector_get(&sVec, 1));
    matrix_set(&view, 2, 0, vector_get(&sVec, 2));
    matrix_set(&view, 0, 1, vector_get(&uVec, 0));
    matrix_set(&view, 1, 1, vector_get(&uVec, 1));
    matrix_set(&view, 2, 1, vector_get(&uVec, 2));
    matrix_set(&view, 0, 2, -vector_get(&fVec, 0));
    matrix_set(&view, 1, 2, -vector_get(&fVec, 1));
    matrix_set(&view, 2, 2, -vector_get(&fVec, 2));
    matrix_set(&view, 3, 0, -vector_dot(&sVec, eye));
    matrix_set(&view, 3, 1, -vector_dot(&uVec, eye));
    matrix_set(&view, 3, 2, vector_dot(&fVec, eye));

    return view;
}

JNIEXPORT jint JNICALL Java_Engine_nativeTest(JNIEnv *env, jobject obj) {
    return 0;
}