#ifndef GEOMETRY_H
#define GEOMETRY_H

static float triangle_vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
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