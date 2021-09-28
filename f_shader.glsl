#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec4 i_color;
in vec2 iTexCoord0;
in float multiplier;

void main(void) {
    vec4 kd = texture(textureMap0, iTexCoord0);
	pixelColor=vec4(kd.rgb * multiplier, kd.a);
}
