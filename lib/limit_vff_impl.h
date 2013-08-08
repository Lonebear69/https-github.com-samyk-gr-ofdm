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

#ifndef INCLUDED_OFDM_LIMIT_VFF_IMPL_H
#define INCLUDED_OFDM_LIMIT_VFF_IMPL_H

#include <ofdm/limit_vff.h>

namespace gr {
  namespace ofdm {

    class limit_vff_impl : public limit_vff
    {
     private:
        float d_up_limit;
        float d_lo_limit;
        int d_vlen;

     public:
      limit_vff_impl(int vlen, float up_limit, float lo_limit);
      ~limit_vff_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_LIMIT_VFF_IMPL_H */

