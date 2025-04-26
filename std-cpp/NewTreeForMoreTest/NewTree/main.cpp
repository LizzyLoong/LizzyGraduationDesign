#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <memory>   //����ָ��
#include <string>
#include <random>
#include <iomanip>
#include <numeric>

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
shared_ptr<TreeNode> buildDecisionTree(const vector<DataRow>& dataset,const vector<string>& attributes,vector<bool> usedAttributes,int targetIdx) 
{
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
        for (int i = 0; i < 1; ++i) {
            getline(ss, cell, ',');
            row.decisions.push_back(cell);
        }

        dataset.push_back(row);
    }
    return dataset;
}



void splitDataset(const string& inputFile, int row,
    const string& outputTrainFile,
    const string& outputTestFile) {
    // ��ȡ�����У��������⣩
    vector<string> allLines;
    ifstream inFile(inputFile);
    string line;

    // ��ȡ������
    getline(inFile, line);
    allLines.push_back(line);

    // ��ȡ������
    while (getline(inFile, line)) {
        if (!line.empty()) { // ��������
            allLines.push_back(line);
        }
    }
    inFile.close();

    // ����ʵ�ʿ��õ���������
    int totalDataRows = allLines.size() - 1;
    if (row <= 0 || row > totalDataRows) {
        cerr << "Invalid row number: " << row << endl;
        return;
    }

    // ������������������������У�
    random_device rd;
    mt19937 gen(rd());
    set<int> selectedIndices;
    while (selectedIndices.size() < row) {
        uniform_int_distribution<> dis(1, totalDataRows); // �����д�1��ʼ
        selectedIndices.insert(dis(gen));
    }

    // д������ļ�
    ofstream testFile(outputTestFile);
    testFile << allLines[0] << endl; // д�����
    for (int idx : selectedIndices) {
        testFile << allLines[idx] << endl;
    }
    testFile.close();

    // д���µ�ѵ���ļ�������δѡ�е��У�
    ofstream trainFile(outputTrainFile);
    trainFile << allLines[0] << endl; // д�����

    // д��ʣ��������
    for (int i = 1; i < allLines.size(); ++i) {
        if (selectedIndices.find(i) == selectedIndices.end()) {
            trainFile << allLines[i] << endl;
        }
    }
    trainFile.close();
}

// ����������
void splitDataset(const string& inputFile, int row, const string& outputTestFile) {
    // ��ȡ�����У��������⣩
    vector<string> allLines;
    ifstream inFile(inputFile);
    string line;

    // ��ȡ������
    getline(inFile, line);
    allLines.push_back(line);

    // ��ȡ������
    while (getline(inFile, line)) {
        if (!line.empty()) { // ��������
            allLines.push_back(line);
        }
    }
    inFile.close();

    // ����ʵ�ʿ��õ���������
    int totalDataRows = allLines.size() - 1;
    if (row <= 0 || row > totalDataRows) {
        cerr << "Invalid row number: " << row << endl;
        return;
    }

    // ������������������������У�
    random_device rd;
    mt19937 gen(rd());
    set<int> selectedIndices;
    while (selectedIndices.size() < row) {
        uniform_int_distribution<> dis(1, totalDataRows); // �����д�1��ʼ
        selectedIndices.insert(dis(gen));
    }

    // д������ļ�
    ofstream testFile(outputTestFile);
    testFile << allLines[0] << endl; // д�����
    for (int idx : selectedIndices) {
        testFile << allLines[idx] << endl;
    }
    testFile.close();

    // ��ԭʼ�������Ƴ�ѡ�е��У���������
    vector<string> remainingLines;
    remainingLines.push_back(allLines[0]); // ��������
    for (int i = 1; i < allLines.size(); ++i) {
        if (selectedIndices.find(i) == selectedIndices.end()) {
            remainingLines.push_back(allLines[i]);
        }
    }

    // д��ԭʼ�ļ�
    ofstream outTrainFile(inputFile, ios::trunc);
    for (size_t i = 0; i < remainingLines.size(); ++i) {
        outTrainFile << remainingLines[i];
        // �������һ�г��ֿ���
        if (i != remainingLines.size() - 1) outTrainFile << endl;
    }
    outTrainFile.close();
}

// ������������Ԥ����д������ļ�
void writePredictionsToCSV(const string& filename,
    const shared_ptr<TreeNode>& tree,
    const vector<string>& attributes) {
    // ��ȡ�����ļ�������
    vector<string> lines;
    ifstream inFile(filename);
    string header;

    // ��ȡ�����в��������
    getline(inFile, header);
    header += ",Ԥ����";  // ��ӵ�7�б���
    lines.push_back(header);

    // ����������
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // ����ԭʼ����
        DataRow row;
        stringstream ss(line);
        string cell;

        // ��ȡ��������
        for (int i = 0; i < 5; ++i) {
            getline(ss, cell, ',');
            row.conditions.push_back(cell);
        }

        // ��ȡԭ�������ԣ����޸ģ�
        getline(ss, cell, ',');
        row.decisions.push_back(cell);

        // ����Ԥ��
        string prediction = predict(tree, row, attributes);

        // ��������
        string newLine = line + "," + prediction;
        lines.push_back(newLine);
    }
    inFile.close();

    // д���ļ�
    ofstream outFile(filename, ios::trunc);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
}

// ��������������ģ��׼ȷ��
double calculateAccuracy(const vector<DataRow>& testSet, const shared_ptr<TreeNode>& tree,
    const vector<string>& attributes, int targetIdx) {
    if (testSet.empty()) return 0.0;

    int correctCount = 0;
    for (const auto& sample : testSet) {
        string predicted = predict(tree, sample, attributes);
        string actual = sample.decisions[targetIdx];

        if (predicted == actual) {
            correctCount++;
        }
    }
    return static_cast<double>(correctCount) / testSet.size() * 100.0;
}



int main() 
{

    // ���ò���
    const int TOTAL_ROWS = 162;   // ����ʵ���������޸�
    const int TEST_TIMES = 5;     // ÿ��row���Դ���
    const string ORIGINAL_FILE = "train.csv";
    vector<string> attributes = { "Ӣ������ƫ��", "�����������", "������������", "�з��������", "�з���������" };
    vector<bool> usedAttributes(5, false);
    // ��������ļ�
    ofstream resultFile("test_results.csv");
    resultFile << "row,x,test1,test2,test3,test4,test5,average\n";

    // ������ѭ��
    for (int row = 0; row <= TOTAL_ROWS; ++row) {
        // ������Чֵ
        if (row < 0 || row > TOTAL_ROWS) continue;

        // ����xֵ
        double x = 100.0 * (TOTAL_ROWS - row) / TOTAL_ROWS;

        vector<double> accuracies;
        for (int test = 0; test < TEST_TIMES; ++test) {
            // �ָ����ݼ�
            splitDataset(ORIGINAL_FILE, row, "train_over.csv", "test_over.csv");

            // ����ѵ������
            auto trainData = loadCSV("train_over.csv");
            if (trainData.empty()) {
                accuracies.push_back(0.0);
                continue;
            }

            // ����������
            auto tree = buildDecisionTree(trainData, attributes, usedAttributes, 0);

            // ���ز�������
            auto testData = loadCSV("test_over.csv");

            // ����׼ȷ��
            double accuracy = calculateAccuracy(testData, tree, attributes, 0);
            accuracies.push_back(accuracy);
        }

        // ����ƽ��ֵ
        double sum = accumulate(accuracies.begin(), accuracies.end(), 0.0);
        double average = sum / TEST_TIMES;

        // д����
        resultFile << row << ","
            << fixed << setprecision(2) << x << ","
            << accuracies[0] << "," << accuracies[1] << ","
            << accuracies[2] << "," << accuracies[3] << ","
            << accuracies[4] << "," << average << "\n";

        // �������
        cout << "Progress: " << row << "/" << TOTAL_ROWS
            << " (" << (row * 100.0 / TOTAL_ROWS) << "%)\n";
    }

    resultFile.close();
    cout << "\n�Զ���������ɣ�����ѱ����� test_results.csv\n";
    return 0;

















    // runAutomatedTests();













   /*
    splitDataset("train.csv", 150, "train_over.csv", "test_over.csv");
    vector<string> attributes = 
    {
        "Ӣ������ƫ��", "�����������", "������������",
        "�з��������", "�з���������"
    };
    vector<bool> usedAttributes(5, false);

    auto trainDataset = loadCSV("train_over.csv");
    shared_ptr<TreeNode> tree = buildDecisionTree(trainDataset, attributes, usedAttributes, 0);


    auto testDataset = loadCSV("test_over.csv");

    double accuracy = calculateAccuracy(testDataset, tree, attributes, 0);

    // cout << fixed << setprecision(2);

    cout << "ģ��׼ȷ��: " << accuracy << "%" << endl;

    // ��Ԥ����д���ļ�
    writePredictionsToCSV("test_over.csv", tree, attributes);
    */


     // StatisticalTableOfDifferentConfidenceLevels.csv





    
}