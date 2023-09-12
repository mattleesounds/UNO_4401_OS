import pydot
import json

# Function to draw edge between parent and child nodes
def draw(parent_name, child_name, level):
    edge = pydot.Edge(f"{parent_name}\nLevel {level}", f"{child_name}\nLevel {level + 1}")
    graph.add_edge(edge)

# Load JSON data
with open('output.json', 'r') as f:
    data = json.load(f)

# Create an empty graph
graph = pydot.Dot(graph_type='graph')

# Create a dictionary to keep track of child processes for each parent
child_dict = {}
for process in data['processes']:
    pid = process['ProcessID']
    ppid = process['ParentProcessID']
    if ppid not in child_dict:
        child_dict[ppid] = []
    child_dict[ppid].append(pid)

# Recursive function to visit nodes and draw edges
def visit(node_id, level):
    if node_id in child_dict:
        for child_id in child_dict[node_id]:
            draw(node_id, child_id, level)
            visit(child_id, level + 1)

# Start from the root node
root_node = 35821  # Replace with your root node ID
visit(root_node, 0)

# Generate the graph
graph.write_png('process_tree.png')
