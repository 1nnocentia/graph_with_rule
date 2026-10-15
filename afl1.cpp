#include <bits/stdc++.h>
using namespace std;

using Graph = map<string, vector<string>>;

class Node {
    public:
        string state;
        Node* parent;
        
        Node(string state, Node* parent){
            this->state = state;
            this->parent = parent;
        }
};

class StackFrontier {
    protected:
        vector<Node*> frontier;
    public:
        void add(Node* node) {
            frontier.push_back(node);
        }
    bool contains_state(string search_state){
        for(Node* node : frontier){
            if (node->state == search_state) return true;
        }
        return false;
    }
    bool empty(){
        return frontier.empty();
    }
    virtual Node* remove(){
        if(empty()){
            throw runtime_error("frontier empty");
        }
        Node* node = frontier.back();
        frontier.pop_back();
        return node;
    }
};

class QueueFrontier : public StackFrontier {
    public:
        Node* remove() override {
            if (empty()){
                throw runtime_error("frontier kosong");
            }
            Node* node = frontier.front();
            frontier.erase(frontier.begin());
            return node;
        }
};


void print_path(Node* target_node){
    vector<string> path;
    Node* current = target_node;
    while(current != nullptr){
        path.push_back(current->state);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    
    cout << "Path: ";
    for(size_t i = 0; i < path.size(); ++i){
        cout << path[i] << (i == path.size() - 1 ? "" : "-> ");
    }
    cout << endl;
}

void graph_search(string start, string target, Graph& graph, StackFrontier& frontier){
    Node* start_node = new Node(start, nullptr);
    frontier.add(start_node);
    
    set<string> explored;
    
    cout << "Start searching from " << start << " to " << target << endl;
    
    while(!frontier.empty()){
        Node* curr_node = frontier.remove();
        string curr_state = curr_node->state;
        
        cout << "Visiting node: " << curr_state << endl;
        
        if(curr_state == target) {
            cout << "Target found!" << endl;
            print_path(curr_node);
            return;
        }
        explored.insert(curr_state);
        if(graph.find(curr_state) != graph.end()){
            vector<string> neighbour = graph[curr_state];
            sort(neighbour.begin(), neighbour.end());
            
            if(dynamic_cast<QueueFrontier*>(&frontier) == nullptr){
                reverse(neighbour.begin(), neighbour.end());
            }
            
            for(string& n : neighbour){
                if(explored.find(n) == explored.end() && !frontier.contains_state(n)){
                    Node* child_node = new Node(n, curr_node);
                    frontier.add(child_node);
                }
            }
        }
    }
    cout << "Target not found" << endl;
}


int main() {
    Graph peta = {
        {"Home", {"MesjidRaya", "Lamuru"}},
        {"MesjidRaya", {"UripSumoharjo", "Bawakaraeng"}},
        {"Lamuru", {"Tinumbu", "BandangXIV", "BandangXV"}},
        {"Tinumbu", {"Bandang", "TinumbuII"}},
        {"BandangXIV", {"Bandang"}},
        {"TinumbuII", {"Andalas"}},ve
        {"Bandang", {"TinumbuII", "RappoRappo", "VeteranUtara", "MesjidRaya"}},
        {"Andalas", {"Laiya", "Lamputang", "MesjidRaya", "Latimojong"}},
        {"VeteranUtara", {"Bawakaraeng", "Nico", "BuluDua", "Salahutu"}},
        {"Latimojong", {"Limboto", "GunungNona", "Bawakaraeng"}},
        {"BuluDua", {"Latimojong"}},
        {"Salahutu", {"Latimojong"}},
        {"Bawakaraeng", {"RAKartini", "JendralSudirman"}},
        {"Limboto", {"GunungMerapi"}},
        {"GunungNona", {"GunungMerapi"}},
        {"RAKartini", {"Kajolalido"}},
        {"JendralSudirman", {"InceNurdin", "ChairilAnwar", "EmmySaelan", "Karunrung", "HjBau"}},
        {"GunungMerapi", {"Karunrung", "Klabat", "SungaiLariang"}},
        {"Kajolalido",{"Botolempangan", "UsmanJafar"}},
        {"Botolempangan", {"AriefRate", "SultanHasanuddin"}},
        {"InceNurdin", {"Botolempangan"}},
        {"ChairilAnwar", {"Botolempangan"}},
        {"Klabat", {"JendralSudirman"}},
        {"SungaiLariang", {"JendralSudirman"}},
        // {"JendralSudirman", {"EmmySaelan", "Karunrung", "HjBau"}},
        {"HjBau", {"AriefRate", "Rajawali", "SombaOpu", "MetroTjBunga"}},
        {"Karunrung", {"SultanHasanuddin", "AriefRate"}},
        {"SultanHasanuddin", {"Lamadukelleng"}},
        {"Lamadukelleng", {"YosepLatumahina", "HjBau"}},
        {"MetroTjBunga",{"JembatanPhinisi", "JembatanCPI"}},
        {"AriefRate", {"HjBau"}},
        {"JembatanPhinisi", {"BusinessPark", "CenterPointCafe", "SunsetQuayB"}},
        {"BusinessPark", {"CiputraUniversity", "SunsetQuayA", "Delft"}},
        {"CenterPointCafe", {"SunsetQuayA","SunsetQuayB", "Delft", "CiputraUniversity"}},
    };
    
    string start, target;
    
	QueueFrontier bfs_frontier;
	StackFrontier dfs_frontier;
	
	cout << "Starting Place: "; cin >> start;
	cout << "Target Place: "; cin >> target;
	cout << "BFS" << endl;
	graph_search(start, target, peta, bfs_frontier);
	cout << endl;
	cout << "DFS" << endl;
	graph_search(start, target, peta, dfs_frontier);
	return 0;
}
