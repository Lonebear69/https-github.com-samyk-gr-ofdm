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


#ifndef INCLUDED_OFDM_CORBA_RXINFO_SINK_H
#define INCLUDED_OFDM_CORBA_RXINFO_SINK_H

#include <ofdm/api.h>
#include <gnuradio/sync_block.h>

#include <string>

namespace gr {
  namespace ofdm {

  /*!
   * \brief Collect RX performance measure and push to event channel
   *
   * Inputs:
   * 1. ID
   * 2. CTF vector
   * 3. CTF_2 vector
   * 4. BER
   * 5. SNR
   * 6. SNR_2
   */
    class OFDM_API corba_rxinfo_sink : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<corba_rxinfo_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm::corba_rxinfo_sink.
       *
       * To avoid accidental use of raw pointers, ofdm::corba_rxinfo_sink's
       * constructor is in a private implementation
       * class. ofdm::corba_rxinfo_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string sevent_channel, std::string snameservice_ip, std::string snameservice_port, int vlen, int vlen_sc, long station_id);
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_CORBA_RXINFO_SINK_H */

