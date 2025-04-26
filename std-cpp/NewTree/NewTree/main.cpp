#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <memory>   //����ָ��

using namespace std;

// ���ݽṹ����
struct DataRow {
    vector<string> conditions;
    vector<string> decisions;
};

struct TreeNode {
    string attribute;
    map<string, shared_ptr<TreeNode>> children;
    string decision;
};

// ������
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

// ������Ϣ����
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

// ѡ����ѷ�������
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

// ID3�㷨������
shared_ptr<TreeNode> buildDecisionTree(const vector<DataRow>& dataset,
    const vector<string>& attributes,
    vector<bool> usedAttributes,
    int targetIdx) {
    auto node = make_shared<TreeNode>();

    // ����Ƿ�������������ͬһ���
    map<string, int> classCounts;
    for (const auto& row : dataset) {
        classCounts[row.decisions[targetIdx]]++;
    }

    if (classCounts.size() == 1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    // ѡ����ѷ�������
    int bestAttr = chooseBestAttribute(dataset, usedAttributes, targetIdx);
    if (bestAttr == -1) {
        node->decision = classCounts.begin()->first;
        return node;
    }

    node->attribute = attributes[bestAttr];
    vector<bool> newUsed = usedAttributes;
    newUsed[bestAttr] = true;

    // ��������
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

// Ԥ�⺯��
string predict(const shared_ptr<TreeNode>& root, const DataRow& sample, const vector<string>& attributes) {
    if (!root->decision.empty()) {
        return root->decision;
    }

    // ���������������е�����λ��
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

// CSV��������
vector<DataRow> loadCSV(const string& filename) {
    vector<DataRow> dataset;
    ifstream file(filename);
    string line;

    // ����������
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        DataRow row;

        // ��ȡǰ5����������
        for (int i = 0; i < 5; ++i) {
            getline(ss, cell, ',');
            row.conditions.push_back(cell);
        }

        // ��ȡ��3����������
        for (int i = 0; i < 3; ++i) {
            getline(ss, cell, ',');
            row.decisions.push_back(cell);
        }

        dataset.push_back(row);
    }
    return dataset;
}





int main() {
    // ��������
    auto dataset = loadCSV("train.csv");
    vector<string> attributes = {
        "Ӣ������ƫ��", "�����������", "������������",
        "�з��������", "�з���������"
    };

    // Ϊÿ������Ŀ�깹��������
    vector<shared_ptr<TreeNode>> trees;
    for (int target = 0; target < 3; ++target) {
        vector<bool> usedAttributes(5, false);
        trees.push_back(buildDecisionTree(dataset, attributes, usedAttributes, target));
    }

    // ʾ��Ԥ��
    DataRow sample = {
        {"���", "��ʵ�˺�", "����ƫ��", "�����˺�", "����ƫ��"},
        {}
    };

    cout << "���װ�Ƽ�: " << predict(trees[0], sample, attributes) << endl;
    cout << "����װ�Ƽ�: " << predict(trees[1], sample, attributes) << endl;
    cout << "װ���Ƽ���: " << predict(trees[2], sample, attributes) << endl;

    return 0;
}