/* Author:  G. Jungman
 * RCS:     $Id$
 */
#ifndef GSL_ODEIV_H
#define GSL_ODEIV_H


/* Description of a system of ODEs.
 *
 * y' = f(t,y) = dydt(t, y)
 *
 * The system is specified by giving the right-hand-side
 * of the equation and possibly a jacobian function.
 *
 * Some methods require the jacobian function, which calculates
 * the matrix dfdy and the vector dfdt. The matrix dfdy conforms
 * to the GSL standard, being a continuous range of floating point
 * values, in row-order.
 *
 * As with GSL function objects, user-supplied parameter
 * data can also be given. 
 */
typedef struct  {
  int (* function) (double t, const double y[], double dydt[], void * params);
  int (* jacobian) (double t, const double y[], double * dfdy, double dfdt[], void * params);
  void * params;
}
gsl_odeiv_system;

#define GSL_ODEIV_FN_EVAL(S,t,y,f)  (*((S)->function))(t,y,f,(S)->params)
#define GSL_ODEIV_JA_EVAL(S,t,y,dfdy,dfdt)  (*((S)->jacobian))(t,y,dfdy,dfdt,(S)->params)


/* General stepper object.
 *
 * Opaque object for stepping
 * an ODE system from t to t+h.
 */
typedef struct {
  int  (*_step)  (void *, unsigned int dim, double t, double h, double y[], double yerr[], const gsl_odeiv_system * dydt);
  int  (*_reset) (void *);
  void (*_free)  (void *);
  void * _state;
  unsigned int dimension;
}
gsl_odeiv_step;


/* General stepper object factory.
 *
 * Specialized factory instances create
 * steppers embodying different methods.
 */
typedef struct {
  const char * name;
  gsl_odeiv_step * (*create) (unsigned int dimension);
}
gsl_odeiv_step_factory;


/* Available stepper factories.
 *
 * rk4    : 4th order (classical) Runge-Kutta
 * rkck   : embedded 4th(5th) Runge-Kutta with theoretical error estimate
 * rk4imp : implicit 4th order Runge-Kutta at Gaussian points
 * gear1  : M=1 implicit Gear method
 * gear2  : M=2 implicit Gear method
 */
extern const gsl_odeiv_step_factory  gsl_odeiv_step_factory_rk4;
extern const gsl_odeiv_step_factory  gsl_odeiv_step_factory_rkck;
extern const gsl_odeiv_step_factory  gsl_odeiv_step_factory_rk4imp;
extern const gsl_odeiv_step_factory  gsl_odeiv_step_factory_gear1;
extern const gsl_odeiv_step_factory  gsl_odeiv_step_factory_gear2;


/* General stepper object methods.
 */
int  gsl_odeiv_step_impl(gsl_odeiv_step * s, double t, double h, double y[], double yerr[], const gsl_odeiv_system * dydt);
int  gsl_odeiv_step_reset(gsl_odeiv_step * s);
void gsl_odeiv_step_free(gsl_odeiv_step * s);


#endif  /* !GSL_ODEIV_H */
