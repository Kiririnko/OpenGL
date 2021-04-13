#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

void cart2cyl(
		double x, double y, double z,
		double &r, double &phi, double &cz);

void cyl2cart(
		double r, double phi, double cz,
		double &x, double &y, double &z,
		double coord);


void cart2sph(
		double x, double y, double z,
		double &r, double &phi, double &theta);

void sph2cart(
		double r, double phi, double theta,
		double &x, double &y, double &z,
		double coord);


void draw_prism_smooth(int sides, double cdx, double cdy);
void draw_pyramid(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);
void draw_cylinder(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);
void draw_cone_carrot(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);
void draw_cone_fir(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW);
void draw_sphere_smooth(int rows, int cols, double cdx, double cdy, double cdz, double cdr);


#endif /* PRIMITIVES_H_ */
