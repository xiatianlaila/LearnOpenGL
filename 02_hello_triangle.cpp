#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

//顶点着色器的源代码硬编码在代码文件顶部的C风格字符串中
const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n" //将gl_Position设置的值会成为该顶点着色器的输出
								 "}\0";

//片段着色器的源代码硬编码在代码文件顶部的C风格字符串中
const char* fragmentShaderSource = "#version 330 core\n"
								   "out vec4 FragColor;\n"
								   "void main()\n"
								   "{\n"
								   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								   "}\n\0";


//注册一个回调函数，在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
这里我们检查用户是否按下了返回键(Esc)
如果没有按下，glfwGetKey将会返回GLFW_RELEASE。如果用户的确按下了返回键，
我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
下一次while循环的条件检测将会失败，程序将会关闭
*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	//初始化GLFW
	glfwInit();
	//设置GLFW的主要版本号(Major)和次要版本号(Minor)都为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置GLFW使用核心模式(Core-profile),意味着我们只能使用OpenGL的一个子集，不再需要向后兼容特性
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口对象
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "未能成功创建窗口" << endl;
		glfwTerminate(); //释放所有资源为GLFW的下一次初始化设置做准备
		return -1;
	}

	//将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "未能成功初始化GLAD" << endl;
		return -1;
	}

	//设置视口
	glViewport(0, 0, 800, 600);	//前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度

	//注册窗口变化监听
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

	//创建顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//附加着色器源码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); //编译顶点着色器
	//检测是否编译成功
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//创建片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//附加着色器源码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); //编译片段着色器
	//检测是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//创建着色器程序对象
	unsigned int shaderProgram = glCreateProgram();
	//将编译完成的顶点着色器和片段着色器附加在着色器程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//链接着色器
	glLinkProgram(shaderProgram);
	//检测是着色器程序是否编译成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
	}

	//删除着色器
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader); //现在，我们已经把输入顶点数据发送给了GPU，并指示了GPU如何在顶点和片段着色器中处理它

	//------------------------------------------------------------------------------
	//设置顶点数据和缓冲并配置顶点属性
	//定义顶点数组
	/*三角形绘制用顶点
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	*/
	//矩形绘制用顶点
	float vertices[] =
	{
		 0.5f, 0.5f, 0.0f,   // 右上角
		 0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	//创建索引
	unsigned int indices[] = 
	{	// 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	//创建VAO顶点数组对象(Vertex Buffer Object)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//创建VBO顶点缓冲对象(Vertex Buffer Object)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//创建VBO顶点缓冲对象(Vertex Buffer Object)
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//绑定VAO对象
	glBindVertexArray(VAO);

	//将顶点缓冲对象绑定到缓冲区(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	/*
	glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
	第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。
	第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
	GL_STATIC_DRAW ：数据不会或几乎不会改变。
	GL_DYNAMIC_DRAW：数据会被改变很多。
	GL_STREAM_DRAW ：数据每次绘制时都会改变。
	*/
	//将顶点数据填充到缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//绑定EBO对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//将索引数据填充到索引缓冲区
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解绑
	glBindVertexArray(0); //解除VAO的绑定，这样其他VAO调用就不会意外地修改这个VAO

	//设置渲染循环(Render Loop)
	while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose函数在每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了
	{
		//输入
		processInput(window);

		//渲染指令
		//使用着色器程序对象
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //glClearColor来设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); //glClear函数来清空屏幕的颜色缓冲
		//渲染我的第一个三角形
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); //因为我们只有一个VAO，所以没有必要每次都绑定它，但我们将这样做以使事情更有条理  
		//glDrawArrays(GL_TRIANGLES, 0, 6); //画三角形
		//glDrawArrays(GL_POINTS, 0, 3);		//画点
		//glDrawArrays(GL_LINE_LOOP, 0, 6);	//画线
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//解绑
		glBindVertexArray(0);
		

		//检查并调用事件，交换缓冲
		glfwPollEvents(); //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwSwapBuffers(window); //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
	}

	//释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//释放所有资源为GLFW的下一次初始化设置做准备
	glfwTerminate();

	return 0;
}