#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        int cameras = 0;
        if (dfs(root, cameras) == 0) {
            cameras++; 
        }
        return cameras;
    }

private:
    int dfs(TreeNode* node, int& cameras) {
        if (!node) return 2; 
        
        int left = dfs(node->left, cameras);
        int right = dfs(node->right, cameras);
        
        if (left == 0 || right == 0) {
            cameras++;
            return 1; 
        }
        
        if (left == 1 || right == 1) {
            return 2;
        }
        
        return 0;
    }
};

int main() {
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(0);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(0);
    root->right = new TreeNode(0);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(0);
    root->right->right->right = new TreeNode(0);
    
    
    Solution solution;
    cout << "Minimum number of cameras needed: " << solution.minCameraCover(root) << endl;
    
    return 0;
}
