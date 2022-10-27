#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
#include "graphic_engine/shaders/Shader.h"
#include "graphic_engine/windows/window.h"
#include "math_engine/PSBmath.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <alloca.h>
#include <iostream>
#include <vector>
#include <fstream>


std::ifstream fs("graphic_engine/shaders/fragmentShader.shader");
std::ifstream vs("graphic_engine/shaders/vertexShader.shader");
std::string vertexShader=Shader::FileToString(vs);
std::string fragmentShader=Shader::FileToString(fs);

float a=600.0f/800.0f;
float d1=0.01f;
float d2=1000.0f;
float angle=90.0f;

float v[24]
{
-0.5f, -0.5f, -1.0f,
 0.5f, -0.5f, -1.0f,
-0.5f,  0.5f, -1.0f,
 0.5f,  0.5f, -1.0f, 
-0.5f, -0.5f, -3.0f, 
 0.5f, -0.5f, -3.0f,
-0.5f,  0.5f, -3.0f, 
 0.5f,  0.5f, -3.0f

};





int main()
{



Window window("My Window",800,600);
SDL_Event event;
//0A.VERTEX DATA (opengl foloseste coordonate normalizate)
float vertexData2F[56]=
{
-0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
 0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
-0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
-1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
-1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};





//0B.INDEX DATA (Ordinera desenarii punctelor)
unsigned int indexData[36]=
{
0,2,1,
2,1,3,
2,6,3,
6,7,3,
0,4,2,
4,6,2,
7,1,3,
7,5,1,
6,4,7,
4,5,7,
4,0,5,
0,1,5
};


//I.VERTEX BUFFER 
unsigned int buffer; 
unsigned int indexBuffer;

glGenBuffers(1,&buffer);  //genereaza lista de puncte  1-id buffer 
glGenBuffers(2,&indexBuffer);

glBindBuffer(GL_ARRAY_BUFFER, buffer); //buffer ul ales va fi utilizat 
glBufferData(GL_ARRAY_BUFFER,56*sizeof(float),vertexData2F,GL_STATIC_DRAW); 

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); //buffer ul ales va fi utilizat 
glBufferData(GL_ELEMENT_ARRAY_BUFFER,12*sizeof(float),indexData,GL_STATIC_DRAW);
// 6*sizeof(float) nr de biti alocati pentru coordonate , vertexData lista de coordonate 
// opengl nu va stii interpretarea coordonatelor , nu inca 




//II. VERTEX ATTRIBUTES

glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*7,(GLvoid*)0); 
glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(float)*7,(GLvoid*)(3*sizeof(float))); 

/*creare atribut nou - atribut pozitie  
0-id atribut , 2 - nr alemente atribut, GL_Float tipul de data al atributului
sizeof(float)*2 -nr de biti dintre inceputul primului element cu atributul respectiv si inceputul celui de-al
doilea(cati biti trebuie parcursi pentru a ajunge la urmatorul element cu atributul respectiv)
*/
glEnableVertexAttribArray(0); //cosntruieste atributul creat
glEnableVertexAttribArray(1); //cosntruieste atributul creat

glBindBuffer(GL_ARRAY_BUFFER,1);





//III. VERTEX SHADER && FRAGMENT SHADER

unsigned int shader=Shader::CreateShader(vertexShader, fragmentShader);
glUseProgram(shader);

glClearColor(0.0f,0.3f,0.3f,0.0f);

while(!window.isClosed())
{
    
    glClear(GL_COLOR_BUFFER_BIT);



    window.pollEvents(event);
if(event.type==SDL_KEYDOWN)
{
if(event.key.keysym.sym==SDLK_a){
 for(int i=0;i<24;i++){
  if(i==0 || i==1 || i==6 || i==7 || i==12 || i==13 || i==18 || i==19){
 if(vertexData2F[i]==0.5f)vertexData2F[i]=1.0f;
 if(vertexData2F[i]==-0.5f)vertexData2F[i]=-1.0f;
  }
 }

 glBufferData(GL_ARRAY_BUFFER,24*sizeof(float),vertexData2F,GL_STATIC_DRAW); 
}

if(event.key.keysym.sym==SDLK_b){
 for(int i=0;i<24;i++){
  if(i==0 || i==1 || i==6 || i==7 || i==12 || i==13 || i==18 || i==19){
 if(vertexData2F[i]==1.0f)vertexData2F[i]=0.5f;
 if(vertexData2F[i]==-1.0f)vertexData2F[i]=-0.5f;
  }
 }

 glBufferData(GL_ARRAY_BUFFER,24*sizeof(float),vertexData2F,GL_STATIC_DRAW); 
}

if(event.key.keysym.sym==SDLK_c)
{
glViewport(0,0,window.getWidth(),window.getHeight());
}
}

  // glViewport(0,0,window.getWidth(),window.getHeight());



    glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,nullptr);
    
 
    window.GLswap();
   



       
}
return 0;
}