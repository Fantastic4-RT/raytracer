/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome_4_resolve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:17:17 by vhorbach          #+#    #+#             */
/*   Updated: 2017/06/26 16:17:18 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
// solution of cubic and quartic equation
#define	TwoPi  6.28318530717958648
const double eps=1e-14;


void		ft_swap_1(double *a, double *b)
{
	double t;

	t = *b;
	*b = *a;
	*a = t;
}

static double root_3_1 ( double x )
{
	double s = 1.;
	while ( x < 1. )
	{
		x *= 8.;
		s *= 0.5;
	}
	while ( x > 8. )
	{
		x *= 0.125;
		s *= 2.;
	}
	double r = 1.5;
	r -= 1./3. * ( r - x / ( r * r ) );
	r -= 1./3. * ( r - x / ( r * r ) );
	r -= 1./3. * ( r - x / ( r * r ) );
	r -= 1./3. * ( r - x / ( r * r ) );
	r -= 1./3. * ( r - x / ( r * r ) );
	r -= 1./3. * ( r - x / ( r * r ) );
	return r * s;
}

double root_3 ( double x )
{
	if ( x > 0 ) return root_3_1( x ); else
	if ( x < 0 ) return -root_3_1(-x ); else
		return 0.;
}

//---------------------------------------------------------------------------
// x - array of size 3
// In case 3 real roots: => x[0], x[1], x[2], return 3
//         2 real roots: x[0], x[1],          return 2
//         1 real root : x[0], x[1] ± i*x[2], return 1
int solve_p3(double *x,double a,double b,double c) {	// solve cubic equation x^3 + a*x^2 + b*x + c = 0
	double a2 = a*a;
	double q  = (a2 - 3*b)/9;
	double r  = (a*(2*a2-9*b) + 27*c)/54;
	// equation x^3 + q*x + r = 0
	double r2 = r*r;
	double q3 = q*q*q;
	double A,B;
	if(r2<q3) {
		double t=r/sqrt(q3);
		if( t<-1) t=-1;
		if( t> 1) t= 1;
		t=acos(t);
		a/=3; q=-2*sqrt(q);
		x[0]=q*cos(t/3)-a;
		x[1]=q*cos((t+TwoPi)/3)-a;
		x[2]=q*cos((t-TwoPi)/3)-a;
		return(3);
	} else {
		//A =-pow(fabs(r)+sqrt(r2-q3),1./3);
		A = -root_3(fabs(r) + sqrt(r2-q3));
		if( r<0 ) A=-A;
		B = A == 0 ? 0 : q/A;

		a/=3;
		x[0] =(A+B)-a;
		x[1] =-0.5*(A+B)-a;
		x[2] = 0.5*sqrt(3.)*(A-B);
		if(fabs(x[2])<eps) { x[2]=x[1]; return(2); }
		return(1);
	}
}// SolveP3(double *x,double a,double b,double c) {
//---------------------------------------------------------------------------
// a>=0!
void  c_sqrt(double x, double y, double *a, double *b) // returns:  a+i*s = sqrt(x+i*y)
{
	double r  = sqrt(x * x + y * y);
	if (y == 0)
	{
		r = sqrt(r);
		if(x >= 0)
		{
			*a = r;
			*b = 0;
		}
		else
		{
			*a = 0;
			*b = r;
		}
	}
	else
	{		// y != 0
		*a = sqrt(0.5 * ( x + r));
		*b = 0.5* y / *a;
	}
}
//---------------------------------------------------------------------------
int   solve_p4_bi(double *x, double b, double d)	// solve equation x^4 + b*x^2 + d = 0
{
	double D = b*b-4*d;
	if( D>=0 )
	{
		double sD = sqrt(D);
		double x1 = (-b+sD)/2;
		double x2 = (-b-sD)/2;	// x2 <= x1
		if( x2>=0 )				// 0 <= x2 <= x1, 4 real roots
		{
			double sx1 = sqrt(x1);
			double sx2 = sqrt(x2);
			x[0] = -sx1;
			x[1] =  sx1;
			x[2] = -sx2;
			x[3] =  sx2;
			return 4;
		}
		if( x1 < 0 )				// x2 <= x1 < 0, two pair of imaginary roots
		{
			double sx1 = sqrt(-x1);
			double sx2 = sqrt(-x2);
			x[0] =    0;
			x[1] =  sx1;
			x[2] =    0;
			x[3] =  sx2;
			return 0;
		}
		// now x2 < 0 <= x1 , two real roots and one pair of imginary root
		double sx1 = sqrt( x1);
		double sx2 = sqrt(-x2);
		x[0] = -sx1;
		x[1] =  sx1;
		x[2] =    0;
		x[3] =  sx2;
		return 2;
	} else { // if( D < 0 ), two pair of compex roots
		double sD2 = 0.5*sqrt(-D);
		c_sqrt(-0.5*b, sD2, &x[0], &x[1]);
		c_sqrt(-0.5*b, -sD2, &x[2], &x[3]);
		return 0;
	} // if( D>=0 )
} // SolveP4Bi(double *x, double b, double d)	// solve equation x^4 + b*x^2 d
//---------------------------------------------------------------------------

static void  dbl_sort3(double *a, double *b, double *c) // make: a <= b <= c
{
	if(*a > *b)
		ft_swap_1(a,b);	// now a<=b
	if(*c < *b)
	{
		ft_swap_1(b,c);			// now a<=b, b<=c
		if(*a > *b)
 			ft_swap_1(a,b);// now a<=b
	}
}
//---------------------------------------------------------------------------
int   solve_p4_de(double *x, double b, double c, double d)	// solve equation x^4 + b*x^2 + c*x + d
{
	//if( c==0 ) return SolveP4Bi(x,b,d); // After that, c!=0
	if(fabs(c)<1e-14*(fabs(b)+fabs(d)))
		return solve_p4_bi(x,b,d); // After that, c!=0
	int res3 = solve_p3( x, 2*b, b*b-4*d, -c*c);	// solve resolvent
	// by Viet theorem:  x1*x2*x3=-c*c not equals to 0, so x1!=0, x2!=0, x3!=0
	if(res3 > 1)	// 3 real roots,
	{
		dbl_sort3(&x[0], &x[1], &x[2]);	// sort roots to x[0] <= x[1] <= x[2]
		// Note: x[0]*x[1]*x[2]= c*c > 0
		if( x[0] > 0) // all roots are positive
		{
			double sz1 = sqrt(x[0]);
			double sz2 = sqrt(x[1]);
			double sz3 = sqrt(x[2]);
			// Note: sz1*sz2*sz3= -c (and not equal to 0)
			if( c>0 )
			{
				x[0] = (-sz1 -sz2 -sz3)/2;
				x[1] = (-sz1 +sz2 +sz3)/2;
				x[2] = (+sz1 -sz2 +sz3)/2;
				x[3] = (+sz1 +sz2 -sz3)/2;
				return 4;
			}
			// now: c<0
			x[0] = (-sz1 -sz2 +sz3)/2;
			x[1] = (-sz1 +sz2 -sz3)/2;
			x[2] = (+sz1 -sz2 -sz3)/2;
			x[3] = (+sz1 +sz2 +sz3)/2;
			return 4;
		} // if( x[0] > 0) // all roots are positive
		// now x[0] <= x[1] < 0, x[2] > 0
		// two pair of comlex roots
		double sz1 = sqrt(-x[0]);
		double sz2 = sqrt(-x[1]);
		double sz3 = sqrt( x[2]);

		if( c>0 )	// sign = -1
		{
			x[0] = -sz3/2;
			x[1] = ( sz1 -sz2)/2;		// x[0]±i*x[1]
			x[2] =  sz3/2;
			x[3] = (-sz1 -sz2)/2;		// x[2]±i*x[3]
			return 0;
		}
		// now: c<0 , sign = +1
		x[0] =   sz3/2;
		x[1] = (-sz1 +sz2)/2;
		x[2] =  -sz3/2;
		x[3] = ( sz1 +sz2)/2;
		return 0;
	} // if( res3>1 )	// 3 real roots,
	// now resoventa have 1 real and pair of compex roots
	// x[0] - real root, and x[0]>0,
	// x[1]±i*x[2] - complex roots,
	// x[0] must be >=0. But one times x[0]=~ 1e-17, so:
	if (x[0] < 0) x[0] = 0;
	double sz1 = sqrt(x[0]);
	double szr, szi;
	c_sqrt(x[1], x[2], &szr, &szi);  // (szr+i*szi)^2 = x[1]+i*x[2]
	if( c>0 )	// sign = -1
	{
		x[0] = -sz1/2-szr;			// 1st real root
		x[1] = -sz1/2+szr;			// 2nd real root
		x[2] = sz1/2;
		x[3] = szi;
		return 2;
	}
	// now: c<0 , sign = +1
	x[0] = sz1/2-szr;			// 1st real root
	x[1] = sz1/2+szr;			// 2nd real root
	x[2] = -sz1/2;
	x[3] = szi;
	return 2;
} // SolveP4De(double *x, double b, double c, double d)	// solve equation x^4 + b*x^2 + c*x + d
//-----------------------------------------------------------------------------
double n4_step(double x, double a,double b,double c,double d)	// one Newton step for x^4 + a*x^3 + b*x^2 + c*x + d
{
	double fxs= ((4 * x + 3 * a) * x + 2 * b) * x + c;	// f'(x)
	if (fxs == 0)
		return 1e99;
	double fx = (((x + a) * x + b) * x + c) * x + d;	// f(x)
	return (x - fx/fxs);
}
//-----------------------------------------------------------------------------
// x - array of size 4
// return 4: 4 real roots x[0], x[1], x[2], x[3], possible multiple roots
// return 2: 2 real roots x[0], x[1] and complex x[2]±i*x[3],
// return 0: two pair of complex roots: x[0]±i*x[1],  x[2]±i*x[3],
int   solve_p4(double *x, double a, double b, double c, double d)
{	// solve equation x^4 + a*x^3 + b*x^2 + c*x + d by Dekart-Euler method
	// move to a=0:
	double d1 = d + 0.25 * a * (0.25 * b * a - 3./64 * a * a * a - c);
	double c1 = c + 0.5 * a *(0.25 * a * a - b);
	double b1 = b - 0.375 * a * a;
	int res = solve_p4_de( x, b1, c1, d1);
	if( res == 4) { x[0]-= a/4; x[1]-= a/4; x[2]-= a/4; x[3]-= a/4; }
	else if (res == 2) { x[0]-= a/4; x[1]-= a/4; x[2]-= a/4; }
	else             { x[0]-= a/4; x[2]-= a/4; }
	// one Newton step for each real root:
	if( res > 0 )
	{
		x[0] = n4_step(x[0], a,b,c,d);
		x[1] = n4_step(x[1], a,b,c,d);
	}
	if( res > 2 )
	{
		x[2] = n4_step(x[2], a,b,c,d);
		x[3] = n4_step(x[3], a,b,c,d);
	}
	return (res);
}