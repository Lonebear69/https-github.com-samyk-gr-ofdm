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

#ifndef INCLUDED_OFDM_VECTOR_MASK_IMPL_H
#define INCLUDED_OFDM_VECTOR_MASK_IMPL_H

#include <ofdm/vector_mask.h>

#include <vector>

namespace gr {
  namespace ofdm {

    class vector_mask_impl : public vector_mask
    {
     private:
		size_t d_vlen;
		size_t d_cut_left;
		size_t d_mask_len;
		std::vector<unsigned char> d_mask;

     public:
      vector_mask_impl(size_t vlen, size_t cut_left, size_t mask_len, std::vector<unsigned char> mask);
      ~vector_mask_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_VECTOR_MASK_IMPL_H */

