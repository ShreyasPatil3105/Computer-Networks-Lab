clf();
scf(0);
figure(0, "position", [0,0,800,600]);
title("Hybrid Network Topology - Star + Ring + Bus", "fontsize", 4);

//Star Topology (Central Hub + 8 Nodes)

//Hub Coordinates - center of star topology 
hub_x = 0;//x coordinate of hub at center
hub_y = 0;//y coordinate of hub at center 

//Create arrays to store positions of 8 star nodes 
star_nodes_x = [];//Empty array to store X cooordinates 
star_nodes_y = [];//Empty array to store X cooordinates 
// Loop to create 8 nodes around the hub in a circle
for i = 1:8  // i goes from 1 to 8 (creates 8 nodes)
    // Calculate angle for each node - equally spaced around 360 degrees
    // (i-1) makes first node at angle 0, second at 45°, etc.
    // 2 * %pi is 360 degrees in radians
    angle = (i-1) * 2 * %pi / 8;
    // Calculate X coordinate using cosine: x = radius * cos(angle)
    star_nodes_x(i) = 3 * cos(angle);
    // Calculate Y coordinate using sine: y = radius * sin(angle)
    star_nodes_y(i) = 3 * sin(angle);
end
// Draw edges (connections) for Star topology
// Each star node connects to the central hub
for i = 1:8
    // plot([x1,x2], [y1,y2]) draws a line between point1 (hub) and point2 (star node)
    // 'b-' means blue solid line (b=blue, -=solid line)
    plot([hub_x, star_nodes_x(i)], [hub_y, star_nodes_y(i)], 'b-', 'LineWidth', 1.5);
end
//RING TOPOLOGY (10 Nodes in a Circle)
// Create arrays to store positions of 10 ring nodes
ring_nodes_x = [];  // Empty array for ring X coordinates
ring_nodes_y = [];  // Empty array for ring Y coordinates

// Loop to create 10 nodes arranged in a circle
for i = 1:10  // i goes from 1 to 10 (creates 10 nodes)
    // Calculate angle - equally spaced around the circle
    angle = (i-1) * 2 * %pi / 10;
    
    // Radius of 8 units makes ring larger than star (star radius was 3)
    ring_nodes_x(i) = 8 * cos(angle);
    ring_nodes_y(i) = 8 * sin(angle);
end

// Draw edges for Ring topology
// In a ring, each node connects to its next neighbor
for i = 1:9  // Connect node 1 to 2, 2 to 3, ..., 9 to 10
    // 'r-' means red solid line (r=red, -=solid line)
    plot([ring_nodes_x(i), ring_nodes_x(i+1)], [ring_nodes_y(i), ring_nodes_y(i+1)], 'r-', 'LineWidth', 1.5);
end
// Connect last node (10) back to first node (1) to complete the ring
plot([ring_nodes_x(10), ring_nodes_x(1)], [ring_nodes_y(10), ring_nodes_y(1)], 'r-', 'LineWidth', 1.5);
//BUS TOPOLOGY (10 Nodes on a Horizontal Line)
// Create arrays to store positions of 10 bus nodes
bus_nodes_x = [];  // Empty array for bus X coordinates
bus_nodes_y = [];  // Empty array for bus Y coordinates

// Loop to create 10 nodes along a horizontal line
for i = 1:10
    // X coordinate: start at -12 and increase by 2.5 for each node
    // This spreads nodes evenly across the bottom of the graph
    bus_nodes_x(i) = -12 + (i-1) * 2.5;
    
    // Y coordinate: all nodes at y = -6 (horizontal line)
    bus_nodes_y(i) = -6;
end

// Draw the main backbone (horizontal line connecting all bus nodes)
// 'g-' means green solid line (g=green, -=solid line)
// LineWidth 2 makes backbone thicker than normal connections
plot([bus_nodes_x(1), bus_nodes_x(10)], [bus_nodes_y(1), bus_nodes_y(10)], 'g-', 'LineWidth', 2);

// Draw vertical drop lines from each node to the backbone
// This shows each node is connected to the main bus line
for i = 1:10
    // 'g:' means green dotted line (: = dotted)
    // Draw vertical line from node down to backbone (y-0.5)
    plot([bus_nodes_x(i), bus_nodes_x(i)], [bus_nodes_y(i), bus_nodes_y(i) - 0.5], 'g:', 'LineWidth', 1);
end
//PLOT ALL NODES WITH COLORS AND NUMBERS
// --- STAR TOPOLOGY NODES (Blue) ---
// Plot the central hub (node 1)
// 'bo' means blue circle (b=blue, o=circle)
// MarkerSize controls size of the node
// MarkerFaceColor fills the circle with color
plot(hub_x, hub_y, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'blue');
// xstring(x,y,"text") adds text label at position (x,y)
// Label node 1 at position slightly offset so it doesn't cover the node
xstring(hub_x - 0.3, hub_y - 0.3, "1");

// Plot the 8 star nodes (nodes 2-9)
for i = 1:8
    // 'bo' with cyan fill for star nodes (different shade from hub)
    plot(star_nodes_x(i), star_nodes_y(i), 'bo', 'MarkerSize', 8, 'MarkerFaceColor', 'cyan');
    // Label each node with its number (i+1 because node 1 is hub)
    xstring(star_nodes_x(i) - 0.3, star_nodes_y(i) - 0.3, string(i+1));
end

// --- RING TOPOLOGY NODES (Red) ---
// Node numbering continues: star had 9 nodes (1 hub + 8 nodes)
// So ring nodes start from node 10
node_counter = 10;  // Starting number for ring nodes
for i = 1:10
    // 'ro' means red circle
    plot(ring_nodes_x(i), ring_nodes_y(i), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'red');
    // Label node with number (node_counter + i)
    // When i=1, label = 10+1 = 11? Wait, need to fix numbering
    // Actually: star had nodes 1-9, so ring should start at 10
    xstring(ring_nodes_x(i) - 0.3, ring_nodes_y(i) - 0.3, string(9 + i));
    // 9 + i gives: i=1->10, i=2->11, ..., i=10->19 ✓
end

// --- BUS TOPOLOGY NODES (Green) ---
// Bus nodes start from node 20 (since ring had nodes 10-19)
node_counter = 20;  // Starting number for bus nodes
for i = 1:10
    // 'go' means green circle
    plot(bus_nodes_x(i), bus_nodes_y(i), 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'green');
    // Label node with number (19 + i gives 20 to 29)
    xstring(bus_nodes_x(i) - 0.3, bus_nodes_y(i) - 0.3, string(19 + i));
end
//CONNECT THE THREE TOPOLOGIES (Hybrid Connections)
// Connect Ring to Star - creates a hybrid network
// Connect ring's first node (node 10) to star's first node (node 2)
// 'm--' means magenta dashed line (m=magenta, --=dashed)
plot([ring_nodes_x(1), star_nodes_x(1)], [ring_nodes_y(1), star_nodes_y(1)], 'm--', 'LineWidth', 1);

// Connect Bus to Star - another hybrid connection
// Connect bus's 5th node (node 24) to star's 3rd node (node 4)
plot([bus_nodes_x(5), star_nodes_x(3)], [bus_nodes_y(5), star_nodes_y(3)], 'm--', 'LineWidth', 1);
//FORMATTING AND DISPLAY ENHANCEMENTS
xlabel("X Coordinate");  // Label for X-axis
ylabel("Y Coordinate");  // Label for Y-axis

// Add legend to explain what each color means
// legend(["label1","label2",...], "fontsize", size)
legend(["Star Edges", "Ring Edges", "Bus Edges", "Hybrid Connections"], "fontsize", 2);

// Auto-scale the graph to fit all elements
set(gca(), "auto_scale", "on");

// Make the graph isometric (same scale on X and Y axes)
// This ensures circles look like circles, not ovals
set(gca(), "isoview", "on");

// Add grid lines for easier visualization
xgrid(1);
//NETWORK STATISTICS - PRINT TO CONSOLE
// Print heading
printf("\n========================================\n");
printf("NETWORK TOPOLOGY STATISTICS\n");
printf("========================================\n");

// TOTAL NODES: hub(1) + star(8) + ring(10) + bus(10) = 29
total_nodes = 1 + 8 + 10 + 10;
printf("Total Number of Nodes: %d\n", total_nodes);
// %d is placeholder for integer, \n adds new line

// TOTAL EDGES: star connections + ring connections + bus connections + hybrid connections
// Star: hub connects to 8 nodes = 8 edges
// Ring: 10 nodes each connected to 2 neighbors = 10 edges (not 20 because each edge counted once)
// Bus: 10 nodes connected to backbone = 10 edges (each node has one connection)
// Hybrid: 2 connections between topologies = 2 edges
star_edges = 8;
ring_edges = 10;
bus_edges = 10;
hybrid_edges = 2;
total_edges = star_edges + ring_edges + bus_edges + hybrid_edges;
printf("Total Number of Edges: %d\n", total_edges);

// NODE DEGREE STATISTICS
// Degree = number of connections (edges) a node has
printf("\n--- Node Degree Statistics ---\n");

// Node 1 (Hub): connected to all 8 star nodes
printf("Node 1 (Hub): 8 connections\n");

// Star nodes (2-9): each connected only to hub (1 connection each)
for i = 2:9
    printf("Node %d (Star Node): 1 connection\n", i);
end

// Ring nodes (10-19): each connected to 2 neighbors in ring
for i = 10:19
    printf("Node %d (Ring Node): 2 connections\n", i);
end

// Bus nodes (20-29): each connected to backbone (1 connection each)
for i = 20:29
    printf("Node %d (Bus Node): 1 connection\n", i);
end

// NODE WITH MAXIMUM DEGREE
printf("\n--- Node with Maximum Connections ---\n");
printf("Node 1 (Hub) has the maximum connections: 8 edges\n");

// SUMMARY
printf("\n========================================\n");
printf("Topology created using: STAR + RING + BUS\n");
printf("Total Nodes: 29 | Total Edges: 30\n");
printf("========================================\n");

// ============================================
// END OF CODE
// ============================================
// TO RUN: Press F5 or click the green play button
// OUTPUT: A graph window with the topology + console showing statistics
