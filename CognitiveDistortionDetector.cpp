// CognitiveDistortionHelper.cpp
// Program: Learn your thinking patterns using a Binary Tree
// Author: McKenna Makran
// Purpose: Allows users to log their feelings based on common cognitive distortions,
//          stores them in a Binary Search Tree, shows top 3 distortions, and provides advice


#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node { //create node structure/blueprint
    string distortion;
    int count; //how many times a distortion has been logged
    Node* left;
    Node* right;

    Node(string _distortion) {
        distortion = _distortion;
        count = 1;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;
    vector<Node*> collected; //dynamic list that will hold all distortions

    Node* insertNode(Node* node, string distortion) {
        if (node == nullptr) {
            return new Node(distortion); //base case
        }

        if (distortion < node->distortion) {
            node->left = insertNode(node->left, distortion);
        }
        else if (distortion > node->distortion) {
            node->right = insertNode(node->right, distortion);
        }
        else {
            node->count++; //if the same distortion is selcted again, count++
        }
        return node;
    }

    void inorderCollect(Node* node) {
        if (node == nullptr) return;
        inorderCollect(node->left); //recursive function to collect all nodes in order
        collected.push_back(node);
        inorderCollect(node->right);
    }

public:
    BinaryTree() {
        root = nullptr; //constructor
    }

    void insert(string distortion) {
        root = insertNode(root, distortion);
    }

    vector<Node*> getAllNodes() { //return all nodes in-order
        collected.clear();
        inorderCollect(root);
        return collected;
    }
};

string explain(string d) { //explanation for each distortion
    if (d == "Catastrophizing")
        return "Catastrophizing means you imagine the worst possible outcome even if it is unlikely.";
    if (d == "Mind Reading")
        return "Mind Reading means assuming you know what others think, without real evidence.";
    if (d == "All or Nothing Thinking")
        return "All or Nothing Thinking makes you see things as only success or failure, no in-between.";
    if (d == "Overgeneralization")
        return "Overgeneralization means turning a single event into a pattern or rule.";
    if (d == "Emotional Reasoning")
        return "Emotional Reasoning means believing that feelings are facts.";
    return "No explanation available.";
}

string advice(string d) { //advice based on #1 distortion
    if (d == "Catastrophizing")
        return "Try asking yourself: What is a more realistic outcome? What evidence supports my fear?";
    if (d == "Mind Reading")
        return "Try checking the facts: Is there proof? Consider asking directly instead of assuming.";
    if (d == "All or Nothing Thinking")
        return "Try finding the middle: What is a more balanced viewpoint between perfect and terrible?";
    if (d == "Overgeneralization")
        return "Try reminding yourself: One moment does not define all moments. Look for exceptions.";
    if (d == "Emotional Reasoning")
        return "Try separating feelings from facts. Both matter, but they are not the same.";
    return "Keep practicing awareness and grounding.";
}

void printSummary(BinaryTree& tree) { //summary
    vector<Node*> list = tree.getAllNodes();

    if (list.empty()) {
        cout << "\nNo distortions recorded yet.\n";
        return;
    }

    for (int i = 0; i < list.size(); i++) {
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j]->count > list[i]->count) {
                swap(list[i], list[j]);
            }
        }
    }

    cout << "\n-----------------------------------------------\n";
    cout << "SUMMARY: Your Top Thinking Patterns\n";
    cout << "-----------------------------------------------\n";

    int top = min(3, (int)list.size()); //top 3

    for (int i = 0; i < top; i++) {
        cout << i + 1 << ". " << list[i]->distortion
            << " (x" << list[i]->count << ")" << endl;
        cout << "   Meaning: " << explain(list[i]->distortion) << endl;
        cout << endl;
    }

    cout << "Personal Advice Based on Your Most Common Pattern:\n";
    cout << advice(list[0]->distortion) << endl;
}


int main() {
    BinaryTree tree;
    int choice = 0;

    vector<string> descriptions = {
        "I feel like everything will go horribly wrong.",
        "I keep thinking people secretly dislike me.",
        "If something is not perfect, it feels like a failure.",
        "One bad thing happened, so it feels like everything will always go wrong.",
        "I feel something strongly so I assume it must be true."
    };

    vector<string> keys = {
        "Catastrophizing",
        "Mind Reading",
        "All or Nothing Thinking",
        "Overgeneralization",
        "Emotional Reasoning"
    };

    cout << "Welcome to the Cognitive Distortion Helper!\n";

    do {
        cout << "\nChoose an option:\n";
        cout << "1 - Log how you are feeling today\n";
        cout << "2 - View your summary (Top 3 patterns)\n";
        cout << "3 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nWhich one sounds closest to your feelings today?\n\n";
            for (int i = 0; i < descriptions.size(); i++) {
                cout << i + 1 << ". " << descriptions[i] << endl;
            }
            cout << "\nChoose (1-5): ";
            int pick;
            cin >> pick;

            if (pick >= 1 && pick <= 5) {
                tree.insert(keys[pick - 1]);
                cout << "\nThank you. Logged.\n";
            }
            else {
                cout << "Invalid choice.\n";
            }
        }

        if (choice == 2) {
            printSummary(tree);
        }

    } while (choice != 3);

    cout << "\nGoodbye! Take care of yourself.\n";

    return 0;
}
