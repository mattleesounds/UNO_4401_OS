import pydot
import csv

# Read the tree.csv file and create a dictionary
tree_dict = {}
with open('tree.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  # Skip the header row
    for row in reader:
        pid, parent_pid = row
        if parent_pid not in tree_dict:
            tree_dict[parent_pid] = []
        tree_dict[parent_pid].append(pid)

# Function to add edges between parent and child nodes
def draw(parent_name, child_name):
    edge = pydot.Edge(str(parent_name), str(child_name))
    graph.add_edge(edge)

# Function to visit each node
def visit(node, parent=None):
    if parent:
        draw(parent, node)
    if node in tree_dict:
        for child in tree_dict[node]:
            visit(child, node)

# Create an empty graph
graph = pydot.Dot(graph_type='digraph')

# Populate the graph by visiting each node
visit(next(iter(tree_dict)))  # Start with the root node

# Save the graph
graph.write_png('fork_tree.png')
