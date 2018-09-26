/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2018 NITK Surathkal
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
 * Authors: Shikha Bakshi <shikhabakshi912@gmail.com>
 *          Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 */

// The network topology used in this example is based on the Fig. 17 described in
// Mohammad Alizadeh, Albert Greenberg, David A. Maltz, Jitendra Padhye,
// Parveen Patel, Balaji Prabhakar, Sudipta Sengupta, and Murari Sridharan.
// "Data Center TCP (DCTCP)." In ACM SIGCOMM Computer Communication Review,
// Vol. 40, No. 4, pp. 63-74. ACM, 2010.

#include <iostream>
#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/applications-module.h"
#include "ns3/packet-sink.h"
#include "ns3/traffic-control-module.h"
#include "ns3/log.h"
#include "ns3/random-variable-stream.h"
#include "ns3/gtk-config-store.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/callback.h"

using namespace ns3;

std::vector<std::stringstream> filePlotQueue;
//std::vector<std::stringstream> filePlotPacketSojourn;
Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable> ();
std::string dir = "results/gfc-dctcp/";
double stopTime = 10;

void
CheckQueueSize (Ptr<QueueDisc> queue)
{
  uint32_t qSize = queue->GetCurrentSize ().GetValue ();

  // check queue size every 1/100 of a second
  Simulator::Schedule (Seconds (0.001), &CheckQueueSize, queue);

  std::ofstream fPlotQueue (std::stringstream (dir + "queue-0.plotme").str ().c_str (), std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << qSize << std::endl;
  fPlotQueue.close ();
}

void
CheckQueueSize1 (Ptr<QueueDisc> queue)
{
  uint32_t qSize = queue->GetCurrentSize ().GetValue ();

  // check queue size every 1/100 of a second
  Simulator::Schedule (Seconds (0.001), &CheckQueueSize1, queue);

  std::ofstream fPlotQueue (std::stringstream (dir + "queue-1.plotme").str ().c_str (), std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << qSize << std::endl;
  fPlotQueue.close ();
}

void
CheckQueueSize2 (Ptr<QueueDisc> queue)
{
  uint32_t qSize = queue->GetCurrentSize ().GetValue ();

  // check queue size every 1/100 of a second
  Simulator::Schedule (Seconds (0.001), &CheckQueueSize2, queue);

  std::ofstream fPlotQueue (std::stringstream (dir + "queue-2.plotme").str ().c_str (), std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << qSize << std::endl;
  fPlotQueue.close ();
}

static void
CwndChange (Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << " " << newCwnd/1446.0 << std::endl;
}

static void
DropAtQueue (Ptr<OutputStreamWrapper> stream, Ptr<const QueueDiscItem> item)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << " 1" << std::endl;
}

static void
MarkAtQueue (Ptr<OutputStreamWrapper> stream, Ptr<const QueueDiscItem> item, const char* reason)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << " 1" << std::endl;
}

void
TraceCwnd (uint32_t node, uint32_t cwndWindow,
           Callback <void, uint32_t, uint32_t> CwndTrace)
{
  Config::ConnectWithoutContext ("/NodeList/" + std::to_string (node) + "/$ns3::TcpL4Protocol/SocketList/" + std::to_string (cwndWindow) + "/CongestionWindow", CwndTrace);
}

void
ProbChange0 (double oldP, double newP)
{
  std::ofstream fPlotQueue (dir + "ProbTraces/T1.plotme", std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newP << std::endl;
  fPlotQueue.close ();
}
void
ProbChange1 (double oldP, double newP)
{
  std::ofstream fPlotQueue (dir + "ProbTraces/T2.plotme", std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newP << std::endl;
  fPlotQueue.close ();
}
void
ProbChange2 (double oldP, double newP)
{
  std::ofstream fPlotQueue (dir + "ProbTraces/Scorp.plotme", std::ios::out | std::ios::app);
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newP << std::endl;
  fPlotQueue.close ();
}
void
TraceProb (uint32_t node, uint32_t probability,
           Callback <void, double, double> ProbTrace)
{
  Config::ConnectWithoutContext ("$ns3::NodeListPriv/NodeList/" + std::to_string (node) + "/$ns3::TrafficControlLayer/RootQueueDiscList/" + std::to_string (probability) + "/$ns3::PiQueueDisc/Probability", ProbTrace);
}

void InstallPacketSink (Ptr<Node> node, uint16_t port)
{
  PacketSinkHelper sink ("ns3::TcpSocketFactory",
                         InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApps = sink.Install (node);
  sinkApps.Start (Seconds (0));
  sinkApps.Stop (Seconds (stopTime));
}

void InstallBulkSend (Ptr<Node> node, Ipv4Address address, uint16_t port, 
                      uint32_t nodeId, uint32_t cwndWindow,
                      Callback <void, uint32_t, uint32_t> CwndTrace)
{

  BulkSendHelper source ("ns3::TcpSocketFactory", 
                         InetSocketAddress (address, port));

  source.SetAttribute ("MaxBytes", UintegerValue (0));
  ApplicationContainer sourceApps = source.Install (node);
  Time timeToStart = Seconds (uv->GetValue (0, 1));
  sourceApps.Start (timeToStart);
  Simulator::Schedule (timeToStart + Seconds (0.001), &TraceCwnd, nodeId, cwndWindow, CwndTrace);
  sourceApps.Stop (Seconds (stopTime));
}



int main (int argc, char *argv[])
{
  uint32_t stream = 1;
  std::string transport_prot = "TcpNewReno";
  std::string queue_disc_type = "FifoQueueDisc";
  bool useEcn = true;
  uint32_t dataSize = 1446;
  uint32_t delAckCount = 2;

  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y-%I-%M-%S",timeinfo);
  std::string currentTime (buffer);

  CommandLine cmd;
  cmd.AddValue ("stream", "Seed value for random variable", stream);
  cmd.AddValue ("transport_prot", "Transport protocol to use: TcpNewReno, "
                "TcpHybla, TcpHighSpeed, TcpHtcp, TcpVegas, TcpScalable, TcpVeno, "
                "TcpBic, TcpYeah, TcpIllinois, TcpWestwood, TcpWestwoodPlus, TcpLedbat, "
                "TcpLp", transport_prot);
  cmd.AddValue ("queue_disc_type", "Queue disc type for gateway (e.g. ns3::CoDelQueueDisc)", queue_disc_type);
  cmd.AddValue ("useEcn", "Use ECN", useEcn);
  cmd.AddValue ("dataSize", "Data packet size", dataSize);
  cmd.AddValue ("delAckCount", "Delayed ack count", delAckCount);
  cmd.AddValue ("stopTime", "Stop time for applications / simulation time will be stopTime", stopTime);
  cmd.Parse (argc,argv);

  uv->SetStream (stream);
  transport_prot = std::string ("ns3::") + transport_prot;
  queue_disc_type = std::string ("ns3::") + queue_disc_type;

  TypeId qdTid;
  NS_ABORT_MSG_UNLESS (TypeId::LookupByNameFailSafe (queue_disc_type, &qdTid), "TypeId " << queue_disc_type << " not found");

  // Select TCP variant
  if (transport_prot.compare ("ns3::TcpWestwoodPlus") == 0)
    {
      // TcpWestwoodPlus is not an actual TypeId name; we need TcpWestwood here
      Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TcpWestwood::GetTypeId ()));
      // the default protocol type in ns3::TcpWestwood is WESTWOOD
      Config::SetDefault ("ns3::TcpWestwood::ProtocolType", EnumValue (TcpWestwood::WESTWOODPLUS));
    }
  else
    {
      TypeId tcpTid;
      NS_ABORT_MSG_UNLESS (TypeId::LookupByNameFailSafe (transport_prot, &tcpTid), "TypeId " << transport_prot << " not found");
      Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (transport_prot)));
    }

  NodeContainer S1, S2, S3, R1, R2, T, Scorp;
  T.Create (2);
  Scorp.Create (1);

  S1.Create (10);
  S2.Create (20);
  S3.Create (10);

  R2.Create (20);
  R1.Create (1);


  PointToPointHelper pointToPointSR;
  pointToPointSR.SetDeviceAttribute ("DataRate", StringValue ("1000Mbps"));
  pointToPointSR.SetChannelAttribute ("Delay", StringValue ("0.05ms"));

  PointToPointHelper pointToPointT;
  pointToPointT.SetDeviceAttribute ("DataRate", StringValue ("10000Mbps"));
  pointToPointT.SetChannelAttribute ("Delay", StringValue ("0.05ms"));

  PointToPointHelper pointToPointT1;
  pointToPointT1.SetDeviceAttribute ("DataRate", StringValue ("10000Mbps"));
  pointToPointT1.SetChannelAttribute ("Delay", StringValue ("0.05ms"));

  NetDeviceContainer T1ScorpDev, T2ScorpDev, S1T1Dev, S2T1Dev, S3T2Dev, R1T2Dev, R2T2Dev;
  T1ScorpDev = pointToPointT.Install (T.Get (0), Scorp.Get (0));
  T2ScorpDev = pointToPointT1.Install (Scorp.Get (0), T.Get (1));
  R1T2Dev = pointToPointSR.Install (R1.Get (0), T.Get (1));

  for (uint32_t i = 0; i < S1.GetN (); i++)
    {
      S1T1Dev.Add (pointToPointSR.Install (S1.Get (i), T.Get (0)));
      S3T2Dev.Add (pointToPointSR.Install (S3.Get (i), T.Get (1)));
    }

  for (uint32_t i = 0; i < S2.GetN (); i++)
    {
      S2T1Dev.Add (pointToPointSR.Install (S2.Get (i), T.Get (0)));
     
    }

  for (uint32_t i = 0; i < R2.GetN (); i++)
    {
      R2T2Dev.Add (pointToPointSR.Install (R2.Get (i), T.Get (1)));
    }

  InternetStackHelper stack;
  stack.Install (S1);
  stack.Install (S2);
  stack.Install (S3);
  stack.Install (R1);
  stack.Install (R2);
  stack.Install (T);
  stack.Install (Scorp);

  //Assign IP address. We keep each sender-switch link in a different network
  Ipv4AddressHelper address;
  Ipv4InterfaceContainer S1Int, S2Int, S3Int, R1Int, R2Int, T1Int,T2Int;

  address.SetBase ("10.1.0.0", "255.255.255.0");



  for(uint32_t i=0; i<S1T1Dev.GetN (); i = i+2)
  {
     address.NewNetwork ();
     NetDeviceContainer S1iT1i;
     S1iT1i.Add(S1T1Dev.Get (i));
     S1iT1i.Add(S1T1Dev.Get (i+1));
     S1Int.Add (address.Assign (S1iT1i));
  }
  address.SetBase ("10.2.0.0", "255.255.255.0");


  for(uint32_t i=0; i<S2T1Dev.GetN (); i = i+2)
  {
     address.NewNetwork ();
     NetDeviceContainer S2iT1i;
     S2iT1i.Add(S2T1Dev.Get (i));
     S2iT1i.Add(S2T1Dev.Get (i+1));
     S2Int.Add (address.Assign (S2iT1i));
  }

  address.SetBase ("10.3.0.0", "255.255.255.0");

  for(uint32_t i=0; i<S3T2Dev.GetN (); i = i+2)
  {
     address.NewNetwork ();
     NetDeviceContainer S3iT2i;
     S3iT2i.Add(S3T2Dev.Get (i));
     S3iT2i.Add(S3T2Dev.Get (i+1));
     S3Int.Add (address.Assign (S3iT2i));
  }

  address.SetBase ("10.4.0.0", "255.255.255.0");
  R1Int = address.Assign (R1T2Dev);
  address.SetBase ("10.5.0.0", "255.255.255.0");


  for(uint32_t i=0; i<R2T2Dev.GetN (); i = i+2)
  {
     address.NewNetwork ();
     NetDeviceContainer R2iT2i;
     R2iT2i.Add(R2T2Dev.Get (i));
     R2iT2i.Add(R2T2Dev.Get (i+1));
     R2Int.Add (address.Assign (R2iT2i));
  }

  address.SetBase ("10.6.0.0", "255.255.255.0");
  T1Int = address.Assign (T1ScorpDev);

  address.SetBase ("10.7.0.0", "255.255.255.0");
  T2Int = address.Assign (T2ScorpDev);

  dir += (currentTime + "/");
  std::string dirToSave = "mkdir -p " + dir;
  system (dirToSave.c_str ());
  system ((dirToSave + "/pcap/").c_str ());
  system ((dirToSave + "/cwndTraces/").c_str ());
  system ((dirToSave + "/ProbTraces/").c_str ());
  system ((dirToSave + "/markTraces/").c_str ());
  system ((dirToSave + "/queueTraces/").c_str ());
  system (("cp -R PlotScripts-gfc-dctcp/* " + dir + "/pcap/").c_str ());

  Config::SetDefault ("ns3::TcpSocket::SndBufSize", UintegerValue (1 << 20));
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (1 << 20));
  Config::SetDefault ("ns3::TcpSocket::InitialCwnd", UintegerValue (10));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (delAckCount));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (dataSize));
  Config::SetDefault ("ns3::TcpSocketBase::UseEcn", BooleanValue (useEcn));
  Config::SetDefault ("ns3::PiQueueDisc::UseEcn", BooleanValue (useEcn));
  Config::SetDefault ("ns3::PiQueueDisc::MeanPktSize", UintegerValue (1500));
  Config::SetDefault ("ns3::PiQueueDisc::A", DoubleValue ( 0.00007477268187));
  Config::SetDefault ("ns3::PiQueueDisc::B", DoubleValue ( 0.00006680872759));
  Config::SetDefault ("ns3::PiQueueDisc::W", DoubleValue (4000));
  Config::SetDefault ("ns3::PiQueueDisc::QueueRef", DoubleValue (50));
  Config::SetDefault (queue_disc_type + "::MaxSize", QueueSizeValue (QueueSize ("666p")));

  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> streamWrapper;

  TrafficControlHelper tch;
  tch.SetRootQueueDisc (queue_disc_type);

  QueueDiscContainer qd, qd1, qd2;
  tch.Uninstall (T1ScorpDev);
  qd = tch.Install (T1ScorpDev);
  Simulator::ScheduleNow (&CheckQueueSize, qd.Get (0));
  Simulator::Schedule (Seconds (2.0), &TraceProb, 0, 0, MakeCallback (&ProbChange0));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/drop-0.plotme");
  qd.Get (0)->TraceConnectWithoutContext ("Drop", MakeBoundCallback (&DropAtQueue, streamWrapper));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/mark-0.plotme");
  qd.Get (0)->TraceConnectWithoutContext ("Mark", MakeBoundCallback (&MarkAtQueue, streamWrapper));

  tch.Uninstall (T2ScorpDev);
  qd1 = tch.Install (T2ScorpDev);
  Simulator::ScheduleNow (&CheckQueueSize1, qd1.Get (0));
 
  Simulator::Schedule (Seconds (2.0), &TraceProb, 2, 0, MakeCallback (&ProbChange2));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/drop-1.plotme");
  qd1.Get (0)->TraceConnectWithoutContext ("Drop", MakeBoundCallback (&DropAtQueue, streamWrapper));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/mark-1.plotme");
  qd1.Get (0)->TraceConnectWithoutContext ("Mark", MakeBoundCallback (&MarkAtQueue, streamWrapper));

  tch.Uninstall (R1T2Dev);
  qd2 = tch.Install (R1T2Dev);
  Simulator::ScheduleNow (&CheckQueueSize2, qd2.Get (1));
  Simulator::Schedule (Seconds (2.0), &TraceProb, 1, 1, MakeCallback (&ProbChange1));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/drop-2.plotme");
  qd2.Get (1)->TraceConnectWithoutContext ("Drop", MakeBoundCallback (&DropAtQueue, streamWrapper));
  streamWrapper = asciiTraceHelper.CreateFileStream (dir + "/queueTraces/mark-2.plotme");
  qd2.Get (1)->TraceConnectWithoutContext ("Mark", MakeBoundCallback (&MarkAtQueue, streamWrapper));

Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/0/$" + queue_disc_type + "/MaxSize", QueueSizeValue (QueueSize ("666p")));
  Config::Set ("/$ns3::NodeListPriv/NodeList/1/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$" + queue_disc_type + "/MaxSize", QueueSizeValue (QueueSize ("666p")));
  Config::Set ("/$ns3::NodeListPriv/NodeList/2/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$" + queue_disc_type + "/MaxSize", QueueSizeValue (QueueSize ("666p")));

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/0/$ns3::PiQueueDisc/QueueRef", DoubleValue (50));
  Config::Set ("/$ns3::NodeListPriv/NodeList/1/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/QueueRef", DoubleValue (50));
  Config::Set ("/$ns3::NodeListPriv/NodeList/2/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/QueueRef", DoubleValue (50));

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/0/$ns3::PiQueueDisc/A", DoubleValue ( 0.00007477268187));
  Config::Set ("/$ns3::NodeListPriv/NodeList/1/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/A", DoubleValue (0.007460151193));
  Config::Set ("/$ns3::NodeListPriv/NodeList/2/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/A", DoubleValue (0.00007477268187));

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/0/$ns3::PiQueueDisc/B", DoubleValue (0.00006680872759));
  Config::Set ("/$ns3::NodeListPriv/NodeList/1/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/B", DoubleValue (0.003907698244));
  Config::Set ("/$ns3::NodeListPriv/NodeList/2/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/B", DoubleValue (0.00006680872759));

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/0/$ns3::PiQueueDisc/W", DoubleValue (4000));
  Config::Set ("/$ns3::NodeListPriv/NodeList/1/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/W", DoubleValue (4000));
  Config::Set ("/$ns3::NodeListPriv/NodeList/2/$ns3::Node/$ns3::TrafficControlLayer/RootQueueDiscList/1/$ns3::PiQueueDisc/W", DoubleValue (4000));

  uint16_t port = 50000;
  //Install Sink applications on R1
  for(int i=0; i<20; i++)
    {
      InstallPacketSink (R1.Get (0), port+i);
    }
  
  //Install BulkSend applications on S1 and S3
  for (int i = 0; i < 10; i++)
    {
      Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream (dir + "cwndTraces/S1" + std::to_string (i) + ".plotme");
      InstallBulkSend (S1.Get (i), R1Int.GetAddress (0), port + i, 3 + i, 0, MakeBoundCallback (&CwndChange, stream));
    }

  for (int i = 0; i < 10; i++)
    {
      Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream (dir + "cwndTraces/S3" + std::to_string (i) + ".plotme");
      InstallBulkSend (S3.Get (i), R1Int.GetAddress (0), port + 10 + i, 33 + i, 0, MakeBoundCallback (&CwndChange, stream));
    }

  //Install Sink applications on R2
  for (uint32_t i = 0; i < R2.GetN (); i++)
    {
      InstallPacketSink (R2.Get (i), port);
    }

  //Install BulkSend applications on S2

  for (int i = 0; i < 20; i++)
    {
      Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream (dir + "cwndTraces/S2" + std::to_string (i) + ".plotme");
      InstallBulkSend (S2.Get (i), R2Int.GetAddress (2 * i), port, 13 + i, 0, MakeBoundCallback (&CwndChange, stream));
    }

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  pointToPointSR.EnablePcapAll (dir + "pcap/N", true);
  Ptr<FlowMonitor> monitor;
  FlowMonitorHelper flowmon;
  monitor=flowmon.InstallAll();

  Simulator::Stop (Seconds (stopTime));
  Simulator::Run ();
  
  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
      // first 2 FlowIds are for ECHO apps, we don't want to display them
      //
      // Duration for throughput measurement is 9.0 seconds, since
      //   StartTime of the OnOffApplication is at about "second 1"
      // and
      //   Simulator::Stops at "second 10".
      if (i->first > 2)
        {
          Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
          std::cout << "Flow " << i->first - 2 << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Packets: " << i->second.txPackets << "\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  TxOffered:  " << i->second.txBytes * 8.0 / 9.0 / 1000 / 1000  << " Mbps\n";
          std::cout << "  Rx Packets: " << i->second.rxPackets << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
          std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / 9.0 / 1000 / 1000  << " Mbps\n";
        }
  }
  std::ofstream myfile;
  myfile.open (dir + "queueStats.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  myfile << std::endl;
  myfile << "Stat for Queue 0";
  myfile << qd.Get (0)->GetStats ();
  myfile << "Stat for Queue 1";
  myfile << qd1.Get (0)->GetStats ();
  myfile << "Stat for Queue 2";
  myfile << qd2.Get (1)->GetStats ();
  myfile.close ();

  myfile.open (dir + "config.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  myfile << "useEcn " << useEcn << "\n";
  myfile << "queue_disc_type " << queue_disc_type << "\n";
  myfile << "stream  " << stream << "\n";
  myfile << "transport_prot " << transport_prot << "\n";
  myfile << "dataSize " << dataSize << "\n";
  myfile << "delAckCount " << delAckCount << "\n";
  myfile << "stopTime " << stopTime << "\n";
  myfile.close ();

  Simulator::Destroy ();
  return 0;

}
