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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "allocation_src_impl.h"
#include <iostream>

namespace gr {
  namespace ofdm {

    allocation_src::sptr
    allocation_src::make(int subcarriers, int data_symbols)
    {
      return gnuradio::get_initial_sptr
        (new allocation_src_impl(subcarriers, data_symbols));
    }

    /*
     * The private constructor
     *
     * Description of output format:
     *
     * id: 0..255
     * bitcount: number of payload bits in a frame
     * bitloading: vector containing 2 vectors with bitloading for 1.: id and 2.: data
     * power: vector containing power allocation vectors for id symbol and every data symbol
     *
     */
    allocation_src_impl::allocation_src_impl(int subcarriers, int data_symbols)
        : gr::block("allocation_src",
                         gr::io_signature::make(0, 0, 0),
                         gr::io_signature::make(0, 0, 0))
        ,d_subcarriers(subcarriers), d_data_symbols(data_symbols)
    {
        std::vector<int> out_sig(4);
        out_sig[0] = sizeof(short);                             // id
        out_sig[1] = sizeof(int);                               // bitcount
        out_sig[2] = sizeof(char)*subcarriers;                  // bitloading
        out_sig[3] = sizeof(gr_complex)*subcarriers;            // power
        set_output_signature(io_signature::makev(4,4,out_sig));

        d_allocation.id = 0;

        std::vector<char> bitloading_vec;
        std::vector<gr_complex> power_vec;
        // default data modulation scheme is BPSK
        for(int i=0;i<subcarriers;i++)
        {
            bitloading_vec.push_back(1);
        }
        // init power allocation vector
        for(int i=0;i<subcarriers;i++)
        {
            power_vec.push_back(1);
        }
        set_allocation(bitloading_vec,power_vec);
    }

    /*
     * Our virtual destructor.
     */
    allocation_src_impl::~allocation_src_impl()
    {
    }

    void
    allocation_src_impl::set_allocation(std::vector<char> bitloading,
                                        std::vector<gr_complex> power)
    {
        gr::thread::scoped_lock guard(d_mutex);
        // push back ID symbol modulation
        for(int i=0;i<d_subcarriers;i++)
        {
            d_allocation.bitloading.push_back(1);
        }
        // insert data symbol modulation at the end ONCE
        d_allocation.bitloading.insert(d_allocation.bitloading.end(), bitloading.begin(), bitloading.end());

        // push back ID symbol power
        for(int i=0;i<d_subcarriers;i++)
        {
            d_allocation.power.push_back(1);
        }
        // insert data symbol power at the end TIMES data_symbols
        for(int i=0;i<d_data_symbols;i++)
        {
            d_allocation.power.insert(d_allocation.power.end(), power.begin(), power.end());
        }

        int sum_of_elems = 0;
        for(std::vector<char>::iterator j=bitloading.begin();j!=bitloading.end();++j)
            sum_of_elems += *j;
        d_bitcount = sum_of_elems*d_data_symbols;

        d_mux_ctrl.clear();
        // switch mux to ID
        for(int i=0;i<d_subcarriers;i++)
        {
            d_mux_ctrl.push_back(0);
        }
        // switch mux to DATA
        for(int i=0;i<d_bitcount;i++)
        {
            d_mux_ctrl.push_back(1);
        }
    }


    int
    allocation_src_impl::general_work(int noutput_items,
                                      gr_vector_int &ninput_items,
                                      gr_vector_const_void_star &input_items,
                                      gr_vector_void_star &output_items)

    {
        gr::thread::scoped_lock guard(d_mutex);

        short *out_id = (short *) output_items[0];
        int *out_bitcount = (int *) output_items[1];
        char *out_bitloading = (char *) output_items[2];
        gr_complex *out_power = (gr_complex *) output_items[3];

        *out_id = d_allocation.id;
        *out_bitcount = d_bitcount;
        //FIXME: probably dirty hack
        // output 2 vectors for id and data
        memcpy(out_bitloading, &d_allocation.bitloading[0], sizeof(char)*2*d_subcarriers);
        // output 1 vector for id and the rest for data
        memcpy(out_power, &d_allocation.power[0], sizeof(gr_complex)*(1+d_data_symbols)*d_subcarriers);

        d_allocation.id++;
        if (d_allocation.id > 255) {
            d_allocation.id = 0;
        }
        produce(0,1);
        produce(1,1);
        produce(2,2);
        produce(3,1+d_data_symbols);

        // Tell runtime system how many output items we produced.
        return WORK_CALLED_PRODUCE;
    }

  } /* namespace ofdm */
} /* namespace gr */
