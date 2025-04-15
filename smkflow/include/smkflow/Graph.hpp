#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <imgui.h>

inline ImVec2 operator+(const ImVec2& a, const ImVec2& b) {
    return ImVec2(a.x + b.x, a.y + b.y);
}

inline ImVec2 operator-(const ImVec2& a, const ImVec2& b) {
    return ImVec2(a.x - b.x, a.y - b.y);
}

inline ImVec2 operator*(const ImVec2& a, float b) {
    return ImVec2(a.x * b, a.y * b);
}

inline ImVec2 ImBezierCubicCalc(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, float t) {
    float u = 1.0f - t;
    float w1 = u * u * u;
    float w2 = 3 * u * u * t;
    float w3 = 3 * u * t * t;
    float w4 = t * t * t;
    return ImVec2(
        w1 * p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x,
        w1 * p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y
    );
}

namespace smkflow {

    struct Connection {
        std::string fromNodeId;
        int fromSlot;
        std::string toNodeId;
        int toSlot;
    };

    class Node {
    public:
        std::string name;
        std::vector<Node*> outputs;
        std::vector<Node*> inputs;
        ImVec2 position = ImVec2(100, 100);
        ImVec2 windowPos;
        ImVec2 windowSize;

        Node(const std::string& name) : name(name) {}

        void ConnectTo(Node* other) {
            outputs.push_back(other);
            other->inputs.push_back(this);
        }
    };

    class Graph {
        public:
            Node* AddNode(const std::string& name);
            void addConnection(const Connection& conn);
            void removeConnection(const std::string& fromNodeId, const std::string& toNodeId);
            void removeConnectionForTarget(const std::string& toNodeId);
            void removeConnectionForTargetSlot(const std::string& toNodeId, int toSlot);
            void removeNode(const std::string& nodeId);
            void recursiveInvalidate(const std::string& nodeId, Node* node, std::unordered_set<Node*>& visited);
            void Show();
            // inline ImVec2 GetInputSlotPos(const smkflow::Node& node, int index) {
            //     return node.windowPos + ImVec2(0, 25 + index * 12);
            // }
            // inline ImVec2 GetOutputSlotPos(const smkflow::Node& node, int index) {
            //     return node.windowPos + ImVec2(node.windowSize.x, 25 + index * 12);
            // }
        
            bool layoutInitialized = false;
            std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
            std::vector<Connection> connections;
            std::optional<std::pair<std::string, std::string>> selectedConnection;

        };    

    void Theme_Default();

}
