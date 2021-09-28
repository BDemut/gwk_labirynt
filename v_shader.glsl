#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(1,1,1,1);

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku


//Zmienne interpolowane
out vec4 i_color;

void main(void) {
    vec4 lp = vec4(0,0,0, 1); //przestrzeñ oka

    float d;

    d = distance(V*M*vertex, lp);
    if (d < 5)
        d = 1 - (d / 5);
    else
        d = 0;

    vec4 l = lp - normalize(V*M*vertex);
    vec4 n = normalize(V*M*normal);

    float nl = clamp(dot(n,l),0.5,1);

    gl_Position=P*V*M*vertex;
    i_color=vec4(color.rgb*nl*d*d,color.a);
}
