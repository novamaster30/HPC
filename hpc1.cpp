//BFS

#include <iostream>
#include <queue>
#include <omp.h>  // added
using namespace std;
struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};
Node* insert(Node* root, int data) {
    if (!root) return new Node(data);
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front(); q.pop();
        if (!temp->left) return temp->left = new Node(data), root;
        else q.push(temp->left);
        if (!temp->right) return temp->right = new Node(data), root;
        else q.push(temp->right);
    }
    return root;
}
void bfs(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            Node* temp;
            #pragma omp critical
            {
                if (!q.empty()) {
                    temp = q.front(); q.pop();
                    cout << temp->data << " ";
                }
            }
            #pragma omp critical
            {
                if (temp) {
                    if (temp->left) q.push(temp->left);
                    if (temp->right) q.push(temp->right);
                }
            }
        }
    }
}
int main() {
    Node* root = NULL;
    int data; char ans;
    do {
        cout << "Enter data => "; cin >> data;
        root = insert(root, data);
        cout << "Do you want to insert one more node? (y/n): "; cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    cout << "Breadth-First Search (BFS) of the tree: ";
    bfs(root);
    return 0;
}

//DFS

#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;
vector<int> graph[100];
bool visited[100];
void dfs(int start) {
    stack<int> s; s.push(start);
    while (!s.empty()) {
        int u;
        #pragma omp critical
        { u = s.top(); s.pop(); }
        if (visited[u]) continue;
        visited[u] = true;
        for (int i = graph[u].size() - 1; i >= 0; i--) {
            int v = graph[u][i];
            if (!visited[v])
                #pragma omp critical
                s.push(v);
        }
    }
}
int main() {
    int n, m, start;
    cout << "Enter number of nodes, edges and starting node: " << flush;
    cin >> n >> m >> start;
    cout << "Enter " << m << " edges (u v):" << endl;
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(start);
    cout << "\nNodes visited in DFS order starting from " << start << ":\n";
    for (int i = 0; i < n; i++)
        if (visited[i]) cout << i << " ";
    cout << endl;
}