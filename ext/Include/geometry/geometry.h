#ifndef GEOMETRY_H
#define GEOMETRY_H

static float triangle_vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

static float triangle_tex_coords[] = 
{
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

static float triangle_color_vertices[] = 
{
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};  

static float rectangle_vertices[] = 
{
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
}; 
static unsigned int rectangle_indices[] = 
{ 
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
}; 

#endif