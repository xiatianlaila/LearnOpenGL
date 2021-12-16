#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

//������ɫ����Դ����Ӳ�����ڴ����ļ�������C����ַ�����
const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n" //��gl_Position���õ�ֵ���Ϊ�ö�����ɫ�������
								 "}\0";

//Ƭ����ɫ����Դ����Ӳ�����ڴ����ļ�������C����ַ�����
const char* fragmentShaderSource = "#version 330 core\n"
								   "out vec4 FragColor;\n"
								   "void main()\n"
								   "{\n"
								   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								   "}\n\0";


//ע��һ���ص���������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
�������Ǽ���û��Ƿ����˷��ؼ�(Esc)
���û�а��£�glfwGetKey���᷵��GLFW_RELEASE������û���ȷ�����˷��ؼ���
���ǽ�ͨ��glfwSetwindowShouldCloseʹ�ð�WindowShouldClose��������Ϊ true�ķ����ر�GLFW��
��һ��whileѭ����������⽫��ʧ�ܣ����򽫻�ر�
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
	//��ʼ��GLFW
	glfwInit();
	//����GLFW����Ҫ�汾��(Major)�ʹ�Ҫ�汾��(Minor)��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����GLFWʹ�ú���ģʽ(Core-profile),��ζ������ֻ��ʹ��OpenGL��һ���Ӽ���������Ҫ����������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�������ڶ���
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "δ�ܳɹ���������" << endl;
		glfwTerminate(); //�ͷ�������ԴΪGLFW����һ�γ�ʼ��������׼��
		return -1;
	}

	//�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "δ�ܳɹ���ʼ��GLAD" << endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 800, 600);	//ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶�

	//ע�ᴰ�ڱ仯����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

	//����������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//������ɫ��Դ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); //���붥����ɫ��
	//����Ƿ����ɹ�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//����Ƭ����ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//������ɫ��Դ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); //����Ƭ����ɫ��
	//����Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//������ɫ���������
	unsigned int shaderProgram = glCreateProgram();
	//��������ɵĶ�����ɫ����Ƭ����ɫ����������ɫ�����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//������ɫ��
	glLinkProgram(shaderProgram);
	//�������ɫ�������Ƿ����ɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
	}

	//ɾ����ɫ��
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader); //���ڣ������Ѿ������붥�����ݷ��͸���GPU����ָʾ��GPU����ڶ����Ƭ����ɫ���д�����

	//------------------------------------------------------------------------------
	//���ö������ݺͻ��岢���ö�������
	//���嶥������
	/*�����λ����ö���
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	*/
	//���λ����ö���
	float vertices[] =
	{
		 0.5f, 0.5f, 0.0f,   // ���Ͻ�
		 0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};
	//��������
	unsigned int indices[] = 
	{	// ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	//����VAO�����������(Vertex Buffer Object)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//����VBO���㻺�����(Vertex Buffer Object)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//����VBO���㻺�����(Vertex Buffer Object)
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//��VAO����
	glBindVertexArray(VAO);

	//�����㻺�����󶨵�������(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	/*
	glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ��������ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
	�ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�����������������ϣ�����͵�ʵ�����ݡ�
	���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��
	GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	*/
	//������������䵽������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//��EBO����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//������������䵽����������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//���
	glBindVertexArray(0); //���VAO�İ󶨣���������VAO���þͲ���������޸����VAO

	//������Ⱦѭ��(Render Loop)
	while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó�����
	{
		//����
		processInput(window);

		//��Ⱦָ��
		//ʹ����ɫ���������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //glClearColor�����������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //glClear�����������Ļ����ɫ����
		//��Ⱦ�ҵĵ�һ��������
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); //��Ϊ����ֻ��һ��VAO������û�б�Ҫÿ�ζ������������ǽ���������ʹ�����������  
		//glDrawArrays(GL_TRIANGLES, 0, 6); //��������
		//glDrawArrays(GL_POINTS, 0, 3);		//����
		//glDrawArrays(GL_LINE_LOOP, 0, 6);	//����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindVertexArray(0);

		//��鲢�����¼�����������
		glfwPollEvents(); //glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
		glfwSwapBuffers(window); //glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
	}

	//�ͷ�������ԴΪGLFW����һ�γ�ʼ��������׼��
	glfwTerminate();

	return 0;
}