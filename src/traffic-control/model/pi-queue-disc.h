/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Viyom Mittal <viyommittal@gmail.com>
 *          Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 */

/*
 * PORT NOTE: This code was ported from ns-2.36rc1 (queue/pi.h).
 * Most of the comments are also ported from the same.
 */

#ifndef PI_QUEUE_DISC_H
#define PI_QUEUE_DISC_H

#include "ns3/queue-disc.h"
#include "ns3/nstime.h"
#include "ns3/boolean.h"
#include "ns3/data-rate.h"
#include "ns3/timer.h"
#include "ns3/event-id.h"
#include "ns3/random-variable-stream.h"

namespace ns3 {

class TraceContainer;
class UniformRandomVariable;

/**
 * \ingroup traffic-control
 *
 * \brief Implements PI Active Queue Management discipline
 */
class PiQueueDisc : public QueueDisc
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * \brief PiQueueDisc Constructor
   */
  PiQueueDisc ();

  /**
   * \brief PiQueueDisc Destructor
   */
  virtual ~PiQueueDisc ();

  /**
   * \brief Enumeration of the modes supported in the class.
   * \deprecated This enum will go away in future versions of ns-3.
   *
   */
  enum QueueDiscMode
  {
    QUEUE_DISC_MODE_PACKETS,     /**< Use number of packets for maximum queue disc size */
    QUEUE_DISC_MODE_BYTES,       /**< Use number of bytes for maximum queue disc size */
  };

//  TracedCallback<double, double> m_dropProbTrace;
  /**
   * \brief Set the operating mode of this queue disc.
   *
   * \param mode The operating mode of this queue disc.
   * \deprecated This method will go away in future versions of ns-3.
   * See instead SetMaxSize()
   */
  void SetMode (QueueDiscMode mode);

  /**
   * \brief Get the operating mode of this queue disc.
   *
   * \returns The operating mode of this queue disc.
   * \deprecated This method will go away in future versions of ns-3.
   * See instead GetMaxSize()
   */
  QueueDiscMode GetMode (void) const;

  /**
   * \brief Get the current value of the queue in bytes or packets.
   *
   * \returns The queue size in bytes or packets.
   */
  uint32_t GetQueueSize (void);

  /**
   * \brief Set the limit of the queue in bytes or packets.
   *
   * \param lim The limit in bytes or packets.
   * \deprecated This method will go away in future versions of ns-3.
   * See instead SetMaxSize()
   */
  void SetQueueLimit (double lim);

  /**
   * Assign a fixed random variable stream number to the random variables
   * used by this model.  Return the number of streams (possibly zero) that
   * have been assigned.
   *
   * \param stream first stream index to use
   * \return the number of stream indices assigned by this model
   */
  int64_t AssignStreams (int64_t stream);

  // Reasons for dropping/marking packets
  static constexpr const char* UNFORCED_DROP = "Unforced drop";  //!< Early probability drops
  static constexpr const char* UNFORCED_MARK = "Unforced mark";  //!< Early probability marks
  static constexpr const char* FORCED_DROP = "Forced drop";      //!< Forced drops

protected:
  /**
   * \brief Dispose of the object
   */
  virtual void DoDispose (void);

private:
  virtual bool DoEnqueue (Ptr<QueueDiscItem> item);
  virtual Ptr<QueueDiscItem> DoDequeue (void);
  virtual Ptr<const QueueDiscItem> DoPeek (void);
  virtual bool CheckConfig (void);

  /**
   * \brief Initialize the queue parameters.
   */
  virtual void InitializeParams (void);

  /**
   * \brief Check if a packet needs to be dropped due to probability drop
   * \param item queue item
   * \param qSize queue size
   * \returns 0 for no drop, 1 for drop
   */
  bool DropEarly (Ptr<QueueDiscItem> item, uint32_t qSize);

  /**
   * Periodically update the drop probability based on the delay samples:
   * not only the current delay sample but also the trend where the delay
   * is going, up or down
   */
  void CalculateP ();

  static const uint64_t DQCOUNT_INVALID = std::numeric_limits<uint64_t>::max();  //!< Invalid dqCount value

  // ** Variables supplied by user
  uint32_t m_meanPktSize;                       //!< Average packet size in bytes
  double m_qRef;                                //!< Desired queue size
  double m_a;                                   //!< Parameter to PI controller
  double m_b;                                   //!< Parameter to PI controller
  double m_w;                                   //!< Sampling frequency (Number of times per second)
  bool m_useEcn;                                //!< True if ECN is used (packets are marked instead of being dropped)

  // ** Variables maintained by PI
  TracedValue<double> m_dropProb;               //!< Variable used in calculation of drop probability
  uint32_t m_qOld;                              //!< Old value of queue length
  EventId m_rtrsEvent;                          //!< Event used to decide the decision of interval of drop probability calculation
  Ptr<UniformRandomVariable> m_uv;              //!< Rng stream
};

};   // namespace ns3

#endif
