#include "ply_object.h"


void _ply_object::create(vector<float> &Vertices1, vector<int> &Triangles1)
{
  int Num_vertices,Num_triangles;

  Num_vertices=Vertices1.size()/3;
  Num_triangles=Triangles1.size()/3;

  if (Num_vertices<3) cout << "num vertices<3 " << __FILE__ << " " << __LINE__ << endl;
  if (Num_triangles<1) cout << "num triangles<1 " << __FILE__ << " " << __LINE__ << endl;

  Vertices.resize(Num_vertices);
  Triangles.resize(Num_triangles);

  _vertex3f Vertex_aux;
  _vertex3i Triangle_aux;

  for (int i=0;i<Num_vertices;i++){
    Vertex_aux.x=Vertices1[i*3];
    Vertex_aux.y=Vertices1[i*3+1];
    Vertex_aux.z=Vertices1[i*3+2];
    Vertices[i]=Vertex_aux;
  }

  for (int i=0;i<Num_triangles;i++){
    Triangle_aux.x=Triangles1[i*3];
    Triangle_aux.y=Triangles1[i*3+1];
    Triangle_aux.z=Triangles1[i*3+2];
    Triangles[i]=Triangle_aux;
  }

  // random colors
  random_device RD;
  mt19937 MT(RD());
  uniform_real_distribution<float> Random;
  _vertex3f Color;

  Vertices_colors.resize(Vertices.size());
  for (unsigned int i=0;i<Vertices_colors.size();i++){
    Color.x=Random(MT);
    Color.y=Random(MT);
    Color.z=Random(MT);
    Vertices_colors[i]=Color;
  }

  compute_triangles_normals();
  compute_vertices_normals();

  // create drawarrays
  // vertices
  Vertices_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_drawarray[i*3]=Vertices[Triangles[i]._0];
    Vertices_drawarray[i*3+1]=Vertices[Triangles[i]._1];
    Vertices_drawarray[i*3+2]=Vertices[Triangles[i]._2];
  }
  // vertices colors
  Vertices_colors_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_colors_drawarray[i*3]=Vertices_colors[Triangles[i]._0];
    Vertices_colors_drawarray[i*3+1]=Vertices_colors[Triangles[i]._1];
    Vertices_colors_drawarray[i*3+2]=Vertices_colors[Triangles[i]._2];
  }


//  // vertices triangle normals
  Vertices_triangles_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_triangles_normals_drawarray[i*3]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+1]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+2]=Triangles_normals[i];
  }

//  // vertices normals
//  // the cube must appear like a cube not like a sphere
  Vertices_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_normals_drawarray[i*3]=Vertices_normals[Triangles[i]._0];
    Vertices_normals_drawarray[i*3+1]=Vertices_normals[Triangles[i]._1];
    Vertices_normals_drawarray[i*3+2]=Vertices_normals[Triangles[i]._2];
  }

  Vertices_texture_coordinates_drawarray.resize(Triangles.size()*3);

  Initial_position=0;
  Num_vertices=Vertices_drawarray.size();
}




void _ply_object::create()
{
//  int Num_vertices=Vertices.size();
//  int Num_triangles=Triangles.size();

  // random colors
  random_device RD;
  mt19937 MT(RD());
  uniform_real_distribution<float> Random;
  _vertex3f Color;

  Vertices_colors.resize(Vertices.size());
  for (unsigned int i=0;i<Vertices_colors.size();i++){
    Color.x=Random(MT);
    Color.y=Random(MT);
    Color.z=Random(MT);
    Vertices_colors[i]=Color;
  }

  compute_triangles_normals();
  compute_vertices_normals();

  // create drawarrays
  // vertices
  Vertices_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_drawarray[i*3]=Vertices[Triangles[i]._0];
    Vertices_drawarray[i*3+1]=Vertices[Triangles[i]._1];
    Vertices_drawarray[i*3+2]=Vertices[Triangles[i]._2];
  }
  // vertices colors
  Vertices_colors_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_colors_drawarray[i*3]=Vertices_colors[Triangles[i]._0];
    Vertices_colors_drawarray[i*3+1]=Vertices_colors[Triangles[i]._1];
    Vertices_colors_drawarray[i*3+2]=Vertices_colors[Triangles[i]._2];
  }


//  // vertices triangle normals
  Vertices_triangles_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_triangles_normals_drawarray[i*3]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+1]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+2]=Triangles_normals[i];
  }

//  // vertices normals
//  // the cube must appear like a cube not like a sphere
  Vertices_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_normals_drawarray[i*3]=Vertices_normals[Triangles[i]._0];
    Vertices_normals_drawarray[i*3+1]=Vertices_normals[Triangles[i]._1];
    Vertices_normals_drawarray[i*3+2]=Vertices_normals[Triangles[i]._2];
  }

  Vertices_texture_coordinates_drawarray.resize(Triangles.size()*3);

  Initial_position=0;
  Num_vertices=Vertices_drawarray.size();

}


//*************************************************************************
//
//*************************************************************************

void _ply_object::draw()
{
//  glUniformMatrix4fv(10,1,GL_FALSE,Pile.top());
//  glUniformMatrix3fv(13,1,GL_FALSE,Pile.top_matrix().normalMatrix().data());
  glDrawArrays(GL_TRIANGLES,Initial_position,Num_vertices);
}


//*************************************************************************
//
//*************************************************************************

void _ply_object::center(float Min_scale)
{
  _vertex3f Minimum(1e10,1e10,1e10);
  _vertex3f Maximum(1e-10,1e-10,1e-10);
  _vertex3f Vertex;

  for (unsigned int i=0;i<Vertices.size();i++){
    Vertex=Vertices[i];
    if (Vertex.x<Minimum.x) Minimum.x=Vertex.x;
    if (Vertex.y<Minimum.y) Minimum.y=Vertex.y;
    if (Vertex.z<Minimum.z) Minimum.z=Vertex.z;
    if (Vertex.x>Maximum.x) Maximum.x=Vertex.x;
    if (Vertex.y>Maximum.y) Maximum.y=Vertex.y;
    if (Vertex.z>Maximum.z) Maximum.z=Vertex.z;
  }

  _vertex3f Center=Maximum+Minimum;
  Center/=2;

  float Inc_x=fabs(Maximum.x-Minimum.x);
  float Inc_y=fabs(Maximum.y-Minimum.y);
  float Inc_z=fabs(Maximum.z-Minimum.z);
  float Max_value;

  if (Inc_x>Inc_y) Max_value=Inc_x;
  else Max_value=Inc_y;
  if (Inc_z>Max_value) Max_value=Inc_z;
  Max_value/=8;

  for (unsigned int i=0;i<Vertices.size();i++){
    Vertices[i]=(Vertices[i]-Center)/Max_value;
  }
}
