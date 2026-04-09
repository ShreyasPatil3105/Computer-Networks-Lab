#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
    std::cout << "\n=== NS3 TREE TOPOLOGY WITH 15 NODES ===\n" << std::endl;
    
    // Tree structure: 1 root, 3 internal, 11 leaves
    // Root (node 0) -> 3 internal nodes (nodes 1,2,3)
    // Each internal node -> 3-4 leaf nodes
    
    NodeContainer nodes;
    nodes.Create(15);
    
    InternetStackHelper stack;
    stack.Install(nodes);
    
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    Ipv4AddressHelper address;
    
    // Root (0) to internal nodes (1,2,3)
    for (int i = 1; i <= 3; i++)
    {
        NodeContainer pair = NodeContainer(nodes.Get(0), nodes.Get(i));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10.1." << i << ".0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    // Internal node 1 (node 1) to leaves (4,5,6)
    for (int i = 4; i <= 6; i++)
    {
        NodeContainer pair = NodeContainer(nodes.Get(1), nodes.Get(i));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10.2." << i << ".0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    // Internal node 2 (node 2) to leaves (7,8,9,10)
    for (int i = 7; i <= 10; i++)
    {
        NodeContainer pair = NodeContainer(nodes.Get(2), nodes.Get(i));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10.3." << i << ".0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    // Internal node 3 (node 3) to leaves (11,12,13,14)
    for (int i = 11; i <= 14; i++)
    {
        NodeContainer pair = NodeContainer(nodes.Get(3), nodes.Get(i));
        NetDeviceContainer link = p2p.Install(pair);
        
        std::ostringstream subnet;
        subnet << "10.4." << i << ".0";
        address.SetBase(subnet.str().c_str(), "255.255.255.0");
        address.Assign(link);
    }
    
    std::cout << "Tree Topology Created:\n";
    std::cout << "- Total Nodes: 15\n";
    std::cout << "- 1 Root Node\n";
    std::cout << "- 3 Internal Nodes\n";
    std::cout << "- 11 Leaf Nodes\n";
    std::cout << "\nRunning simulation...\n" << std::endl;
    
    p2p.EnablePcapAll("tree-topology-15");
    
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "Simulation completed!\n" << std::endl;
    
    return 0;
}

