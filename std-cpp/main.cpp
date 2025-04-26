#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;


struct DataRow {
    vector<string> conditions;
    vector<string> decisions;
};

struct TreeNode {
    string attribute;
    map<string, shared_ptr<TreeNode>> children;
    string decision;
};













double calculateEntropy(const vector<DataRow>& dataset, int targetIdx) 
{
    map<string, int> freq;
    for (const auto& row : dataset) {
        freq[row.decisions[targetIdx]]++;
    }

    double entropy = 0.0;
    for (const auto& pair : freq) {
        double prob = static_cast<double>(pair.second) / dataset.size();
        entropy -= prob * log2(prob);
    }
    return entropy;
}

double calculateInfoGain(const vector<DataRow>& dataset, int attrIdx, int targetIdx) 
{
    map<string, vector<DataRow>> subsets;
    for (const auto& row : dataset) {
        subsets[row.conditions[attrIdx]].push_back(row);
    }

    double subsetEntropy = 0.0;
    for (const auto& subset : subsets) {
        double weight = static_cast<double>(subset.second.size()) / dataset.size();
        subsetEntropy += weight * calculateEntropy(subset.second, targetIdx);
    }

    return calculateEntropy(dataset, targetIdx) - subsetEntropy;
}

int chooseBestAttribute(const vector<DataRow>& dataset, const vector<bool>& usedAttributes, int targetIdx) 
{
    double maxGain = -1;
    int bestAttr = -1;

    for (size_t i = 0; i < usedAttributes.size(); ++i) {
        if (!usedAttributes[i]) {
            double gain = calculateInfoGain(dataset, i, targetIdx);
            if (gain > maxGain) {
                maxGain = gain;
                bestAttr = i;
            }
        }
    }
    return bestAttr;
}

shared_ptr<TreeNode> buildDecisionTree(const vector<DataRow>& dataset,const vector<string>& attributes,vector<bool> usedAttributes,int targetIdx) 
{
    auto node = make_shared<TreeNode>();
    map<string, int> classCounts;
    for (const auto& row : dataset) {
        classCounts[row.decisions[targetIdx]]++;
    }

    if (classCounts.size() == 1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    int bestAttr = chooseBestAttribute(dataset, usedAttributes, targetIdx);
    if (bestAttr == -1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    node->attribute = attributes[bestAttr];
    vector<bool> newUsed = usedAttributes;
    newUsed[bestAttr] = true;

    map<string, vector<DataRow>> subsets;
    for (const auto& row : dataset) {
        subsets[row.conditions[bestAttr]].push_back(row);
    }

    for (const auto& subset : subsets) {
        if (subset.second.empty()) {
            auto leaf = make_shared<TreeNode>();
            leaf->decision = classCounts.begin()->first;
            node->children[subset.first] = leaf;
        }
        else {
            node->children[subset.first] = buildDecisionTree(subset.second, attributes, newUsed, targetIdx);
        }
    }

    return node;
}

string predict(const shared_ptr<TreeNode>& root, const DataRow& sample, const vector<string>& attributes) 
{
    if (!root->decision.empty()) {
        return root->decision;
    }

    auto it = find(attributes.begin(), attributes.end(), root->attribute);
    if (it == attributes.end()) {
        return "Unknown";
    }
    int attrIndex = distance(attributes.begin(), it);

    string attrValue = sample.conditions[attrIndex];

    if (root->children.find(attrValue) == root->children.end()) {
        return "Unknown";
    }

    return predict(root->children[attrValue], sample, attributes);
}














int main() {

    vector<DataRow> dataset = {
        {{"HOTPT","HATK","HDEF","HATK","HDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HMAG","HDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HATK","HDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HATK","HDEF"}, {"Decay","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HHRT","HDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HATK","HDEF","HATK","HDEF"}, {"Decay","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HMAG","HDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HATK","HDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HATK","HDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HATK","HDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HHRT","HDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HLIVE"}, {"about","HP","LIVE"}}
    };

    vector<string> attributes = {
        "LegendComment", "SelfOutputComment", "SelfLiveComment",
        "TargetOutputComment", "TargetLiveComment"
    };




    DataRow sample = {
        {"HOTPT","HATK","HDEF","HATK","HDEF"},
        {}
    };





    vector<shared_ptr<TreeNode>> trees;
    for (int target = 0; target < 3; ++target) {
        vector<bool> usedAttributes(5, false);
        trees.push_back(buildDecisionTree(dataset, attributes, usedAttributes, target));
    }

    cout << "输出装推荐: " << predict(trees[0], sample, attributes) << endl;
    cout << "防御装推荐: " << predict(trees[1], sample, attributes) << endl;
    cout << "装备推荐项: " << predict(trees[2], sample, attributes) << endl;

    return 0;


    
}

