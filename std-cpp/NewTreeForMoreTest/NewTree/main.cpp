#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <memory>   //智能指针
#include <string>
#include <random>
#include <iomanip>
#include <numeric>

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
shared_ptr<TreeNode> buildDecisionTree(const vector<DataRow>& dataset,const vector<string>& attributes,vector<bool> usedAttributes,int targetIdx) 
{
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
    // 读取所有行（包括标题）
    vector<string> allLines;
    ifstream inFile(inputFile);
    string line;

    // 读取标题行
    getline(inFile, line);
    allLines.push_back(line);

    // 读取数据行
    while (getline(inFile, line)) {
        if (!line.empty()) { // 跳过空行
            allLines.push_back(line);
        }
    }
    inFile.close();

    // 计算实际可用的数据行数
    int totalDataRows = allLines.size() - 1;
    if (row <= 0 || row > totalDataRows) {
        cerr << "Invalid row number: " << row << endl;
        return;
    }

    // 生成随机索引（不包括标题行）
    random_device rd;
    mt19937 gen(rd());
    set<int> selectedIndices;
    while (selectedIndices.size() < row) {
        uniform_int_distribution<> dis(1, totalDataRows); // 数据行从1开始
        selectedIndices.insert(dis(gen));
    }

    // 写入测试文件
    ofstream testFile(outputTestFile);
    testFile << allLines[0] << endl; // 写入标题
    for (int idx : selectedIndices) {
        testFile << allLines[idx] << endl;
    }
    testFile.close();

    // 写入新的训练文件（保留未选中的行）
    ofstream trainFile(outputTrainFile);
    trainFile << allLines[0] << endl; // 写入标题

    // 写入剩余数据行
    for (int i = 1; i < allLines.size(); ++i) {
        if (selectedIndices.find(i) == selectedIndices.end()) {
            trainFile << allLines[i] << endl;
        }
    }
    trainFile.close();
}

// 函数已弃用
void splitDataset(const string& inputFile, int row, const string& outputTestFile) {
    // 读取所有行（包括标题）
    vector<string> allLines;
    ifstream inFile(inputFile);
    string line;

    // 读取标题行
    getline(inFile, line);
    allLines.push_back(line);

    // 读取数据行
    while (getline(inFile, line)) {
        if (!line.empty()) { // 跳过空行
            allLines.push_back(line);
        }
    }
    inFile.close();

    // 计算实际可用的数据行数
    int totalDataRows = allLines.size() - 1;
    if (row <= 0 || row > totalDataRows) {
        cerr << "Invalid row number: " << row << endl;
        return;
    }

    // 生成随机索引（不包括标题行）
    random_device rd;
    mt19937 gen(rd());
    set<int> selectedIndices;
    while (selectedIndices.size() < row) {
        uniform_int_distribution<> dis(1, totalDataRows); // 数据行从1开始
        selectedIndices.insert(dis(gen));
    }

    // 写入测试文件
    ofstream testFile(outputTestFile);
    testFile << allLines[0] << endl; // 写入标题
    for (int idx : selectedIndices) {
        testFile << allLines[idx] << endl;
    }
    testFile.close();

    // 从原始数据中移除选中的行（按降序处理）
    vector<string> remainingLines;
    remainingLines.push_back(allLines[0]); // 保留标题
    for (int i = 1; i < allLines.size(); ++i) {
        if (selectedIndices.find(i) == selectedIndices.end()) {
            remainingLines.push_back(allLines[i]);
        }
    }

    // 写回原始文件
    ofstream outTrainFile(inputFile, ios::trunc);
    for (size_t i = 0; i < remainingLines.size(); ++i) {
        outTrainFile << remainingLines[i];
        // 避免最后一行出现空行
        if (i != remainingLines.size() - 1) outTrainFile << endl;
    }
    outTrainFile.close();
}

// 新增函数：将预测结果写入测试文件
void writePredictionsToCSV(const string& filename,
    const shared_ptr<TreeNode>& tree,
    const vector<string>& attributes) {
    // 读取测试文件所有行
    vector<string> lines;
    ifstream inFile(filename);
    string header;

    // 读取标题行并添加新列
    getline(inFile, header);
    header += ",预测结果";  // 添加第7列标题
    lines.push_back(header);

    // 处理数据行
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // 解析原始数据
        DataRow row;
        stringstream ss(line);
        string cell;

        // 读取条件属性
        for (int i = 0; i < 5; ++i) {
            getline(ss, cell, ',');
            row.conditions.push_back(cell);
        }

        // 读取原决策属性（不修改）
        getline(ss, cell, ',');
        row.decisions.push_back(cell);

        // 进行预测
        string prediction = predict(tree, row, attributes);

        // 构建新行
        string newLine = line + "," + prediction;
        lines.push_back(newLine);
    }
    inFile.close();

    // 写回文件
    ofstream outFile(filename, ios::trunc);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
}

// 新增函数：计算模型准确率
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

    // 配置参数
    const int TOTAL_ROWS = 162;   // 根据实际数据量修改
    const int TEST_TIMES = 5;     // 每个row测试次数
    const string ORIGINAL_FILE = "train.csv";
    vector<string> attributes = { "英雄自身偏向", "本方输出属性", "本方防御属性", "敌方输出属性", "敌方防御属性" };
    vector<bool> usedAttributes(5, false);
    // 创建结果文件
    ofstream resultFile("test_results.csv");
    resultFile << "row,x,test1,test2,test3,test4,test5,average\n";

    // 主测试循环
    for (int row = 0; row <= TOTAL_ROWS; ++row) {
        // 跳过无效值
        if (row < 0 || row > TOTAL_ROWS) continue;

        // 计算x值
        double x = 100.0 * (TOTAL_ROWS - row) / TOTAL_ROWS;

        vector<double> accuracies;
        for (int test = 0; test < TEST_TIMES; ++test) {
            // 分割数据集
            splitDataset(ORIGINAL_FILE, row, "train_over.csv", "test_over.csv");

            // 加载训练数据
            auto trainData = loadCSV("train_over.csv");
            if (trainData.empty()) {
                accuracies.push_back(0.0);
                continue;
            }

            // 构建决策树
            auto tree = buildDecisionTree(trainData, attributes, usedAttributes, 0);

            // 加载测试数据
            auto testData = loadCSV("test_over.csv");

            // 计算准确率
            double accuracy = calculateAccuracy(testData, tree, attributes, 0);
            accuracies.push_back(accuracy);
        }

        // 计算平均值
        double sum = accumulate(accuracies.begin(), accuracies.end(), 0.0);
        double average = sum / TEST_TIMES;

        // 写入结果
        resultFile << row << ","
            << fixed << setprecision(2) << x << ","
            << accuracies[0] << "," << accuracies[1] << ","
            << accuracies[2] << "," << accuracies[3] << ","
            << accuracies[4] << "," << average << "\n";

        // 输出进度
        cout << "Progress: " << row << "/" << TOTAL_ROWS
            << " (" << (row * 100.0 / TOTAL_ROWS) << "%)\n";
    }

    resultFile.close();
    cout << "\n自动化测试完成，结果已保存至 test_results.csv\n";
    return 0;

















    // runAutomatedTests();













   /*
    splitDataset("train.csv", 150, "train_over.csv", "test_over.csv");
    vector<string> attributes = 
    {
        "英雄自身偏向", "本方输出属性", "本方防御属性",
        "敌方输出属性", "敌方防御属性"
    };
    vector<bool> usedAttributes(5, false);

    auto trainDataset = loadCSV("train_over.csv");
    shared_ptr<TreeNode> tree = buildDecisionTree(trainDataset, attributes, usedAttributes, 0);


    auto testDataset = loadCSV("test_over.csv");

    double accuracy = calculateAccuracy(testDataset, tree, attributes, 0);

    // cout << fixed << setprecision(2);

    cout << "模型准确率: " << accuracy << "%" << endl;

    // 将预测结果写入文件
    writePredictionsToCSV("test_over.csv", tree, attributes);
    */


     // StatisticalTableOfDifferentConfidenceLevels.csv





    
}