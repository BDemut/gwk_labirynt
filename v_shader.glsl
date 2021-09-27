#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(1,1,1,1);
uniform vec4 lightDir=vec4(0,0,1,0);

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku


//Zmienne interpolowane
out vec4 i_color;

void main(void) {
    //vec4 = P*V*vec4(0,0,0,0)

    float d;

    d = distance(V*M*vertex, vec4(0,0,0,1));
    if (d < 5)
        d = 1 - (d / 5);
    else
        d = 0;

    gl_Position=P*V*M*vertex;
    i_color=vec4(color.rgb*d,color.a);
}
