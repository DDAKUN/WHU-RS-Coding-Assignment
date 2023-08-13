#include "pch.h"
#include "CObject3D.h"

void CObject3D::CreateBall(double x0, double y0, double z0, double r)
{
	int i = 0, j;
	double pi = 3.1415926;
	bx = x0;by = y0;bz = z0;
	for (double u = -pi / 2;u < pi / 2 + pi / 32;u = u + pi / 32)
	{
		j = 0;
		for (double v = 0;v < 2 * pi - pi / 32;v = v + pi / 32)
		{
			p3d[i][j].x = x0 + r * cos(u) * cos(v);
			p3d[i][j].y = y0 + r * cos(u) * sin(v);
			p3d[i][j].z = z0 + r * sin(u);
			j++;
		}
		i++;
	}
	countx = i;
	county = j;
	SetSurfaceList();

}

void CObject3D::SetSurfaceList()
{
	for (int i = 0;i < countx - 1;i++)
	{
		for (int j = 0;j < county;j++)
		{
			TriSurface surface1;
			surface1.p1 = p3d[i][j];
			surface1.p2 = p3d[(i + 1) % countx][(j + 1) % county];
			surface1.p3 = p3d[(i + 1) % countx][j];
			SetFVector(&surface1);
			m_SurfaceList.Add(surface1);
			TriSurface surface2;
			surface2.p1 = p3d[i][j];
			surface2.p2 = p3d[i][(j + 1) % county];
			surface2.p3 = p3d[(i + 1) % countx][(j + 1) % county];
			SetFVector(&surface2);
			m_SurfaceList.Add(surface2);
		}
	}

}

void CObject3D::SetFVector(TriSurface* surface)
{
	double xu, yu, zu, xv, yv, zv, d;
	xu = surface->p2.x - surface->p1.x;
	yu = surface->p2.y - surface->p1.y;
	zu = surface->p2.z - surface->p1.z;
	xv = surface->p3.x - surface->p1.x;
	yv = surface->p3.y - surface->p1.y;
	zv = surface->p3.z - surface->p1.z;
	d = sqrt((yu * zv - yv * zu) * (yu * zv - yv * zu) +
		(zu * xv - zv * xu) * (zu * xv - zv * xu) +
		(xu * yv - xv * yu) * (xu * yv - xv * yu));
	surface->xn = (yu * zv - yv * zu) / d;
	surface->yn = (zu * xv - zv * xu) / d;
	surface->zn = (xu * yv - xv * yu) / d;

}

void CObject3D::SetParam(Param param)
{
	m_Param.kra = param.kra;
	m_Param.kga = param.kga;
	m_Param.kba = param.kba;
	m_Param.krd = param.krd;
	m_Param.kgd = param.kgd;
	m_Param.kbd = param.kbd;
	m_Param.krs = param.krs;
	m_Param.kgs = param.kgs;
	m_Param.kbs = param.kbs;
	m_Param.n = param.n;

}
