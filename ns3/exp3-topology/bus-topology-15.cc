#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
    std::cout << "\n=== NS3 BUS TOPOLOGY WITH 15 NODES ===\n" << std::endl;
    
    int numNodes = 15;
    
    // Create nodes
    NodeContainer nodes;
    nodes.Create(numNodes);
    
    // Install Internet stack
    InternetStackHelper stack;
    stack.Install(nodes);
    
    // Create CSMA (Ethernet) bus
    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));
    
    NetDeviceContainer devices = csma.Install(nodes);
    
    // Assign IP addresses
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    address.Assign(devices);
    
    std::cout << "Bus Topology Created:\n";
    std::cout << "- Total Nodes: " << numNodes << "\n";
    std::cout << "- All nodes share a single bus (CSMA)\n";
    std::cout << "\nRunning simulation...\n" << std::endl;
    
    // Enable PCAP tracing
    csma.EnablePcapAll("bus-topology-15");
    
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "Simulation completed!\n" << std::endl;
    
    return 0;
}

