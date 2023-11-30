import java.io.*;
import java.util.*;

public class Deadlock {
    private static RAG rag = new RAG();
    private static ResourceManager resourceManager = new ResourceManager();

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Usage: java Deadlock <inputfile>");
            System.exit(1);
        }

        String inputFile = args[0];
        processInput(inputFile);
    }

    private static void processInput(String inputFile) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile))) {
            String line;
            while ((line = reader.readLine()) != null) {
                processLine(line);
            }
        }
    }

    private static void processLine(String line) {
        String[] parts = line.split(" ");
        int processId = Integer.parseInt(parts[0]);
        String action = parts[1];
        int resourceId = Integer.parseInt(parts[2]);

        if (action.equals("W")) {
            handleRequest(processId, resourceId);
        } else if (action.equals("R")) {
            handleRelease(processId, resourceId);
        } else {
            System.out.println("Invalid action: " + action);
        }
    }

    private static void handleRequest(int processId, int resourceId) {
        if (resourceManager.isResourceFree(resourceId)) {
            resourceManager.requestResource(processId, resourceId);
            rag.addAllocation(processId, resourceId);
            System.out.println("Process " + processId + " wants resource " + resourceId + " – Resource " + resourceId
                    + " is allocated to process " + processId + ".");
        } else {
            resourceManager.requestResource(processId, resourceId);
            rag.addRequest(processId, resourceId);
            System.out.println("Process " + processId + " wants resource " + resourceId + " – Process " + processId
                    + " must wait.");
        }

        List<Node> deadlockNodes = rag.detectDeadlock();
        if (!deadlockNodes.isEmpty()) {
            System.out.println(buildDeadlockMessage(deadlockNodes));
            System.exit(1);
        }
    }

    private static void handleRelease(int processId, int resourceId) {
        Integer nextProcess = resourceManager.releaseResource(resourceId);
        rag.removeAllocation(resourceId, processId);

        if (nextProcess != null) {
            rag.addAllocation(resourceId, nextProcess);
            System.out.println("Process " + processId + " releases resource " + resourceId + " – Resource " + resourceId
                    + " is allocated to process " + nextProcess + ".");
        } else {
            System.out.println("Process " + processId + " releases resource " + resourceId + " – Resource " + resourceId
                    + " is now free.");
        }
    }

    private static String buildDeadlockMessage(List<Node> deadlockNodes) {
        Set<Integer> processes = new HashSet<>();
        Set<Integer> resources = new HashSet<>();

        for (Node node : deadlockNodes) {
            if (node.getType() == Node.NodeType.PROCESS) {
                processes.add(node.getId());
            } else if (node.getType() == Node.NodeType.RESOURCE) {
                resources.add(node.getId());
            }
        }

        return "DEADLOCK DETECTED: Processes " + processes + " and Resources " + resources + " are found in a cycle.";
    }
}

class RAG {
    private Graph graph;

    public RAG() {
        this.graph = new Graph();
    }

    public void addRequest(int processId, int resourceId) {
        Node resourceNode = new Node(resourceId, Node.NodeType.RESOURCE);
        Node processNode = new Node(processId, Node.NodeType.PROCESS);
        graph.addNode(resourceNode);
        graph.addNode(processNode);
        graph.addEdge(resourceNode, processNode);
    }

    public void addAllocation(int processId, int resourceId) {
        Node processNode = new Node(processId, Node.NodeType.PROCESS);
        Node resourceNode = new Node(resourceId, Node.NodeType.RESOURCE);
        graph.addNode(processNode);
        graph.addNode(resourceNode);
        graph.addEdge(processNode, resourceNode); // Process to Resource edge
    }

    public void removeAllocation(int processId, int resourceId) {
        Node processNode = new Node(processId, Node.NodeType.PROCESS);
        Node resourceNode = new Node(resourceId, Node.NodeType.RESOURCE);
        graph.removeEdge(resourceNode, processNode);
    }

    public List<Node> detectDeadlock() {
        return graph.detectCycle();
    }
}

class Graph {
    private Map<Node, List<Node>> adjacencyList;
    private Set<Node> visited;
    private Set<Node> recStack;

    public Graph() {
        this.adjacencyList = new HashMap<>();
        this.visited = new HashSet<>();
        this.recStack = new HashSet<>();
    }

    public void addNode(Node node) {
        adjacencyList.putIfAbsent(node, new ArrayList<>());
    }

    public void addEdge(Node from, Node to) {
        adjacencyList.get(from).add(to);
    }

    public void removeEdge(Node from, Node to) {
        List<Node> edges = adjacencyList.get(from);
        if (edges != null) {
            edges.remove(to);
        }
    }

    public List<Node> detectCycle() {
        List<Node> cycleNodes = new ArrayList<>();
        visited.clear();
        recStack.clear();

        for (Node node : adjacencyList.keySet()) {
            if (!visited.contains(node)) {
                cycleNodes.clear();
                if (detectCycleUtil(node, cycleNodes)) {
                    return new ArrayList<>(cycleNodes);
                }
            }
        }
        return Collections.emptyList();
    }

    private boolean detectCycleUtil(Node node, List<Node> cycleNodes) {
        if (recStack.contains(node)) {
            cycleNodes.add(node);
            return true;
        }
        if (!visited.add(node)) {
            return false;
        }

        recStack.add(node);
        cycleNodes.add(node);

        if (adjacencyList.containsKey(node)) {
            for (Node neighbor : adjacencyList.get(node)) {
                if (detectCycleUtil(neighbor, cycleNodes)) {
                    return true;
                }
            }
        }

        recStack.remove(node);
        cycleNodes.remove(node);
        return false;
    }
}

class Node {
    private int id;
    private NodeType type;

    public Node(int id, NodeType type) {
        this.id = id;
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public NodeType getType() {
        return type;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        Node node = (Node) o;
        return id == node.id && type == node.type;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, type);
    }

    enum NodeType {
        PROCESS, RESOURCE
    }

    @Override
    public String toString() {
        return type + " " + id;
    }
}

class Edge {
    private Node from;
    private Node to;

    public Edge(Node from, Node to) {
        this.from = from;
        this.to = to;
    }

    public Node getFrom() {
        return from;
    }

    public Node getTo() {
        return to;
    }
}

class ResourceManager {
    private Map<Integer, Integer> resourceAllocation;
    private Map<Integer, Queue<Integer>> waitingProcesses;

    public ResourceManager() {
        resourceAllocation = new HashMap<>();
        waitingProcesses = new HashMap<>();
    }

    public void requestResource(int processId, int resourceId) {
        if (!resourceAllocation.containsKey(resourceId) || resourceAllocation.get(resourceId) == null) {
            resourceAllocation.put(resourceId, processId);
        } else {
            waitingProcesses.computeIfAbsent(resourceId, k -> new LinkedList<>()).add(processId);
        }
    }

    public Integer releaseResource(int resourceId) {
        Queue<Integer> queue = waitingProcesses.get(resourceId);
        if (queue != null && !queue.isEmpty()) {
            Integer nextProcess = queue.poll();
            resourceAllocation.put(resourceId, nextProcess);
            return nextProcess;
        } else {
            resourceAllocation.put(resourceId, null);
            return null;
        }
    }

    public Integer getResourceHolder(int resourceId) {
        return resourceAllocation.get(resourceId);
    }

    public boolean isResourceFree(int resourceId) {
        return !resourceAllocation.containsKey(resourceId) || resourceAllocation.get(resourceId) == null;
    }
}
