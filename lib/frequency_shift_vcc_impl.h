/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OFDM_FREQUENCY_SHIFT_VCC_IMPL_H
#define INCLUDED_OFDM_FREQUENCY_SHIFT_VCC_IMPL_H

#include <ofdm/frequency_shift_vcc.h>

namespace gr {
  namespace ofdm {

    class frequency_shift_vcc_impl : public frequency_shift_vcc
    {
     private:
      double	d_sensitivity;
      int 		d_vlen;
      double	d_phase;
      int 		d_cp_length;
      float d_eps;
      int d_need_eps;

     public:
      frequency_shift_vcc_impl(int vlen, double sensitivity, int cp_length );
      ~frequency_shift_vcc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
      virtual int noutput_forecast( gr_vector_int &ninput_items,
          int available_space, int max_items_avail,
          std::vector<bool> &input_done );
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_FREQUENCY_SHIFT_VCC_IMPL_H */

