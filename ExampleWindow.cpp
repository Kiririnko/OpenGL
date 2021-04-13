#include "ExampleWindow.h"
#include "Primitives.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>

ExampleWindow::ExampleWindow(int width, int height)
: Window(width, height),
  _haus("haus.png"), _roof("roof.png"),
  _green("green.png"), _brown("brown.png"), _orange("orange.png")
{

}

void ExampleWindow::setup()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);

	glClearColor(1.0f, 0.3f, 0.4f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, double(width()) / double(height()), 0.1, 30.0);
	glMatrixMode(GL_MODELVIEW);
}

//Куб для дома
static VertexVector haus_cube_vertices {
	{  0.0,  4.0,  2.0 },
	{  0.0,  0.0,  2.0 },
	{ -4.0,  0.0,  2.0 },
	{ -4.0,  4.0,  2.0 },
	{  0.0,  4.0,  0.0 },
	{  0.0,  0.0,  0.0 },
	{ -4.0,  0.0,  0.0 },
	{ -4.0,  4.0,  0.0 },
};

static FaceVector haus_cube_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector haus_cube_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector haus_cube_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector haus_cube_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 }, { 0.00, 0.50 } },
	{ { 0.50, 0.50 }, { 1.00, 0.50 }, { 1.00, 1.00 }, { 0.50, 1.00 } },
	{ { 0.50, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.50 }, { 0.50, 0.50 } },
};

//Крыша для дома
static VertexVector haus_roof_vertices {
	{  0.0,   0.0,  2.0 },
	{  0.0,   4.0,  2.0 },
	{ -4.0,   4.0,  2.0 },
	{ -4.0,   0.0,  2.0 },
	{  0.0,   2.0,  3.5 },
	{ -4.0,   2.0,  3.5 },
};

static FaceVector haus_roof_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 1, 4, 5, 2 },
	{ 4, 0, 3, 5, 4 },
	{ 3, 0, 4, 1 },
	{ 3, 2, 5, 3 },
};

static NormalVector haus_roof_normals {
	{  0.0,  0.0, -1.0 },
	{  0.0,  1.0,  1.0 },
	{  0.0, -1.0,  1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
};

static ColorVector haus_roof_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector haus_roof_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 1.00 } },
	{ { 0.50, 1.00 }, { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
};

//Труба для дома
static VertexVector haus_tube_vertices {
	{ -1.25,  0.75, 3.0 },
	{ -1.25,  0.5,  3.0 },
	{ -1.5,   0.5,  3.0 },
	{ -1.5,   0.75, 3.0 },
	{ -1.25,  0.75, 2.0 },
	{ -1.25,  0.5,  2.0 },
	{ -1.5,   0.5,  2.0 },
	{ -1.5,   0.75, 2.0 },
};

static FaceVector haus_tube_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector haus_tube_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector haus_tube_colors {
	{  0.0f,  0.0f,  0.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector haus_tube_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
};

SimpleModel haus_cube { haus_cube_vertices, haus_cube_faces, haus_cube_normals, haus_cube_colors, haus_cube_tex_coords };
SimpleModel haus_roof { haus_roof_vertices, haus_roof_faces, haus_roof_normals, haus_roof_colors, haus_roof_tex_coords };
SimpleModel haus_tube { haus_tube_vertices, haus_tube_faces, haus_tube_normals, haus_tube_colors, haus_tube_tex_coords };



void ExampleWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // Identity matrix - единичная матрица

	gluLookAt(10.0, 10.0, 10.0,
			  0.0, 0.0, 0.0,
			  0.0, 0.0, 1.0);


	glRotated(_angle, 0.0, 0.0, 1.0);

	_haus.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(haus_cube);
	glDisable(GL_TEXTURE_2D);

	_roof.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(haus_roof);
	glDisable(GL_TEXTURE_2D);

	_roof.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(haus_tube);
	glDisable(GL_TEXTURE_2D);

	_green.bind();
	glEnable(GL_TEXTURE_2D);
	draw_cone_fir(20, 5., 0., 2, 1+zz, 1.0);
	draw_cone_fir(20, 5., 0., 2.5, 1.5+zz, 0.9);
	draw_cone_fir(20, 5., 0., 3.0, 2.0+zz, 0.8);
	draw_cone_fir(20, 5., 0., 3.5, 2.5+zz, 0.7);
	draw_cone_fir(20, 5., 0., 4.0, 3.0+zz, 0.6);
	draw_cone_fir(20, 5., 0., 4.5, 3.5+zz, 0.5);
	glDisable(GL_TEXTURE_2D);

	_brown.bind();
	glEnable(GL_TEXTURE_2D);
	draw_prism_smooth(20, 5., 0.);
	glDisable(GL_TEXTURE_2D);

	draw_sphere_smooth(20, 10, 2, -4, 0.5+zz, 0.5);
	draw_sphere_smooth(20, 10, 2, -4, 1.2+zz, 0.35);
	draw_sphere_smooth(20, 10, 2, -4, 1.7+zz, 0.2);

	draw_sphere_smooth(20, 10, -7, 3, 0.5, 0.5);
	draw_sphere_smooth(20, 10, -7, 3, 1.2, 0.35);
	draw_sphere_smooth(20, 10, -7, 3, 1.7, 0.2);

	draw_sphere_smooth(20, 10, -1, 7, 0.5, 0.5);
	draw_sphere_smooth(20, 10, -1, 7, 1.2, 0.35);
	draw_sphere_smooth(20, 10, -1, 7, 1.7, 0.2);

	_orange.bind();
	glEnable(GL_TEXTURE_2D);
	draw_pyramid(20, 2, 1.7+zz, -3.5, -4, 0.03);
	draw_pyramid(20, -7, 1.7, 2.4, 2.9, 0.03);
	draw_pyramid(20, -1, 1.7, 6.5, 7, 0.03);
	glDisable(GL_TEXTURE_2D);

}

void ExampleWindow::draw_model(SimpleModel &model)
{
	for (unsigned i = 0; i < model.faces.size(); ++i) {
		int count = model.faces[i][0];
		if (count == 3)
			glBegin(GL_TRIANGLES);
		else if (count == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);

		glNormal3dv(&model.normals[i][0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
		for (int j = 1; j <= count; ++j) {
			glTexCoord2dv(&model.tex_coords[i][j-1][0]);
			glVertex3dv(&model.vertices[model.faces[i][j]][0]);
		}

		glEnd();
	}
}

void ExampleWindow::do_logic()
{
	_angle -= 0.09;
	if (_angle >= 360.)
		_angle -= 360.;
		zz += 0.01 * i;
	if (zz >= 0.5) i = -1;
	else if (zz <= 0) i = 1;
}

void ExampleWindow::handle_keys(const Uint8 *keys)
{


}
