// Problem found at https://www.hackerrank.com/challenges/matrix-rotation-algo/problem

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<int> get_layer(vector<vector<int>> &, int);
void set_rotated_layer(vector<vector<int>> &, vector<int> &, size_t, int);


void matrixRotation(vector<vector<int>> matrix, int r) {
    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();
    const size_t layer_count = min(rows, cols)/2;
    for (size_t layer_idx = 0; layer_idx < layer_count; ++layer_idx) {
        const size_t layer_size = 2 * (rows + cols - 4 * layer_idx - 2);  // Don't really need this, but could be useful if a direct mapping between (row, col, layer_idx) and index_in_flattened_layer is found
        const int cur_layer_r = r % layer_size;
        vector<int> flat_layer = get_layer(matrix, layer_idx);
        set_rotated_layer(matrix, flat_layer, layer_idx, cur_layer_r);
    }
    
    for (vector<int> &row : matrix) {
        for (int el : row) {
            cout << el << " ";
        }
        cout << endl;
    }

}

// Go through each side of each layer one after another. First top -> , then right col down, then bottom row <-, and last left column up
vector<int> get_layer(vector<vector<int>> &matrix, int layer_idx) {
    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();
    vector<int> layer;

    for (size_t top_row_col_idx = layer_idx; top_row_col_idx < (cols - layer_idx); ++top_row_col_idx) {
        layer.push_back(matrix[layer_idx][top_row_col_idx]);
    }
    
    for (size_t last_col_row_idx = 1 + layer_idx; last_col_row_idx < (rows - layer_idx); ++last_col_row_idx) {
        layer.push_back(matrix[last_col_row_idx][cols - layer_idx - 1]);
    }
    
    for (size_t bottom_row_col_idx = cols - 2 - layer_idx; bottom_row_col_idx >= 0 + layer_idx; --bottom_row_col_idx) {
        layer.push_back(matrix[rows-1-layer_idx][bottom_row_col_idx]);
        if (bottom_row_col_idx == 0) { // necessary, because otherwise the (unsigned) size_t would go to very high positive values, infinite loop
            break;
        }
    }
    
    for (size_t left_col_row_idx = rows - 2 - layer_idx; left_col_row_idx > 0 + layer_idx; --left_col_row_idx) {
        layer.push_back(matrix[left_col_row_idx][layer_idx]);
    }
    return layer;    
}


void set_rotated_layer(vector<vector<int>> &matrix, vector<int> &layer, size_t layer_idx, int rot) {
    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();
    const size_t layer_size = layer.size();
    size_t idx = rot;
    
    for (size_t top_row_col_idx = layer_idx; top_row_col_idx < (cols - layer_idx); ++top_row_col_idx) {
        matrix[layer_idx][top_row_col_idx] = layer[idx];
        idx = (idx + 1) % layer_size;
    }
    
    for (size_t last_col_row_idx = 1 + layer_idx; last_col_row_idx < (rows - layer_idx); ++last_col_row_idx) {
        matrix[last_col_row_idx][cols - layer_idx - 1] = layer[idx];
        idx = (idx + 1) % layer_size;
    }
    
    for (size_t bottom_row_col_idx = cols - 2 - layer_idx; bottom_row_col_idx >= 0 + layer_idx; --bottom_row_col_idx) {
        matrix[rows-1-layer_idx][bottom_row_col_idx] = layer[idx];
        idx = (idx + 1) % layer_size;
        if (bottom_row_col_idx == 0) {
            break;
        }
    }
    
    for (size_t left_col_row_idx = rows - 2 - layer_idx; left_col_row_idx > 0 + layer_idx; --left_col_row_idx) {
        matrix[left_col_row_idx][layer_idx] = layer[idx];
        idx = (idx + 1) % layer_size;
    }
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
