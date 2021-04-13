#include "Primitives.h"

static constexpr double Pi = acos(-1.);


void cart2cyl(
		double x, double y, double cz,
		double &r, double &phi, double &z)
{
	r = hypot(y, x);
	phi = atan2(y, x);
	cz = z;
}

void cyl2cart(
		double r, double phi, double cz,
		double &x, double &y, double &z,
		double cdx, double cdy)
{
	x = r * cos(phi) + cdx;
	y = r * sin(phi) + cdy;
	z = cz;
}

void cart2sph(
		double x, double y, double z,
		double &r, double &phi, double &theta)
{
	r = sqrt(x*x + y*y + z*z);
	phi = atan2(y, x);
	theta = atan2(hypot(x, y), z);
}

void sph2cart(
		double r, double phi, double theta,
		double &x, double &y, double &z,
		double cdx, double cdy, double cdz)
{
	x = r * sin(theta) * cos(phi) + cdx;
	y = r * sin(theta) * sin(phi) + cdy;
	z = r * cos(theta) + cdz;
}


void draw_prism_smooth(int sides, double cdx, double cdy)
{
	for (int i = 0; i < sides; ++i) {
		double phi1 = double(i + 0.) / double(sides) * 2. * Pi;
		double phi2 = double(i + 1.) / double(sides) * 2. * Pi;

		double points[6][3];
		double normals[4][3];

		cyl2cart(0., 0., 0., points[0][0], points[0][1], points[0][2], cdx, cdy);
		cyl2cart(0., 0., 1., points[1][0], points[1][1], points[1][2], cdx, cdy);
		cyl2cart(0.2, phi2, 1., points[2][0], points[2][1], points[2][2], cdx, cdy);
		cyl2cart(0.2, phi1, 1., points[3][0], points[3][1], points[3][2], cdx, cdy);
		cyl2cart(0.2, phi1, 0., points[4][0], points[4][1], points[4][2], cdx, cdy);
		cyl2cart(0.2, phi2, 0., points[5][0], points[5][1], points[5][2], cdx, cdy);

		cyl2cart(0., 0., 1., normals[0][0], normals[0][1], normals[0][2], cdx, cdy);
		cyl2cart(0., 0., -1., normals[1][0], normals[1][1], normals[1][2], cdx, cdy);
		cyl2cart(1., phi1, 0., normals[2][0], normals[2][1], normals[2][2], cdx, cdy);
		cyl2cart(1., phi2, 0., normals[3][0], normals[3][1], normals[3][2], cdx, cdy);

		glBegin(GL_TRIANGLES);
		glNormal3dv(normals[0]);
		glVertex3dv(points[1]);
		glVertex3dv(points[2]);
		glVertex3dv(points[3]);

		glNormal3dv(normals[1]);
		glVertex3dv(points[0]);
		glVertex3dv(points[4]);
		glVertex3dv(points[5]);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3dv(normals[3]);
		glVertex3dv(points[2]);
		glVertex3dv(points[5]);
		glNormal3dv(normals[2]);
		glVertex3dv(points[4]);
		glVertex3dv(points[3]);
		glEnd();

	}
}

void draw_pyramid(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW)
{
	double phi_step = 2. * Pi / sides;
	for (int side = 0; side < sides; side++){
		double  phi1 = phi_step * side,
				phi2 = phi_step * (side + 1),
				phin = (phi1 + phi2) / 2.;
		double x1, x2, y1, y2, z1, z2, xn, yn, zn;
		double xn1, xn2, yn1, yn2, zn1, zn2;
		cyl2cart(cdW, phi1, 0., x1, y1, z1, cdx, cdy);
		cyl2cart(cdW, phi2, 1., x2, y2, z2, cdx, cdy);
		sph2cart(1., phin, Pi/4., xn, yn, zn, 0, 0, 0);
		sph2cart(1., phi1, Pi/4., xn1, yn1, zn1, 0, 0, 0);
		sph2cart(1., phi2, Pi/4., xn2, yn2, zn2, 0, 0, 0);
		glBegin(GL_TRIANGLES);
		{
			glNormal3d(xn, zn, yn);
			glVertex3d(cdx, cdzUP, cdy);
			glNormal3d(xn1, zn1, yn1);
			glVertex3d(x1, cdzDOWN, y1);
			glNormal3d(xn2, zn2, yn2);
			glVertex3d(x2, cdzDOWN, y2);
			glNormal3d(0., -1., 0.);
			glVertex3d(cdx, cdzDOWN, cdy);
			glVertex3d(x2, cdzDOWN, y2);
			glVertex3d(x1, cdzDOWN, y1);
		}
		glEnd();
	}
}

void draw_cylinder(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW)
{
	double phi_step = 2. * Pi / sides;
	for (int side = 0; side < sides; side++){
		double  phi1 = phi_step * side,
				phi2 = phi_step * (side + 1),
				phin = (phi1 + phi2) / 2.;
		double x1, x2, y1, y2, z1, z2, xn, yn, zn;
		double xn1, xn2, yn1, yn2, zn1, zn2;
		cyl2cart(cdW, phi1, 0., x1, y1, z1, cdx, cdy);
		cyl2cart(cdW, phi2, 1., x2, y2, z2, cdx, cdy);
		sph2cart(1., phin, Pi/4., xn, yn, zn, 0, 0, 0);
		sph2cart(1., phi1, Pi/4., xn1, yn1, zn1, 0, 0, 0);
		sph2cart(1., phi2, Pi/4., xn2, yn2, zn2, 0, 0, 0);
		glBegin(GL_TRIANGLES);
		{
			glNormal3d(zn, yn, xn);
			glVertex3d(cdzUP, cdy, cdx);
			glNormal3d(zn1, yn1, xn1);
			glVertex3d(cdzDOWN, y1, x1);
			glNormal3d(zn2, yn2, xn2);
			glVertex3d(cdzDOWN, y2, x2);
			glNormal3d(-1., 0., 0.);
			glVertex3d(cdzDOWN, cdy, cdx);
			glVertex3d(cdzDOWN, y2, x2);
			glVertex3d(cdzDOWN, y1, x1);
		}
		glEnd();
	}
}

void draw_cone_carrot(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW)
{
	double phi_step = 2. * Pi / sides;
	for (int side = 0; side < sides; side++){
		double  phi1 = phi_step * side,
				phi2 = phi_step * (side + 1),
				phin = (phi1 + phi2) / 2.;
		double x1, x2, y1, y2, z1, z2, xn, yn, zn;
		double xn1, xn2, yn1, yn2, zn1, zn2;
		cyl2cart(cdW, phi1, 0., x1, y1, z1, cdx, cdy);
		cyl2cart(cdW, phi2, 1., x2, y2, z2, cdx, cdy);
		sph2cart(1., phin, Pi/4., xn, yn, zn, 0, 0, 0);
		sph2cart(1., phi1, Pi/4., xn1, yn1, zn1, 0, 0, 0);
		sph2cart(1., phi2, Pi/4., xn2, yn2, zn2, 0, 0, 0);
		glBegin(GL_TRIANGLES);
		{
			glNormal3d(zn, yn, xn);
			glVertex3d(cdzUP, cdy, cdx);
			glNormal3d(zn1, yn1, xn1);
			glVertex3d(cdzDOWN, y1, x1);
			glNormal3d(zn2, yn2, xn2);
			glVertex3d(cdzDOWN, y2, x2);
			glNormal3d(-1., 0., 0.);
			glVertex3d(cdzDOWN, cdy, cdx);
			glVertex3d(cdzDOWN, y2, x2);
			glVertex3d(cdzDOWN, y1, x1);
		}
		glEnd();
	}
}

void draw_cone_fir(int sides, double cdx, double cdy, double cdzUP, double cdzDOWN, double cdW)
{
	double phi_step = 2. * Pi / sides;
	for (int side = 0; side < sides; side++){
		double  phi1 = phi_step * side,
				phi2 = phi_step * (side + 1),
				phin = (phi1 + phi2) / 2.;
		double x1, x2, y1, y2, z1, z2, xn, yn, zn;
		double xn1, xn2, yn1, yn2, zn1, zn2;
		cyl2cart(cdW, phi1, 0., x1, y1, z1, cdx, cdy);
		cyl2cart(cdW, phi2, 1., x2, y2, z2, cdx, cdy);
		sph2cart(1., phin, Pi/4., xn, yn, zn, 0, 0, 0);
		sph2cart(1., phi1, Pi/4., xn1, yn1, zn1, 0, 0, 0);
		sph2cart(1., phi2, Pi/4., xn2, yn2, zn2, 0, 0, 0);
		glBegin(GL_TRIANGLES);
		{
			glNormal3d(xn, yn, zn);
			glVertex3d(cdx, cdy, cdzUP);
			glNormal3d(xn1, yn1, zn1);
			glVertex3d(x1, y1, cdzDOWN);
			glNormal3d(xn2, yn2, zn2);
			glVertex3d(x2, y2, cdzDOWN);
			glNormal3d(0., 0., -1.);
			glVertex3d(cdx, cdy, cdzDOWN);
			glVertex3d(x2, y2, cdzDOWN);
			glVertex3d(x1, y1, cdzDOWN);
		}
		glEnd();
	}
}

void draw_sphere_smooth(int rows, int cols, double cdx, double cdy, double cdz, double cdr)
{
	double  phi_step = 2. * Pi / cols,
			theta_step = Pi / rows;
	glBegin(GL_QUADS);
	for (int row = 0; row < rows; ++row){
		for (int col = 0; col < cols; ++col){
			double  phi1 = phi_step * col,
					phi2 = phi_step * (col + 1),
					theta1 = theta_step * row,
					theta2 = theta_step * (row + 1),
					phin = (phi1 + phi2) / 2.,
					thetan = (theta1 + theta2) / 2.;

			double  x11, x12, x21, x22,
					y11, y12, y21, y22,
					z11, z12, z21, z22,
					nx, ny, nz;

			sph2cart(cdr, phi1, theta1, x11, y11, z11, cdx, cdy, cdz);
			sph2cart(cdr, phi1, theta2, x12, y12, z12, cdx, cdy, cdz);
			sph2cart(cdr, phi2, theta1, x21, y21, z21, cdx, cdy, cdz);
			sph2cart(cdr, phi2, theta2, x22, y22, z22, cdx, cdy, cdz);
			sph2cart(cdr, phin, thetan, nx, ny, nz, cdx, cdy, cdz);

			glNormal3d(x11, y11, z11);
			glVertex3d(x11, y11, z11);
			glNormal3d(x12, y12, z12);
			glVertex3d(x12, y12, z12);
			glNormal3d(x22, y22, z22);
			glVertex3d(x22, y22, z22);
			glNormal3d(x21, y21, z21);
			glVertex3d(x21, y21, z21);
		}
	}
	glEnd();
}
