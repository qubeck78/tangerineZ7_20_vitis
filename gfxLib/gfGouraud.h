#ifndef _GFGOURAUD_H
#define _GFGOURAUD_H

#ifdef __cplusplus
extern "C" 
{
#endif

#include "gfTypes.h"
#include "gfBitmap.h"

typedef struct _tgfPoint3D
{
	float 	x3D;
	float 	y3D;
	float 	z3D;

	float 	x3DT;
	float 	y3DT;
	float 	z3DT;

	int16_t 	x2D;
	int16_t 	y2D;
	uint16_t	z2D;
	uint16_t	unused0;

	uint8_t 	r;
	uint8_t 	g;
	uint8_t 	b;
	uint8_t	unused1;

}tgfPoint3D;


typedef struct _tgfTriangle3D
{
	tgfPoint3D 	*a;
	tgfPoint3D 	*b;
	tgfPoint3D 	*c;

	tgfBitmap   *texture;

	int16_t		 aTx2D;
	int16_t      aTy2D;

	int16_t      bTx2D;
	int16_t      bTy2D;

	int16_t      cTx2D;
	int16_t      cTy2D;

}tgfTriangle3D;


static int32_t inline gfGouraudEdge( tgfPoint3D *e1, tgfPoint3D *e2, tgfPoint3D *p )
{
   tgfPoint3D a,b;

/*float Edge(Point v0, Point v1, Point p)
{
   // Vector from edge origin to test point
   Vector a = p - v0;

   // Vector from edge origin to edge end
   Vector b = v1 - v0;

   // 2D cross product
   // Zero: Point is on edge
   // Positive: Point is right of edge
   // Negative: Point is left of edge
   return a.x * b.y - a.y * b.x;
}*/


   a.x2D = p->x2D - e1->x2D;
   a.y2D = p->y2D - e1->y2D;

   b.x2D = e2->x2D - e1->x2D;
   b.y2D = e2->y2D - e1->y2D;

   return ( ( a.x2D * b.y2D ) - ( a.y2D * b.x2D ) );
}
uint32_t gfGouraudDrawTriangleBlt( tgfBitmap *bmp, tgfTriangle3D *triangle );
uint32_t gfGouraudDrawTriangleZBufferBlt( tgfBitmap *bmp, tgfBitmap *zBuffer, tgfTriangle3D *triangle );
uint32_t gfGouraudDrawTexturedTriangleZBufferBlt( tgfBitmap *bmp, tgfBitmap *zBuffer, tgfTriangle3D *triangle );

uint32_t gfGouraudDrawTriangle( tgfBitmap *bmp, tgfTriangle3D *triangle );
uint32_t gfGouraudDrawTriangleZBuffer( tgfBitmap *bmp, tgfBitmap *zBuffer, tgfTriangle3D *triangle );
uint32_t gfGouraudDrawTexturedTriangleZBuffer( tgfBitmap *bmp, tgfBitmap *zBuffer, tgfTriangle3D *triangle );

#ifdef __cplusplus
}
#endif

#endif
