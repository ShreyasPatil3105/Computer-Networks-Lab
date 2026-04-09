/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("StarTopology16");

int main(int argc, char *argv[])
{
    std::cout << "\n=== NS3 STAR TOPOLOGY WITH 16 NODES ===\n" << std::endl;
    
    int numSpokes = 15;  // 15 spoke nodes
    
    // Create 1 hub node
    NodeContainer hub;
    hub.Create(1);
    
    // Create spoke nodes
    NodeContainer spokes;
    spokes.Create(numSpokes);
    
    NodeContainer allNodes = NodeContainer(hub, spokes);
    
    // Install Internet stack
    InternetStackHelper stack;
    stack.Install(allNodes);
    
    // Create point-to-point links
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    Ipv4AddressHelper address;
    
    for (int i = 0; i < numSpokes; i++)
    {
        NodeContainer pair = NodeContainer(hub.Get(0), spokes.Get(i));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10.1." << i + 1 << ".0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    std::cout << "Star Topology Created:\n";
    std::cout << "- 1 Hub Node\n";
    std::cout << "- " << numSpokes << " Spoke Nodes\n";
    std::cout << "- Total Nodes: " << numSpokes + 1 << "\n";
    std::cout << "\nRunning simulation...\n" << std::endl;
    
    // Enable PCAP tracing
    p2p.EnablePcapAll("star-topology-16");
    
    // Run simulation
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "Simulation completed!\n" << std::endl;
    
    return 0;
}
