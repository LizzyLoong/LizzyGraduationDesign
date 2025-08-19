#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <memory>   //智能指针

using namespace std;

// 数据结构定义
struct DataRow {
    vector<string> conditions;
    vector<string> decisions;
};

struct TreeNode {
    string attribute;
    map<string, shared_ptr<TreeNode>> children;
    string decision;
};

// 计算熵
double calculateEntropy(const vector<DataRow>& dataset, int targetIdx) {
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

// 计算信息增益
double calculateInfoGain(const vector<DataRow>& dataset, int attrIdx, int targetIdx) {
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

// 选择最佳分裂属性
int chooseBestAttribute(const vector<DataRow>& dataset, const vector<bool>& usedAttributes, int targetIdx) {
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

// ID3算法主函数
shared_ptr<TreeNode> buildDecisionTree(const vector<DataRow>& dataset,
    const vector<string>& attributes,
    vector<bool> usedAttributes,
    int targetIdx) {
    auto node = make_shared<TreeNode>();

    // 检查是否所有样本属于同一类别
    map<string, int> classCounts;
    for (const auto& row : dataset) {
        classCounts[row.decisions[targetIdx]]++;
    }

    if (classCounts.size() == 1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    // 选择最佳分裂属性
    int bestAttr = chooseBestAttribute(dataset, usedAttributes, targetIdx);
    if (bestAttr == -1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    node->attribute = attributes[bestAttr];
    vector<bool> newUsed = usedAttributes;
    newUsed[bestAttr] = true;

    // 创建子树
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

// 预测函数
string predict(const shared_ptr<TreeNode>& root, const DataRow& sample, const vector<string>& attributes) {
    if (!root->decision.empty()) {
        return root->decision;
    }

    // 查找属性在条件中的索引位置
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

// CSV解析函数
vector<DataRow> loadCSV(const string& filename) {
    vector<DataRow> dataset;
    ifstream file(filename);
    string line;

    // 跳过标题行
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        DataRow row;

        // 读取前5个条件属性
        for (int i = 0; i < 5; ++i) {
            getline(ss, cell, ',');
            row.conditions.push_back(cell);
        }

        // 读取后3个决策属性
        for (int i = 0; i < 3; ++i) {
            getline(ss, cell, ',');
            row.decisions.push_back(cell);
        }

        dataset.push_back(row);
    }
    return dataset;
}





int main() {
    // 加载数据
    auto dataset = loadCSV("train.csv");
    vector<string> attributes = {
        "英雄自身偏向", "本方输出属性", "本方防御属性",
        "敌方输出属性", "敌方防御属性"
    };

    // 为每个决策目标构建决策树
    vector<shared_ptr<TreeNode>> trees;
    for (int target = 0; target < 3; ++target) {
        vector<bool> usedAttributes(5, false);
        trees.push_back(buildDecisionTree(dataset, attributes, usedAttributes, target));
    }

    // 示例预测
    DataRow sample = {
        {"输出", "真实伤害", "护甲偏高", "物理伤害", "护甲偏高"},
        {}
    };

    cout << "输出装推荐: " << predict(trees[0], sample, attributes) << endl;
    cout << "防御装推荐: " << predict(trees[1], sample, attributes) << endl;
    cout << "装备推荐项: " << predict(trees[2], sample, attributes) << endl;

    return 0;
}