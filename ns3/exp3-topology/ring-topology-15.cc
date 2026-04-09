#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
    std::cout << "\n=== NS3 RING TOPOLOGY WITH 15 NODES ===\n" << std::endl;
    
    int numNodes = 15;
    
    // Create nodes
    NodeContainer nodes;
    nodes.Create(numNodes);
    
    // Install Internet stack
    InternetStackHelper stack;
    stack.Install(nodes);
    
    // Create point-to-point links in a ring
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    Ipv4AddressHelper address;
    
    // Connect nodes in a ring (node i to node i+1)
    for (int i = 0; i < numNodes - 1; i++)
    {
        NodeContainer pair = NodeContainer(nodes.Get(i), nodes.Get(i+1));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10." << i + 1 << ".1.0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    // Connect last node to first to complete the ring
    NodeContainer lastPair = NodeContainer(nodes.Get(numNodes-1), nodes.Get(0));
    NetDeviceContainer lastLink = p2p.Install(lastPair);
    address.SetBase("10.100.1.0", "255.255.255.0");
    address.Assign(lastLink);
    
    std::cout << "Ring Topology Created:\n";
    std::cout << "- Total Nodes: " << numNodes << "\n";
    std::cout << "- Each node connected to 2 neighbors\n";
    std::cout << "\nRunning simulation...\n" << std::endl;
    
    // Enable PCAP tracing
    p2p.EnablePcapAll("ring-topology-15");
    
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "Simulation completed!\n" << std::endl;
    
    return 0;
}

