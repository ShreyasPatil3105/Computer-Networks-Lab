#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
    std::cout << "\n=== NS3 MESH TOPOLOGY WITH 16 NODES ===\n" << std::endl;
    
    int numNodes = 16;
    
    // Create nodes
    NodeContainer nodes;
    nodes.Create(numNodes);
    
    // Install Internet stack
    InternetStackHelper stack;
    stack.Install(nodes);
    
    // Create point-to-point links for full mesh
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    Ipv4AddressHelper address;
    int subnetCounter = 1;
    
    // Connect every node to every other node (full mesh)
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = i + 1; j < numNodes; j++)
        {
            NodeContainer pair = NodeContainer(nodes.Get(i), nodes.Get(j));
            NetDeviceContainer link = p2p.Install(pair);
            
            std::ostringstream subnet;
            subnet << "10." << subnetCounter / 256 << "." << subnetCounter % 256 << ".0";
            address.SetBase(subnet.str().c_str(), "255.255.255.0");
            address.Assign(link);
            subnetCounter++;
        }
    }
    
    std::cout << "Mesh Topology Created:\n";
    std::cout << "- Total Nodes: " << numNodes << "\n";
    std::cout << "- Full mesh connections: " << (numNodes * (numNodes - 1)) / 2 << " links\n";
    std::cout << "\nRunning simulation...\n" << std::endl;
    
    // Enable PCAP tracing
    p2p.EnablePcapAll("mesh-topology-16");
    
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "Simulation completed!\n" << std::endl;
    
    return 0;
}

