#include <math.h>
#include <gsl_vector.h>
#include <gsl_matrix.h>
#include <gsl_multiroots.h>

#include "test_funcs.h"

gsl_multiroot_function_fdf rosenbrock =
{&rosenbrock_f,
 &rosenbrock_df,
 &rosenbrock_fdf,
 2, 0};

void
rosenbrock_initpt (gsl_vector * x)
{
  gsl_vector_set (x, 0, -1.2);
  gsl_vector_set (x, 1, 1.0);
}

int
rosenbrock_f (const gsl_vector * x, void *params, gsl_vector * f)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);

  double y0 = 1 - x0;
  double y1 = 10 * (x1 - x0 * x0);

  gsl_vector_set (f, 0, y0);
  gsl_vector_set (f, 1, y1);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
rosenbrock_df (const gsl_vector * x, void *params, gsl_matrix * df)
{
  double x0 = gsl_vector_get (x, 0);

  double df00 = -1;
  double df01 = 0;
  double df10 = -20 * x0;
  double df11 = 10;

  gsl_matrix_set (df, 0, 0, df00);
  gsl_matrix_set (df, 0, 1, df01);
  gsl_matrix_set (df, 1, 0, df10);
  gsl_matrix_set (df, 1, 1, df11);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
rosenbrock_fdf (const gsl_vector * x, void *params,
		gsl_vector * f, gsl_matrix * df)
{
  rosenbrock_f (x, params, f);
  rosenbrock_df (x, params, df);

  return GSL_SUCCESS;
}


gsl_multiroot_function_fdf powellsing =
{&powellsing_f,
 &powellsing_df,
 &powellsing_fdf,
 4, 0};

void
powellsing_initpt (gsl_vector * x)
{
  gsl_vector_set (x, 0, 3.0);
  gsl_vector_set (x, 1, -1.0);
  gsl_vector_set (x, 2, 0.0);
  gsl_vector_set (x, 3, 1.0);
}

int
powellsing_f (const gsl_vector * x, void *params, gsl_vector * f)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);
  double x3 = gsl_vector_get (x, 3);

  double y0 = x0 + 10 * x1;
  double y1 = sqrt (5.0) * (x2 - x3);
  double y2 = pow (x1 - 2 * x2, 2.0);
  double y3 = sqrt (10.0) * pow (x0 - x3, 2.0);

  gsl_vector_set (f, 0, y0);
  gsl_vector_set (f, 1, y1);
  gsl_vector_set (f, 2, y2);
  gsl_vector_set (f, 3, y3);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
powellsing_df (const gsl_vector * x, void *params, gsl_matrix * df)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);
  double x3 = gsl_vector_get (x, 3);

  double df00 = 1, df01 = 10, df02 = 0, df03 = 0;
  double df10 = 0, df11 = 0, df12 = sqrt (5.0), df13 = -df12;
  double df20 = 0, df21 = 2 * (x1 - 2 * x2), df22 = -2 * df21, df23 = 0;
  double df30 = 2 * sqrt (10.0) * (x0 - x3), df31 = 0, df32 = 0, df33 = -df30;

  gsl_matrix_set (df, 0, 0, df00);
  gsl_matrix_set (df, 0, 1, df01);
  gsl_matrix_set (df, 0, 2, df02);
  gsl_matrix_set (df, 0, 3, df03);

  gsl_matrix_set (df, 1, 0, df10);
  gsl_matrix_set (df, 1, 1, df11);
  gsl_matrix_set (df, 1, 2, df12);
  gsl_matrix_set (df, 1, 3, df13);

  gsl_matrix_set (df, 2, 0, df20);
  gsl_matrix_set (df, 2, 1, df21);
  gsl_matrix_set (df, 2, 2, df22);
  gsl_matrix_set (df, 2, 3, df23);

  gsl_matrix_set (df, 3, 0, df30);
  gsl_matrix_set (df, 3, 1, df31);
  gsl_matrix_set (df, 3, 2, df32);
  gsl_matrix_set (df, 3, 3, df33);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
powellsing_fdf (const gsl_vector * x, void *params,
		    gsl_vector * f, gsl_matrix * df)
{
  powellsing_f (x, params, f);
  powellsing_df (x, params, df);

  return GSL_SUCCESS;
}


gsl_multiroot_function_fdf powellscal =
{&powellscal_f,
 &powellscal_df,
 &powellscal_fdf,
 2, 0};

void
powellscal_initpt (gsl_vector * x)
{
  gsl_vector_set (x, 0, 0.0);
  gsl_vector_set (x, 1, 1.0);
}

int
powellscal_f (const gsl_vector * x, void *params, gsl_vector * f)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);

  double y0 = 10000.0 * x0 * x1 - 1.0;
  double y1 = exp (-x0) + exp (-x1) - 1.0001;

  gsl_vector_set (f, 0, y0);
  gsl_vector_set (f, 1, y1);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
powellscal_df (const gsl_vector * x, void *params, gsl_matrix * df)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);

  double df00 = 10000.0 * x1, df01 = 10000.0 * x0;
  double df10 = -exp (-x0), df11 = -exp (-x1);

  gsl_matrix_set (df, 0, 0, df00);
  gsl_matrix_set (df, 0, 1, df01);
  gsl_matrix_set (df, 1, 0, df10);
  gsl_matrix_set (df, 1, 1, df11);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
powellscal_fdf (const gsl_vector * x, void *params,
		  gsl_vector * f, gsl_matrix * df)
{
  powellscal_f (x, params, f);
  powellscal_df (x, params, df);

  return GSL_SUCCESS;
}


gsl_multiroot_function_fdf wood =
{&wood_f,
 &wood_df,
 &wood_fdf,
 4, 0};

void
wood_initpt (gsl_vector * x)
{
  gsl_vector_set (x, 0, -3.0);
  gsl_vector_set (x, 1, -1.0);
  gsl_vector_set (x, 2, -3.0);
  gsl_vector_set (x, 3, -1.0);
}

int
wood_f (const gsl_vector * x, void *params, gsl_vector * f)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);
  double x3 = gsl_vector_get (x, 3);

  double t1 = x1 - x0 * x0;
  double t2 = x3 - x2 * x2;

  double y0 = -200.0 * x0 * t1 - (1 - x0);
  double y1 = 200.0 * t1 + 20.2 * (x1 - 1) + 19.8 * (x3 - 1);
  double y2 = -180.0 * x2 * t2 - (1 - x2);
  double y3 = 180.0 * t2 + 20.2 * (x3 - 1) + 19.8 * (x1 - 1);

  gsl_vector_set (f, 0, y0);
  gsl_vector_set (f, 1, y1);
  gsl_vector_set (f, 2, y2);
  gsl_vector_set (f, 3, y3);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
wood_df (const gsl_vector * x, void *params, gsl_matrix * df)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);
  double x3 = gsl_vector_get (x, 3);

  double t1 = x1 - 3 * x0 * x0;
  double t2 = x3 - 3 * x2 * x2;

  double df00 = -200.0 * t1 + 1, df01 = -200.0 * x0, df02 = 0, df03 = 0;
  double df10 = -400.0*x0, df11 = 200.0 + 20.2, df12 = 0, df13 = 19.8;
  double df20 = 0, df21 = 0, df22 = -180.0 * t2 + 1, df23 = -180.0 * x2;
  double df30 = 0, df31 = 19.8, df32 = -2 * 180 * x2, df33 = 180.0 + 20.2;

  gsl_matrix_set (df, 0, 0, df00);
  gsl_matrix_set (df, 0, 1, df01);
  gsl_matrix_set (df, 0, 2, df02);
  gsl_matrix_set (df, 0, 3, df03);

  gsl_matrix_set (df, 1, 0, df10);
  gsl_matrix_set (df, 1, 1, df11);
  gsl_matrix_set (df, 1, 2, df12);
  gsl_matrix_set (df, 1, 3, df13);

  gsl_matrix_set (df, 2, 0, df20);
  gsl_matrix_set (df, 2, 1, df21);
  gsl_matrix_set (df, 2, 2, df22);
  gsl_matrix_set (df, 2, 3, df23);

  gsl_matrix_set (df, 3, 0, df30);
  gsl_matrix_set (df, 3, 1, df31);
  gsl_matrix_set (df, 3, 2, df32);
  gsl_matrix_set (df, 3, 3, df33);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
wood_fdf (const gsl_vector * x, void *params,
		    gsl_vector * f, gsl_matrix * df)
{
  wood_f (x, params, f);
  wood_df (x, params, df);

  return GSL_SUCCESS;
}


gsl_multiroot_function_fdf helical =
{&helical_f,
 &helical_df,
 &helical_fdf,
 3, 0};

void
helical_initpt (gsl_vector * x)
{
  gsl_vector_set (x, 0, -1.0);
  gsl_vector_set (x, 1, 0.0);
  gsl_vector_set (x, 2, 0.0);
}

int
helical_f (const gsl_vector * x, void *params, gsl_vector * f)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);

  double t1 = x1 - x0 * x0;
  double t2 = x3 - x2 * x2;

  double y0 = -200.0 * x0 * t1 - (1 - x0);
  double y1 = 200.0 * t1 + 20.2 * (x1 - 1) + 19.8 * (x3 - 1);
  double y2 = -180.0 * x2 * t2 - (1 - x2);
  double y3 = 180.0 * t2 + 20.2 * (x3 - 1) + 19.8 * (x1 - 1);

  gsl_vector_set (f, 0, y0);
  gsl_vector_set (f, 1, y1);
  gsl_vector_set (f, 2, y2);
  gsl_vector_set (f, 3, y3);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
helical_df (const gsl_vector * x, void *params, gsl_matrix * df)
{
  double x0 = gsl_vector_get (x, 0);
  double x1 = gsl_vector_get (x, 1);
  double x2 = gsl_vector_get (x, 2);
  double x3 = gsl_vector_get (x, 3);

  double t1 = x1 - 3 * x0 * x0;
  double t2 = x3 - 3 * x2 * x2;

  double df00 = -200.0 * t1 + 1, df01 = -200.0 * x0, df02 = 0, df03 = 0;
  double df10 = -400.0*x0, df11 = 200.0 + 20.2, df12 = 0, df13 = 19.8;
  double df20 = 0, df21 = 0, df22 = -180.0 * t2 + 1, df23 = -180.0 * x2;
  double df30 = 0, df31 = 19.8, df32 = -2 * 180 * x2, df33 = 180.0 + 20.2;

  gsl_matrix_set (df, 0, 0, df00);
  gsl_matrix_set (df, 0, 1, df01);
  gsl_matrix_set (df, 0, 2, df02);
  gsl_matrix_set (df, 0, 3, df03);

  gsl_matrix_set (df, 1, 0, df10);
  gsl_matrix_set (df, 1, 1, df11);
  gsl_matrix_set (df, 1, 2, df12);
  gsl_matrix_set (df, 1, 3, df13);

  gsl_matrix_set (df, 2, 0, df20);
  gsl_matrix_set (df, 2, 1, df21);
  gsl_matrix_set (df, 2, 2, df22);
  gsl_matrix_set (df, 2, 3, df23);

  gsl_matrix_set (df, 3, 0, df30);
  gsl_matrix_set (df, 3, 1, df31);
  gsl_matrix_set (df, 3, 2, df32);
  gsl_matrix_set (df, 3, 3, df33);

  params = 0;			/* avoid warning about unused parameters */

  return GSL_SUCCESS;
}

int
helical_fdf (const gsl_vector * x, void *params,
		    gsl_vector * f, gsl_matrix * df)
{
  helical_f (x, params, f);
  helical_df (x, params, df);

  return GSL_SUCCESS;
}
