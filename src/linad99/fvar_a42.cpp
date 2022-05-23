/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

 void DF_dble_dv_div(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator/(const prevariable& x, const dvar_vector& t1)
  {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;
    gs->RETURN_ARRAYS_INCREMENT();

    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("ceeb");
    x.save_prevariable_value(fp);
    x.save_prevariable_position(fp);
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=value(x)/t1.elem_value(i);
    }
    t1.save_dvar_vector_value(fp);
    tmp.save_dvar_vector_position(fp);
    t1.save_dvar_vector_position(fp);
    save_identifier_string("deea");
    gs->GRAD_STACK1->set_gradient_stack(DF_dble_dv_div);
    gs->RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_dble_dv_div(void)
 {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    verify_identifier_string("deea");
    dvar_vector_position t1_pos=restore_dvar_vector_position();
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    dvector t1=restore_dvar_vector_value(t1_pos);
    prevariable_position xpos=restore_prevariable_position(fp);
    double x=restore_prevariable_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ceeb");
    double dfx=0.;
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      //tmp.elem_value(i)=value(x)/t1.elem_value(i);
      double t1inv=1./t1.elem(i);
      dfx+=dftmp(i)*t1inv;
      dft1(i)=-dftmp(i)*x*t1inv*t1inv;
    }
    save_double_derivative(dfx,xpos);
    dft1.save_dvector_derivatives(t1_pos);
 }
