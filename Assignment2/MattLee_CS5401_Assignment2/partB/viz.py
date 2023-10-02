import pydot
import csv

tree_dict = {}

# Read the CSV
with open('pids.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for child_pid, parent_pid in reader:
        if parent_pid not in tree_dict:
            tree_dict[parent_pid] = []
        tree_dict[parent_pid].append(child_pid)

graph = pydot.Dot(graph_type='digraph')

# Draw the tree 
for parent, children in tree_dict.items():
    for child in children:
        edge = pydot.Edge(parent, child)
        graph.add_edge(edge)

graph.write_png('fork_tree(partCn=7).png')
