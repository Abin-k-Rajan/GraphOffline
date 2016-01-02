#pragma once

#include <string>
#include <vector>
#include "IGraph.h"
#include "YString.h"
#include <memory>



/**
 * Main Graph class.
 *
 */
template<class WeightInterface, typename WeightType> class Graph : public WeightInterface
{
public:
    
    struct Node;
    struct Edge;
    
    typedef std::shared_ptr<Edge> EdgePtr;
    
    // Node sturct
    struct Node
    {
        String id;
        IndexType privateId;
        
        Node(const String& id, IndexType privateId)
        {
            this->id = id;
            this->privateId = privateId;
        }
        std::vector<Node*> targets;
    };
    
    class NodePtr : public std::shared_ptr<Node>
    {
    public:
        NodePtr () : std::shared_ptr<Node>() {}
        NodePtr (Node* node) : std::shared_ptr<Node>(node) {}
        // Operator to compare pointers.
        bool operator == (const Graph::Node* node2) const
        {
            return std::shared_ptr<Node>::get() == node2;
        }
    };
    
    // Edge struct
    struct Edge
    {
        String id;
        NodePtr source;
        NodePtr target;
        bool  direct;
        WeightType weight;
        IndexType privateId;
        
        Edge(const String& id, NodePtr source, NodePtr target, bool direct, const WeightType& weight, IndexType privateId)
        {
            this->id = id;
            this->source = source;
            this->target = target;
            this->direct = direct;
            this->weight = weight;
            this->privateId = privateId;
        }
    };
    
    Graph(void);
    virtual ~Graph(void);
    
    // Load from GraphML format.
    bool LoadFromGraphML(const char * pBuffer, uint32_t bufferSize);
    
    // Clear Graph.
    void Clear();
    
    // IGraph
    // Get Nodes count.
    virtual IndexType GetNodesCount() const;
    // Get Edges count.
    virtual IndexType GetEdgesCount() const;
    // Get node of this graph.
    virtual ObjectId GetNode(IndexType index) const;
    // Get node of this graph.
    virtual ObjectId GetNode(const char* nodeId) const;
    // Get connected graph count.
    virtual IndexType GetConnectedNodes(ObjectId source) const;
    // Get connected graph for this graph.
    virtual ObjectId GetConnectedNode(ObjectId source, IndexType index) const;
    // Is edge exists.
    virtual bool AreNodesConnected(ObjectId source, ObjectId target) const;
    // Get Egde weight. TODO: float.
    virtual WeightType GetEdgeWeight(ObjectId source, ObjectId target) const;
    // Return graph string Id.
    virtual bool GetNodeStrId(ObjectId node, char* outBuffer, IndexType bufferSize) const;
    // Is edge exists in input graph.
    virtual bool IsEgdeExists(ObjectId source, ObjectId target) const;
    // Get weight real type
    virtual EdgeWeightType GetEdgeWeightType() const;
    // Create copy of graph.
    virtual WeightInterface* MakeCopy(GraphCopyType type);

    // Find Node by Id
    NodePtr FindNode(const String& id) const;
    
protected:
    
    // Find Node by id in vector.
    template <typename T> T FindNode(const String& id, const std::vector<T>& nodes)  const;
    template <typename T> T FindNode(ObjectId objectId, const std::vector<T>& nodes) const;
    
    // Find element in vector.
    template <typename T> bool Has(const std::vector<T>& vector, const T& value) const;
    template <typename T1, typename T2> bool Has(const std::vector<T1>& vector, const T2& value) const;
    
    // Is valid Object id.
    bool IsValidNodeId(ObjectId id, NodePtr& ptr) const;
    
    // Is edge exists.
    EdgePtr FindEdge(ObjectId source, ObjectId target) const;
    
    typedef std::vector<NodePtr> NodePtrVector;
    typedef std::vector<EdgePtr> EdgePtrVector;
    
    bool IsDouble(double value);
    
    IndexType GetNextId();
    
    // List of graph.
    NodePtrVector m_nodes;
    EdgePtrVector m_edges;
    
    EdgeWeightType m_weightType;
    IndexType      m_autoIncIndex;
};

typedef Graph<IGraphInt, IntWeightType> IntGraph;
typedef Graph<IGraphFloat, FloatWeightType> FloatGraph;

#include "GraphImpl.h"

