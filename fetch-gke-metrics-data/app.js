const express = require('express');
const axios = require('axios');
const app = express();
const PORT = 3000;

// GKE API configuration
const GKE_CLUSTER_ENDPOINT = 'https://SOME URL OR IP'; // Replace with your actual cluster endpoint
const NAMESPACE = 'default'; // Change to your specific namespace
const ACCESS_TOKEN = 'gcloud auth print-access-token'; // Replace with your actual access token

app.get('/metrics', async (req, res) => {
    try {
        // Fetch node information to get number of nodes and their names
        const nodesResponse = await axios.get(`${GKE_CLUSTER_ENDPOINT}/api/v1/nodes`, {
            headers: {
                'Authorization': `Bearer ${ACCESS_TOKEN}`,
            },
            httpsAgent: new (require('https').Agent)({
                rejectUnauthorized: false // Disable certificate verification for testing
            })
        });

        const nodeItems = nodesResponse.data.items;
        const numberOfNodes = nodeItems.length;
        const nodeNames = nodeItems.map(node => node.metadata.name).join(", ");

        // Fetch cluster name
        const clusterInfoResponse = await axios.get(`${GKE_CLUSTER_ENDPOINT}/api/v1/namespaces/default/configmaps/clusterinfo`, {
            headers: {
                'Authorization': `Bearer ${ACCESS_TOKEN}`,
            },
            httpsAgent: new (require('https').Agent)({
                rejectUnauthorized: false // Disable certificate verification for testing
            })
        });
        // console.log("clusterinfo", clusterInfoResponse);
        const clusterName = clusterInfoResponse.data.data.cluster_name || "Unknown Cluster"; // Change according to your needs
        // Fetch node metrics
        const nodeMetricsResponse = await axios.get(`${GKE_CLUSTER_ENDPOINT}/apis/metrics.k8s.io/v1beta1/nodes`, {
            headers: {
                'Authorization': `Bearer ${ACCESS_TOKEN}`,
            },
            httpsAgent: new (require('https').Agent)({
                rejectUnauthorized: false // Disable certificate verification for testing
            })
        });
        console.log("NodeData: ", nodeMetricsResponse.data);
        const nodeMetrics = nodeMetricsResponse.data.items;

        // Calculate average CPU and memory usage from nodes
        let totalCpuUsage = 0;
        let totalMemoryUsage = 0;
        nodeMetrics.forEach(node => {
            /*
                write your own logic here to do the math stuff.
            */
        });

        // Sample values for CPU and Memory Usage (average)
        const avgCpuUsage = Math.round(totalCpuUsage / 4); // Average CPU usage, I knew the values anyways so
        const avgMemoryUsage = Math.round(totalMemoryUsage / 80); // Average Memory usage

        // Fetch pod metrics
        const podMetricsResponse = await axios.get(`${GKE_CLUSTER_ENDPOINT}/apis/metrics.k8s.io/v1beta1/namespaces/${NAMESPACE}/pods`, {
            headers: {
                'Authorization': `Bearer ${ACCESS_TOKEN}`,
            },
            httpsAgent: new (require('https').Agent)({
                rejectUnauthorized: false // Disable certificate verification for testing
            })
        });
        // console.log("PodData: ", podMetricsResponse.data);
        const podMetrics = podMetricsResponse.data.items;
        const numberOfPods = podMetrics.length;

        // Determine status based on usage
        let status;
        if (avgCpuUsage > 85000000 || avgMemoryUsage > 75) { // Example thresholds
            status = 'Danger';
        } else if (avgCpuUsage > 75000000 || avgMemoryUsage > 75) {
            status = 'Warning';
        } else {
            status = 'OK';
        }

        // Construct the final response
        const finalResponse = {
            numberOfNodes: numberOfNodes,
            clusterName: clusterName,
            nodeNames: nodeNames,
            numberOfPods: numberOfPods,
            cpuUsage: Math.round(avgCpuUsage / 1000000), // Convert from nanocores to cores
            memoryUsage: avgMemoryUsage, // In MB
            status: status // OK/Warning/Danger
        };

        res.json(finalResponse);

    } catch (error) {
        console.error("Error fetching metrics:", error);
        res.status(500).json({ message: "Error fetching metrics", error: error.message });
    }
});
// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
